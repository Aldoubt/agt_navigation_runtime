// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ListTaskGroups.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/list_task_groups__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListTaskGroups_Request_map_version_id
{
public:
  explicit Init_ListTaskGroups_Request_map_version_id(::agt_interfaces::srv::ListTaskGroups_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListTaskGroups_Request map_version_id(::agt_interfaces::srv::ListTaskGroups_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Request msg_;
};

class Init_ListTaskGroups_Request_map_id
{
public:
  Init_ListTaskGroups_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListTaskGroups_Request_map_version_id map_id(::agt_interfaces::srv::ListTaskGroups_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ListTaskGroups_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListTaskGroups_Request>()
{
  return agt_interfaces::srv::builder::Init_ListTaskGroups_Request_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListTaskGroups_Response_validation_states
{
public:
  explicit Init_ListTaskGroups_Response_validation_states(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListTaskGroups_Response validation_states(::agt_interfaces::srv::ListTaskGroups_Response::_validation_states_type arg)
  {
    msg_.validation_states = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_updated_at
{
public:
  explicit Init_ListTaskGroups_Response_updated_at(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_validation_states updated_at(::agt_interfaces::srv::ListTaskGroups_Response::_updated_at_type arg)
  {
    msg_.updated_at = std::move(arg);
    return Init_ListTaskGroups_Response_validation_states(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_enabled_point_counts
{
public:
  explicit Init_ListTaskGroups_Response_enabled_point_counts(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_updated_at enabled_point_counts(::agt_interfaces::srv::ListTaskGroups_Response::_enabled_point_counts_type arg)
  {
    msg_.enabled_point_counts = std::move(arg);
    return Init_ListTaskGroups_Response_updated_at(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_content_sha256
{
public:
  explicit Init_ListTaskGroups_Response_content_sha256(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_enabled_point_counts content_sha256(::agt_interfaces::srv::ListTaskGroups_Response::_content_sha256_type arg)
  {
    msg_.content_sha256 = std::move(arg);
    return Init_ListTaskGroups_Response_enabled_point_counts(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_revisions
{
public:
  explicit Init_ListTaskGroups_Response_revisions(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_content_sha256 revisions(::agt_interfaces::srv::ListTaskGroups_Response::_revisions_type arg)
  {
    msg_.revisions = std::move(arg);
    return Init_ListTaskGroups_Response_content_sha256(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_names
{
public:
  explicit Init_ListTaskGroups_Response_names(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_revisions names(::agt_interfaces::srv::ListTaskGroups_Response::_names_type arg)
  {
    msg_.names = std::move(arg);
    return Init_ListTaskGroups_Response_revisions(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_task_group_ids
{
public:
  explicit Init_ListTaskGroups_Response_task_group_ids(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_names task_group_ids(::agt_interfaces::srv::ListTaskGroups_Response::_task_group_ids_type arg)
  {
    msg_.task_group_ids = std::move(arg);
    return Init_ListTaskGroups_Response_names(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_map_version_id
{
public:
  explicit Init_ListTaskGroups_Response_map_version_id(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_task_group_ids map_version_id(::agt_interfaces::srv::ListTaskGroups_Response::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ListTaskGroups_Response_task_group_ids(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_map_id
{
public:
  explicit Init_ListTaskGroups_Response_map_id(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_map_version_id map_id(::agt_interfaces::srv::ListTaskGroups_Response::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ListTaskGroups_Response_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_technical_message
{
public:
  explicit Init_ListTaskGroups_Response_technical_message(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_map_id technical_message(::agt_interfaces::srv::ListTaskGroups_Response::_technical_message_type arg)
  {
    msg_.technical_message = std::move(arg);
    return Init_ListTaskGroups_Response_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_operator_message
{
public:
  explicit Init_ListTaskGroups_Response_operator_message(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_technical_message operator_message(::agt_interfaces::srv::ListTaskGroups_Response::_operator_message_type arg)
  {
    msg_.operator_message = std::move(arg);
    return Init_ListTaskGroups_Response_technical_message(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_blocker_code
{
public:
  explicit Init_ListTaskGroups_Response_blocker_code(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_operator_message blocker_code(::agt_interfaces::srv::ListTaskGroups_Response::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_ListTaskGroups_Response_operator_message(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_error_code
{
public:
  explicit Init_ListTaskGroups_Response_error_code(::agt_interfaces::srv::ListTaskGroups_Response & msg)
  : msg_(msg)
  {}
  Init_ListTaskGroups_Response_blocker_code error_code(::agt_interfaces::srv::ListTaskGroups_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ListTaskGroups_Response_blocker_code(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

class Init_ListTaskGroups_Response_success
{
public:
  Init_ListTaskGroups_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListTaskGroups_Response_error_code success(::agt_interfaces::srv::ListTaskGroups_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ListTaskGroups_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ListTaskGroups_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListTaskGroups_Response>()
{
  return agt_interfaces::srv::builder::Init_ListTaskGroups_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_TASK_GROUPS__BUILDER_HPP_
