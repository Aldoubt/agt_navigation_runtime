// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/GetTaskGroup.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/get_task_group__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetTaskGroup_Request_task_revision
{
public:
  explicit Init_GetTaskGroup_Request_task_revision(::agt_interfaces::srv::GetTaskGroup_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::GetTaskGroup_Request task_revision(::agt_interfaces::srv::GetTaskGroup_Request::_task_revision_type arg)
  {
    msg_.task_revision = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Request msg_;
};

class Init_GetTaskGroup_Request_task_group_id
{
public:
  explicit Init_GetTaskGroup_Request_task_group_id(::agt_interfaces::srv::GetTaskGroup_Request & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Request_task_revision task_group_id(::agt_interfaces::srv::GetTaskGroup_Request::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_GetTaskGroup_Request_task_revision(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Request msg_;
};

class Init_GetTaskGroup_Request_map_version_id
{
public:
  explicit Init_GetTaskGroup_Request_map_version_id(::agt_interfaces::srv::GetTaskGroup_Request & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Request_task_group_id map_version_id(::agt_interfaces::srv::GetTaskGroup_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_GetTaskGroup_Request_task_group_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Request msg_;
};

class Init_GetTaskGroup_Request_map_id
{
public:
  Init_GetTaskGroup_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTaskGroup_Request_map_version_id map_id(::agt_interfaces::srv::GetTaskGroup_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_GetTaskGroup_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetTaskGroup_Request>()
{
  return agt_interfaces::srv::builder::Init_GetTaskGroup_Request_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetTaskGroup_Response_task_json
{
public:
  explicit Init_GetTaskGroup_Response_task_json(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::GetTaskGroup_Response task_json(::agt_interfaces::srv::GetTaskGroup_Response::_task_json_type arg)
  {
    msg_.task_json = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_content_sha256
{
public:
  explicit Init_GetTaskGroup_Response_content_sha256(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_task_json content_sha256(::agt_interfaces::srv::GetTaskGroup_Response::_content_sha256_type arg)
  {
    msg_.content_sha256 = std::move(arg);
    return Init_GetTaskGroup_Response_task_json(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_revision
{
public:
  explicit Init_GetTaskGroup_Response_revision(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_content_sha256 revision(::agt_interfaces::srv::GetTaskGroup_Response::_revision_type arg)
  {
    msg_.revision = std::move(arg);
    return Init_GetTaskGroup_Response_content_sha256(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_task_group_id
{
public:
  explicit Init_GetTaskGroup_Response_task_group_id(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_revision task_group_id(::agt_interfaces::srv::GetTaskGroup_Response::_task_group_id_type arg)
  {
    msg_.task_group_id = std::move(arg);
    return Init_GetTaskGroup_Response_revision(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_map_version_id
{
public:
  explicit Init_GetTaskGroup_Response_map_version_id(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_task_group_id map_version_id(::agt_interfaces::srv::GetTaskGroup_Response::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_GetTaskGroup_Response_task_group_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_map_id
{
public:
  explicit Init_GetTaskGroup_Response_map_id(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_map_version_id map_id(::agt_interfaces::srv::GetTaskGroup_Response::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_GetTaskGroup_Response_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_technical_message
{
public:
  explicit Init_GetTaskGroup_Response_technical_message(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_map_id technical_message(::agt_interfaces::srv::GetTaskGroup_Response::_technical_message_type arg)
  {
    msg_.technical_message = std::move(arg);
    return Init_GetTaskGroup_Response_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_operator_message
{
public:
  explicit Init_GetTaskGroup_Response_operator_message(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_technical_message operator_message(::agt_interfaces::srv::GetTaskGroup_Response::_operator_message_type arg)
  {
    msg_.operator_message = std::move(arg);
    return Init_GetTaskGroup_Response_technical_message(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_blocker_code
{
public:
  explicit Init_GetTaskGroup_Response_blocker_code(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_operator_message blocker_code(::agt_interfaces::srv::GetTaskGroup_Response::_blocker_code_type arg)
  {
    msg_.blocker_code = std::move(arg);
    return Init_GetTaskGroup_Response_operator_message(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_error_code
{
public:
  explicit Init_GetTaskGroup_Response_error_code(::agt_interfaces::srv::GetTaskGroup_Response & msg)
  : msg_(msg)
  {}
  Init_GetTaskGroup_Response_blocker_code error_code(::agt_interfaces::srv::GetTaskGroup_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_GetTaskGroup_Response_blocker_code(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

class Init_GetTaskGroup_Response_success
{
public:
  Init_GetTaskGroup_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTaskGroup_Response_error_code success(::agt_interfaces::srv::GetTaskGroup_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetTaskGroup_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::GetTaskGroup_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::GetTaskGroup_Response>()
{
  return agt_interfaces::srv::builder::Init_GetTaskGroup_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_TASK_GROUP__BUILDER_HPP_
