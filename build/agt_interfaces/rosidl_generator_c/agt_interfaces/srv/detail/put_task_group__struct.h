// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/PutTaskGroup.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__PUT_TASK_GROUP__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__PUT_TASK_GROUP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'map_id'
// Member 'map_version_id'
// Member 'task_group_id'
// Member 'client_request_id'
// Member 'task_json'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/PutTaskGroup in the package agt_interfaces.
typedef struct agt_interfaces__srv__PutTaskGroup_Request
{
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String task_group_id;
  /// Current robot-side revision expected by the client. 0 means create-only.
  uint32_t expected_revision;
  rosidl_runtime_c__String client_request_id;
  rosidl_runtime_c__String task_json;
} agt_interfaces__srv__PutTaskGroup_Request;

// Struct for a sequence of agt_interfaces__srv__PutTaskGroup_Request.
typedef struct agt_interfaces__srv__PutTaskGroup_Request__Sequence
{
  agt_interfaces__srv__PutTaskGroup_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__PutTaskGroup_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_REVISION_CONFLICT'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_REVISION_CONFLICT = 2
};

/// Constant 'ERROR_CONTENT_HASH_MISMATCH'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_CONTENT_HASH_MISMATCH = 3
};

/// Constant 'ERROR_SCHEMA_INVALID'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_SCHEMA_INVALID = 4
};

/// Constant 'ERROR_MAP_NOT_READY'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_MAP_NOT_READY = 5
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__PutTaskGroup_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'blocker_code'
// Member 'operator_message'
// Member 'technical_message'
// Member 'map_id'
// Member 'map_version_id'
// Member 'task_group_id'
// Member 'content_sha256'
// Member 'task_json'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/PutTaskGroup in the package agt_interfaces.
typedef struct agt_interfaces__srv__PutTaskGroup_Response
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String blocker_code;
  rosidl_runtime_c__String operator_message;
  rosidl_runtime_c__String technical_message;
  bool duplicate_request;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String task_group_id;
  uint32_t revision;
  rosidl_runtime_c__String content_sha256;
  rosidl_runtime_c__String task_json;
} agt_interfaces__srv__PutTaskGroup_Response;

// Struct for a sequence of agt_interfaces__srv__PutTaskGroup_Response.
typedef struct agt_interfaces__srv__PutTaskGroup_Response__Sequence
{
  agt_interfaces__srv__PutTaskGroup_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__PutTaskGroup_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__PUT_TASK_GROUP__STRUCT_H_
