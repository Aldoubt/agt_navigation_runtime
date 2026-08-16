// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ListMapVersions.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListMapVersions in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListMapVersions_Request
{
  rosidl_runtime_c__String map_id;
  uint8_t state;
  bool include_deleted;
} agt_interfaces__srv__ListMapVersions_Request;

// Struct for a sequence of agt_interfaces__srv__ListMapVersions_Request.
typedef struct agt_interfaces__srv__ListMapVersions_Request__Sequence
{
  agt_interfaces__srv__ListMapVersions_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListMapVersions_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ListMapVersions_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ListMapVersions_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ListMapVersions_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'versions'
#include "agt_interfaces/msg/detail/map_version_summary__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListMapVersions in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListMapVersions_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__MapVersionSummary__Sequence versions;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__ListMapVersions_Response;

// Struct for a sequence of agt_interfaces__srv__ListMapVersions_Response.
typedef struct agt_interfaces__srv__ListMapVersions_Response__Sequence
{
  agt_interfaces__srv__ListMapVersions_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListMapVersions_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_H_
