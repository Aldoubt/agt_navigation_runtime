// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__TRAITS_HPP_
#define AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/msg/detail/localization_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'global_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__traits.hpp"

namespace agt_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LocalizationStatus & msg,
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

  // member: pose_valid
  {
    out << "pose_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_valid, out);
    out << ", ";
  }

  // member: localization_accepted
  {
    out << "localization_accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_accepted, out);
    out << ", ";
  }

  // member: has_converged
  {
    out << "has_converged: ";
    rosidl_generator_traits::value_to_yaml(msg.has_converged, out);
    out << ", ";
  }

  // member: ambiguous_result
  {
    out << "ambiguous_result: ";
    rosidl_generator_traits::value_to_yaml(msg.ambiguous_result, out);
    out << ", ";
  }

  // member: status_stale
  {
    out << "status_stale: ";
    rosidl_generator_traits::value_to_yaml(msg.status_stale, out);
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: backend
  {
    out << "backend: ";
    rosidl_generator_traits::value_to_yaml(msg.backend, out);
    out << ", ";
  }

  // member: candidate_source
  {
    out << "candidate_source: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_source, out);
    out << ", ";
  }

  // member: candidate_id
  {
    out << "candidate_id: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_id, out);
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << ", ";
  }

  // member: map_hash
  {
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
    out << ", ";
  }

  // member: correction_generation
  {
    out << "correction_generation: ";
    rosidl_generator_traits::value_to_yaml(msg.correction_generation, out);
    out << ", ";
  }

  // member: global_pose
  {
    out << "global_pose: ";
    to_flow_style_yaml(msg.global_pose, out);
    out << ", ";
  }

  // member: fitness_score
  {
    out << "fitness_score: ";
    rosidl_generator_traits::value_to_yaml(msg.fitness_score, out);
    out << ", ";
  }

  // member: overlap_ratio
  {
    out << "overlap_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_ratio, out);
    out << ", ";
  }

  // member: inlier_ratio
  {
    out << "inlier_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.inlier_ratio, out);
    out << ", ";
  }

  // member: ambiguity_score
  {
    out << "ambiguity_score: ";
    rosidl_generator_traits::value_to_yaml(msg.ambiguity_score, out);
    out << ", ";
  }

  // member: translation_innovation
  {
    out << "translation_innovation: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_innovation, out);
    out << ", ";
  }

  // member: yaw_innovation
  {
    out << "yaw_innovation: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_innovation, out);
    out << ", ";
  }

  // member: runtime_ms
  {
    out << "runtime_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.runtime_ms, out);
    out << ", ";
  }

  // member: tested_candidates
  {
    out << "tested_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.tested_candidates, out);
    out << ", ";
  }

  // member: total_candidates
  {
    out << "total_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.total_candidates, out);
    out << ", ";
  }

  // member: consecutive_successes
  {
    out << "consecutive_successes: ";
    rosidl_generator_traits::value_to_yaml(msg.consecutive_successes, out);
    out << ", ";
  }

  // member: consecutive_failures
  {
    out << "consecutive_failures: ";
    rosidl_generator_traits::value_to_yaml(msg.consecutive_failures, out);
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
  const LocalizationStatus & msg,
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

  // member: pose_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_valid, out);
    out << "\n";
  }

  // member: localization_accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "localization_accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.localization_accepted, out);
    out << "\n";
  }

  // member: has_converged
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "has_converged: ";
    rosidl_generator_traits::value_to_yaml(msg.has_converged, out);
    out << "\n";
  }

  // member: ambiguous_result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ambiguous_result: ";
    rosidl_generator_traits::value_to_yaml(msg.ambiguous_result, out);
    out << "\n";
  }

  // member: status_stale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status_stale: ";
    rosidl_generator_traits::value_to_yaml(msg.status_stale, out);
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

  // member: backend
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "backend: ";
    rosidl_generator_traits::value_to_yaml(msg.backend, out);
    out << "\n";
  }

  // member: candidate_source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "candidate_source: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_source, out);
    out << "\n";
  }

  // member: candidate_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "candidate_id: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_id, out);
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

  // member: map_hash
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.map_hash, out);
    out << "\n";
  }

  // member: correction_generation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "correction_generation: ";
    rosidl_generator_traits::value_to_yaml(msg.correction_generation, out);
    out << "\n";
  }

  // member: global_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "global_pose:\n";
    to_block_style_yaml(msg.global_pose, out, indentation + 2);
  }

  // member: fitness_score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fitness_score: ";
    rosidl_generator_traits::value_to_yaml(msg.fitness_score, out);
    out << "\n";
  }

  // member: overlap_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overlap_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_ratio, out);
    out << "\n";
  }

  // member: inlier_ratio
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inlier_ratio: ";
    rosidl_generator_traits::value_to_yaml(msg.inlier_ratio, out);
    out << "\n";
  }

  // member: ambiguity_score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ambiguity_score: ";
    rosidl_generator_traits::value_to_yaml(msg.ambiguity_score, out);
    out << "\n";
  }

  // member: translation_innovation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "translation_innovation: ";
    rosidl_generator_traits::value_to_yaml(msg.translation_innovation, out);
    out << "\n";
  }

  // member: yaw_innovation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_innovation: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_innovation, out);
    out << "\n";
  }

  // member: runtime_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "runtime_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.runtime_ms, out);
    out << "\n";
  }

  // member: tested_candidates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tested_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.tested_candidates, out);
    out << "\n";
  }

  // member: total_candidates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.total_candidates, out);
    out << "\n";
  }

  // member: consecutive_successes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "consecutive_successes: ";
    rosidl_generator_traits::value_to_yaml(msg.consecutive_successes, out);
    out << "\n";
  }

  // member: consecutive_failures
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "consecutive_failures: ";
    rosidl_generator_traits::value_to_yaml(msg.consecutive_failures, out);
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

inline std::string to_yaml(const LocalizationStatus & msg, bool use_flow_style = false)
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
  const agt_interfaces::msg::LocalizationStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::msg::LocalizationStatus & msg)
{
  return agt_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::msg::LocalizationStatus>()
{
  return "agt_interfaces::msg::LocalizationStatus";
}

template<>
inline const char * name<agt_interfaces::msg::LocalizationStatus>()
{
  return "agt_interfaces/msg/LocalizationStatus";
}

template<>
struct has_fixed_size<agt_interfaces::msg::LocalizationStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::msg::LocalizationStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::msg::LocalizationStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__MSG__DETAIL__LOCALIZATION_STATUS__TRAITS_HPP_
