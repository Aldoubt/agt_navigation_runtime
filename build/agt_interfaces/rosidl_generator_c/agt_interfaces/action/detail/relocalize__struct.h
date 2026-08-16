// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_AUTO_SEARCH'.
enum
{
  agt_interfaces__action__Relocalize_Goal__MODE_AUTO_SEARCH = 0
};

/// Constant 'MODE_SINGLE_INITIAL_POSE'.
enum
{
  agt_interfaces__action__Relocalize_Goal__MODE_SINGLE_INITIAL_POSE = 1
};

/// Constant 'MODE_LOCAL_CANDIDATES'.
enum
{
  agt_interfaces__action__Relocalize_Goal__MODE_LOCAL_CANDIDATES = 2
};

/// Constant 'MODE_EXTERNAL_COARSE_POSE'.
enum
{
  agt_interfaces__action__Relocalize_Goal__MODE_EXTERNAL_COARSE_POSE = 3
};

// Include directives for member types
// Member 'initial_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_Goal
{
  uint8_t mode;
  bool use_initial_pose;
  geometry_msgs__msg__PoseWithCovarianceStamped initial_pose;
  bool use_last_valid_pose;
  bool use_configured_candidates;
  bool use_external_coarse_pose;
  uint32_t max_candidates;
  bool publish_debug;
  double timeout_s;
} agt_interfaces__action__Relocalize_Goal;

// Struct for a sequence of agt_interfaces__action__Relocalize_Goal.
typedef struct agt_interfaces__action__Relocalize_Goal__Sequence
{
  agt_interfaces__action__Relocalize_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'final_pose'
// already included above
// #include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.h"
// Member 'final_status'
#include "agt_interfaces/msg/detail/localization_status__struct.h"
// Member 'failure_reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_Result
{
  bool success;
  uint16_t error_code;
  geometry_msgs__msg__PoseWithCovarianceStamped final_pose;
  agt_interfaces__msg__LocalizationStatus final_status;
  rosidl_runtime_c__String failure_reason;
} agt_interfaces__action__Relocalize_Result;

// Struct for a sequence of agt_interfaces__action__Relocalize_Result.
typedef struct agt_interfaces__action__Relocalize_Result__Sequence
{
  agt_interfaces__action__Relocalize_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'best_candidate_source'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_Feedback
{
  uint8_t state;
  uint32_t total_candidates;
  uint32_t tested_candidates;
  double best_fitness_score;
  rosidl_runtime_c__String best_candidate_source;
  double elapsed_s;
} agt_interfaces__action__Relocalize_Feedback;

// Struct for a sequence of agt_interfaces__action__Relocalize_Feedback.
typedef struct agt_interfaces__action__Relocalize_Feedback__Sequence
{
  agt_interfaces__action__Relocalize_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/relocalize__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__Relocalize_Goal goal;
} agt_interfaces__action__Relocalize_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__Relocalize_SendGoal_Request.
typedef struct agt_interfaces__action__Relocalize_SendGoal_Request__Sequence
{
  agt_interfaces__action__Relocalize_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__Relocalize_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__Relocalize_SendGoal_Response.
typedef struct agt_interfaces__action__Relocalize_SendGoal_Response__Sequence
{
  agt_interfaces__action__Relocalize_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__Relocalize_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__Relocalize_GetResult_Request.
typedef struct agt_interfaces__action__Relocalize_GetResult_Request__Sequence
{
  agt_interfaces__action__Relocalize_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/relocalize__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__Relocalize_Result result;
} agt_interfaces__action__Relocalize_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__Relocalize_GetResult_Response.
typedef struct agt_interfaces__action__Relocalize_GetResult_Response__Sequence
{
  agt_interfaces__action__Relocalize_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/relocalize__struct.h"

/// Struct defined in action/Relocalize in the package agt_interfaces.
typedef struct agt_interfaces__action__Relocalize_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__Relocalize_Feedback feedback;
} agt_interfaces__action__Relocalize_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__Relocalize_FeedbackMessage.
typedef struct agt_interfaces__action__Relocalize_FeedbackMessage__Sequence
{
  agt_interfaces__action__Relocalize_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__Relocalize_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__STRUCT_H_
