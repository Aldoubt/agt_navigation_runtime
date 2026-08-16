// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_H_
#define AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MODE_UNKNOWN'.
enum
{
  agt_interfaces__msg__RobotState__MODE_UNKNOWN = 0
};

/// Constant 'MODE_IDLE'.
enum
{
  agt_interfaces__msg__RobotState__MODE_IDLE = 1
};

/// Constant 'MODE_SENSOR_ONLY'.
enum
{
  agt_interfaces__msg__RobotState__MODE_SENSOR_ONLY = 2
};

/// Constant 'MODE_MAPPING'.
enum
{
  agt_interfaces__msg__RobotState__MODE_MAPPING = 3
};

/// Constant 'MODE_LOCALIZATION_DEBUG'.
enum
{
  agt_interfaces__msg__RobotState__MODE_LOCALIZATION_DEBUG = 4
};

/// Constant 'MODE_NAVIGATION'.
enum
{
  agt_interfaces__msg__RobotState__MODE_NAVIGATION = 5
};

/// Constant 'MODE_ERROR'.
enum
{
  agt_interfaces__msg__RobotState__MODE_ERROR = 6
};

/// Constant 'NAV2_UNKNOWN'.
enum
{
  agt_interfaces__msg__RobotState__NAV2_UNKNOWN = 0
};

/// Constant 'NAV2_INACTIVE'.
enum
{
  agt_interfaces__msg__RobotState__NAV2_INACTIVE = 1
};

/// Constant 'NAV2_ACTIVE'.
enum
{
  agt_interfaces__msg__RobotState__NAV2_ACTIVE = 2
};

/// Constant 'NAV2_ERROR'.
enum
{
  agt_interfaces__msg__RobotState__NAV2_ERROR = 3
};

/// Constant 'CHASSIS_MODE_UNKNOWN'.
enum
{
  agt_interfaces__msg__RobotState__CHASSIS_MODE_UNKNOWN = 0
};

/// Constant 'CHASSIS_MODE_MONITOR'.
enum
{
  agt_interfaces__msg__RobotState__CHASSIS_MODE_MONITOR = 1
};

/// Constant 'CHASSIS_MODE_CONTROL'.
enum
{
  agt_interfaces__msg__RobotState__CHASSIS_MODE_CONTROL = 2
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'active_profile'
// Member 'blocker_codes'
// Member 'blocker_messages'
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'system_health'
#include "agt_interfaces/msg/detail/system_health__struct.h"
// Member 'task_readiness'
#include "agt_interfaces/msg/detail/task_readiness__struct.h"
// Member 'active_map'
#include "agt_interfaces/msg/detail/map_version_summary__struct.h"
// Member 'localization'
#include "agt_interfaces/msg/detail/localization_status__struct.h"
// Member 'mission'
#include "agt_interfaces/msg/detail/mission_status__struct.h"
// Member 'bag_session'
#include "agt_interfaces/msg/detail/bag_session_summary__struct.h"

/// Struct defined in msg/RobotState in the package agt_interfaces.
/**
  * Unified read model for interchangeable operator clients.
 */
typedef struct agt_interfaces__msg__RobotState
{
  std_msgs__msg__Header header;
  uint64_t revision;
  uint8_t system_mode;
  rosidl_runtime_c__String active_profile;
  uint32_t managed_process_count;
  uint32_t running_process_count;
  bool system_health_known;
  double system_health_freshness_s;
  agt_interfaces__msg__SystemHealth system_health;
  bool task_readiness_known;
  double task_readiness_freshness_s;
  agt_interfaces__msg__TaskReadiness task_readiness;
  bool active_map_known;
  double active_map_freshness_s;
  agt_interfaces__msg__MapVersionSummary active_map;
  bool localization_status_known;
  double localization_freshness_s;
  agt_interfaces__msg__LocalizationStatus localization;
  bool mission_status_known;
  double mission_freshness_s;
  agt_interfaces__msg__MissionStatus mission;
  uint8_t nav2_state;
  double nav2_freshness_s;
  bool safety_status_known;
  bool safety_motion_enabled;
  bool emergency_stop;
  bool estop_latched;
  bool navigation_ready;
  double safety_freshness_s;
  bool chassis_status_known;
  bool chassis_connected;
  uint8_t chassis_control_mode;
  double chassis_status_freshness_s;
  double chassis_odometry_freshness_s;
  bool bag_status_known;
  double bag_freshness_s;
  agt_interfaces__msg__BagSessionSummary bag_session;
  uint16_t error_code;
  rosidl_runtime_c__String__Sequence blocker_codes;
  rosidl_runtime_c__String__Sequence blocker_messages;
  rosidl_runtime_c__String message;
} agt_interfaces__msg__RobotState;

// Struct for a sequence of agt_interfaces__msg__RobotState.
typedef struct agt_interfaces__msg__RobotState__Sequence
{
  agt_interfaces__msg__RobotState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__msg__RobotState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__STRUCT_H_
