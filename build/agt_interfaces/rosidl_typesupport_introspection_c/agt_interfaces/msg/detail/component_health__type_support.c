// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/msg/detail/component_health__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/msg/detail/component_health__functions.h"
#include "agt_interfaces/msg/detail/component_health__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `component_id`
// Member `display_name`
// Member `missing_topics`
// Member `missing_frames`
// Member `missing_nodes`
// Member `lifecycle_failures`
// Member `condition_failures`
// Member `warnings`
// Member `errors`
// Member `detail`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__msg__ComponentHealth__init(message_memory);
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_fini_function(void * message_memory)
{
  agt_interfaces__msg__ComponentHealth__fini(message_memory);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_topics(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_topics(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_topics(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_topics(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_topics(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_topics(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_topics(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_topics(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_frames(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_frames(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_frames(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_frames(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_frames(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_frames(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_frames(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_frames(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_nodes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_nodes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_nodes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_nodes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_nodes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_nodes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_nodes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_nodes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__lifecycle_failures(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__lifecycle_failures(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__lifecycle_failures(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__lifecycle_failures(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__lifecycle_failures(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__lifecycle_failures(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__lifecycle_failures(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__lifecycle_failures(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__condition_failures(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__condition_failures(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__condition_failures(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__condition_failures(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__condition_failures(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__condition_failures(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__condition_failures(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__condition_failures(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__warnings(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__warnings(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__warnings(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__warnings(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__warnings(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__warnings(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__warnings(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__warnings(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__errors(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__errors(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__errors(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__errors(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__errors(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__errors(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__errors(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__errors(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_member_array[17] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "component_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, component_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "display_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, display_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "required",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, required),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "present",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, present),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "observed_rate_hz",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, observed_rate_hz),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message_age_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, message_age_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, message_count),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "missing_topics",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, missing_topics),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_topics,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_topics,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_topics,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_topics,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_topics,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_topics  // resize(index) function pointer
  },
  {
    "missing_frames",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, missing_frames),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_frames,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_frames,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_frames,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_frames,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_frames,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_frames  // resize(index) function pointer
  },
  {
    "missing_nodes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, missing_nodes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__missing_nodes,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__missing_nodes,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__missing_nodes,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__missing_nodes,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__missing_nodes,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__missing_nodes  // resize(index) function pointer
  },
  {
    "lifecycle_failures",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, lifecycle_failures),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__lifecycle_failures,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__lifecycle_failures,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__lifecycle_failures,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__lifecycle_failures,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__lifecycle_failures,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__lifecycle_failures  // resize(index) function pointer
  },
  {
    "condition_failures",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, condition_failures),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__condition_failures,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__condition_failures,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__condition_failures,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__condition_failures,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__condition_failures,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__condition_failures  // resize(index) function pointer
  },
  {
    "warnings",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, warnings),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__warnings,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__warnings,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__warnings,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__warnings,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__warnings,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__warnings  // resize(index) function pointer
  },
  {
    "errors",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, errors),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__size_function__ComponentHealth__errors,  // size() function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_const_function__ComponentHealth__errors,  // get_const(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__get_function__ComponentHealth__errors,  // get(index) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__fetch_function__ComponentHealth__errors,  // fetch(index, &value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__assign_function__ComponentHealth__errors,  // assign(index, value) function pointer
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__resize_function__ComponentHealth__errors  // resize(index) function pointer
  },
  {
    "detail",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__ComponentHealth, detail),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_members = {
  "agt_interfaces__msg",  // message namespace
  "ComponentHealth",  // message name
  17,  // number of fields
  sizeof(agt_interfaces__msg__ComponentHealth),
  agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_member_array,  // message members
  agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_type_support_handle = {
  0,
  &agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, ComponentHealth)() {
  agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__msg__ComponentHealth__rosidl_typesupport_introspection_c__ComponentHealth_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
