// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:msg/SemanticWaypointArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/msg/detail/semantic_waypoint_array__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/msg/detail/semantic_waypoint_array__functions.h"
#include "agt_interfaces/msg/detail/semantic_waypoint_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `schema_version`
// Member `map_id`
// Member `base_map_sha256`
#include "rosidl_runtime_c/string_functions.h"
// Member `waypoints`
#include "agt_interfaces/msg/semantic_waypoint.h"
// Member `waypoints`
#include "agt_interfaces/msg/detail/semantic_waypoint__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__msg__SemanticWaypointArray__init(message_memory);
}

void agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_fini_function(void * message_memory)
{
  agt_interfaces__msg__SemanticWaypointArray__fini(message_memory);
}

size_t agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__size_function__SemanticWaypointArray__waypoints(
  const void * untyped_member)
{
  const agt_interfaces__msg__SemanticWaypoint__Sequence * member =
    (const agt_interfaces__msg__SemanticWaypoint__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_const_function__SemanticWaypointArray__waypoints(
  const void * untyped_member, size_t index)
{
  const agt_interfaces__msg__SemanticWaypoint__Sequence * member =
    (const agt_interfaces__msg__SemanticWaypoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_function__SemanticWaypointArray__waypoints(
  void * untyped_member, size_t index)
{
  agt_interfaces__msg__SemanticWaypoint__Sequence * member =
    (agt_interfaces__msg__SemanticWaypoint__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__fetch_function__SemanticWaypointArray__waypoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const agt_interfaces__msg__SemanticWaypoint * item =
    ((const agt_interfaces__msg__SemanticWaypoint *)
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_const_function__SemanticWaypointArray__waypoints(untyped_member, index));
  agt_interfaces__msg__SemanticWaypoint * value =
    (agt_interfaces__msg__SemanticWaypoint *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__assign_function__SemanticWaypointArray__waypoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  agt_interfaces__msg__SemanticWaypoint * item =
    ((agt_interfaces__msg__SemanticWaypoint *)
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_function__SemanticWaypointArray__waypoints(untyped_member, index));
  const agt_interfaces__msg__SemanticWaypoint * value =
    (const agt_interfaces__msg__SemanticWaypoint *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__resize_function__SemanticWaypointArray__waypoints(
  void * untyped_member, size_t size)
{
  agt_interfaces__msg__SemanticWaypoint__Sequence * member =
    (agt_interfaces__msg__SemanticWaypoint__Sequence *)(untyped_member);
  agt_interfaces__msg__SemanticWaypoint__Sequence__fini(member);
  return agt_interfaces__msg__SemanticWaypoint__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SemanticWaypointArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "schema_version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SemanticWaypointArray, schema_version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SemanticWaypointArray, map_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "base_map_sha256",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SemanticWaypointArray, base_map_sha256),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "waypoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SemanticWaypointArray, waypoints),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__size_function__SemanticWaypointArray__waypoints,  // size() function pointer
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_const_function__SemanticWaypointArray__waypoints,  // get_const(index) function pointer
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__get_function__SemanticWaypointArray__waypoints,  // get(index) function pointer
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__fetch_function__SemanticWaypointArray__waypoints,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__assign_function__SemanticWaypointArray__waypoints,  // assign(index, value) function pointer
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__resize_function__SemanticWaypointArray__waypoints  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_members = {
  "agt_interfaces__msg",  // message namespace
  "SemanticWaypointArray",  // message name
  5,  // number of fields
  sizeof(agt_interfaces__msg__SemanticWaypointArray),
  agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_member_array,  // message members
  agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_type_support_handle = {
  0,
  &agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, SemanticWaypointArray)() {
  agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, SemanticWaypoint)();
  if (!agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__msg__SemanticWaypointArray__rosidl_typesupport_introspection_c__SemanticWaypointArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
