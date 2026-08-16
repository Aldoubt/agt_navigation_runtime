// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:srv/GetSystemHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_HPP_
#define AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__GetSystemHealth_Request __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__GetSystemHealth_Request __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSystemHealth_Request_
{
  using Type = GetSystemHealth_Request_<ContainerAllocator>;

  explicit GetSystemHealth_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->include_optional = false;
    }
  }

  explicit GetSystemHealth_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->include_optional = false;
    }
  }

  // field types and members
  using _include_optional_type =
    bool;
  _include_optional_type include_optional;

  // setters for named parameter idiom
  Type & set__include_optional(
    const bool & _arg)
  {
    this->include_optional = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__GetSystemHealth_Request
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__GetSystemHealth_Request
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSystemHealth_Request_ & other) const
  {
    if (this->include_optional != other.include_optional) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSystemHealth_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSystemHealth_Request_

// alias to use template instance with default allocator
using GetSystemHealth_Request =
  agt_interfaces::srv::GetSystemHealth_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces


// Include directives for member types
// Member 'health'
#include "agt_interfaces/msg/detail/system_health__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__srv__GetSystemHealth_Response __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__srv__GetSystemHealth_Response __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetSystemHealth_Response_
{
  using Type = GetSystemHealth_Response_<ContainerAllocator>;

  explicit GetSystemHealth_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : health(_init)
  {
    (void)_init;
  }

  explicit GetSystemHealth_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : health(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _health_type =
    agt_interfaces::msg::SystemHealth_<ContainerAllocator>;
  _health_type health;

  // setters for named parameter idiom
  Type & set__health(
    const agt_interfaces::msg::SystemHealth_<ContainerAllocator> & _arg)
  {
    this->health = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__srv__GetSystemHealth_Response
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__srv__GetSystemHealth_Response
    std::shared_ptr<agt_interfaces::srv::GetSystemHealth_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetSystemHealth_Response_ & other) const
  {
    if (this->health != other.health) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetSystemHealth_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetSystemHealth_Response_

// alias to use template instance with default allocator
using GetSystemHealth_Response =
  agt_interfaces::srv::GetSystemHealth_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace agt_interfaces

namespace agt_interfaces
{

namespace srv
{

struct GetSystemHealth
{
  using Request = agt_interfaces::srv::GetSystemHealth_Request;
  using Response = agt_interfaces::srv::GetSystemHealth_Response;
};

}  // namespace srv

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_SYSTEM_HEALTH__STRUCT_HPP_
