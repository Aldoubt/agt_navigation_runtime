// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_HPP_
#define AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agt_interfaces__msg__MapVersionSummary __attribute__((deprecated))
#else
# define DEPRECATED__agt_interfaces__msg__MapVersionSummary __declspec(deprecated)
#endif

namespace agt_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MapVersionSummary_
{
  using Type = MapVersionSummary_<ContainerAllocator>;

  explicit MapVersionSummary_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->map_version_id = "";
      this->parent_map_version_id = "";
      this->state = 0;
      this->active = false;
      this->pinned = false;
      this->deleted = false;
      this->valid = false;
      this->map_hash = "";
      this->manifest_sha256 = "";
      this->navigation_yaml_sha256 = "";
      this->navigation_image_sha256 = "";
      this->localization_pcd_sha256 = "";
      this->navigation_yaml = "";
      this->localization_pcd = "";
      this->processing_record = "";
      this->tasks_directory = "";
      this->storage_bytes = 0ull;
      this->created_at = "";
    }
  }

  explicit MapVersionSummary_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    map_id(_alloc),
    map_version_id(_alloc),
    parent_map_version_id(_alloc),
    map_hash(_alloc),
    manifest_sha256(_alloc),
    navigation_yaml_sha256(_alloc),
    navigation_image_sha256(_alloc),
    localization_pcd_sha256(_alloc),
    navigation_yaml(_alloc),
    localization_pcd(_alloc),
    processing_record(_alloc),
    tasks_directory(_alloc),
    created_at(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
      this->map_version_id = "";
      this->parent_map_version_id = "";
      this->state = 0;
      this->active = false;
      this->pinned = false;
      this->deleted = false;
      this->valid = false;
      this->map_hash = "";
      this->manifest_sha256 = "";
      this->navigation_yaml_sha256 = "";
      this->navigation_image_sha256 = "";
      this->localization_pcd_sha256 = "";
      this->navigation_yaml = "";
      this->localization_pcd = "";
      this->processing_record = "";
      this->tasks_directory = "";
      this->storage_bytes = 0ull;
      this->created_at = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_version_id_type map_version_id;
  using _parent_map_version_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _parent_map_version_id_type parent_map_version_id;
  using _state_type =
    uint8_t;
  _state_type state;
  using _active_type =
    bool;
  _active_type active;
  using _pinned_type =
    bool;
  _pinned_type pinned;
  using _deleted_type =
    bool;
  _deleted_type deleted;
  using _valid_type =
    bool;
  _valid_type valid;
  using _map_hash_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_hash_type map_hash;
  using _manifest_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _manifest_sha256_type manifest_sha256;
  using _navigation_yaml_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _navigation_yaml_sha256_type navigation_yaml_sha256;
  using _navigation_image_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _navigation_image_sha256_type navigation_image_sha256;
  using _localization_pcd_sha256_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _localization_pcd_sha256_type localization_pcd_sha256;
  using _navigation_yaml_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _navigation_yaml_type navigation_yaml;
  using _localization_pcd_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _localization_pcd_type localization_pcd;
  using _processing_record_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _processing_record_type processing_record;
  using _tasks_directory_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _tasks_directory_type tasks_directory;
  using _storage_bytes_type =
    uint64_t;
  _storage_bytes_type storage_bytes;
  using _created_at_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _created_at_type created_at;
  using _validation_errors_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _validation_errors_type validation_errors;
  using _validation_warnings_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _validation_warnings_type validation_warnings;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
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
  Type & set__parent_map_version_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->parent_map_version_id = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__active(
    const bool & _arg)
  {
    this->active = _arg;
    return *this;
  }
  Type & set__pinned(
    const bool & _arg)
  {
    this->pinned = _arg;
    return *this;
  }
  Type & set__deleted(
    const bool & _arg)
  {
    this->deleted = _arg;
    return *this;
  }
  Type & set__valid(
    const bool & _arg)
  {
    this->valid = _arg;
    return *this;
  }
  Type & set__map_hash(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_hash = _arg;
    return *this;
  }
  Type & set__manifest_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->manifest_sha256 = _arg;
    return *this;
  }
  Type & set__navigation_yaml_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->navigation_yaml_sha256 = _arg;
    return *this;
  }
  Type & set__navigation_image_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->navigation_image_sha256 = _arg;
    return *this;
  }
  Type & set__localization_pcd_sha256(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->localization_pcd_sha256 = _arg;
    return *this;
  }
  Type & set__navigation_yaml(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->navigation_yaml = _arg;
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
  Type & set__tasks_directory(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->tasks_directory = _arg;
    return *this;
  }
  Type & set__storage_bytes(
    const uint64_t & _arg)
  {
    this->storage_bytes = _arg;
    return *this;
  }
  Type & set__created_at(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->created_at = _arg;
    return *this;
  }
  Type & set__validation_errors(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->validation_errors = _arg;
    return *this;
  }
  Type & set__validation_warnings(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->validation_warnings = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t STATE_UNKNOWN =
    0u;
  static constexpr uint8_t STATE_DRAFT =
    1u;
  static constexpr uint8_t STATE_PROCESSING =
    2u;
  static constexpr uint8_t STATE_READY =
    3u;
  static constexpr uint8_t STATE_INVALID =
    4u;
  static constexpr uint8_t STATE_ARCHIVED =
    5u;
  static constexpr uint8_t STATE_DELETED =
    6u;

  // pointer types
  using RawPtr =
    agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> *;
  using ConstRawPtr =
    const agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agt_interfaces__msg__MapVersionSummary
    std::shared_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agt_interfaces__msg__MapVersionSummary
    std::shared_ptr<agt_interfaces::msg::MapVersionSummary_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MapVersionSummary_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->map_version_id != other.map_version_id) {
      return false;
    }
    if (this->parent_map_version_id != other.parent_map_version_id) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->active != other.active) {
      return false;
    }
    if (this->pinned != other.pinned) {
      return false;
    }
    if (this->deleted != other.deleted) {
      return false;
    }
    if (this->valid != other.valid) {
      return false;
    }
    if (this->map_hash != other.map_hash) {
      return false;
    }
    if (this->manifest_sha256 != other.manifest_sha256) {
      return false;
    }
    if (this->navigation_yaml_sha256 != other.navigation_yaml_sha256) {
      return false;
    }
    if (this->navigation_image_sha256 != other.navigation_image_sha256) {
      return false;
    }
    if (this->localization_pcd_sha256 != other.localization_pcd_sha256) {
      return false;
    }
    if (this->navigation_yaml != other.navigation_yaml) {
      return false;
    }
    if (this->localization_pcd != other.localization_pcd) {
      return false;
    }
    if (this->processing_record != other.processing_record) {
      return false;
    }
    if (this->tasks_directory != other.tasks_directory) {
      return false;
    }
    if (this->storage_bytes != other.storage_bytes) {
      return false;
    }
    if (this->created_at != other.created_at) {
      return false;
    }
    if (this->validation_errors != other.validation_errors) {
      return false;
    }
    if (this->validation_warnings != other.validation_warnings) {
      return false;
    }
    return true;
  }
  bool operator!=(const MapVersionSummary_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MapVersionSummary_

// alias to use template instance with default allocator
using MapVersionSummary =
  agt_interfaces::msg::MapVersionSummary_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_DRAFT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_PROCESSING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_READY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_INVALID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_ARCHIVED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MapVersionSummary_<ContainerAllocator>::STATE_DELETED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace agt_interfaces

#endif  // AGT_INTERFACES__MSG__DETAIL__MAP_VERSION_SUMMARY__STRUCT_HPP_
