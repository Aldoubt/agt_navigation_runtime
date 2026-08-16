// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ManageBagSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_H_

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
  agt_interfaces__srv__ManageBagSession_Request__OP_STATUS = 0
};

/// Constant 'OP_START_RECORDING'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_START_RECORDING = 1
};

/// Constant 'OP_STOP_RECORDING'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_STOP_RECORDING = 2
};

/// Constant 'OP_START_PLAYBACK'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_START_PLAYBACK = 3
};

/// Constant 'OP_STOP_PLAYBACK'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_STOP_PLAYBACK = 4
};

/// Constant 'OP_CREATE_EXPERIMENT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_CREATE_EXPERIMENT = 5
};

/// Constant 'OP_COMPLETE_EXPERIMENT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_COMPLETE_EXPERIMENT = 6
};

/// Constant 'OP_INTERRUPT_EXPERIMENT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_INTERRUPT_EXPERIMENT = 7
};

/// Constant 'OP_START_EXPERIMENT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_START_EXPERIMENT = 8
};

/// Constant 'OP_MARK_EXPERIMENT_INVALID'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_MARK_EXPERIMENT_INVALID = 9
};

/// Constant 'OP_ADD_EXPERIMENT_EVENT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Request__OP_ADD_EXPERIMENT_EVENT = 10
};

// Include directives for member types
// Member 'bag_id'
// Member 'experiment_id'
// Member 'experiment_title'
// Member 'objective'
// Member 'hypothesis'
// Member 'tags_json'
// Member 'operator_note'
// Member 'profile_id'
// Member 'mission_id'
// Member 'mission_version'
// Member 'mission_sha256'
// Member 'map_id'
// Member 'map_version_id'
// Member 'map_sha256'
// Member 'platform_profile'
// Member 'calibration_profile'
// Member 'nav2_profile'
// Member 'launch_profile'
// Member 'event_type'
// Member 'metadata_json'
// Member 'result_status'
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ManageBagSession in the package agt_interfaces.
typedef struct agt_interfaces__srv__ManageBagSession_Request
{
  uint8_t operation;
  rosidl_runtime_c__String bag_id;
  rosidl_runtime_c__String experiment_id;
  rosidl_runtime_c__String experiment_title;
  rosidl_runtime_c__String objective;
  rosidl_runtime_c__String hypothesis;
  rosidl_runtime_c__String tags_json;
  rosidl_runtime_c__String operator_note;
  rosidl_runtime_c__String profile_id;
  double playback_rate;
  rosidl_runtime_c__String mission_id;
  rosidl_runtime_c__String mission_version;
  rosidl_runtime_c__String mission_sha256;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String map_sha256;
  rosidl_runtime_c__String platform_profile;
  rosidl_runtime_c__String calibration_profile;
  rosidl_runtime_c__String nav2_profile;
  rosidl_runtime_c__String launch_profile;
  bool start_experiment;
  rosidl_runtime_c__String event_type;
  rosidl_runtime_c__String metadata_json;
  rosidl_runtime_c__String result_status;
  rosidl_runtime_c__String reason;
} agt_interfaces__srv__ManageBagSession_Request;

// Struct for a sequence of agt_interfaces__srv__ManageBagSession_Request.
typedef struct agt_interfaces__srv__ManageBagSession_Request__Sequence
{
  agt_interfaces__srv__ManageBagSession_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ManageBagSession_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_NOT_FOUND'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_NOT_FOUND = 1
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_INVALID_REQUEST = 2
};

/// Constant 'ERROR_CONFLICT'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_CONFLICT = 3
};

/// Constant 'ERROR_PROFILE_INVALID'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_PROFILE_INVALID = 4
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ManageBagSession_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'session'
#include "agt_interfaces/msg/detail/bag_session_summary__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ManageBagSession in the package agt_interfaces.
typedef struct agt_interfaces__srv__ManageBagSession_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__BagSessionSummary session;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__ManageBagSession_Response;

// Struct for a sequence of agt_interfaces__srv__ManageBagSession_Response.
typedef struct agt_interfaces__srv__ManageBagSession_Response__Sequence
{
  agt_interfaces__srv__ManageBagSession_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ManageBagSession_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__STRUCT_H_
