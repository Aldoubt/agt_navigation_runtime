// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/SemanticWaypointArray.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_H_

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
// Member 'schema_version'
// Member 'map_id'
// Member 'base_map_sha256'
#include "rosidl_runtime_c/string.h"
// Member 'waypoints'
#include "agt_interfaces/msg/detail/semantic_waypoint__struct.h"

/// Struct defined in msg/SemanticWaypointArray in the package agt_interfaces.
/**
  * Versioned semantic waypoint library for one map.
 */
typedef struct agt_interfaces__msg__SemanticWaypointArray
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String schema_version;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String base_map_sha256;
  agt_interfaces__msg__SemanticWaypoint__Sequence waypoints;
} agt_interfaces__msg__SemanticWaypointArray;

// Struct for a sequence of agt_interfaces__msg__SemanticWaypointArray.
typedef struct agt_interfaces__msg__SemanticWaypointArray__Sequence
{
  agt_interfaces__msg__SemanticWaypointArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__SemanticWaypointArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT_ARRAY__STRUCT_H_
