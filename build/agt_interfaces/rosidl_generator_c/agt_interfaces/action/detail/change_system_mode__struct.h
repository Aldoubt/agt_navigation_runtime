// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/ChangeSystemMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_IDLE'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_IDLE = 0
};

/// Constant 'MODE_SENSOR_ONLY'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_SENSOR_ONLY = 1
};

/// Constant 'MODE_MAPPING'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_MAPPING = 2
};

/// Constant 'MODE_LOCALIZATION_DEBUG'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_LOCALIZATION_DEBUG = 3
};

/// Constant 'MODE_NAVIGATION'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_NAVIGATION = 4
};

/// Constant 'MODE_ERROR'.
enum
{
  agt_interfaces__action__ChangeSystemMode_Goal__MODE_ERROR = 5
};

// Include directives for member types
// Member 'profile'
// Member 'argument_keys'
// Member 'argument_values'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_Goal
{
  uint8_t mode;
  rosidl_runtime_c__String profile;
  rosidl_runtime_c__String__Sequence argument_keys;
  rosidl_runtime_c__String__Sequence argument_values;
  bool wait_for_health;
  double startup_timeout_s;
} agt_interfaces__action__ChangeSystemMode_Goal;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_Goal.
typedef struct agt_interfaces__action__ChangeSystemMode_Goal__Sequence
{
  agt_interfaces__action__ChangeSystemMode_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'active_mode'
// Member 'profile'
// Member 'log_paths'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'process_ids'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_Result
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String active_mode;
  rosidl_runtime_c__String profile;
  rosidl_runtime_c__int32__Sequence process_ids;
  rosidl_runtime_c__String__Sequence log_paths;
  rosidl_runtime_c__String message;
} agt_interfaces__action__ChangeSystemMode_Result;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_Result.
typedef struct agt_interfaces__action__ChangeSystemMode_Result__Sequence
{
  agt_interfaces__action__ChangeSystemMode_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_Feedback
{
  rosidl_runtime_c__String state;
  float progress;
  rosidl_runtime_c__String message;
} agt_interfaces__action__ChangeSystemMode_Feedback;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_Feedback.
typedef struct agt_interfaces__action__ChangeSystemMode_Feedback__Sequence
{
  agt_interfaces__action__ChangeSystemMode_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/change_system_mode__struct.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ChangeSystemMode_Goal goal;
} agt_interfaces__action__ChangeSystemMode_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_SendGoal_Request.
typedef struct agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence
{
  agt_interfaces__action__ChangeSystemMode_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__ChangeSystemMode_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_SendGoal_Response.
typedef struct agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence
{
  agt_interfaces__action__ChangeSystemMode_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__ChangeSystemMode_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_GetResult_Request.
typedef struct agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence
{
  agt_interfaces__action__ChangeSystemMode_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/change_system_mode__struct.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__ChangeSystemMode_Result result;
} agt_interfaces__action__ChangeSystemMode_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_GetResult_Response.
typedef struct agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence
{
  agt_interfaces__action__ChangeSystemMode_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/change_system_mode__struct.h"

/// Struct defined in action/ChangeSystemMode in the package agt_interfaces.
typedef struct agt_interfaces__action__ChangeSystemMode_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ChangeSystemMode_Feedback feedback;
} agt_interfaces__action__ChangeSystemMode_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__ChangeSystemMode_FeedbackMessage.
typedef struct agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence
{
  agt_interfaces__action__ChangeSystemMode_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__STRUCT_H_
