// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_TREE_NOT_ALLOWED'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_TREE_NOT_ALLOWED = 2
};

/// Constant 'ERROR_TREE_FAILED'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_TREE_FAILED = 3
};

/// Constant 'ERROR_CANCELED'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_CANCELED = 4
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'tree_id'
// Member 'execution_id'
// Member 'map_id'
// Member 'map_version_id'
// Member 'task_group_id'
// Member 'expected_content_sha256'
// Member 'client_request_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Goal
{
  rosidl_runtime_c__String tree_id;
  rosidl_runtime_c__String execution_id;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String task_group_id;
  uint32_t task_revision;
  rosidl_runtime_c__String expected_content_sha256;
  uint32_t loop_count;
  rosidl_runtime_c__String client_request_id;
} agt_interfaces__action__ExecuteBehaviorTree_Goal;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_Goal.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// Member 'blocker_code'
// Member 'blocker_message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Result
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String message;
  rosidl_runtime_c__String blocker_code;
  rosidl_runtime_c__String blocker_message;
} agt_interfaces__action__ExecuteBehaviorTree_Result;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_Result.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'tree_state'
// Member 'active_node'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Feedback
{
  rosidl_runtime_c__String tree_state;
  rosidl_runtime_c__String active_node;
  uint32_t loop_index;
  uint32_t current_waypoint;
  uint32_t total_waypoints;
} agt_interfaces__action__ExecuteBehaviorTree_Feedback;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_Feedback.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteBehaviorTree_Goal goal;
} agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__ExecuteBehaviorTree_Result result;
} agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.h"

/// Struct defined in action/ExecuteBehaviorTree in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteBehaviorTree_Feedback feedback;
} agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage.
typedef struct agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence
{
  agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_BEHAVIOR_TREE__STRUCT_H_
