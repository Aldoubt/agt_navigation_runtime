// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ListMapVersions.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/list_map_versions__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListMapVersions_Request_include_deleted
{
public:
  explicit Init_ListMapVersions_Request_include_deleted(::agt_interfaces::srv::ListMapVersions_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListMapVersions_Request include_deleted(::agt_interfaces::srv::ListMapVersions_Request::_include_deleted_type arg)
  {
    msg_.include_deleted = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Request msg_;
};

class Init_ListMapVersions_Request_state
{
public:
  explicit Init_ListMapVersions_Request_state(::agt_interfaces::srv::ListMapVersions_Request & msg)
  : msg_(msg)
  {}
  Init_ListMapVersions_Request_include_deleted state(::agt_interfaces::srv::ListMapVersions_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_ListMapVersions_Request_include_deleted(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Request msg_;
};

class Init_ListMapVersions_Request_map_id
{
public:
  Init_ListMapVersions_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListMapVersions_Request_state map_id(::agt_interfaces::srv::ListMapVersions_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ListMapVersions_Request_state(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListMapVersions_Request>()
{
  return agt_interfaces::srv::builder::Init_ListMapVersions_Request_map_id();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListMapVersions_Response_message
{
public:
  explicit Init_ListMapVersions_Response_message(::agt_interfaces::srv::ListMapVersions_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ListMapVersions_Response message(::agt_interfaces::srv::ListMapVersions_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Response msg_;
};

class Init_ListMapVersions_Response_versions
{
public:
  explicit Init_ListMapVersions_Response_versions(::agt_interfaces::srv::ListMapVersions_Response & msg)
  : msg_(msg)
  {}
  Init_ListMapVersions_Response_message versions(::agt_interfaces::srv::ListMapVersions_Response::_versions_type arg)
  {
    msg_.versions = std::move(arg);
    return Init_ListMapVersions_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Response msg_;
};

class Init_ListMapVersions_Response_error_code
{
public:
  explicit Init_ListMapVersions_Response_error_code(::agt_interfaces::srv::ListMapVersions_Response & msg)
  : msg_(msg)
  {}
  Init_ListMapVersions_Response_versions error_code(::agt_interfaces::srv::ListMapVersions_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ListMapVersions_Response_versions(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Response msg_;
};

class Init_ListMapVersions_Response_success
{
public:
  Init_ListMapVersions_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListMapVersions_Response_error_code success(::agt_interfaces::srv::ListMapVersions_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ListMapVersions_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ListMapVersions_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ListMapVersions_Response>()
{
  return agt_interfaces::srv::builder::Init_ListMapVersions_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__BUILDER_HPP_
