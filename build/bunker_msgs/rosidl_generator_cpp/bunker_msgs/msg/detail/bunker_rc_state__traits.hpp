// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bunker_msgs:msg/BunkerRCState.idl
// generated code does not contain a copyright notice

#ifndef BUNKER_MSGS__MSG__DETAIL__BUNKER_RC_STATE__TRAITS_HPP_
#define BUNKER_MSGS__MSG__DETAIL__BUNKER_RC_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bunker_msgs/msg/detail/bunker_rc_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace bunker_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const BunkerRCState & msg,
  std::ostream & out)
{
  out << "{";
  // member: swa
  {
    out << "swa: ";
    rosidl_generator_traits::value_to_yaml(msg.swa, out);
    out << ", ";
  }

  // member: swb
  {
    out << "swb: ";
    rosidl_generator_traits::value_to_yaml(msg.swb, out);
    out << ", ";
  }

  // member: swc
  {
    out << "swc: ";
    rosidl_generator_traits::value_to_yaml(msg.swc, out);
    out << ", ";
  }

  // member: swd
  {
    out << "swd: ";
    rosidl_generator_traits::value_to_yaml(msg.swd, out);
    out << ", ";
  }

  // member: stick_right_v
  {
    out << "stick_right_v: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_right_v, out);
    out << ", ";
  }

  // member: stick_right_h
  {
    out << "stick_right_h: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_right_h, out);
    out << ", ";
  }

  // member: stick_left_v
  {
    out << "stick_left_v: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_left_v, out);
    out << ", ";
  }

  // member: stick_left_h
  {
    out << "stick_left_h: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_left_h, out);
    out << ", ";
  }

  // member: var_a
  {
    out << "var_a: ";
    rosidl_generator_traits::value_to_yaml(msg.var_a, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BunkerRCState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: swa
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "swa: ";
    rosidl_generator_traits::value_to_yaml(msg.swa, out);
    out << "\n";
  }

  // member: swb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "swb: ";
    rosidl_generator_traits::value_to_yaml(msg.swb, out);
    out << "\n";
  }

  // member: swc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "swc: ";
    rosidl_generator_traits::value_to_yaml(msg.swc, out);
    out << "\n";
  }

  // member: swd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "swd: ";
    rosidl_generator_traits::value_to_yaml(msg.swd, out);
    out << "\n";
  }

  // member: stick_right_v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stick_right_v: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_right_v, out);
    out << "\n";
  }

  // member: stick_right_h
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stick_right_h: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_right_h, out);
    out << "\n";
  }

  // member: stick_left_v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stick_left_v: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_left_v, out);
    out << "\n";
  }

  // member: stick_left_h
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stick_left_h: ";
    rosidl_generator_traits::value_to_yaml(msg.stick_left_h, out);
    out << "\n";
  }

  // member: var_a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "var_a: ";
    rosidl_generator_traits::value_to_yaml(msg.var_a, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BunkerRCState & msg, bool use_flow_style = false)
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

}  // namespace bunker_msgs

namespace rosidl_generator_traits
{

[[deprecated("use bunker_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bunker_msgs::msg::BunkerRCState & msg,
  std::ostream & out, size_t indentation = 0)
{
  bunker_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bunker_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const bunker_msgs::msg::BunkerRCState & msg)
{
  return bunker_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<bunker_msgs::msg::BunkerRCState>()
{
  return "bunker_msgs::msg::BunkerRCState";
}

template<>
inline const char * name<bunker_msgs::msg::BunkerRCState>()
{
  return "bunker_msgs/msg/BunkerRCState";
}

template<>
struct has_fixed_size<bunker_msgs::msg::BunkerRCState>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<bunker_msgs::msg::BunkerRCState>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<bunker_msgs::msg::BunkerRCState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BUNKER_MSGS__MSG__DETAIL__BUNKER_RC_STATE__TRAITS_HPP_
