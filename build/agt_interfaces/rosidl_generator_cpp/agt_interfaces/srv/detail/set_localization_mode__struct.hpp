// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/SetLocalizationMode.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetLocalizationMode_Request_
{
  using Type = SetLocalizationMode_Request_<ContainerAllocator>;

  explicit SetLocalizationMode_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
    }
  }

  explicit SetLocalizationMode_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
    }
  }

  // field types and members
  using _mode_type =
    uint8_t;
  _mode_type mode;

  // setters for named parameter idiom
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t MODE_MANUAL_ONLY =
    0u;
  static constexpr uint8_t MODE_AUTO_ON_START =
    1u;
  static constexpr uint8_t MODE_AUTO_RECOVERY =
    2u;

  // pointer types
  using RawPtr =
    agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Request
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Request
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetLocalizationMode_Request_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetLocalizationMode_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetLocalizationMode_Request_

// alias to use template instance with default allocator
using SetLocalizationMode_Request =
  agt_interfaces::srv::SetLocalizationMode_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetLocalizationMode_Request_<ContainerAllocator>::MODE_MANUAL_ONLY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetLocalizationMode_Request_<ContainerAllocator>::MODE_AUTO_ON_START;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t SetLocalizationMode_Request_<ContainerAllocator>::MODE_AUTO_RECOVERY;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace agt_interfaces


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetLocalizationMode_Response_
{
  using Type = SetLocalizationMode_Response_<ContainerAllocator>;

  explicit SetLocalizationMode_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->active_mode = 0;
      this->attempts = 0ul;
      this->message = "";
    }
  }

  explicit SetLocalizationMode_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0;
      this->active_mode = 0;
      this->attempts = 0ul;
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
  using _active_mode_type =
    uint8_t;
  _active_mode_type active_mode;
  using _attempts_type =
    uint32_t;
  _attempts_type attempts;
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
  Type & set__active_mode(
    const uint8_t & _arg)
  {
    this->active_mode = _arg;
    return *this;
  }
  Type & set__attempts(
    const uint32_t & _arg)
  {
    this->attempts = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Response
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__SetLocalizationMode_Response
    std::shared_ptr<agt_interfaces::srv::SetLocalizationMode_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetLocalizationMode_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->active_mode != other.active_mode) {
      return false;
    }
    if (this->attempts != other.attempts) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetLocalizationMode_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetLocalizationMode_Response_

// alias to use template instance with default allocator
using SetLocalizationMode_Response =
  agt_interfaces::srv::SetLocalizationMode_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct SetLocalizationMode
{
  using Request = agt_interfaces::srv::SetLocalizationMode_Request;
  using Response = agt_interfaces::srv::SetLocalizationMode_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__SET_LOCALIZATION_MODE__STRUCT_HPP_
