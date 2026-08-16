// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:action/ManageMappingSession.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
#include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `map_id`
// Member `session_id`
// Member `argument_keys`
// Member `argument_values`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_Goal__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_Goal__fini(message_memory);
}

size_t agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__size_function__ManageMappingSession_Goal__argument_keys(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_keys(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_keys(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__fetch_function__ManageMappingSession_Goal__argument_keys(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_keys(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__assign_function__ManageMappingSession_Goal__argument_keys(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_keys(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__resize_function__ManageMappingSession_Goal__argument_keys(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__size_function__ManageMappingSession_Goal__argument_values(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_values(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_values(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__fetch_function__ManageMappingSession_Goal__argument_values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_values(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__assign_function__ManageMappingSession_Goal__argument_values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_values(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__resize_function__ManageMappingSession_Goal__argument_values(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_member_array[7] = {
  {
    "operation",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, operation),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, map_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "session_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, session_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "argument_keys",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, argument_keys),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__size_function__ManageMappingSession_Goal__argument_keys,  // size() function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_keys,  // get_const(index) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_keys,  // get(index) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__fetch_function__ManageMappingSession_Goal__argument_keys,  // fetch(index, &value) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__assign_function__ManageMappingSession_Goal__argument_keys,  // assign(index, value) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__resize_function__ManageMappingSession_Goal__argument_keys  // resize(index) function pointer
  },
  {
    "argument_values",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, argument_values),  // bytes offset in struct
    NULL,  // default value
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__size_function__ManageMappingSession_Goal__argument_values,  // size() function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_const_function__ManageMappingSession_Goal__argument_values,  // get_const(index) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__get_function__ManageMappingSession_Goal__argument_values,  // get(index) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__fetch_function__ManageMappingSession_Goal__argument_values,  // fetch(index, &value) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__assign_function__ManageMappingSession_Goal__argument_values,  // assign(index, value) function pointer
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__resize_function__ManageMappingSession_Goal__argument_values  // resize(index) function pointer
  },
  {
    "activate_after_commit",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, activate_after_commit),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timeout_s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Goal, timeout_s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_Goal",  // message name
  7,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_Goal),
  agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Goal)() {
  if (!agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_Goal__rosidl_typesupport_introspection_c__ManageMappingSession_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `state`
// Member `session_id`
// Member `map_id`
// Member `map_version_id`
// Member `session_file`
// Member `candidate_map_yaml`
// Member `candidate_map_image`
// Member `localization_pcd`
// Member `processing_record`
// Member `bag_directory`
// Member `registered_map_yaml`
// Member `tasks_directory`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_Result__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_member_array[15] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, success),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ManageMappingSession_Result, error_code),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ManageMappingSession_Result, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "session_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, session_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ManageMappingSession_Result, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ManageMappingSession_Result, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "session_file",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, session_file),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "candidate_map_yaml",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, candidate_map_yaml),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "candidate_map_image",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, candidate_map_image),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "localization_pcd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, localization_pcd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "processing_record",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, processing_record),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "bag_directory",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, bag_directory),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "registered_map_yaml",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, registered_map_yaml),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tasks_directory",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, tasks_directory),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Result, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_Result",  // message name
  15,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_Result),
  agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Result)() {
  if (!agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_Result__rosidl_typesupport_introspection_c__ManageMappingSession_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `state`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_Feedback__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_member_array[3] = {
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Feedback, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "progress",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Feedback, progress),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_Feedback, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_Feedback",  // message name
  3,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_Feedback),
  agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Feedback)() {
  if (!agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_Feedback__rosidl_typesupport_introspection_c__ManageMappingSession_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "agt_interfaces/action/manage_mapping_session.h"
// Member `goal`
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Request),
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Request)() {
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Goal)();
  if (!agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_SendGoal_Request__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_SendGoal_Response),
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Response)() {
  agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_SendGoal_Response__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_members = {
  "agt_interfaces__action",  // service namespace
  "ManageMappingSession_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_type_support_handle = {
  0,
  &agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal)() {
  if (!agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_SendGoal_Response)()->data;
  }

  return &agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_GetResult_Request__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Request),
  agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Request)() {
  agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_GetResult_Request__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "agt_interfaces/action/manage_mapping_session.h"
// Member `result`
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_GetResult_Response__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_GetResult_Response),
  agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Response)() {
  agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Result)();
  if (!agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_GetResult_Response__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_members = {
  "agt_interfaces__action",  // service namespace
  "ManageMappingSession_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_type_support_handle = {
  0,
  &agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult)() {
  if (!agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_GetResult_Response)()->data;
  }

  return &agt_interfaces__action__detail__manage_mapping_session__rosidl_typesupport_introspection_c__ManageMappingSession_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__functions.h"
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/manage_mapping_session.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(message_memory);
}

void agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_fini_function(void * message_memory)
{
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ManageMappingSession_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_members = {
  "agt_interfaces__action",  // message namespace
  "ManageMappingSession_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ManageMappingSession_FeedbackMessage),
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_member_array,  // message members
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_type_support_handle = {
  0,
  &agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_FeedbackMessage)() {
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ManageMappingSession_Feedback)();
  if (!agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ManageMappingSession_FeedbackMessage__rosidl_typesupport_introspection_c__ManageMappingSession_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
