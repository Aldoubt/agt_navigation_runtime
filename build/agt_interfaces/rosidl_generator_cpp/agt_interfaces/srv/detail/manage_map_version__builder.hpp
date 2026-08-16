// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:srv/ManageMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__BUILDER_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/srv/detail/manage_map_version__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ManageMapVersion_Request_parent_map_version_id
{
public:
  explicit Init_ManageMapVersion_Request_parent_map_version_id(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ManageMapVersion_Request parent_map_version_id(::agt_interfaces::srv::ManageMapVersion_Request::_parent_map_version_id_type arg)
  {
    msg_.parent_map_version_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_platform_profile
{
public:
  explicit Init_ManageMapVersion_Request_platform_profile(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_parent_map_version_id platform_profile(::agt_interfaces::srv::ManageMapVersion_Request::_platform_profile_type arg)
  {
    msg_.platform_profile = std::move(arg);
    return Init_ManageMapVersion_Request_parent_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_processing_record
{
public:
  explicit Init_ManageMapVersion_Request_processing_record(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_platform_profile processing_record(::agt_interfaces::srv::ManageMapVersion_Request::_processing_record_type arg)
  {
    msg_.processing_record = std::move(arg);
    return Init_ManageMapVersion_Request_platform_profile(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_localization_pcd
{
public:
  explicit Init_ManageMapVersion_Request_localization_pcd(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_processing_record localization_pcd(::agt_interfaces::srv::ManageMapVersion_Request::_localization_pcd_type arg)
  {
    msg_.localization_pcd = std::move(arg);
    return Init_ManageMapVersion_Request_processing_record(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_candidate_map_yaml
{
public:
  explicit Init_ManageMapVersion_Request_candidate_map_yaml(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_localization_pcd candidate_map_yaml(::agt_interfaces::srv::ManageMapVersion_Request::_candidate_map_yaml_type arg)
  {
    msg_.candidate_map_yaml = std::move(arg);
    return Init_ManageMapVersion_Request_localization_pcd(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_map_id
{
public:
  explicit Init_ManageMapVersion_Request_map_id(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_candidate_map_yaml map_id(::agt_interfaces::srv::ManageMapVersion_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_ManageMapVersion_Request_candidate_map_yaml(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_confirm_destructive
{
public:
  explicit Init_ManageMapVersion_Request_confirm_destructive(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_map_id confirm_destructive(::agt_interfaces::srv::ManageMapVersion_Request::_confirm_destructive_type arg)
  {
    msg_.confirm_destructive = std::move(arg);
    return Init_ManageMapVersion_Request_map_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_map_version_id
{
public:
  explicit Init_ManageMapVersion_Request_map_version_id(::agt_interfaces::srv::ManageMapVersion_Request & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Request_confirm_destructive map_version_id(::agt_interfaces::srv::ManageMapVersion_Request::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_ManageMapVersion_Request_confirm_destructive(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

class Init_ManageMapVersion_Request_operation
{
public:
  Init_ManageMapVersion_Request_operation()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMapVersion_Request_map_version_id operation(::agt_interfaces::srv::ManageMapVersion_Request::_operation_type arg)
  {
    msg_.operation = std::move(arg);
    return Init_ManageMapVersion_Request_map_version_id(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ManageMapVersion_Request>()
{
  return agt_interfaces::srv::builder::Init_ManageMapVersion_Request_operation();
}

}  // namespace agt_interfaces


namespace agt_interfaces
{

namespace srv
{

namespace builder
{

class Init_ManageMapVersion_Response_message
{
public:
  explicit Init_ManageMapVersion_Response_message(::agt_interfaces::srv::ManageMapVersion_Response & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::srv::ManageMapVersion_Response message(::agt_interfaces::srv::ManageMapVersion_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Response msg_;
};

class Init_ManageMapVersion_Response_version
{
public:
  explicit Init_ManageMapVersion_Response_version(::agt_interfaces::srv::ManageMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Response_message version(::agt_interfaces::srv::ManageMapVersion_Response::_version_type arg)
  {
    msg_.version = std::move(arg);
    return Init_ManageMapVersion_Response_message(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Response msg_;
};

class Init_ManageMapVersion_Response_error_code
{
public:
  explicit Init_ManageMapVersion_Response_error_code(::agt_interfaces::srv::ManageMapVersion_Response & msg)
  : msg_(msg)
  {}
  Init_ManageMapVersion_Response_version error_code(::agt_interfaces::srv::ManageMapVersion_Response::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_ManageMapVersion_Response_version(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Response msg_;
};

class Init_ManageMapVersion_Response_success
{
public:
  Init_ManageMapVersion_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ManageMapVersion_Response_error_code success(::agt_interfaces::srv::ManageMapVersion_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ManageMapVersion_Response_error_code(msg_);
  }

private:
  ::agt_interfaces::srv::ManageMapVersion_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::srv::ManageMapVersion_Response>()
{
  return agt_interfaces::srv::builder::Init_ManageMapVersion_Response_success();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__BUILDER_HPP_
