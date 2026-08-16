// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/ManageMappingSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/manage_mapping_session__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: operation
  {
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << ", ";
  }

  // member: session_id
  {
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
    out << ", ";
  }

  // member: argument_keys
  {
    if (msg.argument_keys.size() == 0) {
      out << "argument_keys: []";
    } else {
      out << "argument_keys: [";
      size_t pending_items = msg.argument_keys.size();
      for (auto item : msg.argument_keys) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: argument_values
  {
    if (msg.argument_values.size() == 0) {
      out << "argument_values: []";
    } else {
      out << "argument_values: [";
      size_t pending_items = msg.argument_values.size();
      for (auto item : msg.argument_values) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: activate_after_commit
  {
    out << "activate_after_commit: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_after_commit, out);
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
  const ManageMappingSession_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: operation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
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

  // member: session_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
    out << "\n";
  }

  // member: argument_keys
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.argument_keys.size() == 0) {
      out << "argument_keys: []\n";
    } else {
      out << "argument_keys:\n";
      for (auto item : msg.argument_keys) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: argument_values
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.argument_values.size() == 0) {
      out << "argument_values: []\n";
    } else {
      out << "argument_values:\n";
      for (auto item : msg.argument_values) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: activate_after_commit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "activate_after_commit: ";
    rosidl_generator_traits::value_to_yaml(msg.activate_after_commit, out);
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

inline std::string to_yaml(const ManageMappingSession_Goal & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_Goal>()
{
  return "agt_interfaces::action::ManageMappingSession_Goal";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_Goal>()
{
  return "agt_interfaces/action/ManageMappingSession_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_Result & msg,
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

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: session_id
  {
    out << "session_id: ";
    rosidl_generator_traits::value_to_yaml(msg.session_id, out);
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

  // member: session_file
  {
    out << "session_file: ";
    rosidl_generator_traits::value_to_yaml(msg.session_file, out);
    out << ", ";
  }

  // member: candidate_map_yaml
  {
    out << "candidate_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_yaml, out);
    out << ", ";
  }

  // member: candidate_map_image
  {
    out << "candidate_map_image: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_image, out);
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

  // member: bag_directory
  {
    out << "bag_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_directory, out);
    out << ", ";
  }

  // member: registered_map_yaml
  {
    out << "registered_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.registered_map_yaml, out);
    out << ", ";
  }

  // member: tasks_directory
  {
    out << "tasks_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.tasks_directory, out);
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
  const ManageMappingSession_Result & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
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

  // member: session_file
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session_file: ";
    rosidl_generator_traits::value_to_yaml(msg.session_file, out);
    out << "\n";
  }

  // member: candidate_map_yaml
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "candidate_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_yaml, out);
    out << "\n";
  }

  // member: candidate_map_image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "candidate_map_image: ";
    rosidl_generator_traits::value_to_yaml(msg.candidate_map_image, out);
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

  // member: bag_directory
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bag_directory: ";
    rosidl_generator_traits::value_to_yaml(msg.bag_directory, out);
    out << "\n";
  }

  // member: registered_map_yaml
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "registered_map_yaml: ";
    rosidl_generator_traits::value_to_yaml(msg.registered_map_yaml, out);
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

inline std::string to_yaml(const ManageMappingSession_Result & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_Result>()
{
  return "agt_interfaces::action::ManageMappingSession_Result";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_Result>()
{
  return "agt_interfaces/action/ManageMappingSession_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
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
  const ManageMappingSession_Feedback & msg,
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

inline std::string to_yaml(const ManageMappingSession_Feedback & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_Feedback>()
{
  return "agt_interfaces::action::ManageMappingSession_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_Feedback>()
{
  return "agt_interfaces/action/ManageMappingSession_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/manage_mapping_session__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_SendGoal_Request & msg,
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
  const ManageMappingSession_SendGoal_Request & msg,
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

inline std::string to_yaml(const ManageMappingSession_SendGoal_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_SendGoal_Request>()
{
  return "agt_interfaces::action::ManageMappingSession_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_SendGoal_Request>()
{
  return "agt_interfaces/action/ManageMappingSession_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ManageMappingSession_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ManageMappingSession_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_SendGoal_Request>
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
  const ManageMappingSession_SendGoal_Response & msg,
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
  const ManageMappingSession_SendGoal_Response & msg,
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

inline std::string to_yaml(const ManageMappingSession_SendGoal_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_SendGoal_Response>()
{
  return "agt_interfaces::action::ManageMappingSession_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_SendGoal_Response>()
{
  return "agt_interfaces/action/ManageMappingSession_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_SendGoal>()
{
  return "agt_interfaces::action::ManageMappingSession_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_SendGoal>()
{
  return "agt_interfaces/action/ManageMappingSession_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ManageMappingSession_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::ManageMappingSession_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ManageMappingSession_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::ManageMappingSession_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ManageMappingSession_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ManageMappingSession_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ManageMappingSession_SendGoal_Response>
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
  const ManageMappingSession_GetResult_Request & msg,
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
  const ManageMappingSession_GetResult_Request & msg,
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

inline std::string to_yaml(const ManageMappingSession_GetResult_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_GetResult_Request>()
{
  return "agt_interfaces::action::ManageMappingSession_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_GetResult_Request>()
{
  return "agt_interfaces/action/ManageMappingSession_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/manage_mapping_session__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_GetResult_Response & msg,
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
  const ManageMappingSession_GetResult_Response & msg,
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

inline std::string to_yaml(const ManageMappingSession_GetResult_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_GetResult_Response>()
{
  return "agt_interfaces::action::ManageMappingSession_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_GetResult_Response>()
{
  return "agt_interfaces/action/ManageMappingSession_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ManageMappingSession_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ManageMappingSession_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_GetResult>()
{
  return "agt_interfaces::action::ManageMappingSession_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_GetResult>()
{
  return "agt_interfaces/action/ManageMappingSession_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ManageMappingSession_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::ManageMappingSession_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ManageMappingSession_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::ManageMappingSession_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ManageMappingSession_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ManageMappingSession_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ManageMappingSession_GetResult_Response>
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
// #include "agt_interfaces/action/detail/manage_mapping_session__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ManageMappingSession_FeedbackMessage & msg,
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
  const ManageMappingSession_FeedbackMessage & msg,
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

inline std::string to_yaml(const ManageMappingSession_FeedbackMessage & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ManageMappingSession_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ManageMappingSession_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ManageMappingSession_FeedbackMessage>()
{
  return "agt_interfaces::action::ManageMappingSession_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::ManageMappingSession_FeedbackMessage>()
{
  return "agt_interfaces/action/ManageMappingSession_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::ManageMappingSession_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ManageMappingSession_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ManageMappingSession_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ManageMappingSession_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ManageMappingSession_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::ManageMappingSession>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::ManageMappingSession_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::ManageMappingSession_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::ManageMappingSession_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__MANAGE_MAPPING_SESSION__TRAITS_HPP_
