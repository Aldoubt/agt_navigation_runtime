// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/system_health__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'components'
#include "agt_interfaces/msg/detail/component_health__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SystemHealth & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: overall_state
  {
    out << "overall_state: ";
    rosidl_generator_traits::value_to_yaml(msg.overall_state, out);
    out << ", ";
  }

  // member: revision
  {
    out << "revision: ";
    rosidl_generator_traits::value_to_yaml(msg.revision, out);
    out << ", ";
  }

  // member: components
  {
    if (msg.components.size() == 0) {
      out << "components: []";
    } else {
      out << "components: [";
      size_t pending_items = msg.components.size();
      for (auto item : msg.components) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
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
  const SystemHealth & msg,
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

  // member: overall_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overall_state: ";
    rosidl_generator_traits::value_to_yaml(msg.overall_state, out);
    out << "\n";
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

  // member: components
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.components.size() == 0) {
      out << "components: []\n";
    } else {
      out << "components:\n";
      for (auto item : msg.components) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
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

inline std::string to_yaml(const SystemHealth & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::SystemHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::SystemHealth & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::SystemHealth>()
{
  return "agt_interfaces::msg::SystemHealth";
}

template<>
inline const char * name<agt_interfaces::msg::SystemHealth>()
{
  return "agt_interfaces/msg/SystemHealth";
}

template<>
struct has_fixed_size<agt_interfaces::msg::SystemHealth>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::SystemHealth>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::SystemHealth>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__SYSTEM_HEALTH__TRAITS_HPP_
