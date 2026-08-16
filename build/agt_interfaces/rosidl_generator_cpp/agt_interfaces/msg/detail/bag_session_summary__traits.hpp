// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/bag_session_summary__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const BagSessionSummary & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: bag_id
  {
    out << "bag_id: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_id, out);
    out << ", ";
  }

  // member: experiment_id
  {
    out << "experiment_id: ";
    rosidl_generator_traits::value_to_yaml(msg.experiment_id, out);
    out << ", ";
  }

  // member: profile_id
  {
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << ", ";
  }

  // member: relative_uri
  {
    out << "relative_uri: ";
    rosidl_generator_traits::value_to_yaml(msg.relative_uri, out);
    out << ", ";
  }

  // member: complete
  {
    out << "complete: ";
    rosidl_generator_traits::value_to_yaml(msg.complete, out);
    out << ", ";
  }

  // member: simulation
  {
    out << "simulation: ";
    rosidl_generator_traits::value_to_yaml(msg.simulation, out);
    out << ", ";
  }

  // member: playback_rate
  {
    out << "playback_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.playback_rate, out);
    out << ", ";
  }

  // member: storage_bytes
  {
    out << "storage_bytes: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_bytes, out);
    out << ", ";
  }

  // member: started_at
  {
    out << "started_at: ";
    rosidl_generator_traits::value_to_yaml(msg.started_at, out);
    out << ", ";
  }

  // member: updated_at
  {
    out << "updated_at: ";
    rosidl_generator_traits::value_to_yaml(msg.updated_at, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: process_id
  {
    out << "process_id: ";
    rosidl_generator_traits::value_to_yaml(msg.process_id, out);
    out << ", ";
  }

  // member: message_count
  {
    out << "message_count: ";
    rosidl_generator_traits::value_to_yaml(msg.message_count, out);
    out << ", ";
  }

  // member: storage_identifier
  {
    out << "storage_identifier: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_identifier, out);
    out << ", ";
  }

  // member: mapping_input_ready
  {
    out << "mapping_input_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.mapping_input_ready, out);
    out << ", ";
  }

  // member: contains_mapping_outputs
  {
    out << "contains_mapping_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.contains_mapping_outputs, out);
    out << ", ";
  }

  // member: contains_navigation_outputs
  {
    out << "contains_navigation_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.contains_navigation_outputs, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BagSessionSummary & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: bag_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bag_id: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_id, out);
    out << "\n";
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

  // member: profile_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << "\n";
  }

  // member: relative_uri
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "relative_uri: ";
    rosidl_generator_traits::value_to_yaml(msg.relative_uri, out);
    out << "\n";
  }

  // member: complete
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "complete: ";
    rosidl_generator_traits::value_to_yaml(msg.complete, out);
    out << "\n";
  }

  // member: simulation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "simulation: ";
    rosidl_generator_traits::value_to_yaml(msg.simulation, out);
    out << "\n";
  }

  // member: playback_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "playback_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.playback_rate, out);
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

  // member: started_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "started_at: ";
    rosidl_generator_traits::value_to_yaml(msg.started_at, out);
    out << "\n";
  }

  // member: updated_at
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "updated_at: ";
    rosidl_generator_traits::value_to_yaml(msg.updated_at, out);
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

  // member: process_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "process_id: ";
    rosidl_generator_traits::value_to_yaml(msg.process_id, out);
    out << "\n";
  }

  // member: message_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message_count: ";
    rosidl_generator_traits::value_to_yaml(msg.message_count, out);
    out << "\n";
  }

  // member: storage_identifier
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "storage_identifier: ";
    rosidl_generator_traits::value_to_yaml(msg.storage_identifier, out);
    out << "\n";
  }

  // member: mapping_input_ready
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mapping_input_ready: ";
    rosidl_generator_traits::value_to_yaml(msg.mapping_input_ready, out);
    out << "\n";
  }

  // member: contains_mapping_outputs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contains_mapping_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.contains_mapping_outputs, out);
    out << "\n";
  }

  // member: contains_navigation_outputs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contains_navigation_outputs: ";
    rosidl_generator_traits::value_to_yaml(msg.contains_navigation_outputs, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BagSessionSummary & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::BagSessionSummary & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::BagSessionSummary & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::BagSessionSummary>()
{
  return "agt_interfaces::msg::BagSessionSummary";
}

template<>
inline const char * name<agt_interfaces::msg::BagSessionSummary>()
{
  return "agt_interfaces/msg/BagSessionSummary";
}

template<>
struct has_fixed_size<agt_interfaces::msg::BagSessionSummary>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::BagSessionSummary>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::BagSessionSummary>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__BAG_SESSION_SUMMARY__TRAITS_HPP_
