// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ManageBagSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/manage_bag_session__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ManageBagSession_Request_reason
{
public:
  explicit Init_ManageBagSession_Request_reason(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ManageBagSession_Request reason(::agt_interfaces::srv::ManageBagSession_Request::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_result_status
{
public:
  explicit Init_ManageBagSession_Request_result_status(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_reason result_status(::agt_interfaces::srv::ManageBagSession_Request::_result_status_type arg)
  {
    msg_.result_status = std::move(arg);
    return Init_ManageBagSession_Request_reason(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_metadata_json
{
public:
  explicit Init_ManageBagSession_Request_metadata_json(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_result_status metadata_json(::agt_interfaces::srv::ManageBagSession_Request::_metadata_json_type arg)
  {
    msg_.metadata_json = std::move(arg);
    return Init_ManageBagSession_Request_result_status(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_event_type
{
public:
  explicit Init_ManageBagSession_Request_event_type(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_metadata_json event_type(::agt_interfaces::srv::ManageBagSession_Request::_event_type_type arg)
  {
    msg_.event_type = std::move(arg);
    return Init_ManageBagSession_Request_metadata_json(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_start_experiment
{
public:
  explicit Init_ManageBagSession_Request_start_experiment(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_event_type start_experiment(::agt_interfaces::srv::ManageBagSession_Request::_start_experiment_type arg)
  {
    msg_.start_experiment = std::move(arg);
    return Init_ManageBagSession_Request_event_type(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_launch_profile
{
public:
  explicit Init_ManageBagSession_Request_launch_profile(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_start_experiment launch_profile(::agt_interfaces::srv::ManageBagSession_Request::_launch_profile_type arg)
  {
    msg_.launch_profile = std::move(arg);
    return Init_ManageBagSession_Request_start_experiment(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_nav2_profile
{
public:
  explicit Init_ManageBagSession_Request_nav2_profile(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_launch_profile nav2_profile(::agt_interfaces::srv::ManageBagSession_Request::_nav2_profile_type arg)
  {
    msg_.nav2_profile = std::move(arg);
    return Init_ManageBagSession_Request_launch_profile(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_calibration_profile
{
public:
  explicit Init_ManageBagSession_Request_calibration_profile(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_nav2_profile calibration_profile(::agt_interfaces::srv::ManageBagSession_Request::_calibration_profile_type arg)
  {
    msg_.calibration_profile = std::move(arg);
    return Init_ManageBagSession_Request_nav2_profile(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_platform_profile
{
public:
  explicit Init_ManageBagSession_Request_platform_profile(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_calibration_profile platform_profile(::agt_interfaces::srv::ManageBagSession_Request::_platform_profile_type arg)
  {
    msg_.platform_profile = std::move(arg);
    return Init_ManageBagSession_Request_calibration_profile(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_map_sha256
{
public:
  explicit Init_ManageBagSession_Request_map_sha256(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_platform_profile map_sha256(::agt_interfaces::srv::ManageBagSession_Request::_map_sha256_type arg)
  {
    msg_.map_sha256 = std::move(arg);
    return Init_ManageBagSession_Request_platform_profile(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_map_version_id
{
public:
  explicit Init_ManageBagSession_Request_map_version_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_map_sha256 map_version_id(::agt_interfaces::srv::ManageBagSession_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ManageBagSession_Request_map_sha256(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_map_id
{
public:
  explicit Init_ManageBagSession_Request_map_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_map_version_id map_id(::agt_interfaces::srv::ManageBagSession_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ManageBagSession_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_mission_sha256
{
public:
  explicit Init_ManageBagSession_Request_mission_sha256(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_map_id mission_sha256(::agt_interfaces::srv::ManageBagSession_Request::_mission_sha256_type arg)
  {
    msg_.mission_sha256 = std::move(arg);
    return Init_ManageBagSession_Request_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_mission_version
{
public:
  explicit Init_ManageBagSession_Request_mission_version(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_mission_sha256 mission_version(::agt_interfaces::srv::ManageBagSession_Request::_mission_version_type arg)
  {
    msg_.mission_version = std::move(arg);
    return Init_ManageBagSession_Request_mission_sha256(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_mission_id
{
public:
  explicit Init_ManageBagSession_Request_mission_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_mission_version mission_id(::agt_interfaces::srv::ManageBagSession_Request::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_ManageBagSession_Request_mission_version(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_playback_rate
{
public:
  explicit Init_ManageBagSession_Request_playback_rate(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_mission_id playback_rate(::agt_interfaces::srv::ManageBagSession_Request::_playback_rate_type arg)
  {
    msg_.playback_rate = std::move(arg);
    return Init_ManageBagSession_Request_mission_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_profile_id
{
public:
  explicit Init_ManageBagSession_Request_profile_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_playback_rate profile_id(::agt_interfaces::srv::ManageBagSession_Request::_profile_id_type arg)
  {
    msg_.profile_id = std::move(arg);
    return Init_ManageBagSession_Request_playback_rate(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_operator_note
{
public:
  explicit Init_ManageBagSession_Request_operator_note(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_profile_id operator_note(::agt_interfaces::srv::ManageBagSession_Request::_operator_note_type arg)
  {
    msg_.operator_note = std::move(arg);
    return Init_ManageBagSession_Request_profile_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_tags_json
{
public:
  explicit Init_ManageBagSession_Request_tags_json(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_operator_note tags_json(::agt_interfaces::srv::ManageBagSession_Request::_tags_json_type arg)
  {
    msg_.tags_json = std::move(arg);
    return Init_ManageBagSession_Request_operator_note(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_hypothesis
{
public:
  explicit Init_ManageBagSession_Request_hypothesis(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_tags_json hypothesis(::agt_interfaces::srv::ManageBagSession_Request::_hypothesis_type arg)
  {
    msg_.hypothesis = std::move(arg);
    return Init_ManageBagSession_Request_tags_json(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_objective
{
public:
  explicit Init_ManageBagSession_Request_objective(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_hypothesis objective(::agt_interfaces::srv::ManageBagSession_Request::_objective_type arg)
  {
    msg_.objective = std::move(arg);
    return Init_ManageBagSession_Request_hypothesis(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_experiment_title
{
public:
  explicit Init_ManageBagSession_Request_experiment_title(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_objective experiment_title(::agt_interfaces::srv::ManageBagSession_Request::_experiment_title_type arg)
  {
    msg_.experiment_title = std::move(arg);
    return Init_ManageBagSession_Request_objective(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_experiment_id
{
public:
  explicit Init_ManageBagSession_Request_experiment_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_experiment_title experiment_id(::agt_interfaces::srv::ManageBagSession_Request::_experiment_id_type arg)
  {
    msg_.experiment_id = std::move(arg);
    return Init_ManageBagSession_Request_experiment_title(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_bag_id
{
public:
  explicit Init_ManageBagSession_Request_bag_id(::agt_interfaces::srv::ManageBagSession_Request & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Request_experiment_id bag_id(::agt_interfaces::srv::ManageBagSession_Request::_bag_id_type arg)
  {
    msg_.bag_id = std::move(arg);
    return Init_ManageBagSession_Request_experiment_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

class Init_ManageBagSession_Request_operation
{
public:
  Init_ManageBagSession_Request_operation()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageBagSession_Request_bag_id operation(::agt_interfaces::srv::ManageBagSession_Request::_operation_type arg)
  {
    msg_.operation = std::move(arg);
    return Init_ManageBagSession_Request_bag_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ManageBagSession_Request>()
{
  return agt_interfaces::srv::builder::Init_ManageBagSession_Request_operation();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ManageBagSession_Response_message
{
public:
  explicit Init_ManageBagSession_Response_message(::agt_interfaces::srv::ManageBagSession_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ManageBagSession_Response message(::agt_interfaces::srv::ManageBagSession_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Response msg_;
};

class Init_ManageBagSession_Response_session
{
public:
  explicit Init_ManageBagSession_Response_session(::agt_interfaces::srv::ManageBagSession_Response & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Response_message session(::agt_interfaces::srv::ManageBagSession_Response::_session_type arg)
  {
    msg_.session = std::move(arg);
    return Init_ManageBagSession_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Response msg_;
};

class Init_ManageBagSession_Response_error_code
{
public:
  explicit Init_ManageBagSession_Response_error_code(::agt_interfaces::srv::ManageBagSession_Response & msg)
  : msg_(msg)
  {}
  Init_ManageBagSession_Response_session error_code(::agt_interfaces::srv::ManageBagSession_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ManageBagSession_Response_session(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Response msg_;
};

class Init_ManageBagSession_Response_success
{
public:
  Init_ManageBagSession_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageBagSession_Response_error_code success(::agt_interfaces::srv::ManageBagSession_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ManageBagSession_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ManageBagSession_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ManageBagSession_Response>()
{
  return agt_interfaces::srv::builder::Init_ManageBagSession_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_BAG_SESSION__BUILDER_HPP_
