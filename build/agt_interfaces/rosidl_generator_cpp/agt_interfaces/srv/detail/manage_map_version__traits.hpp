// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/ManageMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/manage_map_version__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ManageMapVersion_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: operation
  {
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
    out << ", ";
  }

  // member: map_version_id
  {
    out << "map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_version_id, out);
    out << ", ";
  }

  // member: confirm_destructive
  {
    out << "confirm_destructive: ";
    rosidl_generator_traits::value_to_yaml(msg.confirm_destructive, out);
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << ", ";
  }

  // member: candidate_map_yaml
  {
    out << "candidate_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_yaml, out);
    out << ", ";
  }

  // member: localization_pcd
  {
    out << "localization_pcd: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_pcd, out);
    out << ", ";
  }

  // member: processing_record
  {
    out << "processing_record: ";
    rosidl_generator_traits::value_to_yaml(msg.processing_record, out);
    out << ", ";
  }

  // member: platform_profile
  {
    out << "platform_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_profile, out);
    out << ", ";
  }

  // member: parent_map_version_id
  {
    out << "parent_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.parent_map_version_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ManageMapVersion_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: operation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
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

  // member: confirm_destructive
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confirm_destructive: ";
    rosidl_generator_traits::value_to_yaml(msg.confirm_destructive, out);
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

  // member: candidate_map_yaml
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "candidate_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_yaml, out);
    out << "\n";
  }

  // member: localization_pcd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_pcd: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_pcd, out);
    out << "\n";
  }

  // member: processing_record
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "processing_record: ";
    rosidl_generator_traits::value_to_yaml(msg.processing_record, out);
    out << "\n";
  }

  // member: platform_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "platform_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_profile, out);
    out << "\n";
  }

  // member: parent_map_version_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "parent_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.parent_map_version_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ManageMapVersion_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ManageMapVersion_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ManageMapVersion_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ManageMapVersion_Request>()
{
  return "agt_interfaces::srv::ManageMapVersion_Request";
}

template<>
inline const char * name<agt_interfaces::srv::ManageMapVersion_Request>()
{
  return "agt_interfaces/srv/ManageMapVersion_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageMapVersion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageMapVersion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ManageMapVersion_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'version'
#include "agt_interfaces/msg/detail/map_version_summary__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ManageMapVersion_Response & msg,
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

  // member: version
  {
    out << "version: ";
    to_flow_style_yaml(msg.version, out);
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
  const ManageMapVersion_Response & msg,
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

  // member: version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "version:\n";
    to_block_style_yaml(msg.version, out, indentation + 2);
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

inline std::string to_yaml(const ManageMapVersion_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ManageMapVersion_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ManageMapVersion_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ManageMapVersion_Response>()
{
  return "agt_interfaces::srv::ManageMapVersion_Response";
}

template<>
inline const char * name<agt_interfaces::srv::ManageMapVersion_Response>()
{
  return "agt_interfaces/srv/ManageMapVersion_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageMapVersion_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageMapVersion_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ManageMapVersion_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::ManageMapVersion>()
{
  return "agt_interfaces::srv::ManageMapVersion";
}

template<>
inline const char * name<agt_interfaces::srv::ManageMapVersion>()
{
  return "agt_interfaces/srv/ManageMapVersion";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageMapVersion>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::ManageMapVersion_Request>::value &&
    has_fixed_size<agt_interfaces::srv::ManageMapVersion_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageMapVersion>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::ManageMapVersion_Request>::value &&
    has_bounded_size<agt_interfaces::srv::ManageMapVersion_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::ManageMapVersion>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::ManageMapVersion_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::ManageMapVersion_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__TRAITS_HPP_
