// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:action/ManageMappingSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__STRUCT_H_
#define AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'OP_STATUS'.
enum
{
  agt_interfaces__action__ManageMappingSession_Goal__OP_STATUS = 0
};

/// Constant 'OP_START'.
enum
{
  agt_interfaces__action__ManageMappingSession_Goal__OP_START = 1
};

/// Constant 'OP_FINALIZE_CAPTURE'.
enum
{
  agt_interfaces__action__ManageMappingSession_Goal__OP_FINALIZE_CAPTURE = 2
};

/// Constant 'OP_COMMIT'.
enum
{
  agt_interfaces__action__ManageMappingSession_Goal__OP_COMMIT = 3
};

/// Constant 'OP_DISCARD'.
enum
{
  agt_interfaces__action__ManageMappingSession_Goal__OP_DISCARD = 4
};

// Include directives for member types
// Member 'map_id'
// Member 'session_id'
// Member 'argument_keys'
// Member 'argument_values'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_Goal
{
  uint8_t operation;
  /// Required for START. A safe portable identifier, not a filesystem path.
  rosidl_runtime_c__String map_id;
  /// Required for operations on an existing session. STATUS may leave it empty to
  /// query the newest managed session.
  rosidl_runtime_c__String session_id;
  /// START-only mapping profile arguments. The server injects and owns runtime_dir,
  /// map_name, mapping_output_dir, record_bag, and bag_profile.
  rosidl_runtime_c__String__Sequence argument_keys;
  rosidl_runtime_c__String__Sequence argument_values;
  /// COMMIT-only. Activation still performs the full map-registry validation.
  bool activate_after_commit;
  /// Bounded wait for map save, normal shutdown, PCD readiness, and offline candidate build.
  double timeout_s;
} agt_interfaces__action__ManageMappingSession_Goal;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_Goal.
typedef struct agt_interfaces__action__ManageMappingSession_Goal__Sequence
{
  agt_interfaces__action__ManageMappingSession_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_Goal__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_SERVER_UNAVAILABLE'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_SERVER_UNAVAILABLE = 2
};

/// Constant 'ERROR_START_FAILED'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_START_FAILED = 3
};

/// Constant 'ERROR_GRID_SAVE_FAILED'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_GRID_SAVE_FAILED = 4
};

/// Constant 'ERROR_STOP_FAILED'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_STOP_FAILED = 5
};

/// Constant 'ERROR_ASSET_TIMEOUT'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_ASSET_TIMEOUT = 6
};

/// Constant 'ERROR_COMMIT_FAILED'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_COMMIT_FAILED = 7
};

/// Constant 'ERROR_INVALID_STATE'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_INVALID_STATE = 8
};

/// Constant 'ERROR_NOT_FOUND'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_NOT_FOUND = 9
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__action__ManageMappingSession_Result__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'state'
// Member 'session_id'
// Member 'map_id'
// Member 'map_version_id'
// Member 'session_file'
// Member 'candidate_map_yaml'
// Member 'candidate_map_image'
// Member 'localization_pcd'
// Member 'processing_record'
// Member 'bag_directory'
// Member 'registered_map_yaml'
// Member 'tasks_directory'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_Result
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String state;
  rosidl_runtime_c__String session_id;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String session_file;
  rosidl_runtime_c__String candidate_map_yaml;
  rosidl_runtime_c__String candidate_map_image;
  rosidl_runtime_c__String localization_pcd;
  rosidl_runtime_c__String processing_record;
  rosidl_runtime_c__String bag_directory;
  rosidl_runtime_c__String registered_map_yaml;
  rosidl_runtime_c__String tasks_directory;
  rosidl_runtime_c__String message;
} agt_interfaces__action__ManageMappingSession_Result;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_Result.
typedef struct agt_interfaces__action__ManageMappingSession_Result__Sequence
{
  agt_interfaces__action__ManageMappingSession_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'state'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_Feedback
{
  rosidl_runtime_c__String state;
  float progress;
  rosidl_runtime_c__String message;
} agt_interfaces__action__ManageMappingSession_Feedback;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_Feedback.
typedef struct agt_interfaces__action__ManageMappingSession_Feedback__Sequence
{
  agt_interfaces__action__ManageMappingSession_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "agt_interfaces/action/detail/manage_mapping_session__struct.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ManageMappingSession_Goal goal;
} agt_interfaces__action__ManageMappingSession_SendGoal_Request;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_SendGoal_Request.
typedef struct agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence
{
  agt_interfaces__action__ManageMappingSession_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} agt_interfaces__action__ManageMappingSession_SendGoal_Response;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_SendGoal_Response.
typedef struct agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence
{
  agt_interfaces__action__ManageMappingSession_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} agt_interfaces__action__ManageMappingSession_GetResult_Request;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_GetResult_Request.
typedef struct agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence
{
  agt_interfaces__action__ManageMappingSession_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_GetResult_Response
{
  int8_t status;
  agt_interfaces__action__ManageMappingSession_Result result;
} agt_interfaces__action__ManageMappingSession_GetResult_Response;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_GetResult_Response.
typedef struct agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence
{
  agt_interfaces__action__ManageMappingSession_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__struct.h"

/// Struct defined in action/ManageMappingSession in the package agt_interfaces.
typedef struct agt_interfaces__action__ManageMappingSession_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  agt_interfaces__action__ManageMappingSession_Feedback feedback;
} agt_interfaces__action__ManageMappingSession_FeedbackMessage;

// Struct for a sequence of agt_interfaces__action__ManageMappingSession_FeedbackMessage.
typedef struct agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence
{
  agt_interfaces__action__ManageMappingSession_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__STRUCT_H_
