// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
// Member 'name'
// Member 'role'
// Member 'tags'
#include "rosidl_runtime_c/string.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/SemanticWaypoint in the package agt_interfaces.
/**
  * Named semantic navigation anchor stored in the map frame.
  * This is map semantics, not an execution sequence.
 */
typedef struct agt_interfaces__msg__SemanticWaypoint
{
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String role;
  geometry_msgs__msg__Pose pose;
  float position_tolerance;
  float yaw_tolerance;
  float preferred_speed;
  rosidl_runtime_c__String__Sequence tags;
  bool enabled;
} agt_interfaces__msg__SemanticWaypoint;

// Struct for a sequence of agt_interfaces__msg__SemanticWaypoint.
typedef struct agt_interfaces__msg__SemanticWaypoint__Sequence
{
  agt_interfaces__msg__SemanticWaypoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__SemanticWaypoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__STRUCT_H_
