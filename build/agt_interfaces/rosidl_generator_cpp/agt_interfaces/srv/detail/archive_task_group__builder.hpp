// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ArchiveTaskGroup.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/archive_task_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ArchiveTaskGroup_Request_client_request_id
{
public:
  explicit Init_ArchiveTaskGroup_Request_client_request_id(::agt_interfaces::srv::ArchiveTaskGroup_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ArchiveTaskGroup_Request client_request_id(::agt_interfaces::srv::ArchiveTaskGroup_Request::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Request msg_;
};

class Init_ArchiveTaskGroup_Request_expected_revision
{
public:
  explicit Init_ArchiveTaskGroup_Request_expected_revision(::agt_interfaces::srv::ArchiveTaskGroup_Request & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Request_client_request_id expected_revision(::agt_interfaces::srv::ArchiveTaskGroup_Request::_expected_revision_type arg)
  {
    msg_.expected_revision = std::move(arg);
    return Init_ArchiveTaskGroup_Request_client_request_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Request msg_;
};

class Init_ArchiveTaskGroup_Request_task_group_id
{
public:
  explicit Init_ArchiveTaskGroup_Request_task_group_id(::agt_interfaces::srv::ArchiveTaskGroup_Request & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Request_expected_revision task_group_id(::agt_interfaces::srv::ArchiveTaskGroup_Request::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_ArchiveTaskGroup_Request_expected_revision(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Request msg_;
};

class Init_ArchiveTaskGroup_Request_map_version_id
{
public:
  explicit Init_ArchiveTaskGroup_Request_map_version_id(::agt_interfaces::srv::ArchiveTaskGroup_Request & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Request_task_group_id map_version_id(::agt_interfaces::srv::ArchiveTaskGroup_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ArchiveTaskGroup_Request_task_group_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Request msg_;
};

class Init_ArchiveTaskGroup_Request_map_id
{
public:
  Init_ArchiveTaskGroup_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArchiveTaskGroup_Request_map_version_id map_id(::agt_interfaces::srv::ArchiveTaskGroup_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ArchiveTaskGroup_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ArchiveTaskGroup_Request>()
{
  return agt_interfaces::srv::builder::Init_ArchiveTaskGroup_Request_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ArchiveTaskGroup_Response_archived_relative_path
{
public:
  explicit Init_ArchiveTaskGroup_Response_archived_relative_path(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ArchiveTaskGroup_Response archived_relative_path(::agt_interfaces::srv::ArchiveTaskGroup_Response::_archived_relative_path_type arg)
  {
    msg_.archived_relative_path = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_archived_revision
{
public:
  explicit Init_ArchiveTaskGroup_Response_archived_revision(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_archived_relative_path archived_revision(::agt_interfaces::srv::ArchiveTaskGroup_Response::_archived_revision_type arg)
  {
    msg_.archived_revision = std::move(arg);
    return Init_ArchiveTaskGroup_Response_archived_relative_path(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_task_group_id
{
public:
  explicit Init_ArchiveTaskGroup_Response_task_group_id(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_archived_revision task_group_id(::agt_interfaces::srv::ArchiveTaskGroup_Response::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_ArchiveTaskGroup_Response_archived_revision(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_map_version_id
{
public:
  explicit Init_ArchiveTaskGroup_Response_map_version_id(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_task_group_id map_version_id(::agt_interfaces::srv::ArchiveTaskGroup_Response::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ArchiveTaskGroup_Response_task_group_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_map_id
{
public:
  explicit Init_ArchiveTaskGroup_Response_map_id(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_map_version_id map_id(::agt_interfaces::srv::ArchiveTaskGroup_Response::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ArchiveTaskGroup_Response_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_duplicate_request
{
public:
  explicit Init_ArchiveTaskGroup_Response_duplicate_request(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_map_id duplicate_request(::agt_interfaces::srv::ArchiveTaskGroup_Response::_duplicate_request_type arg)
  {
    msg_.duplicate_request = std::move(arg);
    return Init_ArchiveTaskGroup_Response_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_technical_message
{
public:
  explicit Init_ArchiveTaskGroup_Response_technical_message(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_duplicate_request technical_message(::agt_interfaces::srv::ArchiveTaskGroup_Response::_technical_message_type arg)
  {
    msg_.technical_message = std::move(arg);
    return Init_ArchiveTaskGroup_Response_duplicate_request(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_operator_message
{
public:
  explicit Init_ArchiveTaskGroup_Response_operator_message(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_technical_message operator_message(::agt_interfaces::srv::ArchiveTaskGroup_Response::_operator_message_type arg)
  {
    msg_.operator_message = std::move(arg);
    return Init_ArchiveTaskGroup_Response_technical_message(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_blocker_code
{
public:
  explicit Init_ArchiveTaskGroup_Response_blocker_code(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_operator_message blocker_code(::agt_interfaces::srv::ArchiveTaskGroup_Response::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_ArchiveTaskGroup_Response_operator_message(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_error_code
{
public:
  explicit Init_ArchiveTaskGroup_Response_error_code(::agt_interfaces::srv::ArchiveTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_ArchiveTaskGroup_Response_blocker_code error_code(::agt_interfaces::srv::ArchiveTaskGroup_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ArchiveTaskGroup_Response_blocker_code(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

class Init_ArchiveTaskGroup_Response_success
{
public:
  Init_ArchiveTaskGroup_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArchiveTaskGroup_Response_error_code success(::agt_interfaces::srv::ArchiveTaskGroup_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ArchiveTaskGroup_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ArchiveTaskGroup_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ArchiveTaskGroup_Response>()
{
  return agt_interfaces::srv::builder::Init_ArchiveTaskGroup_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__BUILDER_HPP_
