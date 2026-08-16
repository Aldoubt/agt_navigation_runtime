// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/relocalize__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'initial_pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: use_initial_pose
  {
    out << "use_initial_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_initial_pose, out);
    out << ", ";
  }

  // member: initial_pose
  {
    out << "initial_pose: ";
    to_flow_style_yaml(msg.initial_pose, out);
    out << ", ";
  }

  // member: use_last_valid_pose
  {
    out << "use_last_valid_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_last_valid_pose, out);
    out << ", ";
  }

  // member: use_configured_candidates
  {
    out << "use_configured_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.use_configured_candidates, out);
    out << ", ";
  }

  // member: use_external_coarse_pose
  {
    out << "use_external_coarse_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_external_coarse_pose, out);
    out << ", ";
  }

  // member: max_candidates
  {
    out << "max_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.max_candidates, out);
    out << ", ";
  }

  // member: publish_debug
  {
    out << "publish_debug: ";
    rosidl_generator_traits::value_to_yaml(msg.publish_debug, out);
    out << ", ";
  }

  // member: timeout_s
  {
    out << "timeout_s: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_s, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: use_initial_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_initial_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_initial_pose, out);
    out << "\n";
  }

  // member: initial_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "initial_pose:\n";
    to_block_style_yaml(msg.initial_pose, out, indentation + 2);
  }

  // member: use_last_valid_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_last_valid_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_last_valid_pose, out);
    out << "\n";
  }

  // member: use_configured_candidates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_configured_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.use_configured_candidates, out);
    out << "\n";
  }

  // member: use_external_coarse_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_external_coarse_pose: ";
    rosidl_generator_traits::value_to_yaml(msg.use_external_coarse_pose, out);
    out << "\n";
  }

  // member: max_candidates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.max_candidates, out);
    out << "\n";
  }

  // member: publish_debug
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "publish_debug: ";
    rosidl_generator_traits::value_to_yaml(msg.publish_debug, out);
    out << "\n";
  }

  // member: timeout_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timeout_s: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_s, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_Goal>()
{
  return "agt_interfaces::action::Relocalize_Goal";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_Goal>()
{
  return "agt_interfaces/action/Relocalize_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_Goal>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseWithCovarianceStamped>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_Goal>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseWithCovarianceStamped>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'final_pose'
// already included above
// #include "geometry_msgs/msg/detail/pose_with_covariance_stamped__traits.hpp"
// Member 'final_status'
#include "agt_interfaces/msg/detail/localization_status__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_Result & msg,
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

  // member: final_pose
  {
    out << "final_pose: ";
    to_flow_style_yaml(msg.final_pose, out);
    out << ", ";
  }

  // member: final_status
  {
    out << "final_status: ";
    to_flow_style_yaml(msg.final_status, out);
    out << ", ";
  }

  // member: failure_reason
  {
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_Result & msg,
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

  // member: final_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_pose:\n";
    to_block_style_yaml(msg.final_pose, out, indentation + 2);
  }

  // member: final_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_status:\n";
    to_block_style_yaml(msg.final_status, out, indentation + 2);
  }

  // member: failure_reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_Result>()
{
  return "agt_interfaces::action::Relocalize_Result";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_Result>()
{
  return "agt_interfaces/action/Relocalize_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: total_candidates
  {
    out << "total_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.total_candidates, out);
    out << ", ";
  }

  // member: tested_candidates
  {
    out << "tested_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.tested_candidates, out);
    out << ", ";
  }

  // member: best_fitness_score
  {
    out << "best_fitness_score: ";
    rosidl_generator_traits::value_to_yaml(msg.best_fitness_score, out);
    out << ", ";
  }

  // member: best_candidate_source
  {
    out << "best_candidate_source: ";
    rosidl_generator_traits::value_to_yaml(msg.best_candidate_source, out);
    out << ", ";
  }

  // member: elapsed_s
  {
    out << "elapsed_s: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_s, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_Feedback & msg,
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

  // member: total_candidates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_candidates: ";
    rosidl_generator_traits::value_to_yaml(msg.total_candidates, out);
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

  // member: best_fitness_score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_fitness_score: ";
    rosidl_generator_traits::value_to_yaml(msg.best_fitness_score, out);
    out << "\n";
  }

  // member: best_candidate_source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "best_candidate_source: ";
    rosidl_generator_traits::value_to_yaml(msg.best_candidate_source, out);
    out << "\n";
  }

  // member: elapsed_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "elapsed_s: ";
    rosidl_generator_traits::value_to_yaml(msg.elapsed_s, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_Feedback>()
{
  return "agt_interfaces::action::Relocalize_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_Feedback>()
{
  return "agt_interfaces/action/Relocalize_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/relocalize__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_SendGoal_Request>()
{
  return "agt_interfaces::action::Relocalize_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_SendGoal_Request>()
{
  return "agt_interfaces/action/Relocalize_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::Relocalize_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::Relocalize_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_SendGoal_Response>()
{
  return "agt_interfaces::action::Relocalize_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_SendGoal_Response>()
{
  return "agt_interfaces/action/Relocalize_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_SendGoal>()
{
  return "agt_interfaces::action::Relocalize_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_SendGoal>()
{
  return "agt_interfaces/action/Relocalize_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::Relocalize_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::Relocalize_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::Relocalize_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::Relocalize_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::Relocalize_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::Relocalize_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::Relocalize_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_GetResult_Request>()
{
  return "agt_interfaces::action::Relocalize_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_GetResult_Request>()
{
  return "agt_interfaces/action/Relocalize_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/relocalize__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_GetResult_Response>()
{
  return "agt_interfaces::action::Relocalize_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_GetResult_Response>()
{
  return "agt_interfaces/action/Relocalize_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::Relocalize_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::Relocalize_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_GetResult>()
{
  return "agt_interfaces::action::Relocalize_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_GetResult>()
{
  return "agt_interfaces/action/Relocalize_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::Relocalize_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::Relocalize_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::Relocalize_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::Relocalize_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::Relocalize_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::Relocalize_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::Relocalize_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "agt_interfaces/action/detail/relocalize__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const Relocalize_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::action::Relocalize_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::Relocalize_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::Relocalize_FeedbackMessage>()
{
  return "agt_interfaces::action::Relocalize_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::Relocalize_FeedbackMessage>()
{
  return "agt_interfaces/action/Relocalize_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::Relocalize_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::Relocalize_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::Relocalize_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::Relocalize_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::Relocalize_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::Relocalize>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::Relocalize_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::Relocalize_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::Relocalize_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__TRAITS_HPP_
