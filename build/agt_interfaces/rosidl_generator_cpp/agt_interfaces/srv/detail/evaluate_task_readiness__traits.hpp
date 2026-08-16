// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const EvaluateTaskReadiness_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: validate_task
  {
    out << "validate_task: ";
    rosidl_generator_traits::value_to_yaml(msg.validate_task, out);
    out << ", ";
  }

  // member: task_id
  {
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << ", ";
  }

  // member: gate_profile
  {
    out << "gate_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.gate_profile, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EvaluateTaskReadiness_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: validate_task
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "validate_task: ";
    rosidl_generator_traits::value_to_yaml(msg.validate_task, out);
    out << "\n";
  }

  // member: task_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << "\n";
  }

  // member: gate_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gate_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.gate_profile, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EvaluateTaskReadiness_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::EvaluateTaskReadiness_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::EvaluateTaskReadiness_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::EvaluateTaskReadiness_Request>()
{
  return "agt_interfaces::srv::EvaluateTaskReadiness_Request";
}

template<>
inline const char * name<agt_interfaces::srv::EvaluateTaskReadiness_Request>()
{
  return "agt_interfaces/srv/EvaluateTaskReadiness_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::EvaluateTaskReadiness_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::EvaluateTaskReadiness_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::EvaluateTaskReadiness_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'readiness'
#include "agt_interfaces/msg/detail/task_readiness__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const EvaluateTaskReadiness_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: readiness
  {
    out << "readiness: ";
    to_flow_style_yaml(msg.readiness, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EvaluateTaskReadiness_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: readiness
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "readiness:\n";
    to_block_style_yaml(msg.readiness, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EvaluateTaskReadiness_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::EvaluateTaskReadiness_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::EvaluateTaskReadiness_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::EvaluateTaskReadiness_Response>()
{
  return "agt_interfaces::srv::EvaluateTaskReadiness_Response";
}

template<>
inline const char * name<agt_interfaces::srv::EvaluateTaskReadiness_Response>()
{
  return "agt_interfaces/srv/EvaluateTaskReadiness_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::EvaluateTaskReadiness_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::msg::TaskReadiness>::value> {};

template<>
struct has_bounded_size<agt_interfaces::srv::EvaluateTaskReadiness_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::msg::TaskReadiness>::value> {};

template<>
struct is_message<agt_interfaces::srv::EvaluateTaskReadiness_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::EvaluateTaskReadiness>()
{
  return "agt_interfaces::srv::EvaluateTaskReadiness";
}

template<>
inline const char * name<agt_interfaces::srv::EvaluateTaskReadiness>()
{
  return "agt_interfaces/srv/EvaluateTaskReadiness";
}

template<>
struct has_fixed_size<agt_interfaces::srv::EvaluateTaskReadiness>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::EvaluateTaskReadiness_Request>::value &&
    has_fixed_size<agt_interfaces::srv::EvaluateTaskReadiness_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::EvaluateTaskReadiness>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::EvaluateTaskReadiness_Request>::value &&
    has_bounded_size<agt_interfaces::srv::EvaluateTaskReadiness_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::EvaluateTaskReadiness>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::EvaluateTaskReadiness_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::EvaluateTaskReadiness_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__EVALUATE_TASK_READINESS__TRAITS_HPP_
