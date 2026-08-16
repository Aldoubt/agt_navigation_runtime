// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/SetMissionRunState.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/set_mission_run_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMissionRunState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: mission_id
  {
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetMissionRunState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetMissionRunState_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::SetMissionRunState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::SetMissionRunState_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::SetMissionRunState_Request>()
{
  return "agt_interfaces::srv::SetMissionRunState_Request";
}

template<>
inline const char * name<agt_interfaces::srv::SetMissionRunState_Request>()
{
  return "agt_interfaces/srv/SetMissionRunState_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::SetMissionRunState_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::SetMissionRunState_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::SetMissionRunState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'status'
#include "agt_interfaces/msg/detail/mission_status__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetMissionRunState_Response & msg,
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

  // member: status
  {
    out << "status: ";
    to_flow_style_yaml(msg.status, out);
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
  const SetMissionRunState_Response & msg,
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

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status:\n";
    to_block_style_yaml(msg.status, out, indentation + 2);
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

inline std::string to_yaml(const SetMissionRunState_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::SetMissionRunState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::SetMissionRunState_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::SetMissionRunState_Response>()
{
  return "agt_interfaces::srv::SetMissionRunState_Response";
}

template<>
inline const char * name<agt_interfaces::srv::SetMissionRunState_Response>()
{
  return "agt_interfaces/srv/SetMissionRunState_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::SetMissionRunState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::SetMissionRunState_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::SetMissionRunState_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::SetMissionRunState>()
{
  return "agt_interfaces::srv::SetMissionRunState";
}

template<>
inline const char * name<agt_interfaces::srv::SetMissionRunState>()
{
  return "agt_interfaces/srv/SetMissionRunState";
}

template<>
struct has_fixed_size<agt_interfaces::srv::SetMissionRunState>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::SetMissionRunState_Request>::value &&
    has_fixed_size<agt_interfaces::srv::SetMissionRunState_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::SetMissionRunState>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::SetMissionRunState_Request>::value &&
    has_bounded_size<agt_interfaces::srv::SetMissionRunState_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::SetMissionRunState>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::SetMissionRunState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::SetMissionRunState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_MISSION_RUN_STATE__TRAITS_HPP_
