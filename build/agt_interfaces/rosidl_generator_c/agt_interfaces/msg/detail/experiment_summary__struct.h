// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/ExperimentSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_H_

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
  agt_interfaces__msg__ExperimentSummary__STATE_UNKNOWN = 0
};

/// Constant 'STATE_CREATED'.
enum
{
  agt_interfaces__msg__ExperimentSummary__STATE_CREATED = 1
};

/// Constant 'STATE_RUNNING'.
enum
{
  agt_interfaces__msg__ExperimentSummary__STATE_RUNNING = 2
};

/// Constant 'STATE_COMPLETED'.
enum
{
  agt_interfaces__msg__ExperimentSummary__STATE_COMPLETED = 3
};

/// Constant 'STATE_INTERRUPTED'.
enum
{
  agt_interfaces__msg__ExperimentSummary__STATE_INTERRUPTED = 4
};

/// Constant 'STATE_INVALID'.
enum
{
  agt_interfaces__msg__ExperimentSummary__STATE_INVALID = 5
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'experiment_id'
// Member 'title'
// Member 'created_at'
// Member 'start_time'
// Member 'end_time'
// Member 'platform_profile'
// Member 'map_id'
// Member 'map_version_id'
// Member 'map_hash'
// Member 'mission_id'
// Member 'mission_version'
// Member 'mission_sha256'
// Member 'launch_profile'
// Member 'result_status'
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ExperimentSummary in the package agt_interfaces.
/**
  * Manager-owned experiment lifecycle summary.
 */
typedef struct agt_interfaces__msg__ExperimentSummary
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String experiment_id;
  rosidl_runtime_c__String title;
  uint8_t state;
  rosidl_runtime_c__String created_at;
  rosidl_runtime_c__String start_time;
  rosidl_runtime_c__String end_time;
  rosidl_runtime_c__String platform_profile;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String map_hash;
  rosidl_runtime_c__String mission_id;
  rosidl_runtime_c__String mission_version;
  rosidl_runtime_c__String mission_sha256;
  rosidl_runtime_c__String launch_profile;
  rosidl_runtime_c__String result_status;
  uint32_t config_snapshot_count;
  rosidl_runtime_c__String message;
} agt_interfaces__msg__ExperimentSummary;

// Struct for a sequence of agt_interfaces__msg__ExperimentSummary.
typedef struct agt_interfaces__msg__ExperimentSummary__Sequence
{
  agt_interfaces__msg__ExperimentSummary * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__ExperimentSummary__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__STRUCT_H_
