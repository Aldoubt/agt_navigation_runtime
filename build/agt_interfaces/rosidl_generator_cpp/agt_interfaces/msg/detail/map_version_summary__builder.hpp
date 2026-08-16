// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__BUILDER_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agt_interfaces/msg/detail/map_version_summary__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agt_interfaces
{

namespace msg
{

namespace builder
{

class Init_MapVersionSummary_validation_warnings
{
public:
  explicit Init_MapVersionSummary_validation_warnings(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  ::agt_interfaces::msg::MapVersionSummary validation_warnings(::agt_interfaces::msg::MapVersionSummary::_validation_warnings_type arg)
  {
    msg_.validation_warnings = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_validation_errors
{
public:
  explicit Init_MapVersionSummary_validation_errors(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_validation_warnings validation_errors(::agt_interfaces::msg::MapVersionSummary::_validation_errors_type arg)
  {
    msg_.validation_errors = std::move(arg);
    return Init_MapVersionSummary_validation_warnings(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_created_at
{
public:
  explicit Init_MapVersionSummary_created_at(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_validation_errors created_at(::agt_interfaces::msg::MapVersionSummary::_created_at_type arg)
  {
    msg_.created_at = std::move(arg);
    return Init_MapVersionSummary_validation_errors(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_storage_bytes
{
public:
  explicit Init_MapVersionSummary_storage_bytes(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_created_at storage_bytes(::agt_interfaces::msg::MapVersionSummary::_storage_bytes_type arg)
  {
    msg_.storage_bytes = std::move(arg);
    return Init_MapVersionSummary_created_at(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_tasks_directory
{
public:
  explicit Init_MapVersionSummary_tasks_directory(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_storage_bytes tasks_directory(::agt_interfaces::msg::MapVersionSummary::_tasks_directory_type arg)
  {
    msg_.tasks_directory = std::move(arg);
    return Init_MapVersionSummary_storage_bytes(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_processing_record
{
public:
  explicit Init_MapVersionSummary_processing_record(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_tasks_directory processing_record(::agt_interfaces::msg::MapVersionSummary::_processing_record_type arg)
  {
    msg_.processing_record = std::move(arg);
    return Init_MapVersionSummary_tasks_directory(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_localization_pcd
{
public:
  explicit Init_MapVersionSummary_localization_pcd(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_processing_record localization_pcd(::agt_interfaces::msg::MapVersionSummary::_localization_pcd_type arg)
  {
    msg_.localization_pcd = std::move(arg);
    return Init_MapVersionSummary_processing_record(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_navigation_yaml
{
public:
  explicit Init_MapVersionSummary_navigation_yaml(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_localization_pcd navigation_yaml(::agt_interfaces::msg::MapVersionSummary::_navigation_yaml_type arg)
  {
    msg_.navigation_yaml = std::move(arg);
    return Init_MapVersionSummary_localization_pcd(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_localization_pcd_sha256
{
public:
  explicit Init_MapVersionSummary_localization_pcd_sha256(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_navigation_yaml localization_pcd_sha256(::agt_interfaces::msg::MapVersionSummary::_localization_pcd_sha256_type arg)
  {
    msg_.localization_pcd_sha256 = std::move(arg);
    return Init_MapVersionSummary_navigation_yaml(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_navigation_image_sha256
{
public:
  explicit Init_MapVersionSummary_navigation_image_sha256(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_localization_pcd_sha256 navigation_image_sha256(::agt_interfaces::msg::MapVersionSummary::_navigation_image_sha256_type arg)
  {
    msg_.navigation_image_sha256 = std::move(arg);
    return Init_MapVersionSummary_localization_pcd_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_navigation_yaml_sha256
{
public:
  explicit Init_MapVersionSummary_navigation_yaml_sha256(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_navigation_image_sha256 navigation_yaml_sha256(::agt_interfaces::msg::MapVersionSummary::_navigation_yaml_sha256_type arg)
  {
    msg_.navigation_yaml_sha256 = std::move(arg);
    return Init_MapVersionSummary_navigation_image_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_manifest_sha256
{
public:
  explicit Init_MapVersionSummary_manifest_sha256(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_navigation_yaml_sha256 manifest_sha256(::agt_interfaces::msg::MapVersionSummary::_manifest_sha256_type arg)
  {
    msg_.manifest_sha256 = std::move(arg);
    return Init_MapVersionSummary_navigation_yaml_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_map_hash
{
public:
  explicit Init_MapVersionSummary_map_hash(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_manifest_sha256 map_hash(::agt_interfaces::msg::MapVersionSummary::_map_hash_type arg)
  {
    msg_.map_hash = std::move(arg);
    return Init_MapVersionSummary_manifest_sha256(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_valid
{
public:
  explicit Init_MapVersionSummary_valid(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_map_hash valid(::agt_interfaces::msg::MapVersionSummary::_valid_type arg)
  {
    msg_.valid = std::move(arg);
    return Init_MapVersionSummary_map_hash(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_deleted
{
public:
  explicit Init_MapVersionSummary_deleted(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_valid deleted(::agt_interfaces::msg::MapVersionSummary::_deleted_type arg)
  {
    msg_.deleted = std::move(arg);
    return Init_MapVersionSummary_valid(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_pinned
{
public:
  explicit Init_MapVersionSummary_pinned(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_deleted pinned(::agt_interfaces::msg::MapVersionSummary::_pinned_type arg)
  {
    msg_.pinned = std::move(arg);
    return Init_MapVersionSummary_deleted(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_active
{
public:
  explicit Init_MapVersionSummary_active(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_pinned active(::agt_interfaces::msg::MapVersionSummary::_active_type arg)
  {
    msg_.active = std::move(arg);
    return Init_MapVersionSummary_pinned(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_state
{
public:
  explicit Init_MapVersionSummary_state(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_active state(::agt_interfaces::msg::MapVersionSummary::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_MapVersionSummary_active(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_parent_map_version_id
{
public:
  explicit Init_MapVersionSummary_parent_map_version_id(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_state parent_map_version_id(::agt_interfaces::msg::MapVersionSummary::_parent_map_version_id_type arg)
  {
    msg_.parent_map_version_id = std::move(arg);
    return Init_MapVersionSummary_state(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_map_version_id
{
public:
  explicit Init_MapVersionSummary_map_version_id(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_parent_map_version_id map_version_id(::agt_interfaces::msg::MapVersionSummary::_map_version_id_type arg)
  {
    msg_.map_version_id = std::move(arg);
    return Init_MapVersionSummary_parent_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_map_id
{
public:
  explicit Init_MapVersionSummary_map_id(::agt_interfaces::msg::MapVersionSummary & msg)
  : msg_(msg)
  {}
  Init_MapVersionSummary_map_version_id map_id(::agt_interfaces::msg::MapVersionSummary::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_MapVersionSummary_map_version_id(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

class Init_MapVersionSummary_header
{
public:
  Init_MapVersionSummary_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MapVersionSummary_map_id header(::agt_interfaces::msg::MapVersionSummary::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MapVersionSummary_map_id(msg_);
  }

private:
  ::agt_interfaces::msg::MapVersionSummary msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agt_interfaces::msg::MapVersionSummary>()
{
  return agt_interfaces::msg::builder::Init_MapVersionSummary_header();
}

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__BUILDER_HPP_
