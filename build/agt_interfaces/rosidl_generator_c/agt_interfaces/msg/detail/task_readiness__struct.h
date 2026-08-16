// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/TaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'active_mode'
// Member 'map_id'
// Member 'map_version_id'
// Member 'localization_state'
// Member 'blocker_codes'
// Member 'blocker_messages'
// Member 'warning_codes'
// Member 'warning_messages'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/TaskReadiness in the package agt_interfaces.
/**
  * Shared fail-closed task dispatch decision.
 */
typedef struct agt_interfaces__msg__TaskReadiness
{
  std_msgs__msg__Header header;
  bool ready;
  rosidl_runtime_c__String active_mode;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String localization_state;
  uint64_t health_revision;
  rosidl_runtime_c__String__Sequence blocker_codes;
  rosidl_runtime_c__String__Sequence blocker_messages;
  rosidl_runtime_c__String__Sequence warning_codes;
  rosidl_runtime_c__String__Sequence warning_messages;
} agt_interfaces__msg__TaskReadiness;

// Struct for a sequence of agt_interfaces__msg__TaskReadiness.
typedef struct agt_interfaces__msg__TaskReadiness__Sequence
{
  agt_interfaces__msg__TaskReadiness * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__TaskReadiness__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__STRUCT_H_
