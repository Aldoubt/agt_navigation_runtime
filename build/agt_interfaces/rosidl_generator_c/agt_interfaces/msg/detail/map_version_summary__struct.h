// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATE_UNKNOWN'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_UNKNOWN = 0
};

/// Constant 'STATE_DRAFT'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_DRAFT = 1
};

/// Constant 'STATE_PROCESSING'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_PROCESSING = 2
};

/// Constant 'STATE_READY'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_READY = 3
};

/// Constant 'STATE_INVALID'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_INVALID = 4
};

/// Constant 'STATE_ARCHIVED'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_ARCHIVED = 5
};

/// Constant 'STATE_DELETED'.
enum
{
  agt_interfaces__msg__MapVersionSummary__STATE_DELETED = 6
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'map_id'
// Member 'map_version_id'
// Member 'parent_map_version_id'
// Member 'map_hash'
// Member 'manifest_sha256'
// Member 'navigation_yaml_sha256'
// Member 'navigation_image_sha256'
// Member 'localization_pcd_sha256'
// Member 'navigation_yaml'
// Member 'localization_pcd'
// Member 'processing_record'
// Member 'tasks_directory'
// Member 'created_at'
// Member 'validation_errors'
// Member 'validation_warnings'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/MapVersionSummary in the package agt_interfaces.
/**
  * Manager-owned map identity and validation summary.
 */
typedef struct agt_interfaces__msg__MapVersionSummary
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_version_id;
  rosidl_runtime_c__String parent_map_version_id;
  uint8_t state;
  bool active;
  bool pinned;
  bool deleted;
  bool valid;
  rosidl_runtime_c__String map_hash;
  rosidl_runtime_c__String manifest_sha256;
  rosidl_runtime_c__String navigation_yaml_sha256;
  rosidl_runtime_c__String navigation_image_sha256;
  rosidl_runtime_c__String localization_pcd_sha256;
  rosidl_runtime_c__String navigation_yaml;
  rosidl_runtime_c__String localization_pcd;
  rosidl_runtime_c__String processing_record;
  rosidl_runtime_c__String tasks_directory;
  uint64_t storage_bytes;
  rosidl_runtime_c__String created_at;
  rosidl_runtime_c__String__Sequence validation_errors;
  rosidl_runtime_c__String__Sequence validation_warnings;
} agt_interfaces__msg__MapVersionSummary;

// Struct for a sequence of agt_interfaces__msg__MapVersionSummary.
typedef struct agt_interfaces__msg__MapVersionSummary__Sequence
{
  agt_interfaces__msg__MapVersionSummary * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__MapVersionSummary__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_H_
