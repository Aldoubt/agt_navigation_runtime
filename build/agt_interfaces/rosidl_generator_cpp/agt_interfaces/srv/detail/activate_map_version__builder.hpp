// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/activate_map_version__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ActivateMapVersion_Request_client_request_id
{
public:
  explicit Init_ActivateMapVersion_Request_client_request_id(::agt_interfaces::srv::ActivateMapVersion_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ActivateMapVersion_Request client_request_id(::agt_interfaces::srv::ActivateMapVersion_Request::_client_request_id_type arg)
  {
    msg_.client_request_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Request msg_;
};

class Init_ActivateMapVersion_Request_map_version_id
{
public:
  explicit Init_ActivateMapVersion_Request_map_version_id(::agt_interfaces::srv::ActivateMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Request_client_request_id map_version_id(::agt_interfaces::srv::ActivateMapVersion_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ActivateMapVersion_Request_client_request_id(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Request msg_;
};

class Init_ActivateMapVersion_Request_map_id
{
public:
  Init_ActivateMapVersion_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActivateMapVersion_Request_map_version_id map_id(::agt_interfaces::srv::ActivateMapVersion_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ActivateMapVersion_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ActivateMapVersion_Request>()
{
  return agt_interfaces::srv::builder::Init_ActivateMapVersion_Request_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ActivateMapVersion_Response_version
{
public:
  explicit Init_ActivateMapVersion_Response_version(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ActivateMapVersion_Response version(::agt_interfaces::srv::ActivateMapVersion_Response::_version_type arg)
  {
    msg_.version = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_technical_messages
{
public:
  explicit Init_ActivateMapVersion_Response_technical_messages(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_version technical_messages(::agt_interfaces::srv::ActivateMapVersion_Response::_technical_messages_type arg)
  {
    msg_.technical_messages = std::move(arg);
    return Init_ActivateMapVersion_Response_version(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_operator_messages
{
public:
  explicit Init_ActivateMapVersion_Response_operator_messages(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_technical_messages operator_messages(::agt_interfaces::srv::ActivateMapVersion_Response::_operator_messages_type arg)
  {
    msg_.operator_messages = std::move(arg);
    return Init_ActivateMapVersion_Response_technical_messages(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_blocker_messages
{
public:
  explicit Init_ActivateMapVersion_Response_blocker_messages(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_operator_messages blocker_messages(::agt_interfaces::srv::ActivateMapVersion_Response::_blocker_messages_type arg)
  {
    msg_.blocker_messages = std::move(arg);
    return Init_ActivateMapVersion_Response_operator_messages(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_blocker_codes
{
public:
  explicit Init_ActivateMapVersion_Response_blocker_codes(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_blocker_messages blocker_codes(::agt_interfaces::srv::ActivateMapVersion_Response::_blocker_codes_type arg)
  {
    msg_.blocker_codes = std::move(arg);
    return Init_ActivateMapVersion_Response_blocker_messages(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_state
{
public:
  explicit Init_ActivateMapVersion_Response_state(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_blocker_codes state(::agt_interfaces::srv::ActivateMapVersion_Response::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ActivateMapVersion_Response_blocker_codes(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_map_version_id
{
public:
  explicit Init_ActivateMapVersion_Response_map_version_id(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_state map_version_id(::agt_interfaces::srv::ActivateMapVersion_Response::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ActivateMapVersion_Response_state(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_map_id
{
public:
  explicit Init_ActivateMapVersion_Response_map_id(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_map_version_id map_id(::agt_interfaces::srv::ActivateMapVersion_Response::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ActivateMapVersion_Response_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_error_code
{
public:
  explicit Init_ActivateMapVersion_Response_error_code(::agt_interfaces::srv::ActivateMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ActivateMapVersion_Response_map_id error_code(::agt_interfaces::srv::ActivateMapVersion_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ActivateMapVersion_Response_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

class Init_ActivateMapVersion_Response_success
{
public:
  Init_ActivateMapVersion_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ActivateMapVersion_Response_error_code success(::agt_interfaces::srv::ActivateMapVersion_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ActivateMapVersion_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ActivateMapVersion_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ActivateMapVersion_Response>()
{
  return agt_interfaces::srv::builder::Init_ActivateMapVersion_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__ACTIVATE_MAP_VERSION__BUILDER_HPP_
