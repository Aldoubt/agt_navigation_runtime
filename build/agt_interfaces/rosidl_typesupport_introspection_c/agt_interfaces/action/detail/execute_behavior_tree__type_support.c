// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
#include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `tree_id`
// Member `execution_id`
// Member `map_id`
// Member `map_version_id`
// Member `task_group_id`
// Member `expected_content_sha256`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_Goal__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_member_array[9] = {
  {
    "tree_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, tree_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "execution_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, execution_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, map_version_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "task_group_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, task_group_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "task_revision",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, task_revision),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "expected_content_sha256",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, expected_content_sha256),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "loop_count",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, loop_count),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Goal, client_request_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_Goal",  // message name
  9,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_Goal),
  agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Goal)() {
  if (!agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_Goal__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `message`
// Member `blocker_code`
// Member `blocker_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_Result__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_member_array[5] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Result, success),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Result, error_code),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Result, message),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Result, blocker_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "blocker_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Result, blocker_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_Result",  // message name
  5,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_Result),
  agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Result)() {
  if (!agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_Result__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `tree_state`
// Member `active_node`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_member_array[5] = {
  {
    "tree_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Feedback, tree_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "active_node",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Feedback, active_node),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "loop_index",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Feedback, loop_index),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_waypoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Feedback, current_waypoint),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "total_waypoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_Feedback, total_waypoints),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_Feedback",  // message name
  5,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_Feedback),
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Feedback)() {
  if (!agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_Feedback__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "agt_interfaces/action/execute_behavior_tree.h"
// Member `goal`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request, goal_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request),
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)() {
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Goal)();
  if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response, accepted),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response),
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)() {
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_members = {
  "agt_interfaces__action",  // service namespace
  "ExecuteBehaviorTree_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_type_support_handle = {
  0,
  &agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal)() {
  if (!agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)()->data;
  }

  return &agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


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

void agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request),
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)() {
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "agt_interfaces/action/execute_behavior_tree.h"
// Member `result`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response, status),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response),
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)() {
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Result)();
  if (!agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_members = {
  "agt_interfaces__action",  // service namespace
  "ExecuteBehaviorTree_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_type_support_handle = {
  0,
  &agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult)() {
  if (!agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)()->data;
  }

  return &agt_interfaces__action__detail__execute_behavior_tree__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__functions.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/execute_behavior_tree.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(message_memory);
}

void agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_fini_function(void * message_memory)
{
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage, goal_id),  // bytes offset in struct
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
    offsetof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_members = {
  "agt_interfaces__action",  // message namespace
  "ExecuteBehaviorTree_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage),
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_member_array,  // message members
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle = {
  0,
  &agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_FeedbackMessage)() {
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, action, ExecuteBehaviorTree_Feedback)();
  if (!agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__rosidl_typesupport_introspection_c__ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
