// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agt_interfaces:srv/ManageBagSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__TRAITS_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agt_interfaces/srv/detail/manage_bag_session__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ManageBagSession_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: operation
  {
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
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

  // member: experiment_title
  {
    out << "experiment_title: ";
    rosidl_generator_traits::value_to_yaml(msg.experiment_title, out);
    out << ", ";
  }

  // member: objective
  {
    out << "objective: ";
    rosidl_generator_traits::value_to_yaml(msg.objective, out);
    out << ", ";
  }

  // member: hypothesis
  {
    out << "hypothesis: ";
    rosidl_generator_traits::value_to_yaml(msg.hypothesis, out);
    out << ", ";
  }

  // member: tags_json
  {
    out << "tags_json: ";
    rosidl_generator_traits::value_to_yaml(msg.tags_json, out);
    out << ", ";
  }

  // member: operator_note
  {
    out << "operator_note: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_note, out);
    out << ", ";
  }

  // member: profile_id
  {
    out << "profile_id: ";
    rosidl_generator_traits::value_to_yaml(msg.profile_id, out);
    out << ", ";
  }

  // member: playback_rate
  {
    out << "playback_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.playback_rate, out);
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

  // member: map_sha256
  {
    out << "map_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.map_sha256, out);
    out << ", ";
  }

  // member: platform_profile
  {
    out << "platform_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_profile, out);
    out << ", ";
  }

  // member: calibration_profile
  {
    out << "calibration_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_profile, out);
    out << ", ";
  }

  // member: nav2_profile
  {
    out << "nav2_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_profile, out);
    out << ", ";
  }

  // member: launch_profile
  {
    out << "launch_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.launch_profile, out);
    out << ", ";
  }

  // member: start_experiment
  {
    out << "start_experiment: ";
    rosidl_generator_traits::value_to_yaml(msg.start_experiment, out);
    out << ", ";
  }

  // member: event_type
  {
    out << "event_type: ";
    rosidl_generator_traits::value_to_yaml(msg.event_type, out);
    out << ", ";
  }

  // member: metadata_json
  {
    out << "metadata_json: ";
    rosidl_generator_traits::value_to_yaml(msg.metadata_json, out);
    out << ", ";
  }

  // member: result_status
  {
    out << "result_status: ";
    rosidl_generator_traits::value_to_yaml(msg.result_status, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ManageBagSession_Request & msg,
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

  // member: experiment_title
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "experiment_title: ";
    rosidl_generator_traits::value_to_yaml(msg.experiment_title, out);
    out << "\n";
  }

  // member: objective
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "objective: ";
    rosidl_generator_traits::value_to_yaml(msg.objective, out);
    out << "\n";
  }

  // member: hypothesis
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hypothesis: ";
    rosidl_generator_traits::value_to_yaml(msg.hypothesis, out);
    out << "\n";
  }

  // member: tags_json
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tags_json: ";
    rosidl_generator_traits::value_to_yaml(msg.tags_json, out);
    out << "\n";
  }

  // member: operator_note
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operator_note: ";
    rosidl_generator_traits::value_to_yaml(msg.operator_note, out);
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

  // member: playback_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "playback_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.playback_rate, out);
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

  // member: map_sha256
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_sha256: ";
    rosidl_generator_traits::value_to_yaml(msg.map_sha256, out);
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

  // member: calibration_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calibration_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.calibration_profile, out);
    out << "\n";
  }

  // member: nav2_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nav2_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.nav2_profile, out);
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

  // member: start_experiment
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_experiment: ";
    rosidl_generator_traits::value_to_yaml(msg.start_experiment, out);
    out << "\n";
  }

  // member: event_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "event_type: ";
    rosidl_generator_traits::value_to_yaml(msg.event_type, out);
    out << "\n";
  }

  // member: metadata_json
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "metadata_json: ";
    rosidl_generator_traits::value_to_yaml(msg.metadata_json, out);
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

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ManageBagSession_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::srv::ManageBagSession_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ManageBagSession_Request & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ManageBagSession_Request>()
{
  return "agt_interfaces::srv::ManageBagSession_Request";
}

template<>
inline const char * name<agt_interfaces::srv::ManageBagSession_Request>()
{
  return "agt_interfaces/srv/ManageBagSession_Request";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageBagSession_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageBagSession_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ManageBagSession_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'session'
#include "agt_interfaces/msg/detail/bag_session_summary__traits.hpp"

namespace agt_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ManageBagSession_Response & msg,
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

  // member: session
  {
    out << "session: ";
    to_flow_style_yaml(msg.session, out);
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
  const ManageBagSession_Response & msg,
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

  // member: session
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session:\n";
    to_block_style_yaml(msg.session, out, indentation + 2);
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

inline std::string to_yaml(const ManageBagSession_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use agt_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agt_interfaces::srv::ManageBagSession_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  agt_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agt_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const agt_interfaces::srv::ManageBagSession_Response & msg)
{
  return agt_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<agt_interfaces::srv::ManageBagSession_Response>()
{
  return "agt_interfaces::srv::ManageBagSession_Response";
}

template<>
inline const char * name<agt_interfaces::srv::ManageBagSession_Response>()
{
  return "agt_interfaces/srv/ManageBagSession_Response";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageBagSession_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageBagSession_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agt_interfaces::srv::ManageBagSession_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<agt_interfaces::srv::ManageBagSession>()
{
  return "agt_interfaces::srv::ManageBagSession";
}

template<>
inline const char * name<agt_interfaces::srv::ManageBagSession>()
{
  return "agt_interfaces/srv/ManageBagSession";
}

template<>
struct has_fixed_size<agt_interfaces::srv::ManageBagSession>
  : std::integral_constant<
    bool,
    has_fixed_size<agt_interfaces::srv::ManageBagSession_Request>::value &&
    has_fixed_size<agt_interfaces::srv::ManageBagSession_Response>::value
  >
{
};

template<>
struct has_bounded_size<agt_interfaces::srv::ManageBagSession>
  : std::integral_constant<
    bool,
    has_bounded_size<agt_interfaces::srv::ManageBagSession_Request>::value &&
    has_bounded_size<agt_interfaces::srv::ManageBagSession_Response>::value
  >
{
};

template<>
struct is_service<agt_interfaces::srv::ManageBagSession>
  : std::true_type
{
};

template<>
struct is_service_request<agt_interfaces::srv::ManageBagSession_Request>
  : std::true_type
{
};

template<>
struct is_service_response<agt_interfaces::srv::ManageBagSession_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__TRAITS_HPP_
