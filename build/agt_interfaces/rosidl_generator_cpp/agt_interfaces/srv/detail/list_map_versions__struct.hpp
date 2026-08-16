// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/ListMapVersions.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ListMapVersions_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ListMapVersions_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ListMapVersions_Request_
{
  using Type = ListMapVersions_Request_<ContainerAllocator>;

  explicit ListMapVersions_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->state = 0;
      this->include_deleted = false;
    }
  }

  explicit ListMapVersions_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : map_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->state = 0;
      this->include_deleted = false;
    }
  }

  // field types and members
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _state_type =
    uint8_t;
  _state_type state;
  using _include_deleted_type =
    bool;
  _include_deleted_type include_deleted;

  // setters for named parameter idiom
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__include_deleted(
    const bool & _arg)
  {
    this->include_deleted = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ListMapVersions_Request
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ListMapVersions_Request
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ListMapVersions_Request_ & other) const
  {
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->include_deleted != other.include_deleted) {
      return false;
    }
    return true;
  }
  bool operator!=(const ListMapVersions_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ListMapVersions_Request_

// alias to use template instance with default allocator
using ListMapVersions_Request =
  agt_interfaces::srv::ListMapVersions_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces


// Include directives for member types
// Member 'versions'
#include "agt_interfaces/msg/detail/map_version_summary__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ListMapVersions_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ListMapVersions_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ListMapVersions_Response_
{
  using Type = ListMapVersions_Response_<ContainerAllocator>;

  explicit ListMapVersions_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->message = "";
    }
  }

  explicit ListMapVersions_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
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
  using _versions_type =
    std::vector<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>>;
  _versions_type versions;
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
  Type & set__versions(
    const std::vector<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>> & _arg)
  {
    this->versions = _arg;
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
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    1u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ListMapVersions_Response
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ListMapVersions_Response
    std::shared_ptr<agt_interfaces::srv::ListMapVersions_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ListMapVersions_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->versions != other.versions) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ListMapVersions_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ListMapVersions_Response_

// alias to use template instance with default allocator
using ListMapVersions_Response =
  agt_interfaces::srv::ListMapVersions_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ListMapVersions_Response_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ListMapVersions_Response_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ListMapVersions_Response_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct ListMapVersions
{
  using Request = agt_interfaces::srv::ListMapVersions_Request;
  using Response = agt_interfaces::srv::ListMapVersions_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_MAP_VERSIONS__STRUCT_HPP_
