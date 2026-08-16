// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ManageMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'OP_GET_ACTIVE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_GET_ACTIVE = 0
};

/// Constant 'OP_VALIDATE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_VALIDATE = 1
};

/// Constant 'OP_ACTIVATE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_ACTIVATE = 2
};

/// Constant 'OP_PIN'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_PIN = 3
};

/// Constant 'OP_UNPIN'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_UNPIN = 4
};

/// Constant 'OP_ARCHIVE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_ARCHIVE = 5
};

/// Constant 'OP_SOFT_DELETE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_SOFT_DELETE = 6
};

/// Constant 'OP_PURGE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_PURGE = 7
};

/// Constant 'OP_IMPORT_CANDIDATE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Request__OP_IMPORT_CANDIDATE = 8
};

// Include directives for member types
// Member 'map_version_id'
// Member 'map_id'
// Member 'candidate_map_yaml'
// Member 'localization_pcd'
// Member 'processing_record'
// Member 'platform_profile'
// Member 'parent_map_version_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ManageMapVersion in the package agt_interfaces.
typedef struct agt_interfaces__srv__ManageMapVersion_Request
{
  uint8_t operation;
  rosidl_runtime_c__String map_version_id;
  bool confirm_destructive;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String candidate_map_yaml;
  rosidl_runtime_c__String localization_pcd;
  rosidl_runtime_c__String processing_record;
  rosidl_runtime_c__String platform_profile;
  rosidl_runtime_c__String parent_map_version_id;
} agt_interfaces__srv__ManageMapVersion_Request;

// Struct for a sequence of agt_interfaces__srv__ManageMapVersion_Request.
typedef struct agt_interfaces__srv__ManageMapVersion_Request__Sequence
{
  agt_interfaces__srv__ManageMapVersion_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ManageMapVersion_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_NOT_FOUND'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_NOT_FOUND = 1
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_INVALID_REQUEST = 2
};

/// Constant 'ERROR_CONFLICT'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_CONFLICT = 3
};

/// Constant 'ERROR_VALIDATION_FAILED'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_VALIDATION_FAILED = 4
};

/// Constant 'ERROR_CONFIRMATION_REQUIRED'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_CONFIRMATION_REQUIRED = 5
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ManageMapVersion_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'version'
#include "agt_interfaces/msg/detail/map_version_summary__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ManageMapVersion in the package agt_interfaces.
typedef struct agt_interfaces__srv__ManageMapVersion_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__MapVersionSummary version;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__ManageMapVersion_Response;

// Struct for a sequence of agt_interfaces__srv__ManageMapVersion_Response.
typedef struct agt_interfaces__srv__ManageMapVersion_Response__Sequence
{
  agt_interfaces__srv__ManageMapVersion_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ManageMapVersion_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_H_
