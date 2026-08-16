// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/GetRobotState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/get_robot_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: include_details
  {
    out << "include_details: ";
    rosidl_generator_traits::value_to_yaml(msg.include_details, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetRobotState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: include_details
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "include_details: ";
    rosidl_generator_traits::value_to_yaml(msg.include_details, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetRobotState_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::srv::GetRobotState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::GetRobotState_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::GetRobotState_Request>()
{
  return "agt_interfaces::srv::GetRobotState_Request";
}

template<>
inline const char * name<agt_interfaces::srv::GetRobotState_Request>()
{
  return "agt_interfaces/srv/GetRobotState_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetRobotState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<agt_interfaces::srv::GetRobotState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<agt_interfaces::srv::GetRobotState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'state'
#include "agt_interfaces/msg/detail/robot_state__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetRobotState_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    to_flow_style_yaml(msg.state, out);
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
  const GetRobotState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state:\n";
    to_block_style_yaml(msg.state, out, indentation + 2);
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

inline std::string to_yaml(const GetRobotState_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::srv::GetRobotState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::GetRobotState_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::GetRobotState_Response>()
{
  return "agt_interfaces::srv::GetRobotState_Response";
}

template<>
inline const char * name<agt_interfaces::srv::GetRobotState_Response>()
{
  return "agt_interfaces/srv/GetRobotState_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetRobotState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::GetRobotState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::GetRobotState_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::GetRobotState>()
{
  return "agt_interfaces::srv::GetRobotState";
}

template<>
inline const char * name<agt_interfaces::srv::GetRobotState>()
{
  return "agt_interfaces/srv/GetRobotState";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetRobotState>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::GetRobotState_Request>::value &&
    has_fixed_size<agt_interfaces::srv::GetRobotState_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::GetRobotState>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::GetRobotState_Request>::value &&
    has_bounded_size<agt_interfaces::srv::GetRobotState_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::GetRobotState>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::GetRobotState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::GetRobotState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_ROBOT_STATE__TRAITS_HPP_
