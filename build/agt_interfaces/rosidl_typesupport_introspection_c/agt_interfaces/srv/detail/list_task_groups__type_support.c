// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:srv/ListTaskGroups.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/srv/detail/list_task_groups__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/srv/detail/list_task_groups__functions.h"
#include "agt_interfaces/srv/detail/list_task_groups__struct.h"


// Include directives for member types
// Member `map_id`
// Member `map_version_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__ListTaskGroups_Request__init(message_memory);
}

void agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_fini_function(void * message_memory)
{
  agt_interfaces__srv__ListTaskGroups_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_member_array[2] = {
  {
    "map_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Request, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ListTaskGroups_Request, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_members = {
  "agt_interfaces__srv",  // message namespace
  "ListTaskGroups_Request",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__srv__ListTaskGroups_Request),
  agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_member_array,  // message members
  agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_type_support_handle = {
  0,
  &agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Request)() {
  if (!agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__ListTaskGroups_Request__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__functions.h"
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__struct.h"


// Include directives for member types
// Member `blocker_code`
// Member `operator_message`
// Member `technical_message`
// Member `map_id`
// Member `map_version_id`
// Member `task_group_ids`
// Member `names`
// Member `content_sha256`
// Member `updated_at`
// Member `validation_states`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `revisions`
// Member `enabled_point_counts`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__ListTaskGroups_Response__init(message_memory);
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_fini_function(void * message_memory)
{
  agt_interfaces__srv__ListTaskGroups_Response__fini(message_memory);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__task_group_ids(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__task_group_ids(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__task_group_ids(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__task_group_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__task_group_ids(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__task_group_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__task_group_ids(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__task_group_ids(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__revisions(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__revisions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__revisions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__revisions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__revisions(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__revisions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__revisions(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__revisions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  rosidl_runtime_c__uint32__Sequence__fini(member);
  return rosidl_runtime_c__uint32__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__content_sha256(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__content_sha256(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__content_sha256(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__content_sha256(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__content_sha256(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__content_sha256(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__content_sha256(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__content_sha256(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__enabled_point_counts(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__enabled_point_counts(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__enabled_point_counts(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__enabled_point_counts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__enabled_point_counts(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__enabled_point_counts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__enabled_point_counts(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__enabled_point_counts(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  rosidl_runtime_c__uint32__Sequence__fini(member);
  return rosidl_runtime_c__uint32__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__updated_at(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__updated_at(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__updated_at(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__updated_at(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__updated_at(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__updated_at(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__updated_at(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__updated_at(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__validation_states(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__validation_states(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__validation_states(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__validation_states(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__validation_states(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__validation_states(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__validation_states(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__validation_states(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_member_array[14] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, success),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "blocker_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, blocker_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "operator_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, operator_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "technical_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, technical_message),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "task_group_ids",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, task_group_ids),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__task_group_ids,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__task_group_ids,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__task_group_ids,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__task_group_ids,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__task_group_ids,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__task_group_ids  // resize(index) function pointer
  },
  {
    "names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, names),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__names,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__names,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__names,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__names,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__names,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__names  // resize(index) function pointer
  },
  {
    "revisions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, revisions),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__revisions,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__revisions,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__revisions,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__revisions,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__revisions,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__revisions  // resize(index) function pointer
  },
  {
    "content_sha256",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, content_sha256),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__content_sha256,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__content_sha256,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__content_sha256,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__content_sha256,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__content_sha256,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__content_sha256  // resize(index) function pointer
  },
  {
    "enabled_point_counts",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, enabled_point_counts),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__enabled_point_counts,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__enabled_point_counts,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__enabled_point_counts,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__enabled_point_counts,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__enabled_point_counts,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__enabled_point_counts  // resize(index) function pointer
  },
  {
    "updated_at",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, updated_at),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__updated_at,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__updated_at,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__updated_at,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__updated_at,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__updated_at,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__updated_at  // resize(index) function pointer
  },
  {
    "validation_states",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__ListTaskGroups_Response, validation_states),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__size_function__ListTaskGroups_Response__validation_states,  // size() function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_const_function__ListTaskGroups_Response__validation_states,  // get_const(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__get_function__ListTaskGroups_Response__validation_states,  // get(index) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__fetch_function__ListTaskGroups_Response__validation_states,  // fetch(index, &value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__assign_function__ListTaskGroups_Response__validation_states,  // assign(index, value) function pointer
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__resize_function__ListTaskGroups_Response__validation_states  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_members = {
  "agt_interfaces__srv",  // message namespace
  "ListTaskGroups_Response",  // message name
  14,  // number of fields
  sizeof(agt_interfaces__srv__ListTaskGroups_Response),
  agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_member_array,  // message members
  agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_type_support_handle = {
  0,
  &agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Response)() {
  if (!agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__ListTaskGroups_Response__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_members = {
  "agt_interfaces__srv",  // service namespace
  "ListTaskGroups",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_type_support_handle = {
  0,
  &agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups)() {
  if (!agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, ListTaskGroups_Response)()->data;
  }

  return &agt_interfaces__srv__detail__list_task_groups__rosidl_typesupport_introspection_c__ListTaskGroups_service_type_support_handle;
}
