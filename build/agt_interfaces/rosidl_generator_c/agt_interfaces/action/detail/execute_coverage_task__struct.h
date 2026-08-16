// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/ExecuteCoverageTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'semantic_map_uri'
// Member 'field_id'
// Member 'planning_mode'
// Member 'controller_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Goal
{
  rosidl_runtime_c__String semantic_map_uri;
  rosidl_runtime_c__String field_id;
  rosidl_runtime_c__String planning_mode;
  rosidl_runtime_c__String controller_id;
  bool allow_repair;
} agt_interfaces__action__ExecuteCoverageTask_Goal;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_Goal.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Result
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String message;
  double coverage_rate;
  double overlap_rate;
  double executed_length;
  uint32_t repaired_segment_count;
} agt_interfaces__action__ExecuteCoverageTask_Result;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_Result.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Result__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'current_stage'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Feedback
{
  rosidl_runtime_c__String current_stage;
  uint32_t current_swath_index;
  uint32_t total_swaths;
  double distance_remaining;
} agt_interfaces__action__ExecuteCoverageTask_Feedback;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_Feedback.
typedef struct agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_coverage_task__struct.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteCoverageTask_Goal goal;
} agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request.
typedef struct agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response.
typedef struct agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__ExecuteCoverageTask_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_GetResult_Request.
typedef struct agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_coverage_task__struct.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__ExecuteCoverageTask_Result result;
} agt_interfaces__action__ExecuteCoverageTask_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_GetResult_Response.
typedef struct agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/execute_coverage_task__struct.h"

/// Struct defined in action/ExecuteCoverageTask in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteCoverageTask_Feedback feedback;
} agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage.
typedef struct agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence
{
  agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__STRUCT_H_
