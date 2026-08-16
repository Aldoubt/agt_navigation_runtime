// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'mission_id'
// Member 'mission_version'
// Member 'expected_content_sha256'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_Goal
{
  rosidl_runtime_c__String mission_id;
  rosidl_runtime_c__String mission_version;
  /// Optional optimistic-lock check. Empty accepts the stored content hash.
  rosidl_runtime_c__String expected_content_sha256;
} agt_interfaces__action__ExecuteMission_Goal;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_Goal.
typedef struct agt_interfaces__action__ExecuteMission_Goal__Sequence
{
  agt_interfaces__action__ExecuteMission_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'final_status'
#include "agt_interfaces/msg/detail/mission_status__struct.h"
// Member 'audit_log_uri'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_Result
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__MissionStatus final_status;
  rosidl_runtime_c__String audit_log_uri;
  rosidl_runtime_c__String message;
} agt_interfaces__action__ExecuteMission_Result;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_Result.
typedef struct agt_interfaces__action__ExecuteMission_Result__Sequence
{
  agt_interfaces__action__ExecuteMission_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
// already included above
// #include "agt_interfaces/msg/detail/mission_status__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_Feedback
{
  agt_interfaces__msg__MissionStatus status;
} agt_interfaces__action__ExecuteMission_Feedback;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_Feedback.
typedef struct agt_interfaces__action__ExecuteMission_Feedback__Sequence
{
  agt_interfaces__action__ExecuteMission_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteMission_Goal goal;
} agt_interfaces__action__ExecuteMission_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_SendGoal_Request.
typedef struct agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence
{
  agt_interfaces__action__ExecuteMission_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__ExecuteMission_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_SendGoal_Response.
typedef struct agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence
{
  agt_interfaces__action__ExecuteMission_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__ExecuteMission_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_GetResult_Request.
typedef struct agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence
{
  agt_interfaces__action__ExecuteMission_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__ExecuteMission_Result result;
} agt_interfaces__action__ExecuteMission_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_GetResult_Response.
typedef struct agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence
{
  agt_interfaces__action__ExecuteMission_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.h"

/// Struct defined in action/ExecuteMission in the package agt_interfaces.
typedef struct agt_interfaces__action__ExecuteMission_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ExecuteMission_Feedback feedback;
} agt_interfaces__action__ExecuteMission_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__ExecuteMission_FeedbackMessage.
typedef struct agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence
{
  agt_interfaces__action__ExecuteMission_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_MISSION__STRUCT_H_
