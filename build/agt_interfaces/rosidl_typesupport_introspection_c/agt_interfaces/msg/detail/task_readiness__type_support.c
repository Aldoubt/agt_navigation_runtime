// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:msg/TaskReadiness.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/msg/detail/task_readiness__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/msg/detail/task_readiness__functions.h"
#include "agt_interfaces/msg/detail/task_readiness__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `active_mode`
// Member `map_id`
// Member `map_version_id`
// Member `localization_state`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `warning_codes`
// Member `warning_messages`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__msg__TaskReadiness__init(message_memory);
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_fini_function(void * message_memory)
{
  agt_interfaces__msg__TaskReadiness__fini(message_memory);
}

size_t agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__blocker_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__blocker_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_codes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__blocker_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_codes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__blocker_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__blocker_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__blocker_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__blocker_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__blocker_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__warning_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__warning_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_codes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__warning_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_codes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__warning_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__warning_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__warning_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__warning_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__warning_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_member_array[11] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ready",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, ready),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "active_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, active_mode),  // bytes offset in struct
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
    offsetof(agt_interfaces__msg__TaskReadiness, map_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_version_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "localization_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, localization_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "health_revision",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, health_revision),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "blocker_codes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, blocker_codes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__blocker_codes,  // size() function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_codes,  // get_const(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_codes,  // get(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__blocker_codes,  // fetch(index, &value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__blocker_codes,  // assign(index, value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__blocker_codes  // resize(index) function pointer
  },
  {
    "blocker_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, blocker_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__blocker_messages,  // size() function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__blocker_messages,  // get_const(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__blocker_messages,  // get(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__blocker_messages,  // fetch(index, &value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__blocker_messages,  // assign(index, value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__blocker_messages  // resize(index) function pointer
  },
  {
    "warning_codes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, warning_codes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__warning_codes,  // size() function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_codes,  // get_const(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_codes,  // get(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__warning_codes,  // fetch(index, &value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__warning_codes,  // assign(index, value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__warning_codes  // resize(index) function pointer
  },
  {
    "warning_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__TaskReadiness, warning_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__size_function__TaskReadiness__warning_messages,  // size() function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_const_function__TaskReadiness__warning_messages,  // get_const(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__get_function__TaskReadiness__warning_messages,  // get(index) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__fetch_function__TaskReadiness__warning_messages,  // fetch(index, &value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__assign_function__TaskReadiness__warning_messages,  // assign(index, value) function pointer
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__resize_function__TaskReadiness__warning_messages  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_members = {
  "agt_interfaces__msg",  // message namespace
  "TaskReadiness",  // message name
  11,  // number of fields
  sizeof(agt_interfaces__msg__TaskReadiness),
  agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_member_array,  // message members
  agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_type_support_handle = {
  0,
  &agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, TaskReadiness)() {
  agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__msg__TaskReadiness__rosidl_typesupport_introspection_c__TaskReadiness_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
