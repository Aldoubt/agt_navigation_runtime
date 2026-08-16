// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/component_health__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ComponentHealth & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: component_id
  {
    out << "component_id: ";
    rosidl_generator_traits::value_to_yaml(msg.component_id, out);
    out << ", ";
  }

  // member: display_name
  {
    out << "display_name: ";
    rosidl_generator_traits::value_to_yaml(msg.display_name, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: required
  {
    out << "required: ";
    rosidl_generator_traits::value_to_yaml(msg.required, out);
    out << ", ";
  }

  // member: present
  {
    out << "present: ";
    rosidl_generator_traits::value_to_yaml(msg.present, out);
    out << ", ";
  }

  // member: observed_rate_hz
  {
    out << "observed_rate_hz: ";
    rosidl_generator_traits::value_to_yaml(msg.observed_rate_hz, out);
    out << ", ";
  }

  // member: message_age_sec
  {
    out << "message_age_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.message_age_sec, out);
    out << ", ";
  }

  // member: message_count
  {
    out << "message_count: ";
    rosidl_generator_traits::value_to_yaml(msg.message_count, out);
    out << ", ";
  }

  // member: missing_topics
  {
    if (msg.missing_topics.size() == 0) {
      out << "missing_topics: []";
    } else {
      out << "missing_topics: [";
      size_t pending_items = msg.missing_topics.size();
      for (auto item : msg.missing_topics) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: missing_frames
  {
    if (msg.missing_frames.size() == 0) {
      out << "missing_frames: []";
    } else {
      out << "missing_frames: [";
      size_t pending_items = msg.missing_frames.size();
      for (auto item : msg.missing_frames) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: missing_nodes
  {
    if (msg.missing_nodes.size() == 0) {
      out << "missing_nodes: []";
    } else {
      out << "missing_nodes: [";
      size_t pending_items = msg.missing_nodes.size();
      for (auto item : msg.missing_nodes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: lifecycle_failures
  {
    if (msg.lifecycle_failures.size() == 0) {
      out << "lifecycle_failures: []";
    } else {
      out << "lifecycle_failures: [";
      size_t pending_items = msg.lifecycle_failures.size();
      for (auto item : msg.lifecycle_failures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: condition_failures
  {
    if (msg.condition_failures.size() == 0) {
      out << "condition_failures: []";
    } else {
      out << "condition_failures: [";
      size_t pending_items = msg.condition_failures.size();
      for (auto item : msg.condition_failures) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: warnings
  {
    if (msg.warnings.size() == 0) {
      out << "warnings: []";
    } else {
      out << "warnings: [";
      size_t pending_items = msg.warnings.size();
      for (auto item : msg.warnings) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: errors
  {
    if (msg.errors.size() == 0) {
      out << "errors: []";
    } else {
      out << "errors: [";
      size_t pending_items = msg.errors.size();
      for (auto item : msg.errors) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: detail
  {
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ComponentHealth & msg,
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

  // member: component_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "component_id: ";
    rosidl_generator_traits::value_to_yaml(msg.component_id, out);
    out << "\n";
  }

  // member: display_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "display_name: ";
    rosidl_generator_traits::value_to_yaml(msg.display_name, out);
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

  // member: required
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "required: ";
    rosidl_generator_traits::value_to_yaml(msg.required, out);
    out << "\n";
  }

  // member: present
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "present: ";
    rosidl_generator_traits::value_to_yaml(msg.present, out);
    out << "\n";
  }

  // member: observed_rate_hz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "observed_rate_hz: ";
    rosidl_generator_traits::value_to_yaml(msg.observed_rate_hz, out);
    out << "\n";
  }

  // member: message_age_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message_age_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.message_age_sec, out);
    out << "\n";
  }

  // member: message_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message_count: ";
    rosidl_generator_traits::value_to_yaml(msg.message_count, out);
    out << "\n";
  }

  // member: missing_topics
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.missing_topics.size() == 0) {
      out << "missing_topics: []\n";
    } else {
      out << "missing_topics:\n";
      for (auto item : msg.missing_topics) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: missing_frames
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.missing_frames.size() == 0) {
      out << "missing_frames: []\n";
    } else {
      out << "missing_frames:\n";
      for (auto item : msg.missing_frames) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: missing_nodes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.missing_nodes.size() == 0) {
      out << "missing_nodes: []\n";
    } else {
      out << "missing_nodes:\n";
      for (auto item : msg.missing_nodes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: lifecycle_failures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.lifecycle_failures.size() == 0) {
      out << "lifecycle_failures: []\n";
    } else {
      out << "lifecycle_failures:\n";
      for (auto item : msg.lifecycle_failures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: condition_failures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.condition_failures.size() == 0) {
      out << "condition_failures: []\n";
    } else {
      out << "condition_failures:\n";
      for (auto item : msg.condition_failures) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: warnings
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.warnings.size() == 0) {
      out << "warnings: []\n";
    } else {
      out << "warnings:\n";
      for (auto item : msg.warnings) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: errors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.errors.size() == 0) {
      out << "errors: []\n";
    } else {
      out << "errors:\n";
      for (auto item : msg.errors) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: detail
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ComponentHealth & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::ComponentHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::ComponentHealth & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::ComponentHealth>()
{
  return "agt_interfaces::msg::ComponentHealth";
}

template<>
inline const char * name<agt_interfaces::msg::ComponentHealth>()
{
  return "agt_interfaces/msg/ComponentHealth";
}

template<>
struct has_fixed_size<agt_interfaces::msg::ComponentHealth>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::ComponentHealth>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::ComponentHealth>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__TRAITS_HPP_
