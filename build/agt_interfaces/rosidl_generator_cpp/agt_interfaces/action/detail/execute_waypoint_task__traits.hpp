// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/ExecuteWaypointTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/execute_waypoint_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'poses'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_Goal & msg,
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

  // member: task_group_id
  {
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << ", ";
  }

  // member: task_revision
  {
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
    out << ", ";
  }

  // member: expected_content_sha256
  {
    out << "expected_content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_content_sha256, out);
    out << ", ";
  }

  // member: loop_count
  {
    out << "loop_count: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_count, out);
    out << ", ";
  }

  // member: client_request_id
  {
    out << "client_request_id: ";
    rosidl_generator_traits::value_to_yaml(msg.client_request_id, out);
    out << ", ";
  }

  // member: task_file
  {
    out << "task_file: ";
    rosidl_generator_traits::value_to_yaml(msg.task_file, out);
    out << ", ";
  }

  // member: poses
  {
    if (msg.poses.size() == 0) {
      out << "poses: []";
    } else {
      out << "poses: [";
      size_t pending_items = msg.poses.size();
      for (auto item : msg.poses) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: loop
  {
    out << "loop: ";
    rosidl_generator_traits::value_to_yaml(msg.loop, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteWaypointTask_Goal & msg,
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

  // member: task_group_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_group_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_group_id, out);
    out << "\n";
  }

  // member: task_revision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_revision: ";
    rosidl_generator_traits::value_to_yaml(msg.task_revision, out);
    out << "\n";
  }

  // member: expected_content_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "expected_content_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.expected_content_sha256, out);
    out << "\n";
  }

  // member: loop_count
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loop_count: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_count, out);
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

  // member: task_file
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_file: ";
    rosidl_generator_traits::value_to_yaml(msg.task_file, out);
    out << "\n";
  }

  // member: poses
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.poses.size() == 0) {
      out << "poses: []\n";
    } else {
      out << "poses:\n";
      for (auto item : msg.poses) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: loop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loop: ";
    rosidl_generator_traits::value_to_yaml(msg.loop, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteWaypointTask_Goal & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_Goal>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_Goal";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_Goal>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'final_status'
#include "agt_interfaces/msg/detail/navigation_session_status__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_Result & msg,
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

  // member: session_id
  {
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
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

  // member: duplicate_request
  {
    out << "duplicate_request: ";
    rosidl_generator_traits::value_to_yaml(msg.duplicate_request, out);
    out << ", ";
  }

  // member: missed_waypoints
  {
    if (msg.missed_waypoints.size() == 0) {
      out << "missed_waypoints: []";
    } else {
      out << "missed_waypoints: [";
      size_t pending_items = msg.missed_waypoints.size();
      for (auto item : msg.missed_waypoints) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: final_status
  {
    out << "final_status: ";
    to_flow_style_yaml(msg.final_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteWaypointTask_Result & msg,
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

  // member: session_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
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

  // member: duplicate_request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "duplicate_request: ";
    rosidl_generator_traits::value_to_yaml(msg.duplicate_request, out);
    out << "\n";
  }

  // member: missed_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.missed_waypoints.size() == 0) {
      out << "missed_waypoints: []\n";
    } else {
      out << "missed_waypoints:\n";
      for (auto item : msg.missed_waypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: final_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_status:\n";
    to_block_style_yaml(msg.final_status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteWaypointTask_Result & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_Result>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_Result";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_Result>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'status'
// already included above
// #include "agt_interfaces/msg/detail/navigation_session_status__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: loop_index
  {
    out << "loop_index: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_index, out);
    out << ", ";
  }

  // member: current_waypoint
  {
    out << "current_waypoint: ";
    rosidl_generator_traits::value_to_yaml(msg.current_waypoint, out);
    out << ", ";
  }

  // member: total_waypoints
  {
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    to_flow_style_yaml(msg.status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExecuteWaypointTask_Feedback & msg,
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

  // member: loop_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "loop_index: ";
    rosidl_generator_traits::value_to_yaml(msg.loop_index, out);
    out << "\n";
  }

  // member: current_waypoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_waypoint: ";
    rosidl_generator_traits::value_to_yaml(msg.current_waypoint, out);
    out << "\n";
  }

  // member: total_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
    out << "\n";
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status:\n";
    to_block_style_yaml(msg.status, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExecuteWaypointTask_Feedback & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_Feedback>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_Feedback>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/execute_waypoint_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_SendGoal_Request & msg,
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
  const ExecuteWaypointTask_SendGoal_Request & msg,
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

inline std::string to_yaml(const ExecuteWaypointTask_SendGoal_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>
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
  const ExecuteWaypointTask_SendGoal_Response & msg,
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
  const ExecuteWaypointTask_SendGoal_Response & msg,
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

inline std::string to_yaml(const ExecuteWaypointTask_SendGoal_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_SendGoal>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_SendGoal>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ExecuteWaypointTask_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ExecuteWaypointTask_SendGoal_Response>
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
  const ExecuteWaypointTask_GetResult_Request & msg,
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
  const ExecuteWaypointTask_GetResult_Request & msg,
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

inline std::string to_yaml(const ExecuteWaypointTask_GetResult_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/execute_waypoint_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_GetResult_Response & msg,
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
  const ExecuteWaypointTask_GetResult_Response & msg,
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

inline std::string to_yaml(const ExecuteWaypointTask_GetResult_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_GetResult>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_GetResult>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ExecuteWaypointTask_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ExecuteWaypointTask_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ExecuteWaypointTask_GetResult_Response>
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
// #include "agt_interfaces/action/detail/execute_waypoint_task__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ExecuteWaypointTask_FeedbackMessage & msg,
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
  const ExecuteWaypointTask_FeedbackMessage & msg,
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

inline std::string to_yaml(const ExecuteWaypointTask_FeedbackMessage & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>()
{
  return "agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>()
{
  return "agt_interfaces/action/ExecuteWaypointTask_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ExecuteWaypointTask_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ExecuteWaypointTask_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ExecuteWaypointTask_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::ExecuteWaypointTask>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::ExecuteWaypointTask_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::ExecuteWaypointTask_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::ExecuteWaypointTask_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_WAYPOINT_TASK__TRAITS_HPP_
