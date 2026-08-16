// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/NavigationSessionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/navigation_session_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'started_at'
// Member 'updated_at'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const NavigationSessionStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: session_id
  {
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
    out << ", ";
  }

  // member: client_request_id
  {
    out << "client_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_request_id, out);
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << ", ";
  }

  // member: map_version_id
  {
    out << "map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_version_id, out);
    out << ", ";
  }

  // member: task_group_id
  {
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << ", ";
  }

  // member: task_revision
  {
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
    out << ", ";
  }

  // member: task_content_sha256
  {
    out << "task_content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.task_content_sha256, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: loop_index
  {
    out << "loop_index: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_index, out);
    out << ", ";
  }

  // member: current_waypoint
  {
    out << "current_waypoint: ";
    rosidl_generator_traits::value_to_yaml(msg.current_waypoint, out);
    out << ", ";
  }

  // member: total_waypoints
  {
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
    out << ", ";
  }

  // member: missed_waypoints
  {
    if (msg.missed_waypoints.size() == 0) {
      out << "missed_waypoints: []";
    } else {
      out << "missed_waypoints: [";
      size_t pending_items = msg.missed_waypoints.size();
      for (auto item : msg.missed_waypoints) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: blocker_code
  {
    out << "blocker_code: ";
    rosidl_generator_traits::value_to_yaml(msg.blocker_code, out);
    out << ", ";
  }

  // member: operator_message
  {
    out << "operator_message: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_message, out);
    out << ", ";
  }

  // member: technical_message
  {
    out << "technical_message: ";
    rosidl_generator_traits::value_to_yaml(msg.technical_message, out);
    out << ", ";
  }

  // member: started_at
  {
    out << "started_at: ";
    to_flow_style_yaml(msg.started_at, out);
    out << ", ";
  }

  // member: updated_at
  {
    out << "updated_at: ";
    to_flow_style_yaml(msg.updated_at, out);
    out << ", ";
  }

  // member: terminal
  {
    out << "terminal: ";
    rosidl_generator_traits::value_to_yaml(msg.terminal, out);
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const NavigationSessionStatus & msg,
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

  // member: session_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
    out << "\n";
  }

  // member: client_request_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "client_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_request_id, out);
    out << "\n";
  }

  // member: map_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << "\n";
  }

  // member: map_version_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_version_id, out);
    out << "\n";
  }

  // member: task_group_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << "\n";
  }

  // member: task_revision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
    out << "\n";
  }

  // member: task_content_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.task_content_sha256, out);
    out << "\n";
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: loop_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loop_index: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_index, out);
    out << "\n";
  }

  // member: current_waypoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_waypoint: ";
    rosidl_generator_traits::value_to_yaml(msg.current_waypoint, out);
    out << "\n";
  }

  // member: total_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
    out << "\n";
  }

  // member: missed_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.missed_waypoints.size() == 0) {
      out << "missed_waypoints: []\n";
    } else {
      out << "missed_waypoints:\n";
      for (auto item : msg.missed_waypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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

  // member: blocker_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "blocker_code: ";
    rosidl_generator_traits::value_to_yaml(msg.blocker_code, out);
    out << "\n";
  }

  // member: operator_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operator_message: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_message, out);
    out << "\n";
  }

  // member: technical_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "technical_message: ";
    rosidl_generator_traits::value_to_yaml(msg.technical_message, out);
    out << "\n";
  }

  // member: started_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "started_at:\n";
    to_block_style_yaml(msg.started_at, out, indentation + 2);
  }

  // member: updated_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "updated_at:\n";
    to_block_style_yaml(msg.updated_at, out, indentation + 2);
  }

  // member: terminal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "terminal: ";
    rosidl_generator_traits::value_to_yaml(msg.terminal, out);
    out << "\n";
  }

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const NavigationSessionStatus & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::NavigationSessionStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::NavigationSessionStatus & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::NavigationSessionStatus>()
{
  return "agt_interfaces::msg::NavigationSessionStatus";
}

template<>
inline const char * name<agt_interfaces::msg::NavigationSessionStatus>()
{
  return "agt_interfaces/msg/NavigationSessionStatus";
}

template<>
struct has_fixed_size<agt_interfaces::msg::NavigationSessionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::NavigationSessionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::NavigationSessionStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__NAVIGATION_SESSION_STATUS__TRAITS_HPP_
