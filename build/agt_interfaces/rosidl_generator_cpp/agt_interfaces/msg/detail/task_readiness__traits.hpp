// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/TaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/task_readiness__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TaskReadiness & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: ready
  {
    out << "ready: ";
    rosidl_generator_traits::value_to_yaml(msg.ready, out);
    out << ", ";
  }

  // member: active_mode
  {
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
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

  // member: localization_state
  {
    out << "localization_state: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_state, out);
    out << ", ";
  }

  // member: health_revision
  {
    out << "health_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.health_revision, out);
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

  // member: warning_codes
  {
    if (msg.warning_codes.size() == 0) {
      out << "warning_codes: []";
    } else {
      out << "warning_codes: [";
      size_t pending_items = msg.warning_codes.size();
      for (auto item : msg.warning_codes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: warning_messages
  {
    if (msg.warning_messages.size() == 0) {
      out << "warning_messages: []";
    } else {
      out << "warning_messages: [";
      size_t pending_items = msg.warning_messages.size();
      for (auto item : msg.warning_messages) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TaskReadiness & msg,
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

  // member: ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ready: ";
    rosidl_generator_traits::value_to_yaml(msg.ready, out);
    out << "\n";
  }

  // member: active_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
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

  // member: localization_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_state: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_state, out);
    out << "\n";
  }

  // member: health_revision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "health_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.health_revision, out);
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

  // member: warning_codes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.warning_codes.size() == 0) {
      out << "warning_codes: []\n";
    } else {
      out << "warning_codes:\n";
      for (auto item : msg.warning_codes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: warning_messages
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.warning_messages.size() == 0) {
      out << "warning_messages: []\n";
    } else {
      out << "warning_messages:\n";
      for (auto item : msg.warning_messages) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TaskReadiness & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::TaskReadiness & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::TaskReadiness & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::TaskReadiness>()
{
  return "agt_interfaces::msg::TaskReadiness";
}

template<>
inline const char * name<agt_interfaces::msg::TaskReadiness>()
{
  return "agt_interfaces/msg/TaskReadiness";
}

template<>
struct has_fixed_size<agt_interfaces::msg::TaskReadiness>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::TaskReadiness>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::TaskReadiness>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__TASK_READINESS__TRAITS_HPP_
