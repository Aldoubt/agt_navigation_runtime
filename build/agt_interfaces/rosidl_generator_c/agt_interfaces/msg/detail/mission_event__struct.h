// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/MissionEvent.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_H_

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
// Member 'event_type'
// Member 'source'
// Member 'correlation_id'
// Member 'mission_id'
// Member 'metadata_json'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MissionEvent in the package agt_interfaces.
/**
  * Timestamped external event consumed by finite WAIT_EVENT mission steps.
 */
typedef struct agt_interfaces__msg__MissionEvent
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String event_type;
  rosidl_runtime_c__String source;
  rosidl_runtime_c__String correlation_id;
  rosidl_runtime_c__String mission_id;
  /// Extension data only. Core event identity is represented by typed fields above.
  rosidl_runtime_c__String metadata_json;
} agt_interfaces__msg__MissionEvent;

// Struct for a sequence of agt_interfaces__msg__MissionEvent.
typedef struct agt_interfaces__msg__MissionEvent__Sequence
{
  agt_interfaces__msg__MissionEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__MissionEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_EVENT__STRUCT_H_
