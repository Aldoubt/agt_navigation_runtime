// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/semantic_waypoint__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SemanticWaypoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: role
  {
    out << "role: ";
    rosidl_generator_traits::value_to_yaml(msg.role, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: position_tolerance
  {
    out << "position_tolerance: ";
    rosidl_generator_traits::value_to_yaml(msg.position_tolerance, out);
    out << ", ";
  }

  // member: yaw_tolerance
  {
    out << "yaw_tolerance: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_tolerance, out);
    out << ", ";
  }

  // member: preferred_speed
  {
    out << "preferred_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.preferred_speed, out);
    out << ", ";
  }

  // member: tags
  {
    if (msg.tags.size() == 0) {
      out << "tags: []";
    } else {
      out << "tags: [";
      size_t pending_items = msg.tags.size();
      for (auto item : msg.tags) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: enabled
  {
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SemanticWaypoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: role
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "role: ";
    rosidl_generator_traits::value_to_yaml(msg.role, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: position_tolerance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position_tolerance: ";
    rosidl_generator_traits::value_to_yaml(msg.position_tolerance, out);
    out << "\n";
  }

  // member: yaw_tolerance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_tolerance: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_tolerance, out);
    out << "\n";
  }

  // member: preferred_speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "preferred_speed: ";
    rosidl_generator_traits::value_to_yaml(msg.preferred_speed, out);
    out << "\n";
  }

  // member: tags
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tags.size() == 0) {
      out << "tags: []\n";
    } else {
      out << "tags:\n";
      for (auto item : msg.tags) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SemanticWaypoint & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::SemanticWaypoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::SemanticWaypoint & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::SemanticWaypoint>()
{
  return "agt_interfaces::msg::SemanticWaypoint";
}

template<>
inline const char * name<agt_interfaces::msg::SemanticWaypoint>()
{
  return "agt_interfaces/msg/SemanticWaypoint";
}

template<>
struct has_fixed_size<agt_interfaces::msg::SemanticWaypoint>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::SemanticWaypoint>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::SemanticWaypoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__TRAITS_HPP_
