// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_H_

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
  agt_interfaces__msg__MissionStatus__STATE_IDLE = 0
};

/// Constant 'STATE_VALIDATING'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_VALIDATING = 1
};

/// Constant 'STATE_RUNNING'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_RUNNING = 2
};

/// Constant 'STATE_WAITING_DURATION'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_WAITING_DURATION = 3
};

/// Constant 'STATE_WAITING_EVENT'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_WAITING_EVENT = 4
};

/// Constant 'STATE_PAUSING'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_PAUSING = 5
};

/// Constant 'STATE_PAUSED'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_PAUSED = 6
};

/// Constant 'STATE_RESUMING'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_RESUMING = 7
};

/// Constant 'STATE_CANCELING'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_CANCELING = 8
};

/// Constant 'STATE_SUCCEEDED'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_SUCCEEDED = 9
};

/// Constant 'STATE_FAILED'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_FAILED = 10
};

/// Constant 'STATE_CANCELED'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_CANCELED = 11
};

/// Constant 'STATE_INTERRUPTED'.
enum
{
  agt_interfaces__msg__MissionStatus__STATE_INTERRUPTED = 12
};

/// Constant 'STEP_UNKNOWN'.
enum
{
  agt_interfaces__msg__MissionStatus__STEP_UNKNOWN = 0
};

/// Constant 'STEP_WAYPOINT_TASK'.
enum
{
  agt_interfaces__msg__MissionStatus__STEP_WAYPOINT_TASK = 1
};

/// Constant 'STEP_WAIT_DURATION'.
enum
{
  agt_interfaces__msg__MissionStatus__STEP_WAIT_DURATION = 2
};

/// Constant 'STEP_WAIT_EVENT'.
enum
{
  agt_interfaces__msg__MissionStatus__STEP_WAIT_EVENT = 3
};

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_MISSION'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_INVALID_MISSION = 1
};

/// Constant 'ERROR_MAP_MISMATCH'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_MAP_MISMATCH = 2
};

/// Constant 'ERROR_READINESS_LOST'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_READINESS_LOST = 3
};

/// Constant 'ERROR_LOCALIZATION_LOST'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_LOCALIZATION_LOST = 4
};

/// Constant 'ERROR_CHILD_REJECTED'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_CHILD_REJECTED = 5
};

/// Constant 'ERROR_CHILD_FAILED'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_CHILD_FAILED = 6
};

/// Constant 'ERROR_EVENT_TIMEOUT'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_EVENT_TIMEOUT = 7
};

/// Constant 'ERROR_CANCELED'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_CANCELED = 8
};

/// Constant 'ERROR_RESUME_BLOCKED'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_RESUME_BLOCKED = 9
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__msg__MissionStatus__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'mission_id'
// Member 'mission_version'
// Member 'content_sha256'
// Member 'map_id'
// Member 'map_version_id'
// Member 'map_manifest_sha256'
// Member 'current_step_id'
// Member 'blocker_codes'
// Member 'blocker_messages'
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MissionStatus in the package agt_interfaces.
/**
  * Authoritative status for one finite sequential mission.
 */
typedef struct agt_interfaces__msg__MissionStatus
{
  std_msgs__msg__Header header;
  uint8_t state;
  rosidl_runtime_c__String mission_id;
  rosidl_runtime_c__String mission_version;
  rosidl_runtime_c__String content_sha256;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String map_manifest_sha256;
  uint32_t current_step_index;
  uint32_t total_steps;
  rosidl_runtime_c__String current_step_id;
  uint8_t current_step_type;
  uint32_t current_waypoint;
  uint32_t total_waypoints;
  double step_elapsed_s;
  double step_remaining_s;
  uint16_t error_code;
  rosidl_runtime_c__String__Sequence blocker_codes;
  rosidl_runtime_c__String__Sequence blocker_messages;
  rosidl_runtime_c__String message;
} agt_interfaces__msg__MissionStatus;

// Struct for a sequence of agt_interfaces__msg__MissionStatus.
typedef struct agt_interfaces__msg__MissionStatus__Sequence
{
  agt_interfaces__msg__MissionStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__MissionStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__STRUCT_H_
