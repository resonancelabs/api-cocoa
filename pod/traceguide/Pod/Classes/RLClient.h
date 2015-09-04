//
//  RLClient.h
//  akin
//
//  Created by Ben Sigelman on 2/21/15.
//  Copyright (c) 2015 Resonance Labs, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "crouton.h"

/// See the golang ActiveSpan interface. Semantics here are [supposed to be] equivalent.
@interface RLActiveSpan : NSObject
- (void) finish;  // (also called automatically by dealloc)
- (void) addJoinId:(NSString*)key value:(NSString*)value;
- (void) setError:(NSString*)errorText;
- (void) log:(NSString*)message;
- (void) log:(NSString*)message payload:(NSDictionary*)payload;
@end

/// The entrypoint to Signal instrumentation for Cocoa.
///
/// Very early in the life of the application, call sharedInstanceWithServiceHostport. From then on, you may just call sharedInstance.
@interface RLClient : NSObject

/// Call this early in the application lifecycle (calls to 'sharedInstance' will return nil beforehand).
///
/// The `groupName` should identify the cocoa client process in the context of the larger distributed system; the default is the bundle name.
///
/// For the pilot, `hostport` should be "api.traceguide.io:9997".
+ (instancetype) sharedInstanceWithServiceHostport:(NSString*)hostport token:(NSString*)accessToken groupName:(NSString*)groupName;

/// See sharedInstanceWithServiceHostport:token:groupName:. This is analagous, but groupName defaults to the bundle name.
+ (instancetype) sharedInstanceWithServiceHostport:(NSString*)hostport token:(NSString*)accessToken;

/// Call this to get the shared instance after initialization.
+ (instancetype) sharedInstance;

/// The remote service URL string (as derived from `sharedInstancWithServiceHostport:token:`).
@property (nonatomic, readonly) NSString* serviceUrl;

/// The runtime guid, which is assigned automatically.
@property (nonatomic, readonly) NSString* runtimeGuid;

/// The key name for the endUserId's JoinId. Defaults to "end_user_id", but may be overridden.
///
/// If you don't know what this is, the default is a fine place to start.
@property (nonatomic, copy) NSString* endUserKeyName;

/// The current end-user's id, which should be consistent with the end-user ids used outside of the mobile app.
@property (nonatomic, copy) NSString* endUserId;

/// Mark the beginning of a new RLActiveSpan.
- (RLActiveSpan*) beginSpan:(NSString*)spanName;

/// A simple logging interface. "payload" must be json-serializable.
- (void) log:(NSString*)message;
- (void) log:(NSString*)message payload:(NSDictionary*)payload;

/// An experimental API that's closer to something like Mixpanel's `track`. The idea
/// is that the `stableName` is, well, stable; it is more of a unique id than a
/// descriptive log message.
- (void) logStable:(NSString*)stableName payload:(NSDictionary*)payload;

/// The fully-specified superset of the other logging calls.
- (void) log:(NSString*)message stableName:(NSString*)stableName payload:(NSDictionary*)payload spanGuid:(NSString*)spanGuid;

/// Explicitly flush to the Signal service (this is called periodically in the background, too).
- (void) flushToService;

@end
