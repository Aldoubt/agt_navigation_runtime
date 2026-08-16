// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/map_version_summary__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MapVersionSummary & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
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

  // member: parent_map_version_id
  {
    out << "parent_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.parent_map_version_id, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: active
  {
    out << "active: ";
    rosidl_generator_traits::value_to_yaml(msg.active, out);
    out << ", ";
  }

  // member: pinned
  {
    out << "pinned: ";
    rosidl_generator_traits::value_to_yaml(msg.pinned, out);
    out << ", ";
  }

  // member: deleted
  {
    out << "deleted: ";
    rosidl_generator_traits::value_to_yaml(msg.deleted, out);
    out << ", ";
  }

  // member: valid
  {
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << ", ";
  }

  // member: map_hash
  {
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
    out << ", ";
  }

  // member: manifest_sha256
  {
    out << "manifest_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.manifest_sha256, out);
    out << ", ";
  }

  // member: navigation_yaml_sha256
  {
    out << "navigation_yaml_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_yaml_sha256, out);
    out << ", ";
  }

  // member: navigation_image_sha256
  {
    out << "navigation_image_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_image_sha256, out);
    out << ", ";
  }

  // member: localization_pcd_sha256
  {
    out << "localization_pcd_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_pcd_sha256, out);
    out << ", ";
  }

  // member: navigation_yaml
  {
    out << "navigation_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_yaml, out);
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

  // member: tasks_directory
  {
    out << "tasks_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.tasks_directory, out);
    out << ", ";
  }

  // member: storage_bytes
  {
    out << "storage_bytes: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_bytes, out);
    out << ", ";
  }

  // member: created_at
  {
    out << "created_at: ";
    rosidl_generator_traits::value_to_yaml(msg.created_at, out);
    out << ", ";
  }

  // member: validation_errors
  {
    if (msg.validation_errors.size() == 0) {
      out << "validation_errors: []";
    } else {
      out << "validation_errors: [";
      size_t pending_items = msg.validation_errors.size();
      for (auto item : msg.validation_errors) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: validation_warnings
  {
    if (msg.validation_warnings.size() == 0) {
      out << "validation_warnings: []";
    } else {
      out << "validation_warnings: [";
      size_t pending_items = msg.validation_warnings.size();
      for (auto item : msg.validation_warnings) {
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
  const MapVersionSummary & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
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

  // member: parent_map_version_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "parent_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.parent_map_version_id, out);
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

  // member: active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active: ";
    rosidl_generator_traits::value_to_yaml(msg.active, out);
    out << "\n";
  }

  // member: pinned
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pinned: ";
    rosidl_generator_traits::value_to_yaml(msg.pinned, out);
    out << "\n";
  }

  // member: deleted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "deleted: ";
    rosidl_generator_traits::value_to_yaml(msg.deleted, out);
    out << "\n";
  }

  // member: valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "valid: ";
    rosidl_generator_traits::value_to_yaml(msg.valid, out);
    out << "\n";
  }

  // member: map_hash
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
    out << "\n";
  }

  // member: manifest_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "manifest_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.manifest_sha256, out);
    out << "\n";
  }

  // member: navigation_yaml_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "navigation_yaml_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_yaml_sha256, out);
    out << "\n";
  }

  // member: navigation_image_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "navigation_image_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_image_sha256, out);
    out << "\n";
  }

  // member: localization_pcd_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_pcd_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_pcd_sha256, out);
    out << "\n";
  }

  // member: navigation_yaml
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "navigation_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.navigation_yaml, out);
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

  // member: tasks_directory
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tasks_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.tasks_directory, out);
    out << "\n";
  }

  // member: storage_bytes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "storage_bytes: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_bytes, out);
    out << "\n";
  }

  // member: created_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "created_at: ";
    rosidl_generator_traits::value_to_yaml(msg.created_at, out);
    out << "\n";
  }

  // member: validation_errors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.validation_errors.size() == 0) {
      out << "validation_errors: []\n";
    } else {
      out << "validation_errors:\n";
      for (auto item : msg.validation_errors) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: validation_warnings
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.validation_warnings.size() == 0) {
      out << "validation_warnings: []\n";
    } else {
      out << "validation_warnings:\n";
      for (auto item : msg.validation_warnings) {
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

inline std::string to_yaml(const MapVersionSummary & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::MapVersionSummary & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::MapVersionSummary & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::MapVersionSummary>()
{
  return "agt_interfaces::msg::MapVersionSummary";
}

template<>
inline const char * name<agt_interfaces::msg::MapVersionSummary>()
{
  return "agt_interfaces/msg/MapVersionSummary";
}

template<>
struct has_fixed_size<agt_interfaces::msg::MapVersionSummary>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::MapVersionSummary>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::MapVersionSummary>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__TRAITS_HPP_
