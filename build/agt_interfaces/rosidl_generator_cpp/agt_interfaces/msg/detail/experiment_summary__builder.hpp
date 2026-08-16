// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/ExperimentSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/experiment_summary__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_ExperimentSummary_message
{
public:
  explicit Init_ExperimentSummary_message(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::ExperimentSummary message(::agt_interfaces::msg::ExperimentSummary::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_config_snapshot_count
{
public:
  explicit Init_ExperimentSummary_config_snapshot_count(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_message config_snapshot_count(::agt_interfaces::msg::ExperimentSummary::_config_snapshot_count_type arg)
  {
    msg_.config_snapshot_count = std::move(arg);
    return Init_ExperimentSummary_message(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_result_status
{
public:
  explicit Init_ExperimentSummary_result_status(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_config_snapshot_count result_status(::agt_interfaces::msg::ExperimentSummary::_result_status_type arg)
  {
    msg_.result_status = std::move(arg);
    return Init_ExperimentSummary_config_snapshot_count(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_launch_profile
{
public:
  explicit Init_ExperimentSummary_launch_profile(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_result_status launch_profile(::agt_interfaces::msg::ExperimentSummary::_launch_profile_type arg)
  {
    msg_.launch_profile = std::move(arg);
    return Init_ExperimentSummary_result_status(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_mission_sha256
{
public:
  explicit Init_ExperimentSummary_mission_sha256(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_launch_profile mission_sha256(::agt_interfaces::msg::ExperimentSummary::_mission_sha256_type arg)
  {
    msg_.mission_sha256 = std::move(arg);
    return Init_ExperimentSummary_launch_profile(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_mission_version
{
public:
  explicit Init_ExperimentSummary_mission_version(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_mission_sha256 mission_version(::agt_interfaces::msg::ExperimentSummary::_mission_version_type arg)
  {
    msg_.mission_version = std::move(arg);
    return Init_ExperimentSummary_mission_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_mission_id
{
public:
  explicit Init_ExperimentSummary_mission_id(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_mission_version mission_id(::agt_interfaces::msg::ExperimentSummary::_mission_id_type arg)
  {
    msg_.mission_id = std::move(arg);
    return Init_ExperimentSummary_mission_version(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_map_hash
{
public:
  explicit Init_ExperimentSummary_map_hash(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_mission_id map_hash(::agt_interfaces::msg::ExperimentSummary::_map_hash_type arg)
  {
    msg_.map_hash = std::move(arg);
    return Init_ExperimentSummary_mission_id(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_map_version_id
{
public:
  explicit Init_ExperimentSummary_map_version_id(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_map_hash map_version_id(::agt_interfaces::msg::ExperimentSummary::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ExperimentSummary_map_hash(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_map_id
{
public:
  explicit Init_ExperimentSummary_map_id(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_map_version_id map_id(::agt_interfaces::msg::ExperimentSummary::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ExperimentSummary_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_platform_profile
{
public:
  explicit Init_ExperimentSummary_platform_profile(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_map_id platform_profile(::agt_interfaces::msg::ExperimentSummary::_platform_profile_type arg)
  {
    msg_.platform_profile = std::move(arg);
    return Init_ExperimentSummary_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_end_time
{
public:
  explicit Init_ExperimentSummary_end_time(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_platform_profile end_time(::agt_interfaces::msg::ExperimentSummary::_end_time_type arg)
  {
    msg_.end_time = std::move(arg);
    return Init_ExperimentSummary_platform_profile(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_start_time
{
public:
  explicit Init_ExperimentSummary_start_time(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_end_time start_time(::agt_interfaces::msg::ExperimentSummary::_start_time_type arg)
  {
    msg_.start_time = std::move(arg);
    return Init_ExperimentSummary_end_time(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_created_at
{
public:
  explicit Init_ExperimentSummary_created_at(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_start_time created_at(::agt_interfaces::msg::ExperimentSummary::_created_at_type arg)
  {
    msg_.created_at = std::move(arg);
    return Init_ExperimentSummary_start_time(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_state
{
public:
  explicit Init_ExperimentSummary_state(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_created_at state(::agt_interfaces::msg::ExperimentSummary::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ExperimentSummary_created_at(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_title
{
public:
  explicit Init_ExperimentSummary_title(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_state title(::agt_interfaces::msg::ExperimentSummary::_title_type arg)
  {
    msg_.title = std::move(arg);
    return Init_ExperimentSummary_state(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_experiment_id
{
public:
  explicit Init_ExperimentSummary_experiment_id(::agt_interfaces::msg::ExperimentSummary & msg)
  : msg_(msg)
  {}
  Init_ExperimentSummary_title experiment_id(::agt_interfaces::msg::ExperimentSummary::_experiment_id_type arg)
  {
    msg_.experiment_id = std::move(arg);
    return Init_ExperimentSummary_title(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

class Init_ExperimentSummary_header
{
public:
  Init_ExperimentSummary_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExperimentSummary_experiment_id header(::agt_interfaces::msg::ExperimentSummary::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ExperimentSummary_experiment_id(msg_);
  }

private:
  ::agt_interfaces::msg::ExperimentSummary msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::ExperimentSummary>()
{
  return agt_interfaces::msg::builder::Init_ExperimentSummary_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__EXPERIMENT_SUMMARY__BUILDER_HPP_
