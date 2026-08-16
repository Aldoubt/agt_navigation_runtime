// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/OptimizeMap.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'source_map_id'
// Member 'source_map_version_id'
// Member 'source_experiment_ids'
// Member 'backend'
// Member 'options_yaml'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_Goal
{
  rosidl_runtime_c__String source_map_id;
  rosidl_runtime_c__String source_map_version_id;
  rosidl_runtime_c__String__Sequence source_experiment_ids;
  rosidl_runtime_c__String backend;
  rosidl_runtime_c__String options_yaml;
  bool activate_on_success;
} agt_interfaces__action__OptimizeMap_Goal;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_Goal.
typedef struct agt_interfaces__action__OptimizeMap_Goal__Sequence
{
  agt_interfaces__action__OptimizeMap_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'new_map_version_id'
// Member 'trajectory_path'
// Member 'optimized_pcd_path'
// Member 'report_path'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_Result
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String new_map_version_id;
  rosidl_runtime_c__String trajectory_path;
  rosidl_runtime_c__String optimized_pcd_path;
  rosidl_runtime_c__String report_path;
  rosidl_runtime_c__String message;
} agt_interfaces__action__OptimizeMap_Result;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_Result.
typedef struct agt_interfaces__action__OptimizeMap_Result__Sequence
{
  agt_interfaces__action__OptimizeMap_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stage'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_Feedback
{
  rosidl_runtime_c__String stage;
  float progress;
  rosidl_runtime_c__String message;
} agt_interfaces__action__OptimizeMap_Feedback;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_Feedback.
typedef struct agt_interfaces__action__OptimizeMap_Feedback__Sequence
{
  agt_interfaces__action__OptimizeMap_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/optimize_map__struct.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__OptimizeMap_Goal goal;
} agt_interfaces__action__OptimizeMap_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_SendGoal_Request.
typedef struct agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence
{
  agt_interfaces__action__OptimizeMap_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__OptimizeMap_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_SendGoal_Response.
typedef struct agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence
{
  agt_interfaces__action__OptimizeMap_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__OptimizeMap_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_GetResult_Request.
typedef struct agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence
{
  agt_interfaces__action__OptimizeMap_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__OptimizeMap_Result result;
} agt_interfaces__action__OptimizeMap_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_GetResult_Response.
typedef struct agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence
{
  agt_interfaces__action__OptimizeMap_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.h"

/// Struct defined in action/OptimizeMap in the package agt_interfaces.
typedef struct agt_interfaces__action__OptimizeMap_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__OptimizeMap_Feedback feedback;
} agt_interfaces__action__OptimizeMap_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__OptimizeMap_FeedbackMessage.
typedef struct agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence
{
  agt_interfaces__action__OptimizeMap_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__STRUCT_H_
