// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/RobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/robot_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'system_health'
#include "agt_interfaces/msg/detail/system_health__traits.hpp"
// Member 'task_readiness'
#include "agt_interfaces/msg/detail/task_readiness__traits.hpp"
// Member 'active_map'
#include "agt_interfaces/msg/detail/map_version_summary__traits.hpp"
// Member 'localization'
#include "agt_interfaces/msg/detail/localization_status__traits.hpp"
// Member 'mission'
#include "agt_interfaces/msg/detail/mission_status__traits.hpp"
// Member 'bag_session'
#include "agt_interfaces/msg/detail/bag_session_summary__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: revision
  {
    out << "revision: ";
    rosidl_generator_traits::value_to_yaml(msg.revision, out);
    out << ", ";
  }

  // member: system_mode
  {
    out << "system_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.system_mode, out);
    out << ", ";
  }

  // member: active_profile
  {
    out << "active_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.active_profile, out);
    out << ", ";
  }

  // member: managed_process_count
  {
    out << "managed_process_count: ";
    rosidl_generator_traits::value_to_yaml(msg.managed_process_count, out);
    out << ", ";
  }

  // member: running_process_count
  {
    out << "running_process_count: ";
    rosidl_generator_traits::value_to_yaml(msg.running_process_count, out);
    out << ", ";
  }

  // member: system_health_known
  {
    out << "system_health_known: ";
    rosidl_generator_traits::value_to_yaml(msg.system_health_known, out);
    out << ", ";
  }

  // member: system_health_freshness_s
  {
    out << "system_health_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.system_health_freshness_s, out);
    out << ", ";
  }

  // member: system_health
  {
    out << "system_health: ";
    to_flow_style_yaml(msg.system_health, out);
    out << ", ";
  }

  // member: task_readiness_known
  {
    out << "task_readiness_known: ";
    rosidl_generator_traits::value_to_yaml(msg.task_readiness_known, out);
    out << ", ";
  }

  // member: task_readiness_freshness_s
  {
    out << "task_readiness_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.task_readiness_freshness_s, out);
    out << ", ";
  }

  // member: task_readiness
  {
    out << "task_readiness: ";
    to_flow_style_yaml(msg.task_readiness, out);
    out << ", ";
  }

  // member: active_map_known
  {
    out << "active_map_known: ";
    rosidl_generator_traits::value_to_yaml(msg.active_map_known, out);
    out << ", ";
  }

  // member: active_map_freshness_s
  {
    out << "active_map_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.active_map_freshness_s, out);
    out << ", ";
  }

  // member: active_map
  {
    out << "active_map: ";
    to_flow_style_yaml(msg.active_map, out);
    out << ", ";
  }

  // member: localization_status_known
  {
    out << "localization_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_status_known, out);
    out << ", ";
  }

  // member: localization_freshness_s
  {
    out << "localization_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_freshness_s, out);
    out << ", ";
  }

  // member: localization
  {
    out << "localization: ";
    to_flow_style_yaml(msg.localization, out);
    out << ", ";
  }

  // member: mission_status_known
  {
    out << "mission_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_status_known, out);
    out << ", ";
  }

  // member: mission_freshness_s
  {
    out << "mission_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_freshness_s, out);
    out << ", ";
  }

  // member: mission
  {
    out << "mission: ";
    to_flow_style_yaml(msg.mission, out);
    out << ", ";
  }

  // member: nav2_state
  {
    out << "nav2_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_state, out);
    out << ", ";
  }

  // member: nav2_freshness_s
  {
    out << "nav2_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_freshness_s, out);
    out << ", ";
  }

  // member: safety_status_known
  {
    out << "safety_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_status_known, out);
    out << ", ";
  }

  // member: safety_motion_enabled
  {
    out << "safety_motion_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_motion_enabled, out);
    out << ", ";
  }

  // member: emergency_stop
  {
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
    out << ", ";
  }

  // member: estop_latched
  {
    out << "estop_latched: ";
    rosidl_generator_traits::value_to_yaml(msg.estop_latched, out);
    out << ", ";
  }

  // member: navigation_ready
  {
    out << "navigation_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_ready, out);
    out << ", ";
  }

  // member: safety_freshness_s
  {
    out << "safety_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_freshness_s, out);
    out << ", ";
  }

  // member: chassis_status_known
  {
    out << "chassis_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_status_known, out);
    out << ", ";
  }

  // member: chassis_connected
  {
    out << "chassis_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_connected, out);
    out << ", ";
  }

  // member: chassis_control_mode
  {
    out << "chassis_control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_control_mode, out);
    out << ", ";
  }

  // member: chassis_status_freshness_s
  {
    out << "chassis_status_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_status_freshness_s, out);
    out << ", ";
  }

  // member: chassis_odometry_freshness_s
  {
    out << "chassis_odometry_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_odometry_freshness_s, out);
    out << ", ";
  }

  // member: bag_status_known
  {
    out << "bag_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_status_known, out);
    out << ", ";
  }

  // member: bag_freshness_s
  {
    out << "bag_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_freshness_s, out);
    out << ", ";
  }

  // member: bag_session
  {
    out << "bag_session: ";
    to_flow_style_yaml(msg.bag_session, out);
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: blocker_codes
  {
    if (msg.blocker_codes.size() == 0) {
      out << "blocker_codes: []";
    } else {
      out << "blocker_codes: [";
      size_t pending_items = msg.blocker_codes.size();
      for (auto item : msg.blocker_codes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: blocker_messages
  {
    if (msg.blocker_messages.size() == 0) {
      out << "blocker_messages: []";
    } else {
      out << "blocker_messages: [";
      size_t pending_items = msg.blocker_messages.size();
      for (auto item : msg.blocker_messages) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: revision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "revision: ";
    rosidl_generator_traits::value_to_yaml(msg.revision, out);
    out << "\n";
  }

  // member: system_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.system_mode, out);
    out << "\n";
  }

  // member: active_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.active_profile, out);
    out << "\n";
  }

  // member: managed_process_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "managed_process_count: ";
    rosidl_generator_traits::value_to_yaml(msg.managed_process_count, out);
    out << "\n";
  }

  // member: running_process_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "running_process_count: ";
    rosidl_generator_traits::value_to_yaml(msg.running_process_count, out);
    out << "\n";
  }

  // member: system_health_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_health_known: ";
    rosidl_generator_traits::value_to_yaml(msg.system_health_known, out);
    out << "\n";
  }

  // member: system_health_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_health_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.system_health_freshness_s, out);
    out << "\n";
  }

  // member: system_health
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "system_health:\n";
    to_block_style_yaml(msg.system_health, out, indentation + 2);
  }

  // member: task_readiness_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_readiness_known: ";
    rosidl_generator_traits::value_to_yaml(msg.task_readiness_known, out);
    out << "\n";
  }

  // member: task_readiness_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_readiness_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.task_readiness_freshness_s, out);
    out << "\n";
  }

  // member: task_readiness
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_readiness:\n";
    to_block_style_yaml(msg.task_readiness, out, indentation + 2);
  }

  // member: active_map_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_map_known: ";
    rosidl_generator_traits::value_to_yaml(msg.active_map_known, out);
    out << "\n";
  }

  // member: active_map_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_map_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.active_map_freshness_s, out);
    out << "\n";
  }

  // member: active_map
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_map:\n";
    to_block_style_yaml(msg.active_map, out, indentation + 2);
  }

  // member: localization_status_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_status_known, out);
    out << "\n";
  }

  // member: localization_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_freshness_s, out);
    out << "\n";
  }

  // member: localization
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization:\n";
    to_block_style_yaml(msg.localization, out, indentation + 2);
  }

  // member: mission_status_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_status_known, out);
    out << "\n";
  }

  // member: mission_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_freshness_s, out);
    out << "\n";
  }

  // member: mission
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission:\n";
    to_block_style_yaml(msg.mission, out, indentation + 2);
  }

  // member: nav2_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nav2_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_state, out);
    out << "\n";
  }

  // member: nav2_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nav2_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_freshness_s, out);
    out << "\n";
  }

  // member: safety_status_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "safety_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_status_known, out);
    out << "\n";
  }

  // member: safety_motion_enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "safety_motion_enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_motion_enabled, out);
    out << "\n";
  }

  // member: emergency_stop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
    out << "\n";
  }

  // member: estop_latched
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estop_latched: ";
    rosidl_generator_traits::value_to_yaml(msg.estop_latched, out);
    out << "\n";
  }

  // member: navigation_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "navigation_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_ready, out);
    out << "\n";
  }

  // member: safety_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "safety_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.safety_freshness_s, out);
    out << "\n";
  }

  // member: chassis_status_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_status_known, out);
    out << "\n";
  }

  // member: chassis_connected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_connected: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_connected, out);
    out << "\n";
  }

  // member: chassis_control_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_control_mode, out);
    out << "\n";
  }

  // member: chassis_status_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_status_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_status_freshness_s, out);
    out << "\n";
  }

  // member: chassis_odometry_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "chassis_odometry_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.chassis_odometry_freshness_s, out);
    out << "\n";
  }

  // member: bag_status_known
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bag_status_known: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_status_known, out);
    out << "\n";
  }

  // member: bag_freshness_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bag_freshness_s: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_freshness_s, out);
    out << "\n";
  }

  // member: bag_session
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bag_session:\n";
    to_block_style_yaml(msg.bag_session, out, indentation + 2);
  }

  // member: error_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << "\n";
  }

  // member: blocker_codes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.blocker_codes.size() == 0) {
      out << "blocker_codes: []\n";
    } else {
      out << "blocker_codes:\n";
      for (auto item : msg.blocker_codes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: blocker_messages
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.blocker_messages.size() == 0) {
      out << "blocker_messages: []\n";
    } else {
      out << "blocker_messages:\n";
      for (auto item : msg.blocker_messages) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::msg::RobotState & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::RobotState & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::RobotState>()
{
  return "agt_interfaces::msg::RobotState";
}

template<>
inline const char * name<agt_interfaces::msg::RobotState>()
{
  return "agt_interfaces/msg/RobotState";
}

template<>
struct has_fixed_size<agt_interfaces::msg::RobotState>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::RobotState>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::RobotState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__ROBOT_STATE__TRAITS_HPP_
