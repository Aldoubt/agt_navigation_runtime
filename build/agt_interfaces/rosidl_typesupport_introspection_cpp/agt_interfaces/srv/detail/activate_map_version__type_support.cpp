// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:srv/ActivateMapVersion.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "agt_interfaces/srv/detail/activate_map_version__struct.hpp"
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

void ActivateMapVersion_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) agt_interfaces::srv::ActivateMapVersion_Request(_init);
}

void ActivateMapVersion_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<agt_interfaces::srv::ActivateMapVersion_Request *>(message_memory);
  typed_message->~ActivateMapVersion_Request();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ActivateMapVersion_Request_message_member_array[3] = {
  {
    "map_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Request, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces::srv::ActivateMapVersion_Request, map_version_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "client_request_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Request, client_request_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ActivateMapVersion_Request_message_members = {
  "agt_interfaces::srv",  // message namespace
  "ActivateMapVersion_Request",  // message name
  3,  // number of fields
  sizeof(agt_interfaces::srv::ActivateMapVersion_Request),
  ActivateMapVersion_Request_message_member_array,  // message members
  ActivateMapVersion_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  ActivateMapVersion_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ActivateMapVersion_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ActivateMapVersion_Request_message_members,
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
get_message_type_support_handle<agt_interfaces::srv::ActivateMapVersion_Request>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ActivateMapVersion_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ActivateMapVersion_Request)() {
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ActivateMapVersion_Request_message_type_support_handle;
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
// #include "agt_interfaces/srv/detail/activate_map_version__struct.hpp"
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

void ActivateMapVersion_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) agt_interfaces::srv::ActivateMapVersion_Response(_init);
}

void ActivateMapVersion_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<agt_interfaces::srv::ActivateMapVersion_Response *>(message_memory);
  typed_message->~ActivateMapVersion_Response();
}

size_t size_function__ActivateMapVersion_Response__blocker_codes(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ActivateMapVersion_Response__blocker_codes(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ActivateMapVersion_Response__blocker_codes(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ActivateMapVersion_Response__blocker_codes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ActivateMapVersion_Response__blocker_codes(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ActivateMapVersion_Response__blocker_codes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ActivateMapVersion_Response__blocker_codes(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ActivateMapVersion_Response__blocker_codes(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ActivateMapVersion_Response__blocker_messages(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ActivateMapVersion_Response__blocker_messages(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ActivateMapVersion_Response__blocker_messages(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ActivateMapVersion_Response__blocker_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ActivateMapVersion_Response__blocker_messages(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ActivateMapVersion_Response__blocker_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ActivateMapVersion_Response__blocker_messages(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ActivateMapVersion_Response__blocker_messages(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ActivateMapVersion_Response__operator_messages(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ActivateMapVersion_Response__operator_messages(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ActivateMapVersion_Response__operator_messages(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ActivateMapVersion_Response__operator_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ActivateMapVersion_Response__operator_messages(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ActivateMapVersion_Response__operator_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ActivateMapVersion_Response__operator_messages(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ActivateMapVersion_Response__operator_messages(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ActivateMapVersion_Response__technical_messages(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ActivateMapVersion_Response__technical_messages(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ActivateMapVersion_Response__technical_messages(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ActivateMapVersion_Response__technical_messages(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ActivateMapVersion_Response__technical_messages(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ActivateMapVersion_Response__technical_messages(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ActivateMapVersion_Response__technical_messages(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ActivateMapVersion_Response__technical_messages(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ActivateMapVersion_Response_message_member_array[10] = {
  {
    "success",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, success),  // bytes offset in struct
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
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, error_code),  // bytes offset in struct
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
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, map_id),  // bytes offset in struct
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
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, map_version_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "blocker_codes",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, blocker_codes),  // bytes offset in struct
    nullptr,  // default value
    size_function__ActivateMapVersion_Response__blocker_codes,  // size() function pointer
    get_const_function__ActivateMapVersion_Response__blocker_codes,  // get_const(index) function pointer
    get_function__ActivateMapVersion_Response__blocker_codes,  // get(index) function pointer
    fetch_function__ActivateMapVersion_Response__blocker_codes,  // fetch(index, &value) function pointer
    assign_function__ActivateMapVersion_Response__blocker_codes,  // assign(index, value) function pointer
    resize_function__ActivateMapVersion_Response__blocker_codes  // resize(index) function pointer
  },
  {
    "blocker_messages",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, blocker_messages),  // bytes offset in struct
    nullptr,  // default value
    size_function__ActivateMapVersion_Response__blocker_messages,  // size() function pointer
    get_const_function__ActivateMapVersion_Response__blocker_messages,  // get_const(index) function pointer
    get_function__ActivateMapVersion_Response__blocker_messages,  // get(index) function pointer
    fetch_function__ActivateMapVersion_Response__blocker_messages,  // fetch(index, &value) function pointer
    assign_function__ActivateMapVersion_Response__blocker_messages,  // assign(index, value) function pointer
    resize_function__ActivateMapVersion_Response__blocker_messages  // resize(index) function pointer
  },
  {
    "operator_messages",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, operator_messages),  // bytes offset in struct
    nullptr,  // default value
    size_function__ActivateMapVersion_Response__operator_messages,  // size() function pointer
    get_const_function__ActivateMapVersion_Response__operator_messages,  // get_const(index) function pointer
    get_function__ActivateMapVersion_Response__operator_messages,  // get(index) function pointer
    fetch_function__ActivateMapVersion_Response__operator_messages,  // fetch(index, &value) function pointer
    assign_function__ActivateMapVersion_Response__operator_messages,  // assign(index, value) function pointer
    resize_function__ActivateMapVersion_Response__operator_messages  // resize(index) function pointer
  },
  {
    "technical_messages",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, technical_messages),  // bytes offset in struct
    nullptr,  // default value
    size_function__ActivateMapVersion_Response__technical_messages,  // size() function pointer
    get_const_function__ActivateMapVersion_Response__technical_messages,  // get_const(index) function pointer
    get_function__ActivateMapVersion_Response__technical_messages,  // get(index) function pointer
    fetch_function__ActivateMapVersion_Response__technical_messages,  // fetch(index, &value) function pointer
    assign_function__ActivateMapVersion_Response__technical_messages,  // assign(index, value) function pointer
    resize_function__ActivateMapVersion_Response__technical_messages  // resize(index) function pointer
  },
  {
    "version",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<agt_interfaces::msg::MapVersionSummary>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces::srv::ActivateMapVersion_Response, version),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ActivateMapVersion_Response_message_members = {
  "agt_interfaces::srv",  // message namespace
  "ActivateMapVersion_Response",  // message name
  10,  // number of fields
  sizeof(agt_interfaces::srv::ActivateMapVersion_Response),
  ActivateMapVersion_Response_message_member_array,  // message members
  ActivateMapVersion_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  ActivateMapVersion_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ActivateMapVersion_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ActivateMapVersion_Response_message_members,
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
get_message_type_support_handle<agt_interfaces::srv::ActivateMapVersion_Response>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ActivateMapVersion_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ActivateMapVersion_Response)() {
  return &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ActivateMapVersion_Response_message_type_support_handle;
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
// #include "agt_interfaces/srv/detail/activate_map_version__struct.hpp"
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
static ::rosidl_typesupport_introspection_cpp::ServiceMembers ActivateMapVersion_service_members = {
  "agt_interfaces::srv",  // service namespace
  "ActivateMapVersion",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<agt_interfaces::srv::ActivateMapVersion>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t ActivateMapVersion_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ActivateMapVersion_service_members,
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
get_service_type_support_handle<agt_interfaces::srv::ActivateMapVersion>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::agt_interfaces::srv::rosidl_typesupport_introspection_cpp::ActivateMapVersion_service_type_support_handle;
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
        ::agt_interfaces::srv::ActivateMapVersion_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::agt_interfaces::srv::ActivateMapVersion_Response
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
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ActivateMapVersion)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<agt_interfaces::srv::ActivateMapVersion>();
}

#ifdef __cplusplus
}
#endif
