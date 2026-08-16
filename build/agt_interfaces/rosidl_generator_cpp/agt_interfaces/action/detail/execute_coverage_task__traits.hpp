// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/ExecuteCoverageTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/execute_coverage_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: semantic_map_uri
  {
    out << "semantic_map_uri: ";
    rosidl_generator_traits::value_to_yaml(msg.semantic_map_uri, out);
    out << ", ";
  }

  // member: field_id
  {
    out << "field_id: ";
    rosidl_generator_traits::value_to_yaml(msg.field_id, out);
    out << ", ";
  }

  // member: planning_mode
  {
    out << "planning_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.planning_mode, out);
    out << ", ";
  }

  // member: controller_id
  {
    out << "controller_id: ";
    rosidl_generator_traits::value_to_yaml(msg.controller_id, out);
    out << ", ";
  }

  // member: allow_repair
  {
    out << "allow_repair: ";
    rosidl_generator_traits::value_to_yaml(msg.allow_repair, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteCoverageTask_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: semantic_map_uri
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "semantic_map_uri: ";
    rosidl_generator_traits::value_to_yaml(msg.semantic_map_uri, out);
    out << "\n";
  }

  // member: field_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "field_id: ";
    rosidl_generator_traits::value_to_yaml(msg.field_id, out);
    out << "\n";
  }

  // member: planning_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "planning_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.planning_mode, out);
    out << "\n";
  }

  // member: controller_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "controller_id: ";
    rosidl_generator_traits::value_to_yaml(msg.controller_id, out);
    out << "\n";
  }

  // member: allow_repair
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "allow_repair: ";
    rosidl_generator_traits::value_to_yaml(msg.allow_repair, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteCoverageTask_Goal & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_Goal>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_Goal";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_Goal>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_Result & msg,
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

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: coverage_rate
  {
    out << "coverage_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_rate, out);
    out << ", ";
  }

  // member: overlap_rate
  {
    out << "overlap_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_rate, out);
    out << ", ";
  }

  // member: executed_length
  {
    out << "executed_length: ";
    rosidl_generator_traits::value_to_yaml(msg.executed_length, out);
    out << ", ";
  }

  // member: repaired_segment_count
  {
    out << "repaired_segment_count: ";
    rosidl_generator_traits::value_to_yaml(msg.repaired_segment_count, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteCoverageTask_Result & msg,
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

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: coverage_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage_rate, out);
    out << "\n";
  }

  // member: overlap_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "overlap_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.overlap_rate, out);
    out << "\n";
  }

  // member: executed_length
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "executed_length: ";
    rosidl_generator_traits::value_to_yaml(msg.executed_length, out);
    out << "\n";
  }

  // member: repaired_segment_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "repaired_segment_count: ";
    rosidl_generator_traits::value_to_yaml(msg.repaired_segment_count, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteCoverageTask_Result & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_Result>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_Result";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_Result>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_stage
  {
    out << "current_stage: ";
    rosidl_generator_traits::value_to_yaml(msg.current_stage, out);
    out << ", ";
  }

  // member: current_swath_index
  {
    out << "current_swath_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_swath_index, out);
    out << ", ";
  }

  // member: total_swaths
  {
    out << "total_swaths: ";
    rosidl_generator_traits::value_to_yaml(msg.total_swaths, out);
    out << ", ";
  }

  // member: distance_remaining
  {
    out << "distance_remaining: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_remaining, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteCoverageTask_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_stage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_stage: ";
    rosidl_generator_traits::value_to_yaml(msg.current_stage, out);
    out << "\n";
  }

  // member: current_swath_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_swath_index: ";
    rosidl_generator_traits::value_to_yaml(msg.current_swath_index, out);
    out << "\n";
  }

  // member: total_swaths
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_swaths: ";
    rosidl_generator_traits::value_to_yaml(msg.total_swaths, out);
    out << "\n";
  }

  // member: distance_remaining
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_remaining: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_remaining, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteCoverageTask_Feedback & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_Feedback>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_Feedback>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_coverage_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_SendGoal_Request & msg,
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
  const ExecuteCoverageTask_SendGoal_Request & msg,
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

inline std::string to_yaml(const ExecuteCoverageTask_SendGoal_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>
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
  const ExecuteCoverageTask_SendGoal_Response & msg,
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
  const ExecuteCoverageTask_SendGoal_Response & msg,
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

inline std::string to_yaml(const ExecuteCoverageTask_SendGoal_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_SendGoal>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_SendGoal>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ExecuteCoverageTask_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ExecuteCoverageTask_SendGoal_Response>
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
  const ExecuteCoverageTask_GetResult_Request & msg,
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
  const ExecuteCoverageTask_GetResult_Request & msg,
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

inline std::string to_yaml(const ExecuteCoverageTask_GetResult_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_coverage_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_GetResult_Response & msg,
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
  const ExecuteCoverageTask_GetResult_Response & msg,
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

inline std::string to_yaml(const ExecuteCoverageTask_GetResult_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_GetResult>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_GetResult>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ExecuteCoverageTask_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ExecuteCoverageTask_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ExecuteCoverageTask_GetResult_Response>
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
// #include "agt_interfaces/action/detail/execute_coverage_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteCoverageTask_FeedbackMessage & msg,
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
  const ExecuteCoverageTask_FeedbackMessage & msg,
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

inline std::string to_yaml(const ExecuteCoverageTask_FeedbackMessage & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>()
{
  return "agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>()
{
  return "agt_interfaces/action/ExecuteCoverageTask_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteCoverageTask_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteCoverageTask_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteCoverageTask_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::ExecuteCoverageTask>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::ExecuteCoverageTask_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::ExecuteCoverageTask_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::ExecuteCoverageTask_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__TRAITS_HPP_
