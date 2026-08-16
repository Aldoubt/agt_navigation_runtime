// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:srv/ListTaskGroups.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "agt_interfaces/srv/detail/list_task_groups__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void ListTaskGroups_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) agt_interfaces::srv::ListTaskGroups_Request(_init);
}

void ListTaskGroups_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<agt_interfaces::srv::ListTaskGroups_Request *>(message_memory);
  typed_message->~ListTaskGroups_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ListTaskGroups_Request_message_member_array[2] = {
  {
    "map_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Request, map_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_version_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Request, map_version_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ListTaskGroups_Request_message_members = {
  "agt_interfaces::srv",  // message namespace
  "ListTaskGroups_Request",  // message name
  2,  // number of fields
  sizeof(agt_interfaces::srv::ListTaskGroups_Request),
  ListTaskGroups_Request_message_member_array,  // message members
  ListTaskGroups_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  ListTaskGroups_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ListTaskGroups_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ListTaskGroups_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace agt_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::srv::ListTaskGroups_Request>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ListTaskGroups_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ListTaskGroups_Request)() {
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ListTaskGroups_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void ListTaskGroups_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) agt_interfaces::srv::ListTaskGroups_Response(_init);
}

void ListTaskGroups_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<agt_interfaces::srv::ListTaskGroups_Response *>(message_memory);
  typed_message->~ListTaskGroups_Response();
}

size_t size_function__ListTaskGroups_Response__task_group_ids(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__task_group_ids(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__task_group_ids(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__task_group_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListTaskGroups_Response__task_group_ids(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__task_group_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListTaskGroups_Response__task_group_ids(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__task_group_ids(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__names(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__names(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__names(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListTaskGroups_Response__names(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListTaskGroups_Response__names(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__names(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__revisions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__revisions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__revisions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__revisions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__ListTaskGroups_Response__revisions(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__revisions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__ListTaskGroups_Response__revisions(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__revisions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__content_sha256(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__content_sha256(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__content_sha256(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__content_sha256(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListTaskGroups_Response__content_sha256(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__content_sha256(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListTaskGroups_Response__content_sha256(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__content_sha256(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__enabled_point_counts(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__enabled_point_counts(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__enabled_point_counts(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__enabled_point_counts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__ListTaskGroups_Response__enabled_point_counts(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__enabled_point_counts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__ListTaskGroups_Response__enabled_point_counts(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__enabled_point_counts(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__updated_at(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__updated_at(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__updated_at(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__updated_at(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListTaskGroups_Response__updated_at(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__updated_at(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListTaskGroups_Response__updated_at(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__updated_at(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListTaskGroups_Response__validation_states(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListTaskGroups_Response__validation_states(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListTaskGroups_Response__validation_states(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListTaskGroups_Response__validation_states(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListTaskGroups_Response__validation_states(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListTaskGroups_Response__validation_states(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListTaskGroups_Response__validation_states(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListTaskGroups_Response__validation_states(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ListTaskGroups_Response_message_member_array[14] = {
  {
    "success",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, success),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "error_code",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, error_code),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "blocker_code",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, blocker_code),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "operator_message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, operator_message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "technical_message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, technical_message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, map_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "map_version_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, map_version_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "task_group_ids",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, task_group_ids),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__task_group_ids,  // size() function pointer
    get_const_function__ListTaskGroups_Response__task_group_ids,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__task_group_ids,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__task_group_ids,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__task_group_ids,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__task_group_ids  // resize(index) function pointer
  },
  {
    "names",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, names),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__names,  // size() function pointer
    get_const_function__ListTaskGroups_Response__names,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__names,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__names,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__names,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__names  // resize(index) function pointer
  },
  {
    "revisions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, revisions),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__revisions,  // size() function pointer
    get_const_function__ListTaskGroups_Response__revisions,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__revisions,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__revisions,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__revisions,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__revisions  // resize(index) function pointer
  },
  {
    "content_sha256",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, content_sha256),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__content_sha256,  // size() function pointer
    get_const_function__ListTaskGroups_Response__content_sha256,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__content_sha256,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__content_sha256,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__content_sha256,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__content_sha256  // resize(index) function pointer
  },
  {
    "enabled_point_counts",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, enabled_point_counts),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__enabled_point_counts,  // size() function pointer
    get_const_function__ListTaskGroups_Response__enabled_point_counts,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__enabled_point_counts,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__enabled_point_counts,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__enabled_point_counts,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__enabled_point_counts  // resize(index) function pointer
  },
  {
    "updated_at",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, updated_at),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__updated_at,  // size() function pointer
    get_const_function__ListTaskGroups_Response__updated_at,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__updated_at,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__updated_at,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__updated_at,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__updated_at  // resize(index) function pointer
  },
  {
    "validation_states",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ListTaskGroups_Response, validation_states),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListTaskGroups_Response__validation_states,  // size() function pointer
    get_const_function__ListTaskGroups_Response__validation_states,  // get_const(index) function pointer
    get_function__ListTaskGroups_Response__validation_states,  // get(index) function pointer
    fetch_function__ListTaskGroups_Response__validation_states,  // fetch(index, &value) function pointer
    assign_function__ListTaskGroups_Response__validation_states,  // assign(index, value) function pointer
    resize_function__ListTaskGroups_Response__validation_states  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ListTaskGroups_Response_message_members = {
  "agt_interfaces::srv",  // message namespace
  "ListTaskGroups_Response",  // message name
  14,  // number of fields
  sizeof(agt_interfaces::srv::ListTaskGroups_Response),
  ListTaskGroups_Response_message_member_array,  // message members
  ListTaskGroups_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  ListTaskGroups_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ListTaskGroups_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ListTaskGroups_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace agt_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::srv::ListTaskGroups_Response>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ListTaskGroups_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ListTaskGroups_Response)() {
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ListTaskGroups_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/list_task_groups__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers ListTaskGroups_service_members = {
  "agt_interfaces::srv",  // service namespace
  "ListTaskGroups",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<agt_interfaces::srv::ListTaskGroups>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t ListTaskGroups_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ListTaskGroups_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace agt_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<agt_interfaces::srv::ListTaskGroups>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ListTaskGroups_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::agt_interfaces::srv::ListTaskGroups_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::agt_interfaces::srv::ListTaskGroups_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ListTaskGroups)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<agt_interfaces::srv::ListTaskGroups>();
}

#ifdef __cplusplus
}
#endif
