// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ListTaskGroups.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListTaskGroups in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListTaskGroups_Request
{
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
} agt_interfaces__srv__ListTaskGroups_Request;

// Struct for a sequence of agt_interfaces__srv__ListTaskGroups_Request.
typedef struct agt_interfaces__srv__ListTaskGroups_Request__Sequence
{
  agt_interfaces__srv__ListTaskGroups_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListTaskGroups_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ListTaskGroups_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ListTaskGroups_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_MAP_NOT_READY'.
enum
{
  agt_interfaces__srv__ListTaskGroups_Response__ERROR_MAP_NOT_READY = 2
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ListTaskGroups_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'blocker_code'
// Member 'operator_message'
// Member 'technical_message'
// Member 'map_id'
// Member 'map_version_id'
// Member 'task_group_ids'
// Member 'names'
// Member 'content_sha256'
// Member 'updated_at'
// Member 'validation_states'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'revisions'
// Member 'enabled_point_counts'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/ListTaskGroups in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListTaskGroups_Response
{
  bool success;
  uint16_t error_code;
  rosidl_runtime_c__String blocker_code;
  rosidl_runtime_c__String operator_message;
  rosidl_runtime_c__String technical_message;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String__Sequence task_group_ids;
  rosidl_runtime_c__String__Sequence names;
  rosidl_runtime_c__uint32__Sequence revisions;
  rosidl_runtime_c__String__Sequence content_sha256;
  rosidl_runtime_c__uint32__Sequence enabled_point_counts;
  rosidl_runtime_c__String__Sequence updated_at;
  rosidl_runtime_c__String__Sequence validation_states;
} agt_interfaces__srv__ListTaskGroups_Response;

// Struct for a sequence of agt_interfaces__srv__ListTaskGroups_Response.
typedef struct agt_interfaces__srv__ListTaskGroups_Response__Sequence
{
  agt_interfaces__srv__ListTaskGroups_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListTaskGroups_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__STRUCT_H_
