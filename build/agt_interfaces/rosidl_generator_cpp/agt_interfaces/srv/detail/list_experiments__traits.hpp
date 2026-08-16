// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/ListExperiments.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/list_experiments__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListExperiments_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ListExperiments_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ListExperiments_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ListExperiments_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ListExperiments_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ListExperiments_Request>()
{
  return "agt_interfaces::srv::ListExperiments_Request";
}

template<>
inline const char * name<agt_interfaces::srv::ListExperiments_Request>()
{
  return "agt_interfaces/srv/ListExperiments_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListExperiments_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ListExperiments_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<agt_interfaces::srv::ListExperiments_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'experiments'
#include "agt_interfaces/msg/detail/experiment_summary__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListExperiments_Response & msg,
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

  // member: experiments
  {
    if (msg.experiments.size() == 0) {
      out << "experiments: []";
    } else {
      out << "experiments: [";
      size_t pending_items = msg.experiments.size();
      for (auto item : msg.experiments) {
        to_flow_style_yaml(item, out);
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
  const ListExperiments_Response & msg,
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

  // member: experiments
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.experiments.size() == 0) {
      out << "experiments: []\n";
    } else {
      out << "experiments:\n";
      for (auto item : msg.experiments) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
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

inline std::string to_yaml(const ListExperiments_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ListExperiments_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ListExperiments_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ListExperiments_Response>()
{
  return "agt_interfaces::srv::ListExperiments_Response";
}

template<>
inline const char * name<agt_interfaces::srv::ListExperiments_Response>()
{
  return "agt_interfaces/srv/ListExperiments_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListExperiments_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ListExperiments_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ListExperiments_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::ListExperiments>()
{
  return "agt_interfaces::srv::ListExperiments";
}

template<>
inline const char * name<agt_interfaces::srv::ListExperiments>()
{
  return "agt_interfaces/srv/ListExperiments";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListExperiments>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::ListExperiments_Request>::value &&
    has_fixed_size<agt_interfaces::srv::ListExperiments_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::ListExperiments>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::ListExperiments_Request>::value &&
    has_bounded_size<agt_interfaces::srv::ListExperiments_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::ListExperiments>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::ListExperiments_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::ListExperiments_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_EXPERIMENTS__TRAITS_HPP_
