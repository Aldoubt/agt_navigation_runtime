// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:action/ChangeSystemMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__TRAITS_HPP_
#define AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/action/detail/change_system_mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: profile
  {
    out << "profile: ";
    rosidl_generator_traits::value_to_yaml(msg.profile, out);
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

  // member: wait_for_health
  {
    out << "wait_for_health: ";
    rosidl_generator_traits::value_to_yaml(msg.wait_for_health, out);
    out << ", ";
  }

  // member: startup_timeout_s
  {
    out << "startup_timeout_s: ";
    rosidl_generator_traits::value_to_yaml(msg.startup_timeout_s, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChangeSystemMode_Goal & msg,
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

  // member: profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "profile: ";
    rosidl_generator_traits::value_to_yaml(msg.profile, out);
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

  // member: wait_for_health
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "wait_for_health: ";
    rosidl_generator_traits::value_to_yaml(msg.wait_for_health, out);
    out << "\n";
  }

  // member: startup_timeout_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "startup_timeout_s: ";
    rosidl_generator_traits::value_to_yaml(msg.startup_timeout_s, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChangeSystemMode_Goal & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_Goal & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_Goal>()
{
  return "agt_interfaces::action::ChangeSystemMode_Goal";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_Goal>()
{
  return "agt_interfaces/action/ChangeSystemMode_Goal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_Result & msg,
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

  // member: active_mode
  {
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
    out << ", ";
  }

  // member: profile
  {
    out << "profile: ";
    rosidl_generator_traits::value_to_yaml(msg.profile, out);
    out << ", ";
  }

  // member: process_ids
  {
    if (msg.process_ids.size() == 0) {
      out << "process_ids: []";
    } else {
      out << "process_ids: [";
      size_t pending_items = msg.process_ids.size();
      for (auto item : msg.process_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: log_paths
  {
    if (msg.log_paths.size() == 0) {
      out << "log_paths: []";
    } else {
      out << "log_paths: [";
      size_t pending_items = msg.log_paths.size();
      for (auto item : msg.log_paths) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
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
  const ChangeSystemMode_Result & msg,
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

  // member: active_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.active_mode, out);
    out << "\n";
  }

  // member: profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "profile: ";
    rosidl_generator_traits::value_to_yaml(msg.profile, out);
    out << "\n";
  }

  // member: process_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.process_ids.size() == 0) {
      out << "process_ids: []\n";
    } else {
      out << "process_ids:\n";
      for (auto item : msg.process_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: log_paths
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.log_paths.size() == 0) {
      out << "log_paths: []\n";
    } else {
      out << "log_paths:\n";
      for (auto item : msg.log_paths) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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

inline std::string to_yaml(const ChangeSystemMode_Result & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_Result & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_Result>()
{
  return "agt_interfaces::action::ChangeSystemMode_Result";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_Result>()
{
  return "agt_interfaces/action/ChangeSystemMode_Result";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_Feedback & msg,
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
  const ChangeSystemMode_Feedback & msg,
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

inline std::string to_yaml(const ChangeSystemMode_Feedback & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_Feedback & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_Feedback>()
{
  return "agt_interfaces::action::ChangeSystemMode_Feedback";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_Feedback>()
{
  return "agt_interfaces/action/ChangeSystemMode_Feedback";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "agt_interfaces/action/detail/change_system_mode__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_SendGoal_Request & msg,
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
  const ChangeSystemMode_SendGoal_Request & msg,
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

inline std::string to_yaml(const ChangeSystemMode_SendGoal_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_SendGoal_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>()
{
  return "agt_interfaces::action::ChangeSystemMode_SendGoal_Request";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>()
{
  return "agt_interfaces/action/ChangeSystemMode_SendGoal_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ChangeSystemMode_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ChangeSystemMode_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>
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
  const ChangeSystemMode_SendGoal_Response & msg,
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
  const ChangeSystemMode_SendGoal_Response & msg,
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

inline std::string to_yaml(const ChangeSystemMode_SendGoal_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_SendGoal_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>()
{
  return "agt_interfaces::action::ChangeSystemMode_SendGoal_Response";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>()
{
  return "agt_interfaces/action/ChangeSystemMode_SendGoal_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_SendGoal>()
{
  return "agt_interfaces::action::ChangeSystemMode_SendGoal";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_SendGoal>()
{
  return "agt_interfaces/action/ChangeSystemMode_SendGoal";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>::value &&
    has_fixed_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>::value &&
    has_bounded_size<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ChangeSystemMode_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ChangeSystemMode_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ChangeSystemMode_SendGoal_Response>
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
  const ChangeSystemMode_GetResult_Request & msg,
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
  const ChangeSystemMode_GetResult_Request & msg,
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

inline std::string to_yaml(const ChangeSystemMode_GetResult_Request & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_GetResult_Request & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_GetResult_Request>()
{
  return "agt_interfaces::action::ChangeSystemMode_GetResult_Request";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_GetResult_Request>()
{
  return "agt_interfaces/action/ChangeSystemMode_GetResult_Request";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "agt_interfaces/action/detail/change_system_mode__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_GetResult_Response & msg,
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
  const ChangeSystemMode_GetResult_Response & msg,
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

inline std::string to_yaml(const ChangeSystemMode_GetResult_Response & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_GetResult_Response & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_GetResult_Response>()
{
  return "agt_interfaces::action::ChangeSystemMode_GetResult_Response";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_GetResult_Response>()
{
  return "agt_interfaces/action/ChangeSystemMode_GetResult_Response";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ChangeSystemMode_Result>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ChangeSystemMode_Result>::value> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_GetResult>()
{
  return "agt_interfaces::action::ChangeSystemMode_GetResult";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_GetResult>()
{
  return "agt_interfaces/action/ChangeSystemMode_GetResult";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::action::ChangeSystemMode_GetResult_Request>::value &&
    has_fixed_size<agt_interfaces::action::ChangeSystemMode_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::action::ChangeSystemMode_GetResult_Request>::value &&
    has_bounded_size<agt_interfaces::action::ChangeSystemMode_GetResult_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::action::ChangeSystemMode_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::action::ChangeSystemMode_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::action::ChangeSystemMode_GetResult_Response>
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
// #include "agt_interfaces/action/detail/change_system_mode__traits.hpp"

namespace agt_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const ChangeSystemMode_FeedbackMessage & msg,
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
  const ChangeSystemMode_FeedbackMessage & msg,
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

inline std::string to_yaml(const ChangeSystemMode_FeedbackMessage & msg, bool use_flow_style = false)
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
  const agt_interfaces::action::ChangeSystemMode_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::action::ChangeSystemMode_FeedbackMessage & msg)
{
  return agt_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::action::ChangeSystemMode_FeedbackMessage>()
{
  return "agt_interfaces::action::ChangeSystemMode_FeedbackMessage";
}

template<>
inline const char * name<agt_interfaces::action::ChangeSystemMode_FeedbackMessage>()
{
  return "agt_interfaces/action/ChangeSystemMode_FeedbackMessage";
}

template<>
struct has_fixed_size<agt_interfaces::action::ChangeSystemMode_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<agt_interfaces::action::ChangeSystemMode_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<agt_interfaces::action::ChangeSystemMode_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<agt_interfaces::action::ChangeSystemMode_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<agt_interfaces::action::ChangeSystemMode_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<agt_interfaces::action::ChangeSystemMode>
  : std::true_type
{
};

template<>
struct is_action_goal<agt_interfaces::action::ChangeSystemMode_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<agt_interfaces::action::ChangeSystemMode_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<agt_interfaces::action::ChangeSystemMode_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // AGT_INTERFACES__ACTION__DETAIL__CHANGE_SYSTEM_MODE__TRAITS_HPP_
