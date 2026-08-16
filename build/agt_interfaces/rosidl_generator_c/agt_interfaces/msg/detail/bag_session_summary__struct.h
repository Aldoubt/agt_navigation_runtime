// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATE_UNKNOWN'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_UNKNOWN = 0
};

/// Constant 'STATE_IDLE'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_IDLE = 1
};

/// Constant 'STATE_RECORDING'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_RECORDING = 2
};

/// Constant 'STATE_PLAYING'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_PLAYING = 3
};

/// Constant 'STATE_COMPLETED'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_COMPLETED = 4
};

/// Constant 'STATE_INTERRUPTED'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_INTERRUPTED = 5
};

/// Constant 'STATE_ERROR'.
enum
{
  agt_interfaces__msg__BagSessionSummary__STATE_ERROR = 6
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'bag_id'
// Member 'experiment_id'
// Member 'profile_id'
// Member 'relative_uri'
// Member 'started_at'
// Member 'updated_at'
// Member 'message'
// Member 'storage_identifier'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/BagSessionSummary in the package agt_interfaces.
/**
  * Manager-owned rosbag or experiment session summary.
 */
typedef struct agt_interfaces__msg__BagSessionSummary
{
  std_msgs__msg__Header header;
  uint8_t state;
  rosidl_runtime_c__String bag_id;
  rosidl_runtime_c__String experiment_id;
  rosidl_runtime_c__String profile_id;
  rosidl_runtime_c__String relative_uri;
  bool complete;
  bool simulation;
  double playback_rate;
  uint64_t storage_bytes;
  rosidl_runtime_c__String started_at;
  rosidl_runtime_c__String updated_at;
  rosidl_runtime_c__String message;
  int64_t process_id;
  uint64_t message_count;
  rosidl_runtime_c__String storage_identifier;
  bool mapping_input_ready;
  bool contains_mapping_outputs;
  bool contains_navigation_outputs;
} agt_interfaces__msg__BagSessionSummary;

// Struct for a sequence of agt_interfaces__msg__BagSessionSummary.
typedef struct agt_interfaces__msg__BagSessionSummary__Sequence
{
  agt_interfaces__msg__BagSessionSummary * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__BagSessionSummary__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__STRUCT_H_
