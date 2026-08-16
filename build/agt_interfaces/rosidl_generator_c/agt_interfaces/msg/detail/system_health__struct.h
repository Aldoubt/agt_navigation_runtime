// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_H_

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
  agt_interfaces__msg__SystemHealth__STATE_UNKNOWN = 0
};

/// Constant 'STATE_OK'.
enum
{
  agt_interfaces__msg__SystemHealth__STATE_OK = 1
};

/// Constant 'STATE_WARN'.
enum
{
  agt_interfaces__msg__SystemHealth__STATE_WARN = 2
};

/// Constant 'STATE_ERROR'.
enum
{
  agt_interfaces__msg__SystemHealth__STATE_ERROR = 3
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'components'
#include "agt_interfaces/msg/detail/component_health__struct.h"
// Member 'blocker_codes'
// Member 'blocker_messages'
// Member 'warning_codes'
// Member 'warning_messages'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SystemHealth in the package agt_interfaces.
/**
  * Snapshot of all configured component health results.
 */
typedef struct agt_interfaces__msg__SystemHealth
{
  std_msgs__msg__Header header;
  uint8_t overall_state;
  uint64_t revision;
  agt_interfaces__msg__ComponentHealth__Sequence components;
  rosidl_runtime_c__String__Sequence blocker_codes;
  rosidl_runtime_c__String__Sequence blocker_messages;
  rosidl_runtime_c__String__Sequence warning_codes;
  rosidl_runtime_c__String__Sequence warning_messages;
} agt_interfaces__msg__SystemHealth;

// Struct for a sequence of agt_interfaces__msg__SystemHealth.
typedef struct agt_interfaces__msg__SystemHealth__Sequence
{
  agt_interfaces__msg__SystemHealth * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__SystemHealth__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__STRUCT_H_
