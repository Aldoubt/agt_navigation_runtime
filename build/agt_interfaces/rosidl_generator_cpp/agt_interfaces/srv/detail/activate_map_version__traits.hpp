// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/activate_map_version__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ActivateMapVersion_Request & msg,
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

  // member: client_request_id
  {
    out << "client_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_request_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ActivateMapVersion_Request & msg,
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

  // member: client_request_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "client_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_request_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ActivateMapVersion_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ActivateMapVersion_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ActivateMapVersion_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ActivateMapVersion_Request>()
{
  return "agt_interfaces::srv::ActivateMapVersion_Request";
}

template<>
inline const char * name<agt_interfaces::srv::ActivateMapVersion_Request>()
{
  return "agt_interfaces/srv/ActivateMapVersion_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ActivateMapVersion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ActivateMapVersion_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ActivateMapVersion_Request>
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
  const ActivateMapVersion_Response & msg,
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

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
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

  // member: operator_messages
  {
    if (msg.operator_messages.size() == 0) {
      out << "operator_messages: []";
    } else {
      out << "operator_messages: [";
      size_t pending_items = msg.operator_messages.size();
      for (auto item : msg.operator_messages) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: technical_messages
  {
    if (msg.technical_messages.size() == 0) {
      out << "technical_messages: []";
    } else {
      out << "technical_messages: [";
      size_t pending_items = msg.technical_messages.size();
      for (auto item : msg.technical_messages) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: version
  {
    out << "version: ";
    to_flow_style_yaml(msg.version, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ActivateMapVersion_Response & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
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

  // member: operator_messages
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.operator_messages.size() == 0) {
      out << "operator_messages: []\n";
    } else {
      out << "operator_messages:\n";
      for (auto item : msg.operator_messages) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: technical_messages
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.technical_messages.size() == 0) {
      out << "technical_messages: []\n";
    } else {
      out << "technical_messages:\n";
      for (auto item : msg.technical_messages) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "version:\n";
    to_block_style_yaml(msg.version, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ActivateMapVersion_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ActivateMapVersion_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ActivateMapVersion_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ActivateMapVersion_Response>()
{
  return "agt_interfaces::srv::ActivateMapVersion_Response";
}

template<>
inline const char * name<agt_interfaces::srv::ActivateMapVersion_Response>()
{
  return "agt_interfaces/srv/ActivateMapVersion_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ActivateMapVersion_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ActivateMapVersion_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ActivateMapVersion_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::ActivateMapVersion>()
{
  return "agt_interfaces::srv::ActivateMapVersion";
}

template<>
inline const char * name<agt_interfaces::srv::ActivateMapVersion>()
{
  return "agt_interfaces/srv/ActivateMapVersion";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ActivateMapVersion>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::ActivateMapVersion_Request>::value &&
    has_fixed_size<agt_interfaces::srv::ActivateMapVersion_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::ActivateMapVersion>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::ActivateMapVersion_Request>::value &&
    has_bounded_size<agt_interfaces::srv::ActivateMapVersion_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::ActivateMapVersion>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::ActivateMapVersion_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::ActivateMapVersion_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__TRAITS_HPP_
