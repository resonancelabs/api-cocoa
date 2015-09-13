//
//  RLClient.m
//  akin
//
//  Created by Ben Sigelman on 2/21/15.
//  Copyright (c) 2015 Resonance Labs, Inc. All rights reserved.
//

#import "RLClient.h"

#import "RLClockState.h"
#import "TBinaryProtocol.h"
#import "THTTPClient.h"
#import "TSocketClient.h"
#import "TTransportException.h"

#import <stdlib.h>  // arc4random_uniform()

static NSString* kDefaultEndUserIdKey = @"end_user_id";
static const int kFlushIntervalSeconds = 30;
static const int kMaxBufferedSpans = 5000;
static const int kMaxBufferedLogs = 10000;

static NSString* _guidGenerator()
{
    return [NSString stringWithFormat:@"%x%x", arc4random(), arc4random()];
}

@interface RLActiveSpan()

@property (nonatomic, copy) NSString* spanName;
@property (nonatomic, weak) RLClient* client;

@end

// TODO: should put this somewhere else.
@interface NSDate(RLActiveSpan)
- (int64_t) toMicros;
@end

@implementation NSDate(RLActiveSpan)
- (int64_t) toMicros
{
    return (int64_t)([self timeIntervalSince1970] * USEC_PER_SEC);
}
@end

@implementation RLClient {
    NSDate* m_startTime;
    NSString* m_accessToken;
    NSString* m_runtimeGuid;
    RLRuntime* m_runtimeInfo;
    RLClockState* m_clockState;

    NSString* m_serviceUrl;
    RLReportingServiceClient* m_serviceStub;
    bool m_enabled;
    float m_refreshStubDelaySecs;  // if kFirstRefreshDelay, we've never tried to refresh.
    NSMutableArray* m_pendingSpanRecords;
    NSMutableArray* m_pendingLogRecords;
    dispatch_queue_t m_queue;
    dispatch_source_t m_flushTimer;
}

static RLClient* s_sharedInstance = nil;
static float kFirstRefreshDelay = 0;

- (instancetype) initWithServiceHostport:(NSString*)hostport token:(NSString*)accessToken groupName:(NSString*)groupName
{
    if (self = [super init]) {
        self.endUserKeyName = kDefaultEndUserIdKey;
        self->m_serviceUrl = [NSString stringWithFormat:@"https://%@/_rpc/v1/reports/binary", hostport];
        self->m_accessToken = accessToken;
        self->m_runtimeGuid = _guidGenerator();
        self->m_startTime = [NSDate date];
        NSMutableArray* runtimeAttrs = @[[[RLKeyValue alloc] initWithKey:@"cruntime_platform" Value:@"cocoa"],
                                         [[RLKeyValue alloc] initWithKey:@"ios_version" Value:[[UIDevice currentDevice] systemVersion]],
                                         [[RLKeyValue alloc] initWithKey:@"device_model" Value:[[UIDevice currentDevice] model]]].mutableCopy;
        self->m_runtimeInfo = [[RLRuntime alloc]
                               initWithGuid:self->m_runtimeGuid
                               start_micros:[m_startTime toMicros]
                               group_name:groupName
                               attrs:runtimeAttrs];

        self->m_pendingSpanRecords = [NSMutableArray array];
        self->m_pendingLogRecords = [NSMutableArray array];
        self->m_queue = dispatch_queue_create("com.resonancelabs.signal.rpc", DISPATCH_QUEUE_SERIAL);
        self->m_flushTimer = nil;
        self->m_refreshStubDelaySecs = kFirstRefreshDelay;
        self->m_enabled = true;  // depends on the remote kill-switch.
        self->m_clockState = [[RLClockState alloc] initWithRLClient:self];
        [self _refreshStub];
    }
    return self;
}

+ (instancetype) sharedInstanceWithServiceHostport:(NSString*)hostport token:(NSString*)accessToken groupName:(NSString*)groupName
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        s_sharedInstance = [[super alloc] initWithServiceHostport:hostport token:accessToken groupName:groupName];
    });
    return s_sharedInstance;
}

+ (instancetype) sharedInstanceWithServiceHostport:(NSString*)hostport token:(NSString*)accessToken
{
    NSString* runtimeGroupName = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString*)kCFBundleNameKey];
    return [RLClient sharedInstanceWithServiceHostport:hostport token:accessToken groupName:runtimeGroupName];
}

+ (RLClient*) sharedInstance
{
    if (s_sharedInstance == nil) {
        NSLog(@"Must call sharedInstanceWithToken: before calling sharedInstance:!");
    }
    return s_sharedInstance;
}

- (NSString*) serviceUrl {
    return m_serviceUrl;
}

- (NSString*) runtimeGuid {
    return m_runtimeGuid;
}

- (bool) enabled {
    return m_enabled;
}

- (void) appendSpanRecord:(RLSpanRecord*)sr {
    if (!m_enabled) {
        // Drop sr.
        return;
    }

    @synchronized(self) {
        if (m_pendingSpanRecords.count < kMaxBufferedSpans) {
            [m_pendingSpanRecords addObject:sr];
        }
    }
}

- (void) appendLogRecord:(RLLogRecord*)lr {
    if (!m_enabled) {
        // Drop lr.
        return;
    }

    @synchronized(self) {
        if (m_pendingLogRecords.count < kMaxBufferedLogs) {
            [m_pendingLogRecords addObject:lr];
        }
    }
}

static NSString* jsonStringForDictionary(NSDictionary* dict) {
    if (dict == nil) {
        return nil;
    }
    NSError* error;
    NSData* jsonData;
    @try {
        jsonData = [NSJSONSerialization dataWithJSONObject:dict options:0 error:&error];
    } @catch (NSException* e) {
        return @"<invalid dict input for json conversation>";
    }
    
    if (!jsonData) {
        NSLog(@"Could not encode JSON for dict: %@", error);
        return nil;
    } else {
        return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
}

- (void) setEndUserId:(NSString*)endUserId {
    if (endUserId.length) {
        _endUserId = endUserId;
    } else {
        _endUserId = @"UNKNOWN";  // guard against bad callers
    }
}

- (RLActiveSpan*) beginSpan:(NSString*)spanName
{
    if (!m_enabled) {
        return nil;
    }

    RLActiveSpan* activeSpan = [RLActiveSpan new];
    activeSpan.spanName = spanName;
    activeSpan.client = self;
    [activeSpan addJoinId:self.endUserKeyName value:self.endUserId];
    return activeSpan;
}

- (void) log:(NSString*)message
{
    [self log:message payload:nil];
}
- (void) log:(NSString*)message payload:(NSDictionary*)payload
{
    [self log:message stableName:nil payload:payload spanGuid:nil];
}
- (void) logStable:(NSString*)stableName payload:(NSDictionary*)payload
{
    [self log:nil stableName:stableName payload:payload spanGuid:nil];
}
- (void) log:(NSString*)message stableName:(NSString*)stableName payload:(NSDictionary*)payload spanGuid:(NSString*)spanGuid
{
    if (!m_enabled) {
        // Noop.
        return;
    }

    RLLogRecord* logRecord = [[RLLogRecord alloc]
                              initWithTimestamp_micros:[[NSDate date] toMicros]
                              runtime_guid:self.runtimeGuid
                              span_guid:spanGuid
                              stable_name:stableName
                              message:message
                              level:nil
                              thread_id:(int64_t)[NSThread currentThread]
                              filename:nil  // TODO: support this
                              line_number:0
                              stack_frames:nil
                              payload_json:jsonStringForDictionary(payload)
                              error_flag:false];
    [logRecord unsetLine_number]; // TODO: support this
    [self appendLogRecord:logRecord];
}

- (void) _refreshStub
{
    if (!m_enabled) {
        // Noop.
        return;
    }

    if (m_serviceUrl == nil || m_serviceUrl.length == 0) {
        // Better safe than sorry (we don't think this should ever actually happen).
        return;
    }
    __weak __typeof__(self) weakSelf = self;
    void (^refreshBlock)() = ^{
        __typeof__(self) strongSelf = weakSelf;
        if (strongSelf) {
            if (strongSelf->m_flushTimer) {
                dispatch_source_cancel(strongSelf->m_flushTimer);
            }
            if (strongSelf->m_refreshStubDelaySecs == kFirstRefreshDelay) {
                // Don't actually sleep the first time we try to initiate m_serviceStub.
                strongSelf->m_refreshStubDelaySecs = 5;
            } else {
                // Exponential backoff with a 30-minute max.
                strongSelf->m_refreshStubDelaySecs = MIN(60*30, strongSelf->m_refreshStubDelaySecs * 1.5);
                NSLog(@"RLClient backing off for %@ seconds", @(strongSelf->m_refreshStubDelaySecs));
                [NSThread sleepForTimeInterval:strongSelf->m_refreshStubDelaySecs];
            }
            
            NSObject<TTransport>* transport = [[THTTPClient alloc] initWithURL:[NSURL URLWithString:strongSelf->m_serviceUrl] userAgent:nil timeout:10];
            TBinaryProtocol* protocol = [[TBinaryProtocol alloc] initWithTransport:transport strictRead:YES strictWrite:YES];
            strongSelf->m_serviceStub = [[RLReportingServiceClient alloc] initWithProtocol:protocol];
            if (strongSelf->m_serviceStub) {
                // Restart the backoff.
                strongSelf->m_refreshStubDelaySecs = 5;

                // Initialize and "resume" (i.e., "start") the m_flushTimer.
                strongSelf->m_flushTimer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, strongSelf->m_queue);
                if (strongSelf->m_flushTimer) {
                    dispatch_source_set_timer(strongSelf->m_flushTimer, DISPATCH_TIME_NOW, kFlushIntervalSeconds * NSEC_PER_SEC, NSEC_PER_SEC);
                    dispatch_source_set_event_handler(strongSelf->m_flushTimer, ^{
                        __typeof__(self) reallyStrongSelf = weakSelf;
                        if (reallyStrongSelf) {
                            [reallyStrongSelf flushToService];
                        }
                    });
                    dispatch_resume(strongSelf->m_flushTimer);
                }
            }
        }
    };
    dispatch_async(m_queue, refreshBlock);
}

static void correctTimestamps(NSArray* logRecords, NSArray* spanRecords, micros_t offset) {
    for (int i = 0; i < logRecords.count; ++i) {
        RLLogRecord* curLog = logRecords[i];
        curLog.timestamp_micros += offset;
    }
    for (int i = 0; i < spanRecords.count; ++i) {
        RLSpanRecord* curSpan = spanRecords[i];
        curSpan.oldest_micros += offset;
        curSpan.youngest_micros += offset;
    }
}

- (void) flushToService
{
    micros_t tsCorrection = m_clockState.offsetMicros;
    if (tsCorrection != 0) {
        [self logStable:@"cr/time_correction_state" payload:@{@"offset_micros": @(tsCorrection)}];
    }

    NSMutableArray* spansToFlush;
    NSMutableArray* logsToFlush;
    @synchronized(self) {
        spansToFlush = m_pendingSpanRecords;
        logsToFlush = m_pendingLogRecords;
        m_pendingSpanRecords = [NSMutableArray array];
        m_pendingLogRecords = [NSMutableArray array];
    }

    if (!m_enabled) {
        // Deliberately do this after clearing the pending records (just in case).
        return;
    }
    
    if (spansToFlush.count + logsToFlush.count == 0) {
        // Nothing to do.
        return;
    }

    void (^revertBlock)() = ^{
        @synchronized(self) {
            // We apparently failed to flush these records, so re-enqueue them
            // at the heads of m_pending*Records. This is a little sketchy
            // since we don't actually *know* if the peer service saw them or
            // not, but this is the more conservative path as far as data loss
            // is concerned.
            //
            // Don't forget to un-correct the timestamps.
            correctTimestamps(logsToFlush, spansToFlush, -tsCorrection);
            [m_pendingSpanRecords insertObjects:spansToFlush atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, spansToFlush.count)]];
            [m_pendingLogRecords insertObjects:logsToFlush atIndexes:[NSIndexSet indexSetWithIndexesInRange:NSMakeRange(0, logsToFlush.count)]];
        }
    };

    // We really want this flush to go through, even if the app enters the
    // background and iOS wants to move on with its life.
    UIBackgroundTaskIdentifier bgTaskId = [[UIApplication sharedApplication] beginBackgroundTaskWithName:@"reslabs_flush" expirationHandler:revertBlock];
    if (bgTaskId == UIBackgroundTaskInvalid) {
        NSLog(@"unable to enter the background, so skipping flush");
        revertBlock();
        return;
    }

    // Correct the timestamps just before building the RLReportRequest.
    correctTimestamps(logsToFlush, spansToFlush, tsCorrection);
    RLAuth* auth = [[RLAuth alloc] initWithAccess_token:m_accessToken];
    RLReportRequest* req = [[RLReportRequest alloc]
                            initWithRuntime:m_runtimeInfo
                            span_records:spansToFlush
                            log_records:logsToFlush
                            timestamp_offset_micros:tsCorrection
                            discarded_log_record_samples:nil];

    __weak __typeof__(self) weakSelf = self;
    void (^rpcBlock)() = ^{
        __typeof__(self) strongSelf = weakSelf;
        if (strongSelf) {
            void(^dropAndRecover)() = ^void() {
                // Try to start from scratch.
                //
                // Don't-call revertBlock() to avoid a client feedback loop.
                [strongSelf _refreshStub];
            };

            RLReportResponse* response = nil;
            @try {
                micros_t originMicros = [RLClockState nowMicros];
                response = [strongSelf->m_serviceStub Report:auth request:req];
                micros_t destinationMicros = [RLClockState nowMicros];
                for (RLCommand* command in response.commands) {
                    if (command.disable) {
                        NSLog(@"NOTE: Signal RLClient disabled by remote peer.");
                        strongSelf->m_enabled = false;
                    }
                }
                if (response.timing.receive_microsIsSet && response.timing.transmit_microsIsSet) {
                    // Update our local NTP-lite clock state with the latest measurements.
                    [m_clockState addSampleWithOriginMicros:originMicros
                                              receiveMicros:response.timing.receive_micros
                                             transmitMicros:response.timing.transmit_micros
                                          destinationMicros:destinationMicros];
                }
            }
            @catch (TApplicationException* e)
            {
                NSLog(@"RPC exception %@: %@", [e name], [e description]);
                dropAndRecover();
            }
            @catch (TException* e)
            {
                // TTransportException, or unknown type of exception: drop data since "first, [we want to] do no harm."
                NSLog(@"Unknown Thrift error %@: %@", [e name], [e description]);
                dropAndRecover();
            }
            @catch (NSException* e)
            {
                // We really don't like catching NSException, but unfortunately
                // Thrift is such a piece of junk that we will sleep better
                // here if we do. For instance, there are NSRangeExceptions
                // thrown by the THttpClient when the server peer returns 0
                // bytes (which is an error, of course, but that doesn't mean
                // the local process should crash!).
                NSLog(@"Unexpected bad things happened %@: %@", [e name], [e description]);
                dropAndRecover();
            }
        }
        [[UIApplication sharedApplication] endBackgroundTask:bgTaskId];
    };

    dispatch_async(m_queue, rpcBlock);
}

@end


#pragma mark - RLActiveSpan

@implementation RLActiveSpan {
    NSString* m_spanGuid;
    NSDate* m_startTime;
    NSDate* m_endTime;
    NSMutableArray* m_joinIds;
}

- (instancetype) init
{
    if (self = [super init]) {
        self->m_spanGuid = _guidGenerator();
        self->m_startTime = [NSDate date];
        self->m_endTime = nil;
        self->m_joinIds = [NSMutableArray array];
    }
    return self;
}

- (void) dealloc
{
    [self finish];  // in case we neglected to do so already.
}

- (void) addJoinId:(NSString *)key value:(NSString *)value {
    [m_joinIds addObject:[[RLTraceJoinId alloc] initWithTraceKey:key Value:value]];
}

- (void) finish
{
    if (m_endTime == nil) {
        m_endTime = [NSDate date];
        
        [self.client appendSpanRecord:[[RLSpanRecord alloc]
                                       initWithSpan_guid:m_spanGuid
                                       runtime_guid:self.client.runtimeGuid
                                       span_name:self.spanName
                                       join_ids:m_joinIds
                                       oldest_micros:[m_startTime toMicros]
                                       youngest_micros:[m_endTime toMicros]
                                       attributes:nil
                                       deprecated_error_text:nil]];
    }
}

- (void) setError:(NSString*)errorText
{
    if (!self.client.enabled) {
        // Noop.
        return;
    }

    RLLogRecord* logRecord = [[RLLogRecord alloc]
                              initWithTimestamp_micros:[[NSDate date] toMicros]
                              runtime_guid:self.client.runtimeGuid
                              span_guid:m_spanGuid
                              stable_name:nil
                              message:errorText
                              level:@"E"
                              thread_id:(int64_t)[NSThread currentThread]
                              filename:nil  // TODO: support this
                              line_number:0
                              stack_frames:nil
                              payload_json:nil
                              error_flag:true];

    [logRecord unsetLine_number]; // TODO: support this
    [self.client appendLogRecord:logRecord];
}

- (void) log:(NSString*)message
{
    [self.client log:message stableName:nil payload:nil spanGuid:m_spanGuid];
}

- (void) log:(NSString*)message payload:(NSDictionary*)payload
{
    [self.client log:message stableName:nil payload:payload spanGuid:m_spanGuid];
}

@end
