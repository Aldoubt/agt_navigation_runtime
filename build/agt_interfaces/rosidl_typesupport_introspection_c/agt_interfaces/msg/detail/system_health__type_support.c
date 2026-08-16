// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/msg/detail/system_health__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/msg/detail/system_health__functions.h"
#include "agt_interfaces/msg/detail/system_health__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `components`
#include "agt_interfaces/msg/component_health.h"
// Member `components`
#include "agt_interfaces/msg/detail/component_health__rosidl_typesupport_introspection_c.h"
// Member `blocker_codes`
// Member `blocker_messages`
// Member `warning_codes`
// Member `warning_messages`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__msg__SystemHealth__init(message_memory);
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_fini_function(void * message_memory)
{
  agt_interfaces__msg__SystemHealth__fini(message_memory);
}

size_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__components(
  const void * untyped_member)
{
  const agt_interfaces__msg__ComponentHealth__Sequence * member =
    (const agt_interfaces__msg__ComponentHealth__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__components(
  const void * untyped_member, size_t index)
{
  const agt_interfaces__msg__ComponentHealth__Sequence * member =
    (const agt_interfaces__msg__ComponentHealth__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__components(
  void * untyped_member, size_t index)
{
  agt_interfaces__msg__ComponentHealth__Sequence * member =
    (agt_interfaces__msg__ComponentHealth__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__components(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const agt_interfaces__msg__ComponentHealth * item =
    ((const agt_interfaces__msg__ComponentHealth *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__components(untyped_member, index));
  agt_interfaces__msg__ComponentHealth * value =
    (agt_interfaces__msg__ComponentHealth *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__components(
  void * untyped_member, size_t index, const void * untyped_value)
{
  agt_interfaces__msg__ComponentHealth * item =
    ((agt_interfaces__msg__ComponentHealth *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__components(untyped_member, index));
  const agt_interfaces__msg__ComponentHealth * value =
    (const agt_interfaces__msg__ComponentHealth *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__components(
  void * untyped_member, size_t size)
{
  agt_interfaces__msg__ComponentHealth__Sequence * member =
    (agt_interfaces__msg__ComponentHealth__Sequence *)(untyped_member);
  agt_interfaces__msg__ComponentHealth__Sequence__fini(member);
  return agt_interfaces__msg__ComponentHealth__Sequence__init(member, size);
}

size_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__blocker_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__blocker_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_codes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__blocker_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_codes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__blocker_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__blocker_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__blocker_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__blocker_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__blocker_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__warning_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__warning_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_codes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__warning_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_codes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__warning_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__warning_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__warning_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__warning_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__warning_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_member_array[8] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "overall_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, overall_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "revision",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, revision),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "components",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, components),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__components,  // size() function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__components,  // get_const(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__components,  // get(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__components,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__components,  // assign(index, value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__components  // resize(index) function pointer
  },
  {
    "blocker_codes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, blocker_codes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__blocker_codes,  // size() function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_codes,  // get_const(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_codes,  // get(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__blocker_codes,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__blocker_codes,  // assign(index, value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__blocker_codes  // resize(index) function pointer
  },
  {
    "blocker_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, blocker_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__blocker_messages,  // size() function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__blocker_messages,  // get_const(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__blocker_messages,  // get(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__blocker_messages,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__blocker_messages,  // assign(index, value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__blocker_messages  // resize(index) function pointer
  },
  {
    "warning_codes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, warning_codes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__warning_codes,  // size() function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_codes,  // get_const(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_codes,  // get(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__warning_codes,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__warning_codes,  // assign(index, value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__warning_codes  // resize(index) function pointer
  },
  {
    "warning_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__msg__SystemHealth, warning_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__size_function__SystemHealth__warning_messages,  // size() function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_const_function__SystemHealth__warning_messages,  // get_const(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__get_function__SystemHealth__warning_messages,  // get(index) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__fetch_function__SystemHealth__warning_messages,  // fetch(index, &value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__assign_function__SystemHealth__warning_messages,  // assign(index, value) function pointer
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__resize_function__SystemHealth__warning_messages  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_members = {
  "agt_interfaces__msg",  // message namespace
  "SystemHealth",  // message name
  8,  // number of fields
  sizeof(agt_interfaces__msg__SystemHealth),
  agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_member_array,  // message members
  agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_type_support_handle = {
  0,
  &agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, SystemHealth)() {
  agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, ComponentHealth)();
  if (!agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__msg__SystemHealth__rosidl_typesupport_introspection_c__SystemHealth_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
