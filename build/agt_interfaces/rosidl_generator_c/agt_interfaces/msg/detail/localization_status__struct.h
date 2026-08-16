// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'STATE_UNINITIALIZED'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_UNINITIALIZED = 0
};

/// Constant 'STATE_SEARCHING'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_SEARCHING = 1
};

/// Constant 'STATE_VERIFYING'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_VERIFYING = 2
};

/// Constant 'STATE_TRACKING'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_TRACKING = 3
};

/// Constant 'STATE_DEGRADED'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_DEGRADED = 4
};

/// Constant 'STATE_RECOVERING'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_RECOVERING = 5
};

/// Constant 'STATE_LOST'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_LOST = 6
};

/// Constant 'STATE_ERROR'.
enum
{
  agt_interfaces__msg__LocalizationStatus__STATE_ERROR = 7
};

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_NONE = 0
};

/// Constant 'ERROR_MAP_NOT_READY'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_MAP_NOT_READY = 100
};

/// Constant 'ERROR_SCAN_TOO_SMALL'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_SCAN_TOO_SMALL = 101
};

/// Constant 'ERROR_BACKEND_FAILED'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_BACKEND_FAILED = 102
};

/// Constant 'ERROR_FITNESS_REJECTED'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_FITNESS_REJECTED = 103
};

/// Constant 'ERROR_INVALID_INITIAL_GUESS'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_INVALID_INITIAL_GUESS = 104
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_INVALID_REQUEST = 105
};

/// Constant 'ERROR_TIMEOUT'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_TIMEOUT = 106
};

/// Constant 'ERROR_CANCELED'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_CANCELED = 107
};

/// Constant 'ERROR_AMBIGUOUS_RESULT'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_AMBIGUOUS_RESULT = 108
};

/// Constant 'ERROR_STALE_STATUS'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_STALE_STATUS = 109
};

/// Constant 'ERROR_TF_UNAVAILABLE'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_TF_UNAVAILABLE = 110
};

/// Constant 'ERROR_MAP_HASH_MISMATCH'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_MAP_HASH_MISMATCH = 111
};

/// Constant 'ERROR_NO_CANDIDATES'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_NO_CANDIDATES = 112
};

/// Constant 'ERROR_STALE_SCAN'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_STALE_SCAN = 113
};

/// Constant 'ERROR_INVALID_SCAN_TIMESTAMP'.
enum
{
  agt_interfaces__msg__LocalizationStatus__ERROR_INVALID_SCAN_TIMESTAMP = 114
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'backend'
// Member 'candidate_source'
// Member 'candidate_id'
// Member 'map_id'
// Member 'map_hash'
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'global_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.h"

/// Struct defined in msg/LocalizationStatus in the package agt_interfaces.
/**
  * Machine-readable global localization state. The string status topic remains
  * a human-facing compatibility channel and is not part of the control contract.
 */
typedef struct agt_interfaces__msg__LocalizationStatus
{
  std_msgs__msg__Header header;
  uint8_t state;
  bool pose_valid;
  bool localization_accepted;
  bool has_converged;
  bool ambiguous_result;
  bool status_stale;
  uint16_t error_code;
  rosidl_runtime_c__String backend;
  rosidl_runtime_c__String candidate_source;
  rosidl_runtime_c__String candidate_id;
  rosidl_runtime_c__String map_id;
  rosidl_runtime_c__String map_hash;
  /// 0 means no accepted GlobalCorrectionManager correction (or relocalization evidence).
  /// >0 is the accepted map->odom correction generation in canonical localization status.
  uint64_t correction_generation;
  geometry_msgs__msg__PoseWithCovarianceStamped global_pose;
  double fitness_score;
  double overlap_ratio;
  double inlier_ratio;
  double ambiguity_score;
  double translation_innovation;
  double yaw_innovation;
  double runtime_ms;
  uint32_t tested_candidates;
  uint32_t total_candidates;
  uint32_t consecutive_successes;
  uint32_t consecutive_failures;
  rosidl_runtime_c__String message;
} agt_interfaces__msg__LocalizationStatus;

// Struct for a sequence of agt_interfaces__msg__LocalizationStatus.
typedef struct agt_interfaces__msg__LocalizationStatus__Sequence
{
  agt_interfaces__msg__LocalizationStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__LocalizationStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__STRUCT_H_
