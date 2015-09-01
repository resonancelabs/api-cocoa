/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */

#import <Foundation/Foundation.h>

#import "TProtocol.h"
#import "TApplicationException.h"
#import "TProtocolException.h"
#import "TProtocolUtil.h"
#import "TProcessor.h"
#import "TObjective-C.h"
#import "TBase.h"


@interface RLKeyValue : NSObject <TBase, NSCoding> {
  NSString * __Key;
  NSString * __Value;

  BOOL __Key_isset;
  BOOL __Value_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=key, setter=setKey:) NSString * Key;
- (void) unsetKey;
@property (nonatomic, retain, getter=value, setter=setValue:) NSString * Value;
- (void) unsetValue;
#endif

- (id) init;
- (id) initWithKey: (NSString *) Key Value: (NSString *) Value;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSString *) key;
- (void) setKey: (NSString *) Key;
#endif
- (BOOL) KeyIsSet;

#if !__has_feature(objc_arc)
- (NSString *) value;
- (void) setValue: (NSString *) Value;
#endif
- (BOOL) ValueIsSet;

@end

@interface RLRuntime : NSObject <TBase, NSCoding> {
  NSString * __guid;
  int64_t __start_micros;
  NSString * __group_name;
  NSMutableArray * __attrs;

  BOOL __guid_isset;
  BOOL __start_micros_isset;
  BOOL __group_name_isset;
  BOOL __attrs_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=guid, setter=setGuid:) NSString * guid;
- (void) unsetGuid;
@property (nonatomic, getter=start_micros, setter=setStart_micros:) int64_t start_micros;
- (void) unsetStart_micros;
@property (nonatomic, retain, getter=group_name, setter=setGroup_name:) NSString * group_name;
- (void) unsetGroup_name;
@property (nonatomic, retain, getter=attrs, setter=setAttrs:) NSMutableArray * attrs;
- (void) unsetAttrs;
#endif

- (id) init;
- (id) initWithGuid: (NSString *) guid start_micros: (int64_t) start_micros group_name: (NSString *) group_name attrs: (NSMutableArray *) attrs;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSString *) guid;
- (void) setGuid: (NSString *) guid;
#endif
- (BOOL) guidIsSet;

#if !__has_feature(objc_arc)
- (int64_t) start_micros;
- (void) setStart_micros: (int64_t) start_micros;
#endif
- (BOOL) start_microsIsSet;

#if !__has_feature(objc_arc)
- (NSString *) group_name;
- (void) setGroup_name: (NSString *) group_name;
#endif
- (BOOL) group_nameIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) attrs;
- (void) setAttrs: (NSMutableArray *) attrs;
#endif
- (BOOL) attrsIsSet;

@end

@interface RLLogRecord : NSObject <TBase, NSCoding> {
  int64_t __timestamp_micros;
  NSString * __runtime_guid;
  NSString * __span_guid;
  NSString * __stable_name;
  NSString * __message;
  NSString * __level;
  int64_t __thread_id;
  NSString * __filename;
  int64_t __line_number;
  NSMutableArray * __stack_frames;
  NSString * __payload_json;
  BOOL __error_flag;

  BOOL __timestamp_micros_isset;
  BOOL __runtime_guid_isset;
  BOOL __span_guid_isset;
  BOOL __stable_name_isset;
  BOOL __message_isset;
  BOOL __level_isset;
  BOOL __thread_id_isset;
  BOOL __filename_isset;
  BOOL __line_number_isset;
  BOOL __stack_frames_isset;
  BOOL __payload_json_isset;
  BOOL __error_flag_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, getter=timestamp_micros, setter=setTimestamp_micros:) int64_t timestamp_micros;
- (void) unsetTimestamp_micros;
@property (nonatomic, retain, getter=runtime_guid, setter=setRuntime_guid:) NSString * runtime_guid;
- (void) unsetRuntime_guid;
@property (nonatomic, retain, getter=span_guid, setter=setSpan_guid:) NSString * span_guid;
- (void) unsetSpan_guid;
@property (nonatomic, retain, getter=stable_name, setter=setStable_name:) NSString * stable_name;
- (void) unsetStable_name;
@property (nonatomic, retain, getter=message, setter=setMessage:) NSString * message;
- (void) unsetMessage;
@property (nonatomic, retain, getter=level, setter=setLevel:) NSString * level;
- (void) unsetLevel;
@property (nonatomic, getter=thread_id, setter=setThread_id:) int64_t thread_id;
- (void) unsetThread_id;
@property (nonatomic, retain, getter=filename, setter=setFilename:) NSString * filename;
- (void) unsetFilename;
@property (nonatomic, getter=line_number, setter=setLine_number:) int64_t line_number;
- (void) unsetLine_number;
@property (nonatomic, retain, getter=stack_frames, setter=setStack_frames:) NSMutableArray * stack_frames;
- (void) unsetStack_frames;
@property (nonatomic, retain, getter=payload_json, setter=setPayload_json:) NSString * payload_json;
- (void) unsetPayload_json;
@property (nonatomic, getter=error_flag, setter=setError_flag:) BOOL error_flag;
- (void) unsetError_flag;
#endif

- (id) init;
- (id) initWithTimestamp_micros: (int64_t) timestamp_micros runtime_guid: (NSString *) runtime_guid span_guid: (NSString *) span_guid stable_name: (NSString *) stable_name message: (NSString *) message level: (NSString *) level thread_id: (int64_t) thread_id filename: (NSString *) filename line_number: (int64_t) line_number stack_frames: (NSMutableArray *) stack_frames payload_json: (NSString *) payload_json error_flag: (BOOL) error_flag;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (int64_t) timestamp_micros;
- (void) setTimestamp_micros: (int64_t) timestamp_micros;
#endif
- (BOOL) timestamp_microsIsSet;

#if !__has_feature(objc_arc)
- (NSString *) runtime_guid;
- (void) setRuntime_guid: (NSString *) runtime_guid;
#endif
- (BOOL) runtime_guidIsSet;

#if !__has_feature(objc_arc)
- (NSString *) span_guid;
- (void) setSpan_guid: (NSString *) span_guid;
#endif
- (BOOL) span_guidIsSet;

#if !__has_feature(objc_arc)
- (NSString *) stable_name;
- (void) setStable_name: (NSString *) stable_name;
#endif
- (BOOL) stable_nameIsSet;

#if !__has_feature(objc_arc)
- (NSString *) message;
- (void) setMessage: (NSString *) message;
#endif
- (BOOL) messageIsSet;

#if !__has_feature(objc_arc)
- (NSString *) level;
- (void) setLevel: (NSString *) level;
#endif
- (BOOL) levelIsSet;

#if !__has_feature(objc_arc)
- (int64_t) thread_id;
- (void) setThread_id: (int64_t) thread_id;
#endif
- (BOOL) thread_idIsSet;

#if !__has_feature(objc_arc)
- (NSString *) filename;
- (void) setFilename: (NSString *) filename;
#endif
- (BOOL) filenameIsSet;

#if !__has_feature(objc_arc)
- (int64_t) line_number;
- (void) setLine_number: (int64_t) line_number;
#endif
- (BOOL) line_numberIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) stack_frames;
- (void) setStack_frames: (NSMutableArray *) stack_frames;
#endif
- (BOOL) stack_framesIsSet;

#if !__has_feature(objc_arc)
- (NSString *) payload_json;
- (void) setPayload_json: (NSString *) payload_json;
#endif
- (BOOL) payload_jsonIsSet;

#if !__has_feature(objc_arc)
- (BOOL) error_flag;
- (void) setError_flag: (BOOL) error_flag;
#endif
- (BOOL) error_flagIsSet;

@end

@interface RLTraceJoinId : NSObject <TBase, NSCoding> {
  NSString * __TraceKey;
  NSString * __Value;

  BOOL __TraceKey_isset;
  BOOL __Value_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=traceKey, setter=setTraceKey:) NSString * TraceKey;
- (void) unsetTraceKey;
@property (nonatomic, retain, getter=value, setter=setValue:) NSString * Value;
- (void) unsetValue;
#endif

- (id) init;
- (id) initWithTraceKey: (NSString *) TraceKey Value: (NSString *) Value;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSString *) traceKey;
- (void) setTraceKey: (NSString *) TraceKey;
#endif
- (BOOL) TraceKeyIsSet;

#if !__has_feature(objc_arc)
- (NSString *) value;
- (void) setValue: (NSString *) Value;
#endif
- (BOOL) ValueIsSet;

@end

@interface RLSpanRecord : NSObject <TBase, NSCoding> {
  NSString * __span_guid;
  NSString * __runtime_guid;
  NSString * __span_name;
  NSMutableArray * __join_ids;
  int64_t __oldest_micros;
  int64_t __youngest_micros;
  NSMutableArray * __attributes;
  NSString * __deprecated_error_text;

  BOOL __span_guid_isset;
  BOOL __runtime_guid_isset;
  BOOL __span_name_isset;
  BOOL __join_ids_isset;
  BOOL __oldest_micros_isset;
  BOOL __youngest_micros_isset;
  BOOL __attributes_isset;
  BOOL __deprecated_error_text_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=span_guid, setter=setSpan_guid:) NSString * span_guid;
- (void) unsetSpan_guid;
@property (nonatomic, retain, getter=runtime_guid, setter=setRuntime_guid:) NSString * runtime_guid;
- (void) unsetRuntime_guid;
@property (nonatomic, retain, getter=span_name, setter=setSpan_name:) NSString * span_name;
- (void) unsetSpan_name;
@property (nonatomic, retain, getter=join_ids, setter=setJoin_ids:) NSMutableArray * join_ids;
- (void) unsetJoin_ids;
@property (nonatomic, getter=oldest_micros, setter=setOldest_micros:) int64_t oldest_micros;
- (void) unsetOldest_micros;
@property (nonatomic, getter=youngest_micros, setter=setYoungest_micros:) int64_t youngest_micros;
- (void) unsetYoungest_micros;
@property (nonatomic, retain, getter=attributes, setter=setAttributes:) NSMutableArray * attributes;
- (void) unsetAttributes;
@property (nonatomic, retain, getter=deprecated_error_text, setter=setDeprecated_error_text:) NSString * deprecated_error_text;
- (void) unsetDeprecated_error_text;
#endif

- (id) init;
- (id) initWithSpan_guid: (NSString *) span_guid runtime_guid: (NSString *) runtime_guid span_name: (NSString *) span_name join_ids: (NSMutableArray *) join_ids oldest_micros: (int64_t) oldest_micros youngest_micros: (int64_t) youngest_micros attributes: (NSMutableArray *) attributes deprecated_error_text: (NSString *) deprecated_error_text;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSString *) span_guid;
- (void) setSpan_guid: (NSString *) span_guid;
#endif
- (BOOL) span_guidIsSet;

#if !__has_feature(objc_arc)
- (NSString *) runtime_guid;
- (void) setRuntime_guid: (NSString *) runtime_guid;
#endif
- (BOOL) runtime_guidIsSet;

#if !__has_feature(objc_arc)
- (NSString *) span_name;
- (void) setSpan_name: (NSString *) span_name;
#endif
- (BOOL) span_nameIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) join_ids;
- (void) setJoin_ids: (NSMutableArray *) join_ids;
#endif
- (BOOL) join_idsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) oldest_micros;
- (void) setOldest_micros: (int64_t) oldest_micros;
#endif
- (BOOL) oldest_microsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) youngest_micros;
- (void) setYoungest_micros: (int64_t) youngest_micros;
#endif
- (BOOL) youngest_microsIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) attributes;
- (void) setAttributes: (NSMutableArray *) attributes;
#endif
- (BOOL) attributesIsSet;

#if !__has_feature(objc_arc)
- (NSString *) deprecated_error_text;
- (void) setDeprecated_error_text: (NSString *) deprecated_error_text;
#endif
- (BOOL) deprecated_error_textIsSet;

@end

@interface RLAuth : NSObject <TBase, NSCoding> {
  NSString * __access_token;

  BOOL __access_token_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=access_token, setter=setAccess_token:) NSString * access_token;
- (void) unsetAccess_token;
#endif

- (id) init;
- (id) initWithAccess_token: (NSString *) access_token;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSString *) access_token;
- (void) setAccess_token: (NSString *) access_token;
#endif
- (BOOL) access_tokenIsSet;

@end

@interface RLTiming : NSObject <TBase, NSCoding> {
  int64_t __receive_micros;
  int64_t __transmit_micros;

  BOOL __receive_micros_isset;
  BOOL __transmit_micros_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, getter=receive_micros, setter=setReceive_micros:) int64_t receive_micros;
- (void) unsetReceive_micros;
@property (nonatomic, getter=transmit_micros, setter=setTransmit_micros:) int64_t transmit_micros;
- (void) unsetTransmit_micros;
#endif

- (id) init;
- (id) initWithReceive_micros: (int64_t) receive_micros transmit_micros: (int64_t) transmit_micros;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (int64_t) receive_micros;
- (void) setReceive_micros: (int64_t) receive_micros;
#endif
- (BOOL) receive_microsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) transmit_micros;
- (void) setTransmit_micros: (int64_t) transmit_micros;
#endif
- (BOOL) transmit_microsIsSet;

@end

@interface RLSampleCount : NSObject <TBase, NSCoding> {
  int64_t __oldest_micros;
  int64_t __youngest_micros;
  int64_t __count;

  BOOL __oldest_micros_isset;
  BOOL __youngest_micros_isset;
  BOOL __count_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, getter=oldest_micros, setter=setOldest_micros:) int64_t oldest_micros;
- (void) unsetOldest_micros;
@property (nonatomic, getter=youngest_micros, setter=setYoungest_micros:) int64_t youngest_micros;
- (void) unsetYoungest_micros;
@property (nonatomic, getter=count, setter=setCount:) int64_t count;
- (void) unsetCount;
#endif

- (id) init;
- (id) initWithOldest_micros: (int64_t) oldest_micros youngest_micros: (int64_t) youngest_micros count: (int64_t) count;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (int64_t) oldest_micros;
- (void) setOldest_micros: (int64_t) oldest_micros;
#endif
- (BOOL) oldest_microsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) youngest_micros;
- (void) setYoungest_micros: (int64_t) youngest_micros;
#endif
- (BOOL) youngest_microsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) count;
- (void) setCount: (int64_t) count;
#endif
- (BOOL) countIsSet;

@end

@interface RLReportRequest : NSObject <TBase, NSCoding> {
  RLRuntime * __runtime;
  NSMutableArray * __span_records;
  NSMutableArray * __log_records;
  int64_t __timestamp_offset_micros;
  NSMutableArray * __discarded_log_record_samples;

  BOOL __runtime_isset;
  BOOL __span_records_isset;
  BOOL __log_records_isset;
  BOOL __timestamp_offset_micros_isset;
  BOOL __discarded_log_record_samples_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=runtime, setter=setRuntime:) RLRuntime * runtime;
- (void) unsetRuntime;
@property (nonatomic, retain, getter=span_records, setter=setSpan_records:) NSMutableArray * span_records;
- (void) unsetSpan_records;
@property (nonatomic, retain, getter=log_records, setter=setLog_records:) NSMutableArray * log_records;
- (void) unsetLog_records;
@property (nonatomic, getter=timestamp_offset_micros, setter=setTimestamp_offset_micros:) int64_t timestamp_offset_micros;
- (void) unsetTimestamp_offset_micros;
@property (nonatomic, retain, getter=discarded_log_record_samples, setter=setDiscarded_log_record_samples:) NSMutableArray * discarded_log_record_samples;
- (void) unsetDiscarded_log_record_samples;
#endif

- (id) init;
- (id) initWithRuntime: (RLRuntime *) runtime span_records: (NSMutableArray *) span_records log_records: (NSMutableArray *) log_records timestamp_offset_micros: (int64_t) timestamp_offset_micros discarded_log_record_samples: (NSMutableArray *) discarded_log_record_samples;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (RLRuntime *) runtime;
- (void) setRuntime: (RLRuntime *) runtime;
#endif
- (BOOL) runtimeIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) span_records;
- (void) setSpan_records: (NSMutableArray *) span_records;
#endif
- (BOOL) span_recordsIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) log_records;
- (void) setLog_records: (NSMutableArray *) log_records;
#endif
- (BOOL) log_recordsIsSet;

#if !__has_feature(objc_arc)
- (int64_t) timestamp_offset_micros;
- (void) setTimestamp_offset_micros: (int64_t) timestamp_offset_micros;
#endif
- (BOOL) timestamp_offset_microsIsSet;

#if !__has_feature(objc_arc)
- (NSMutableArray *) discarded_log_record_samples;
- (void) setDiscarded_log_record_samples: (NSMutableArray *) discarded_log_record_samples;
#endif
- (BOOL) discarded_log_record_samplesIsSet;

@end

@interface RLCommand : NSObject <TBase, NSCoding> {
  BOOL __disable;

  BOOL __disable_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, getter=disable, setter=setDisable:) BOOL disable;
- (void) unsetDisable;
#endif

- (id) init;
- (id) initWithDisable: (BOOL) disable;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (BOOL) disable;
- (void) setDisable: (BOOL) disable;
#endif
- (BOOL) disableIsSet;

@end

@interface RLReportResponse : NSObject <TBase, NSCoding> {
  NSMutableArray * __commands;
  RLTiming * __timing;

  BOOL __commands_isset;
  BOOL __timing_isset;
}

#if TARGET_OS_IPHONE || (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)
@property (nonatomic, retain, getter=commands, setter=setCommands:) NSMutableArray * commands;
- (void) unsetCommands;
@property (nonatomic, retain, getter=timing, setter=setTiming:) RLTiming * timing;
- (void) unsetTiming;
#endif

- (id) init;
- (id) initWithCommands: (NSMutableArray *) commands timing: (RLTiming *) timing;

- (void) read: (id <TProtocol>) inProtocol;
- (void) write: (id <TProtocol>) outProtocol;

- (void) validate;

#if !__has_feature(objc_arc)
- (NSMutableArray *) commands;
- (void) setCommands: (NSMutableArray *) commands;
#endif
- (BOOL) commandsIsSet;

#if !__has_feature(objc_arc)
- (RLTiming *) timing;
- (void) setTiming: (RLTiming *) timing;
#endif
- (BOOL) timingIsSet;

@end

@protocol RLReportingService <NSObject>
- (RLReportResponse *) Report: (RLAuth *) auth request: (RLReportRequest *) request;  // throws TException
@end

@interface RLReportingServiceClient : NSObject <RLReportingService> {
  id <TProtocol> inProtocol;
  id <TProtocol> outProtocol;
}
- (id) initWithProtocol: (id <TProtocol>) protocol;
- (id) initWithInProtocol: (id <TProtocol>) inProtocol outProtocol: (id <TProtocol>) outProtocol;
@end

@interface RLReportingServiceProcessor : NSObject <TProcessor> {
  id <RLReportingService> mService;
  NSDictionary * mMethodMap;
}
- (id) initWithReportingService: (id <RLReportingService>) service;
- (id<RLReportingService>) service;
@end

@interface RLcroutonConstants : NSObject {
}
@end
