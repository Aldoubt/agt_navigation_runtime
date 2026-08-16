// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/srv/detail/activate_map_version__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/srv/detail/activate_map_version__functions.h"
#include "agt_interfaces/srv/detail/activate_map_version__struct.h"


// Include directives for member types
// Member `map_id`
// Member `map_version_id`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__ActivateMapVersion_Request__init(message_memory);
}

void agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_fini_function(void * message_memory)
{
  agt_interfaces__srv__ActivateMapVersion_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_member_array[3] = {
  {
    "map_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Request, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ActivateMapVersion_Request, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "client_request_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Request, client_request_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_members = {
  "agt_interfaces__srv",  // message namespace
  "ActivateMapVersion_Request",  // message name
  3,  // number of fields
  sizeof(agt_interfaces__srv__ActivateMapVersion_Request),
  agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_member_array,  // message members
  agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_type_support_handle = {
  0,
  &agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Request)() {
  if (!agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__ActivateMapVersion_Request__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/srv/detail/activate_map_version__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/srv/detail/activate_map_version__functions.h"
// already included above
// #include "agt_interfaces/srv/detail/activate_map_version__struct.h"


// Include directives for member types
// Member `map_id`
// Member `map_version_id`
// Member `state`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `operator_messages`
// Member `technical_messages`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `version`
#include "agt_interfaces/msg/map_version_summary.h"
// Member `version`
#include "agt_interfaces/msg/detail/map_version_summary__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__ActivateMapVersion_Response__init(message_memory);
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_fini_function(void * message_memory)
{
  agt_interfaces__srv__ActivateMapVersion_Response__fini(message_memory);
}

size_t agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__blocker_codes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_codes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_codes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__blocker_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_codes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__blocker_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_codes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__blocker_codes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__blocker_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__blocker_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__blocker_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__blocker_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__operator_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__operator_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__operator_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__operator_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__operator_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__operator_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__operator_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__operator_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__technical_messages(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__technical_messages(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__technical_messages(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__technical_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__technical_messages(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__technical_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__technical_messages(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__technical_messages(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_member_array[10] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, error_code),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, map_version_id),  // bytes offset in struct
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
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, state),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, blocker_codes),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__blocker_codes,  // size() function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_codes,  // get_const(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_codes,  // get(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__blocker_codes,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__blocker_codes,  // assign(index, value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__blocker_codes  // resize(index) function pointer
  },
  {
    "blocker_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, blocker_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__blocker_messages,  // size() function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__blocker_messages,  // get_const(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__blocker_messages,  // get(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__blocker_messages,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__blocker_messages,  // assign(index, value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__blocker_messages  // resize(index) function pointer
  },
  {
    "operator_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, operator_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__operator_messages,  // size() function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__operator_messages,  // get_const(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__operator_messages,  // get(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__operator_messages,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__operator_messages,  // assign(index, value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__operator_messages  // resize(index) function pointer
  },
  {
    "technical_messages",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, technical_messages),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__size_function__ActivateMapVersion_Response__technical_messages,  // size() function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_const_function__ActivateMapVersion_Response__technical_messages,  // get_const(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__get_function__ActivateMapVersion_Response__technical_messages,  // get(index) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__fetch_function__ActivateMapVersion_Response__technical_messages,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__assign_function__ActivateMapVersion_Response__technical_messages,  // assign(index, value) function pointer
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__resize_function__ActivateMapVersion_Response__technical_messages  // resize(index) function pointer
  },
  {
    "version",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ActivateMapVersion_Response, version),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_members = {
  "agt_interfaces__srv",  // message namespace
  "ActivateMapVersion_Response",  // message name
  10,  // number of fields
  sizeof(agt_interfaces__srv__ActivateMapVersion_Response),
  agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_member_array,  // message members
  agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_type_support_handle = {
  0,
  &agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Response)() {
  agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_member_array[9].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, MapVersionSummary)();
  if (!agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__ActivateMapVersion_Response__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/activate_map_version__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_members = {
  "agt_interfaces__srv",  // service namespace
  "ActivateMapVersion",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_type_support_handle = {
  0,
  &agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion)() {
  if (!agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ActivateMapVersion_Response)()->data;
  }

  return &agt_interfaces__srv__detail__activate_map_version__rosidl_typesupport_introspection_c__ActivateMapVersion_service_type_support_handle;
}
