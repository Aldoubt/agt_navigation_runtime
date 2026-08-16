// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/OptimizeMap.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/optimize_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: source_map_id
  {
    out << "source_map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_map_id, out);
    out << ", ";
  }

  // member: source_map_version_id
  {
    out << "source_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_map_version_id, out);
    out << ", ";
  }

  // member: source_experiment_ids
  {
    if (msg.source_experiment_ids.size() == 0) {
      out << "source_experiment_ids: []";
    } else {
      out << "source_experiment_ids: [";
      size_t pending_items = msg.source_experiment_ids.size();
      for (auto item : msg.source_experiment_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: backend
  {
    out << "backend: ";
    rosidl_generator_traits::value_to_yaml(msg.backend, out);
    out << ", ";
  }

  // member: options_yaml
  {
    out << "options_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.options_yaml, out);
    out << ", ";
  }

  // member: activate_on_success
  {
    out << "activate_on_success: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_on_success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OptimizeMap_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: source_map_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_map_id, out);
    out << "\n";
  }

  // member: source_map_version_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.source_map_version_id, out);
    out << "\n";
  }

  // member: source_experiment_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.source_experiment_ids.size() == 0) {
      out << "source_experiment_ids: []\n";
    } else {
      out << "source_experiment_ids:\n";
      for (auto item : msg.source_experiment_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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

  // member: options_yaml
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "options_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.options_yaml, out);
    out << "\n";
  }

  // member: activate_on_success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "activate_on_success: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_on_success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OptimizeMap_Goal & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_Goal>()
{
  return "agt_interfaces::action::OptimizeMap_Goal";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_Goal>()
{
  return "agt_interfaces/action/OptimizeMap_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_Result & msg,
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

  // member: new_map_version_id
  {
    out << "new_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.new_map_version_id, out);
    out << ", ";
  }

  // member: trajectory_path
  {
    out << "trajectory_path: ";
    rosidl_generator_traits::value_to_yaml(msg.trajectory_path, out);
    out << ", ";
  }

  // member: optimized_pcd_path
  {
    out << "optimized_pcd_path: ";
    rosidl_generator_traits::value_to_yaml(msg.optimized_pcd_path, out);
    out << ", ";
  }

  // member: report_path
  {
    out << "report_path: ";
    rosidl_generator_traits::value_to_yaml(msg.report_path, out);
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
  const OptimizeMap_Result & msg,
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

  // member: new_map_version_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "new_map_version_id: ";
    rosidl_generator_traits::value_to_yaml(msg.new_map_version_id, out);
    out << "\n";
  }

  // member: trajectory_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trajectory_path: ";
    rosidl_generator_traits::value_to_yaml(msg.trajectory_path, out);
    out << "\n";
  }

  // member: optimized_pcd_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "optimized_pcd_path: ";
    rosidl_generator_traits::value_to_yaml(msg.optimized_pcd_path, out);
    out << "\n";
  }

  // member: report_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "report_path: ";
    rosidl_generator_traits::value_to_yaml(msg.report_path, out);
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

inline std::string to_yaml(const OptimizeMap_Result & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_Result>()
{
  return "agt_interfaces::action::OptimizeMap_Result";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_Result>()
{
  return "agt_interfaces/action/OptimizeMap_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: stage
  {
    out << "stage: ";
    rosidl_generator_traits::value_to_yaml(msg.stage, out);
    out << ", ";
  }

  // member: progress
  {
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
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
  const OptimizeMap_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stage: ";
    rosidl_generator_traits::value_to_yaml(msg.stage, out);
    out << "\n";
  }

  // member: progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
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

inline std::string to_yaml(const OptimizeMap_Feedback & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_Feedback>()
{
  return "agt_interfaces::action::OptimizeMap_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_Feedback>()
{
  return "agt_interfaces/action/OptimizeMap_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/optimize_map__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_SendGoal_Request & msg,
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
  const OptimizeMap_SendGoal_Request & msg,
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

inline std::string to_yaml(const OptimizeMap_SendGoal_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_SendGoal_Request>()
{
  return "agt_interfaces::action::OptimizeMap_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_SendGoal_Request>()
{
  return "agt_interfaces/action/OptimizeMap_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::OptimizeMap_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::OptimizeMap_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_SendGoal_Request>
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
  const OptimizeMap_SendGoal_Response & msg,
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
  const OptimizeMap_SendGoal_Response & msg,
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

inline std::string to_yaml(const OptimizeMap_SendGoal_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_SendGoal_Response>()
{
  return "agt_interfaces::action::OptimizeMap_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_SendGoal_Response>()
{
  return "agt_interfaces/action/OptimizeMap_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_SendGoal>()
{
  return "agt_interfaces::action::OptimizeMap_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_SendGoal>()
{
  return "agt_interfaces/action/OptimizeMap_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::OptimizeMap_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::OptimizeMap_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::OptimizeMap_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::OptimizeMap_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::OptimizeMap_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::OptimizeMap_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::OptimizeMap_SendGoal_Response>
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
  const OptimizeMap_GetResult_Request & msg,
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
  const OptimizeMap_GetResult_Request & msg,
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

inline std::string to_yaml(const OptimizeMap_GetResult_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_GetResult_Request>()
{
  return "agt_interfaces::action::OptimizeMap_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_GetResult_Request>()
{
  return "agt_interfaces/action/OptimizeMap_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/optimize_map__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_GetResult_Response & msg,
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
  const OptimizeMap_GetResult_Response & msg,
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

inline std::string to_yaml(const OptimizeMap_GetResult_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_GetResult_Response>()
{
  return "agt_interfaces::action::OptimizeMap_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_GetResult_Response>()
{
  return "agt_interfaces/action/OptimizeMap_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::OptimizeMap_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::OptimizeMap_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_GetResult>()
{
  return "agt_interfaces::action::OptimizeMap_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_GetResult>()
{
  return "agt_interfaces/action/OptimizeMap_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::OptimizeMap_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::OptimizeMap_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::OptimizeMap_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::OptimizeMap_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::OptimizeMap_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::OptimizeMap_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::OptimizeMap_GetResult_Response>
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
// #include "agt_interfaces/action/detail/optimize_map__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const OptimizeMap_FeedbackMessage & msg,
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
  const OptimizeMap_FeedbackMessage & msg,
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

inline std::string to_yaml(const OptimizeMap_FeedbackMessage & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::OptimizeMap_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::OptimizeMap_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::OptimizeMap_FeedbackMessage>()
{
  return "agt_interfaces::action::OptimizeMap_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::OptimizeMap_FeedbackMessage>()
{
  return "agt_interfaces/action/OptimizeMap_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::OptimizeMap_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::OptimizeMap_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::OptimizeMap_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::OptimizeMap_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::OptimizeMap_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::OptimizeMap>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::OptimizeMap_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::OptimizeMap_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::OptimizeMap_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__OPTIMIZE_MAP__TRAITS_HPP_
