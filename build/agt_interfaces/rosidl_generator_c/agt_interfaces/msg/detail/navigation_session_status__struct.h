// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/NavigationSessionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATE_IDLE'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_IDLE = 0
};

/// Constant 'STATE_VALIDATING'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_VALIDATING = 1
};

/// Constant 'STATE_REJECTED'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_REJECTED = 2
};

/// Constant 'STATE_ACCEPTED'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_ACCEPTED = 3
};

/// Constant 'STATE_RUNNING'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_RUNNING = 4
};

/// Constant 'STATE_CANCELING'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_CANCELING = 5
};

/// Constant 'STATE_SUCCEEDED'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_SUCCEEDED = 6
};

/// Constant 'STATE_FAILED'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_FAILED = 7
};

/// Constant 'STATE_CANCELED'.
enum
{
  agt_interfaces__msg__NavigationSessionStatus__STATE_CANCELED = 8
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'session_id'
// Member 'client_request_id'
// Member 'map_id'
// Member 'map_version_id'
// Member 'task_group_id'
// Member 'task_content_sha256'
// Member 'blocker_code'
// Member 'operator_message'
// Member 'technical_message'
#include "rosidl_runtime_c/string.h"
// Member 'missed_waypoints'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'started_at'
// Member 'updated_at'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/NavigationSessionStatus in the package agt_interfaces.
/**
  * Authoritative waypoint-task session state owned by agt_navigation.
  * Published reliable + transient_local on /agt/navigation/session_status.
 */
typedef struct agt_interfaces__msg__NavigationSessionStatus
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String session_id;
  rosidl_runtime_c__String client_request_id;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String task_group_id;
  uint32_t task_revision;
  rosidl_runtime_c__String task_content_sha256;
  uint8_t state;
  uint32_t loop_index;
  uint32_t current_waypoint;
  uint32_t total_waypoints;
  rosidl_runtime_c__uint32__Sequence missed_waypoints;
  uint16_t error_code;
  rosidl_runtime_c__String blocker_code;
  rosidl_runtime_c__String operator_message;
  rosidl_runtime_c__String technical_message;
  builtin_interfaces__msg__Time started_at;
  builtin_interfaces__msg__Time updated_at;
  bool terminal;
  bool success;
} agt_interfaces__msg__NavigationSessionStatus;

// Struct for a sequence of agt_interfaces__msg__NavigationSessionStatus.
typedef struct agt_interfaces__msg__NavigationSessionStatus__Sequence
{
  agt_interfaces__msg__NavigationSessionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__NavigationSessionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__STRUCT_H_
