// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/ManageMapVersion.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ManageMapVersion_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ManageMapVersion_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ManageMapVersion_Request_
{
  using Type = ManageMapVersion_Request_<ContainerAllocator>;

  explicit ManageMapVersion_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->operation = 0;
      this->map_version_id = "";
      this->confirm_destructive = false;
      this->map_id = "";
      this->candidate_map_yaml = "";
      this->localization_pcd = "";
      this->processing_record = "";
      this->platform_profile = "";
      this->parent_map_version_id = "";
    }
  }

  explicit ManageMapVersion_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : map_version_id(_alloc),
    map_id(_alloc),
    candidate_map_yaml(_alloc),
    localization_pcd(_alloc),
    processing_record(_alloc),
    platform_profile(_alloc),
    parent_map_version_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->operation = 0;
      this->map_version_id = "";
      this->confirm_destructive = false;
      this->map_id = "";
      this->candidate_map_yaml = "";
      this->localization_pcd = "";
      this->processing_record = "";
      this->platform_profile = "";
      this->parent_map_version_id = "";
    }
  }

  // field types and members
  using _operation_type =
    uint8_t;
  _operation_type operation;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _confirm_destructive_type =
    bool;
  _confirm_destructive_type confirm_destructive;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _candidate_map_yaml_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _candidate_map_yaml_type candidate_map_yaml;
  using _localization_pcd_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _localization_pcd_type localization_pcd;
  using _processing_record_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _processing_record_type processing_record;
  using _platform_profile_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _platform_profile_type platform_profile;
  using _parent_map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _parent_map_version_id_type parent_map_version_id;

  // setters for named parameter idiom
  Type & set__operation(
    const uint8_t & _arg)
  {
    this->operation = _arg;
    return *this;
  }
  Type & set__map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_version_id = _arg;
    return *this;
  }
  Type & set__confirm_destructive(
    const bool & _arg)
  {
    this->confirm_destructive = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__candidate_map_yaml(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->candidate_map_yaml = _arg;
    return *this;
  }
  Type & set__localization_pcd(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->localization_pcd = _arg;
    return *this;
  }
  Type & set__processing_record(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->processing_record = _arg;
    return *this;
  }
  Type & set__platform_profile(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->platform_profile = _arg;
    return *this;
  }
  Type & set__parent_map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->parent_map_version_id = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t OP_GET_ACTIVE =
    0u;
  static constexpr uint8_t OP_VALIDATE =
    1u;
  static constexpr uint8_t OP_ACTIVATE =
    2u;
  static constexpr uint8_t OP_PIN =
    3u;
  static constexpr uint8_t OP_UNPIN =
    4u;
  static constexpr uint8_t OP_ARCHIVE =
    5u;
  static constexpr uint8_t OP_SOFT_DELETE =
    6u;
  static constexpr uint8_t OP_PURGE =
    7u;
  static constexpr uint8_t OP_IMPORT_CANDIDATE =
    8u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ManageMapVersion_Request
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ManageMapVersion_Request
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ManageMapVersion_Request_ & other) const
  {
    if (this->operation != other.operation) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->confirm_destructive != other.confirm_destructive) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->candidate_map_yaml != other.candidate_map_yaml) {
      return false;
    }
    if (this->localization_pcd != other.localization_pcd) {
      return false;
    }
    if (this->processing_record != other.processing_record) {
      return false;
    }
    if (this->platform_profile != other.platform_profile) {
      return false;
    }
    if (this->parent_map_version_id != other.parent_map_version_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ManageMapVersion_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ManageMapVersion_Request_

// alias to use template instance with default allocator
using ManageMapVersion_Request =
  agt_interfaces::srv::ManageMapVersion_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_GET_ACTIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_VALIDATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_ACTIVATE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_PIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_UNPIN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_ARCHIVE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_SOFT_DELETE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_PURGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t ManageMapVersion_Request_<ContainerAllocator>::OP_IMPORT_CANDIDATE;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces


// Include directives for member types
// Member 'version'
#include "agt_interfaces/msg/detail/map_version_summary__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ManageMapVersion_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ManageMapVersion_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ManageMapVersion_Response_
{
  using Type = ManageMapVersion_Response_<ContainerAllocator>;

  explicit ManageMapVersion_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : version(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
    }
  }

  explicit ManageMapVersion_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : version(_alloc, _init),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _version_type =
    agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>;
  _version_type version;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__error_code(
    const uint16_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__version(
    const agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> & _arg)
  {
    this->version = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_NOT_FOUND =
    1u;
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    2u;
  static constexpr uint16_t ERROR_CONFLICT =
    3u;
  static constexpr uint16_t ERROR_VALIDATION_FAILED =
    4u;
  static constexpr uint16_t ERROR_CONFIRMATION_REQUIRED =
    5u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ManageMapVersion_Response
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ManageMapVersion_Response
    std::shared_ptr<agt_interfaces::srv::ManageMapVersion_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ManageMapVersion_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->version != other.version) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ManageMapVersion_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ManageMapVersion_Response_

// alias to use template instance with default allocator
using ManageMapVersion_Response =
  agt_interfaces::srv::ManageMapVersion_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_NOT_FOUND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_CONFLICT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_VALIDATION_FAILED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_CONFIRMATION_REQUIRED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ManageMapVersion_Response_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct ManageMapVersion
{
  using Request = agt_interfaces::srv::ManageMapVersion_Request;
  using Response = agt_interfaces::srv::ManageMapVersion_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__MANAGE_MAP_VERSION__STRUCT_HPP_
