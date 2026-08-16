// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_H_

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
  agt_interfaces__msg__ComponentHealth__STATE_UNKNOWN = 0
};

/// Constant 'STATE_OK'.
enum
{
  agt_interfaces__msg__ComponentHealth__STATE_OK = 1
};

/// Constant 'STATE_WARN'.
enum
{
  agt_interfaces__msg__ComponentHealth__STATE_WARN = 2
};

/// Constant 'STATE_ERROR'.
enum
{
  agt_interfaces__msg__ComponentHealth__STATE_ERROR = 3
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'component_id'
// Member 'display_name'
// Member 'missing_topics'
// Member 'missing_frames'
// Member 'missing_nodes'
// Member 'lifecycle_failures'
// Member 'condition_failures'
// Member 'warnings'
// Member 'errors'
// Member 'detail'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ComponentHealth in the package agt_interfaces.
/**
  * Machine-readable health result for one configured component.
 */
typedef struct agt_interfaces__msg__ComponentHealth
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String component_id;
  rosidl_runtime_c__String display_name;
  uint8_t state;
  bool required;
  bool present;
  double observed_rate_hz;
  double message_age_sec;
  uint64_t message_count;
  rosidl_runtime_c__String__Sequence missing_topics;
  rosidl_runtime_c__String__Sequence missing_frames;
  rosidl_runtime_c__String__Sequence missing_nodes;
  rosidl_runtime_c__String__Sequence lifecycle_failures;
  rosidl_runtime_c__String__Sequence condition_failures;
  rosidl_runtime_c__String__Sequence warnings;
  rosidl_runtime_c__String__Sequence errors;
  rosidl_runtime_c__String detail;
} agt_interfaces__msg__ComponentHealth;

// Struct for a sequence of agt_interfaces__msg__ComponentHealth.
typedef struct agt_interfaces__msg__ComponentHealth__Sequence
{
  agt_interfaces__msg__ComponentHealth * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__ComponentHealth__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__STRUCT_H_
