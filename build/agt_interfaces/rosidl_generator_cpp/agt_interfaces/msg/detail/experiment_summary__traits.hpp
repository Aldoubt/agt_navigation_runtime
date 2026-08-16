// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/ExperimentSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/experiment_summary__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ExperimentSummary & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: experiment_id
  {
    out << "experiment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.experiment_id, out);
    out << ", ";
  }

  // member: title
  {
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: created_at
  {
    out << "created_at: ";
    rosidl_generator_traits::value_to_yaml(msg.created_at, out);
    out << ", ";
  }

  // member: start_time
  {
    out << "start_time: ";
    rosidl_generator_traits::value_to_yaml(msg.start_time, out);
    out << ", ";
  }

  // member: end_time
  {
    out << "end_time: ";
    rosidl_generator_traits::value_to_yaml(msg.end_time, out);
    out << ", ";
  }

  // member: platform_profile
  {
    out << "platform_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_profile, out);
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

  // member: map_hash
  {
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
    out << ", ";
  }

  // member: mission_id
  {
    out << "mission_id: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_id, out);
    out << ", ";
  }

  // member: mission_version
  {
    out << "mission_version: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_version, out);
    out << ", ";
  }

  // member: mission_sha256
  {
    out << "mission_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_sha256, out);
    out << ", ";
  }

  // member: launch_profile
  {
    out << "launch_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.launch_profile, out);
    out << ", ";
  }

  // member: result_status
  {
    out << "result_status: ";
    rosidl_generator_traits::value_to_yaml(msg.result_status, out);
    out << ", ";
  }

  // member: config_snapshot_count
  {
    out << "config_snapshot_count: ";
    rosidl_generator_traits::value_to_yaml(msg.config_snapshot_count, out);
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
  const ExperimentSummary & msg,
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

  // member: experiment_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "experiment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.experiment_id, out);
    out << "\n";
  }

  // member: title
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "title: ";
    rosidl_generator_traits::value_to_yaml(msg.title, out);
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

  // member: created_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "created_at: ";
    rosidl_generator_traits::value_to_yaml(msg.created_at, out);
    out << "\n";
  }

  // member: start_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_time: ";
    rosidl_generator_traits::value_to_yaml(msg.start_time, out);
    out << "\n";
  }

  // member: end_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "end_time: ";
    rosidl_generator_traits::value_to_yaml(msg.end_time, out);
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

  // member: map_hash
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
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

  // member: mission_version
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_version: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_version, out);
    out << "\n";
  }

  // member: mission_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mission_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.mission_sha256, out);
    out << "\n";
  }

  // member: launch_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "launch_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.launch_profile, out);
    out << "\n";
  }

  // member: result_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result_status: ";
    rosidl_generator_traits::value_to_yaml(msg.result_status, out);
    out << "\n";
  }

  // member: config_snapshot_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "config_snapshot_count: ";
    rosidl_generator_traits::value_to_yaml(msg.config_snapshot_count, out);
    out << "\n";
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

inline std::string to_yaml(const ExperimentSummary & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::ExperimentSummary & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::ExperimentSummary & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::ExperimentSummary>()
{
  return "agt_interfaces::msg::ExperimentSummary";
}

template<>
inline const char * name<agt_interfaces::msg::ExperimentSummary>()
{
  return "agt_interfaces/msg/ExperimentSummary";
}

template<>
struct has_fixed_size<agt_interfaces::msg::ExperimentSummary>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::ExperimentSummary>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::ExperimentSummary>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__TRAITS_HPP_
