// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/MissionStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/mission_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MissionStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: mission_id
  {
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << ", ";
  }

  // member: mission_version
  {
    out << "mission_version: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_version, out);
    out << ", ";
  }

  // member: content_sha256
  {
    out << "content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.content_sha256, out);
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

  // member: map_manifest_sha256
  {
    out << "map_manifest_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.map_manifest_sha256, out);
    out << ", ";
  }

  // member: current_step_index
  {
    out << "current_step_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_index, out);
    out << ", ";
  }

  // member: total_steps
  {
    out << "total_steps: ";
    rosidl_generator_traits::value_to_yaml(msg.total_steps, out);
    out << ", ";
  }

  // member: current_step_id
  {
    out << "current_step_id: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_id, out);
    out << ", ";
  }

  // member: current_step_type
  {
    out << "current_step_type: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_type, out);
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

  // member: step_elapsed_s
  {
    out << "step_elapsed_s: ";
    rosidl_generator_traits::value_to_yaml(msg.step_elapsed_s, out);
    out << ", ";
  }

  // member: step_remaining_s
  {
    out << "step_remaining_s: ";
    rosidl_generator_traits::value_to_yaml(msg.step_remaining_s, out);
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
  const MissionStatus & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: mission_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << "\n";
  }

  // member: mission_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_version: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_version, out);
    out << "\n";
  }

  // member: content_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.content_sha256, out);
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

  // member: map_manifest_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_manifest_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.map_manifest_sha256, out);
    out << "\n";
  }

  // member: current_step_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_step_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_index, out);
    out << "\n";
  }

  // member: total_steps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_steps: ";
    rosidl_generator_traits::value_to_yaml(msg.total_steps, out);
    out << "\n";
  }

  // member: current_step_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_step_id: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_id, out);
    out << "\n";
  }

  // member: current_step_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_step_type: ";
    rosidl_generator_traits::value_to_yaml(msg.current_step_type, out);
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

  // member: step_elapsed_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step_elapsed_s: ";
    rosidl_generator_traits::value_to_yaml(msg.step_elapsed_s, out);
    out << "\n";
  }

  // member: step_remaining_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step_remaining_s: ";
    rosidl_generator_traits::value_to_yaml(msg.step_remaining_s, out);
    out << "\n";
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

inline std::string to_yaml(const MissionStatus & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::MissionStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::MissionStatus & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::MissionStatus>()
{
  return "agt_interfaces::msg::MissionStatus";
}

template<>
inline const char * name<agt_interfaces::msg::MissionStatus>()
{
  return "agt_interfaces/msg/MissionStatus";
}

template<>
struct has_fixed_size<agt_interfaces::msg::MissionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::MissionStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::MissionStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__MISSION_STATUS__TRAITS_HPP_
