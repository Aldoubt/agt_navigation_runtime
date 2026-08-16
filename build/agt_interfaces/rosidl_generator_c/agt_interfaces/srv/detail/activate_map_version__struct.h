// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__STRUCT_H_

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
// Member 'client_request_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ActivateMapVersion in the package agt_interfaces.
typedef struct agt_interfaces__srv__ActivateMapVersion_Request
{
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String client_request_id;
} agt_interfaces__srv__ActivateMapVersion_Request;

// Struct for a sequence of agt_interfaces__srv__ActivateMapVersion_Request.
typedef struct agt_interfaces__srv__ActivateMapVersion_Request__Sequence
{
  agt_interfaces__srv__ActivateMapVersion_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ActivateMapVersion_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ActivateMapVersion_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ActivateMapVersion_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_NOT_FOUND'.
enum
{
  agt_interfaces__srv__ActivateMapVersion_Response__ERROR_NOT_FOUND = 2
};

/// Constant 'ERROR_VALIDATION_FAILED'.
enum
{
  agt_interfaces__srv__ActivateMapVersion_Response__ERROR_VALIDATION_FAILED = 3
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ActivateMapVersion_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'map_id'
// Member 'map_version_id'
// Member 'state'
// Member 'blocker_codes'
// Member 'blocker_messages'
// Member 'operator_messages'
// Member 'technical_messages'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'version'
#include "agt_interfaces/msg/detail/map_version_summary__struct.h"

/// Struct defined in srv/ActivateMapVersion in the package agt_interfaces.
typedef struct agt_interfaces__srv__ActivateMapVersion_Response
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String state;
  rosidl_runtime_c__String__Sequence blocker_codes;
  rosidl_runtime_c__String__Sequence blocker_messages;
  rosidl_runtime_c__String__Sequence operator_messages;
  rosidl_runtime_c__String__Sequence technical_messages;
  agt_interfaces__msg__MapVersionSummary version;
} agt_interfaces__srv__ActivateMapVersion_Response;

// Struct for a sequence of agt_interfaces__srv__ActivateMapVersion_Response.
typedef struct agt_interfaces__srv__ActivateMapVersion_Response__Sequence
{
  agt_interfaces__srv__ActivateMapVersion_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ActivateMapVersion_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__STRUCT_H_
