// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/GetTaskGroup.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/get_task_group__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTaskGroup_Request & msg,
  std::ostream & out)
{
  out << "{";
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

  // member: task_group_id
  {
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << ", ";
  }

  // member: task_revision
  {
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetTaskGroup_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
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

  // member: task_group_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << "\n";
  }

  // member: task_revision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTaskGroup_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::GetTaskGroup_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::GetTaskGroup_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::GetTaskGroup_Request>()
{
  return "agt_interfaces::srv::GetTaskGroup_Request";
}

template<>
inline const char * name<agt_interfaces::srv::GetTaskGroup_Request>()
{
  return "agt_interfaces/srv/GetTaskGroup_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetTaskGroup_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::GetTaskGroup_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::GetTaskGroup_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTaskGroup_Response & msg,
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

  // member: blocker_code
  {
    out << "blocker_code: ";
    rosidl_generator_traits::value_to_yaml(msg.blocker_code, out);
    out << ", ";
  }

  // member: operator_message
  {
    out << "operator_message: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_message, out);
    out << ", ";
  }

  // member: technical_message
  {
    out << "technical_message: ";
    rosidl_generator_traits::value_to_yaml(msg.technical_message, out);
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

  // member: task_group_id
  {
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << ", ";
  }

  // member: revision
  {
    out << "revision: ";
    rosidl_generator_traits::value_to_yaml(msg.revision, out);
    out << ", ";
  }

  // member: content_sha256
  {
    out << "content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.content_sha256, out);
    out << ", ";
  }

  // member: task_json
  {
    out << "task_json: ";
    rosidl_generator_traits::value_to_yaml(msg.task_json, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetTaskGroup_Response & msg,
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

  // member: blocker_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "blocker_code: ";
    rosidl_generator_traits::value_to_yaml(msg.blocker_code, out);
    out << "\n";
  }

  // member: operator_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operator_message: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_message, out);
    out << "\n";
  }

  // member: technical_message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "technical_message: ";
    rosidl_generator_traits::value_to_yaml(msg.technical_message, out);
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

  // member: task_group_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
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

  // member: content_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.content_sha256, out);
    out << "\n";
  }

  // member: task_json
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_json: ";
    rosidl_generator_traits::value_to_yaml(msg.task_json, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTaskGroup_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::GetTaskGroup_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::GetTaskGroup_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::GetTaskGroup_Response>()
{
  return "agt_interfaces::srv::GetTaskGroup_Response";
}

template<>
inline const char * name<agt_interfaces::srv::GetTaskGroup_Response>()
{
  return "agt_interfaces/srv/GetTaskGroup_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetTaskGroup_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::GetTaskGroup_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::GetTaskGroup_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::GetTaskGroup>()
{
  return "agt_interfaces::srv::GetTaskGroup";
}

template<>
inline const char * name<agt_interfaces::srv::GetTaskGroup>()
{
  return "agt_interfaces/srv/GetTaskGroup";
}

template<>
struct has_fixed_size<agt_interfaces::srv::GetTaskGroup>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::GetTaskGroup_Request>::value &&
    has_fixed_size<agt_interfaces::srv::GetTaskGroup_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::GetTaskGroup>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::GetTaskGroup_Request>::value &&
    has_bounded_size<agt_interfaces::srv::GetTaskGroup_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::GetTaskGroup>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::GetTaskGroup_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::GetTaskGroup_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__TRAITS_HPP_
