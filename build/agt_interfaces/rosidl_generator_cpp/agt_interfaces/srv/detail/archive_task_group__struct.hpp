// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/ArchiveTaskGroup.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArchiveTaskGroup_Request_
{
  using Type = ArchiveTaskGroup_Request_<ContainerAllocator>;

  explicit ArchiveTaskGroup_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->expected_revision = 0ul;
      this->client_request_id = "";
    }
  }

  explicit ArchiveTaskGroup_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : map_id(_alloc),
    map_version_id(_alloc),
    task_group_id(_alloc),
    client_request_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->expected_revision = 0ul;
      this->client_request_id = "";
    }
  }

  // field types and members
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _task_group_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_group_id_type task_group_id;
  using _expected_revision_type =
    uint32_t;
  _expected_revision_type expected_revision;
  using _client_request_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _client_request_id_type client_request_id;

  // setters for named parameter idiom
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_version_id = _arg;
    return *this;
  }
  Type & set__task_group_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_group_id = _arg;
    return *this;
  }
  Type & set__expected_revision(
    const uint32_t & _arg)
  {
    this->expected_revision = _arg;
    return *this;
  }
  Type & set__client_request_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->client_request_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Request
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Request
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArchiveTaskGroup_Request_ & other) const
  {
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->task_group_id != other.task_group_id) {
      return false;
    }
    if (this->expected_revision != other.expected_revision) {
      return false;
    }
    if (this->client_request_id != other.client_request_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArchiveTaskGroup_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArchiveTaskGroup_Request_

// alias to use template instance with default allocator
using ArchiveTaskGroup_Request =
  agt_interfaces::srv::ArchiveTaskGroup_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArchiveTaskGroup_Response_
{
  using Type = ArchiveTaskGroup_Response_<ContainerAllocator>;

  explicit ArchiveTaskGroup_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->blocker_code = "";
      this->operator_message = "";
      this->technical_message = "";
      this->duplicate_request = false;
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->archived_revision = 0ul;
      this->archived_relative_path = "";
    }
  }

  explicit ArchiveTaskGroup_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : blocker_code(_alloc),
    operator_message(_alloc),
    technical_message(_alloc),
    map_id(_alloc),
    map_version_id(_alloc),
    task_group_id(_alloc),
    archived_relative_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->blocker_code = "";
      this->operator_message = "";
      this->technical_message = "";
      this->duplicate_request = false;
      this->map_id = "";
      this->map_version_id = "";
      this->task_group_id = "";
      this->archived_revision = 0ul;
      this->archived_relative_path = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    uint16_t;
  _error_code_type error_code;
  using _blocker_code_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _blocker_code_type blocker_code;
  using _operator_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _operator_message_type operator_message;
  using _technical_message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _technical_message_type technical_message;
  using _duplicate_request_type =
    bool;
  _duplicate_request_type duplicate_request;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _task_group_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_group_id_type task_group_id;
  using _archived_revision_type =
    uint32_t;
  _archived_revision_type archived_revision;
  using _archived_relative_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _archived_relative_path_type archived_relative_path;

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
  Type & set__blocker_code(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->blocker_code = _arg;
    return *this;
  }
  Type & set__operator_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->operator_message = _arg;
    return *this;
  }
  Type & set__technical_message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->technical_message = _arg;
    return *this;
  }
  Type & set__duplicate_request(
    const bool & _arg)
  {
    this->duplicate_request = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_version_id = _arg;
    return *this;
  }
  Type & set__task_group_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_group_id = _arg;
    return *this;
  }
  Type & set__archived_revision(
    const uint32_t & _arg)
  {
    this->archived_revision = _arg;
    return *this;
  }
  Type & set__archived_relative_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->archived_relative_path = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t ERROR_NONE =
    0u;
  static constexpr uint16_t ERROR_INVALID_REQUEST =
    1u;
  static constexpr uint16_t ERROR_NOT_FOUND =
    2u;
  static constexpr uint16_t ERROR_REVISION_CONFLICT =
    3u;
  static constexpr uint16_t ERROR_MAP_NOT_READY =
    4u;
  static constexpr uint16_t ERROR_INTERNAL =
    255u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Response
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__ArchiveTaskGroup_Response
    std::shared_ptr<agt_interfaces::srv::ArchiveTaskGroup_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArchiveTaskGroup_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->blocker_code != other.blocker_code) {
      return false;
    }
    if (this->operator_message != other.operator_message) {
      return false;
    }
    if (this->technical_message != other.technical_message) {
      return false;
    }
    if (this->duplicate_request != other.duplicate_request) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->task_group_id != other.task_group_id) {
      return false;
    }
    if (this->archived_revision != other.archived_revision) {
      return false;
    }
    if (this->archived_relative_path != other.archived_relative_path) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArchiveTaskGroup_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArchiveTaskGroup_Response_

// alias to use template instance with default allocator
using ArchiveTaskGroup_Response =
  agt_interfaces::srv::ArchiveTaskGroup_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_INVALID_REQUEST;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_NOT_FOUND;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_REVISION_CONFLICT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_MAP_NOT_READY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint16_t ArchiveTaskGroup_Response_<ContainerAllocator>::ERROR_INTERNAL;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct ArchiveTaskGroup
{
  using Request = agt_interfaces::srv::ArchiveTaskGroup_Request;
  using Response = agt_interfaces::srv::ArchiveTaskGroup_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__ARCHIVE_TASK_GROUP__STRUCT_HPP_
