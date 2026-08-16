// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/ListTaskGroups.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/list_task_groups__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListTaskGroups_Request & msg,
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ListTaskGroups_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ListTaskGroups_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ListTaskGroups_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ListTaskGroups_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ListTaskGroups_Request>()
{
  return "agt_interfaces::srv::ListTaskGroups_Request";
}

template<>
inline const char * name<agt_interfaces::srv::ListTaskGroups_Request>()
{
  return "agt_interfaces/srv/ListTaskGroups_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListTaskGroups_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ListTaskGroups_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ListTaskGroups_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListTaskGroups_Response & msg,
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

  // member: task_group_ids
  {
    if (msg.task_group_ids.size() == 0) {
      out << "task_group_ids: []";
    } else {
      out << "task_group_ids: [";
      size_t pending_items = msg.task_group_ids.size();
      for (auto item : msg.task_group_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: names
  {
    if (msg.names.size() == 0) {
      out << "names: []";
    } else {
      out << "names: [";
      size_t pending_items = msg.names.size();
      for (auto item : msg.names) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: revisions
  {
    if (msg.revisions.size() == 0) {
      out << "revisions: []";
    } else {
      out << "revisions: [";
      size_t pending_items = msg.revisions.size();
      for (auto item : msg.revisions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: content_sha256
  {
    if (msg.content_sha256.size() == 0) {
      out << "content_sha256: []";
    } else {
      out << "content_sha256: [";
      size_t pending_items = msg.content_sha256.size();
      for (auto item : msg.content_sha256) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: enabled_point_counts
  {
    if (msg.enabled_point_counts.size() == 0) {
      out << "enabled_point_counts: []";
    } else {
      out << "enabled_point_counts: [";
      size_t pending_items = msg.enabled_point_counts.size();
      for (auto item : msg.enabled_point_counts) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: updated_at
  {
    if (msg.updated_at.size() == 0) {
      out << "updated_at: []";
    } else {
      out << "updated_at: [";
      size_t pending_items = msg.updated_at.size();
      for (auto item : msg.updated_at) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: validation_states
  {
    if (msg.validation_states.size() == 0) {
      out << "validation_states: []";
    } else {
      out << "validation_states: [";
      size_t pending_items = msg.validation_states.size();
      for (auto item : msg.validation_states) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ListTaskGroups_Response & msg,
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

  // member: task_group_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.task_group_ids.size() == 0) {
      out << "task_group_ids: []\n";
    } else {
      out << "task_group_ids:\n";
      for (auto item : msg.task_group_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: names
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.names.size() == 0) {
      out << "names: []\n";
    } else {
      out << "names:\n";
      for (auto item : msg.names) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: revisions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.revisions.size() == 0) {
      out << "revisions: []\n";
    } else {
      out << "revisions:\n";
      for (auto item : msg.revisions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: content_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.content_sha256.size() == 0) {
      out << "content_sha256: []\n";
    } else {
      out << "content_sha256:\n";
      for (auto item : msg.content_sha256) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: enabled_point_counts
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.enabled_point_counts.size() == 0) {
      out << "enabled_point_counts: []\n";
    } else {
      out << "enabled_point_counts:\n";
      for (auto item : msg.enabled_point_counts) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: updated_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.updated_at.size() == 0) {
      out << "updated_at: []\n";
    } else {
      out << "updated_at:\n";
      for (auto item : msg.updated_at) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: validation_states
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.validation_states.size() == 0) {
      out << "validation_states: []\n";
    } else {
      out << "validation_states:\n";
      for (auto item : msg.validation_states) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ListTaskGroups_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::srv::ListTaskGroups_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ListTaskGroups_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ListTaskGroups_Response>()
{
  return "agt_interfaces::srv::ListTaskGroups_Response";
}

template<>
inline const char * name<agt_interfaces::srv::ListTaskGroups_Response>()
{
  return "agt_interfaces/srv/ListTaskGroups_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListTaskGroups_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ListTaskGroups_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ListTaskGroups_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::ListTaskGroups>()
{
  return "agt_interfaces::srv::ListTaskGroups";
}

template<>
inline const char * name<agt_interfaces::srv::ListTaskGroups>()
{
  return "agt_interfaces/srv/ListTaskGroups";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ListTaskGroups>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::ListTaskGroups_Request>::value &&
    has_fixed_size<agt_interfaces::srv::ListTaskGroups_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::ListTaskGroups>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::ListTaskGroups_Request>::value &&
    has_bounded_size<agt_interfaces::srv::ListTaskGroups_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::ListTaskGroups>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::ListTaskGroups_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::ListTaskGroups_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__TRAITS_HPP_
