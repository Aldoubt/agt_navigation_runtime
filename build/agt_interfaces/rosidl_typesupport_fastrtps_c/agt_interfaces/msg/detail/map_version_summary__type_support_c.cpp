// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from agt_interfaces:msg/MapVersionSummary.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/map_version_summary__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "agt_interfaces/msg/detail/map_version_summary__struct.h"
#include "agt_interfaces/msg/detail/map_version_summary__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // created_at, localization_pcd, localization_pcd_sha256, manifest_sha256, map_hash, map_id, map_version_id, navigation_image_sha256, navigation_yaml, navigation_yaml_sha256, parent_map_version_id, processing_record, tasks_directory, validation_errors, validation_warnings
#include "rosidl_runtime_c/string_functions.h"  // created_at, localization_pcd, localization_pcd_sha256, manifest_sha256, map_hash, map_id, map_version_id, navigation_image_sha256, navigation_yaml, navigation_yaml_sha256, parent_map_version_id, processing_record, tasks_directory, validation_errors, validation_warnings
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_agt_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _MapVersionSummary__ros_msg_type = agt_interfaces__msg__MapVersionSummary;

static bool _MapVersionSummary__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _MapVersionSummary__ros_msg_type * ros_message = static_cast<const _MapVersionSummary__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: map_id
  {
    const rosidl_runtime_c__String * str = &ros_message->map_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: map_version_id
  {
    const rosidl_runtime_c__String * str = &ros_message->map_version_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: parent_map_version_id
  {
    const rosidl_runtime_c__String * str = &ros_message->parent_map_version_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: state
  {
    cdr << ros_message->state;
  }

  // Field name: active
  {
    cdr << (ros_message->active ? true : false);
  }

  // Field name: pinned
  {
    cdr << (ros_message->pinned ? true : false);
  }

  // Field name: deleted
  {
    cdr << (ros_message->deleted ? true : false);
  }

  // Field name: valid
  {
    cdr << (ros_message->valid ? true : false);
  }

  // Field name: map_hash
  {
    const rosidl_runtime_c__String * str = &ros_message->map_hash;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: manifest_sha256
  {
    const rosidl_runtime_c__String * str = &ros_message->manifest_sha256;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: navigation_yaml_sha256
  {
    const rosidl_runtime_c__String * str = &ros_message->navigation_yaml_sha256;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: navigation_image_sha256
  {
    const rosidl_runtime_c__String * str = &ros_message->navigation_image_sha256;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: localization_pcd_sha256
  {
    const rosidl_runtime_c__String * str = &ros_message->localization_pcd_sha256;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: navigation_yaml
  {
    const rosidl_runtime_c__String * str = &ros_message->navigation_yaml;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: localization_pcd
  {
    const rosidl_runtime_c__String * str = &ros_message->localization_pcd;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: processing_record
  {
    const rosidl_runtime_c__String * str = &ros_message->processing_record;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: tasks_directory
  {
    const rosidl_runtime_c__String * str = &ros_message->tasks_directory;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: storage_bytes
  {
    cdr << ros_message->storage_bytes;
  }

  // Field name: created_at
  {
    const rosidl_runtime_c__String * str = &ros_message->created_at;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: validation_errors
  {
    size_t size = ros_message->validation_errors.size;
    auto array_ptr = ros_message->validation_errors.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: validation_warnings
  {
    size_t size = ros_message->validation_warnings.size;
    auto array_ptr = ros_message->validation_warnings.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  return true;
}

static bool _MapVersionSummary__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _MapVersionSummary__ros_msg_type * ros_message = static_cast<_MapVersionSummary__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: map_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->map_id.data) {
      rosidl_runtime_c__String__init(&ros_message->map_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->map_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'map_id'\n");
      return false;
    }
  }

  // Field name: map_version_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->map_version_id.data) {
      rosidl_runtime_c__String__init(&ros_message->map_version_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->map_version_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'map_version_id'\n");
      return false;
    }
  }

  // Field name: parent_map_version_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->parent_map_version_id.data) {
      rosidl_runtime_c__String__init(&ros_message->parent_map_version_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->parent_map_version_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'parent_map_version_id'\n");
      return false;
    }
  }

  // Field name: state
  {
    cdr >> ros_message->state;
  }

  // Field name: active
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->active = tmp ? true : false;
  }

  // Field name: pinned
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->pinned = tmp ? true : false;
  }

  // Field name: deleted
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->deleted = tmp ? true : false;
  }

  // Field name: valid
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->valid = tmp ? true : false;
  }

  // Field name: map_hash
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->map_hash.data) {
      rosidl_runtime_c__String__init(&ros_message->map_hash);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->map_hash,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'map_hash'\n");
      return false;
    }
  }

  // Field name: manifest_sha256
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->manifest_sha256.data) {
      rosidl_runtime_c__String__init(&ros_message->manifest_sha256);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->manifest_sha256,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'manifest_sha256'\n");
      return false;
    }
  }

  // Field name: navigation_yaml_sha256
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->navigation_yaml_sha256.data) {
      rosidl_runtime_c__String__init(&ros_message->navigation_yaml_sha256);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->navigation_yaml_sha256,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'navigation_yaml_sha256'\n");
      return false;
    }
  }

  // Field name: navigation_image_sha256
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->navigation_image_sha256.data) {
      rosidl_runtime_c__String__init(&ros_message->navigation_image_sha256);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->navigation_image_sha256,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'navigation_image_sha256'\n");
      return false;
    }
  }

  // Field name: localization_pcd_sha256
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->localization_pcd_sha256.data) {
      rosidl_runtime_c__String__init(&ros_message->localization_pcd_sha256);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->localization_pcd_sha256,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'localization_pcd_sha256'\n");
      return false;
    }
  }

  // Field name: navigation_yaml
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->navigation_yaml.data) {
      rosidl_runtime_c__String__init(&ros_message->navigation_yaml);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->navigation_yaml,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'navigation_yaml'\n");
      return false;
    }
  }

  // Field name: localization_pcd
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->localization_pcd.data) {
      rosidl_runtime_c__String__init(&ros_message->localization_pcd);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->localization_pcd,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'localization_pcd'\n");
      return false;
    }
  }

  // Field name: processing_record
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->processing_record.data) {
      rosidl_runtime_c__String__init(&ros_message->processing_record);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->processing_record,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'processing_record'\n");
      return false;
    }
  }

  // Field name: tasks_directory
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->tasks_directory.data) {
      rosidl_runtime_c__String__init(&ros_message->tasks_directory);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->tasks_directory,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'tasks_directory'\n");
      return false;
    }
  }

  // Field name: storage_bytes
  {
    cdr >> ros_message->storage_bytes;
  }

  // Field name: created_at
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->created_at.data) {
      rosidl_runtime_c__String__init(&ros_message->created_at);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->created_at,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'created_at'\n");
      return false;
    }
  }

  // Field name: validation_errors
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->validation_errors.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->validation_errors);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->validation_errors, size)) {
      fprintf(stderr, "failed to create array for field 'validation_errors'");
      return false;
    }
    auto array_ptr = ros_message->validation_errors.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'validation_errors'\n");
        return false;
      }
    }
  }

  // Field name: validation_warnings
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->validation_warnings.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->validation_warnings);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->validation_warnings, size)) {
      fprintf(stderr, "failed to create array for field 'validation_warnings'");
      return false;
    }
    auto array_ptr = ros_message->validation_warnings.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'validation_warnings'\n");
        return false;
      }
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t get_serialized_size_agt_interfaces__msg__MapVersionSummary(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MapVersionSummary__ros_msg_type * ros_message = static_cast<const _MapVersionSummary__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name map_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->map_id.size + 1);
  // field.name map_version_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->map_version_id.size + 1);
  // field.name parent_map_version_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->parent_map_version_id.size + 1);
  // field.name state
  {
    size_t item_size = sizeof(ros_message->state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name active
  {
    size_t item_size = sizeof(ros_message->active);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pinned
  {
    size_t item_size = sizeof(ros_message->pinned);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name deleted
  {
    size_t item_size = sizeof(ros_message->deleted);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name valid
  {
    size_t item_size = sizeof(ros_message->valid);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name map_hash
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->map_hash.size + 1);
  // field.name manifest_sha256
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->manifest_sha256.size + 1);
  // field.name navigation_yaml_sha256
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->navigation_yaml_sha256.size + 1);
  // field.name navigation_image_sha256
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->navigation_image_sha256.size + 1);
  // field.name localization_pcd_sha256
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->localization_pcd_sha256.size + 1);
  // field.name navigation_yaml
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->navigation_yaml.size + 1);
  // field.name localization_pcd
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->localization_pcd.size + 1);
  // field.name processing_record
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->processing_record.size + 1);
  // field.name tasks_directory
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->tasks_directory.size + 1);
  // field.name storage_bytes
  {
    size_t item_size = sizeof(ros_message->storage_bytes);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name created_at
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->created_at.size + 1);
  // field.name validation_errors
  {
    size_t array_size = ros_message->validation_errors.size;
    auto array_ptr = ros_message->validation_errors.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name validation_warnings
  {
    size_t array_size = ros_message->validation_warnings.size;
    auto array_ptr = ros_message->validation_warnings.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }

  return current_alignment - initial_alignment;
}

static uint32_t _MapVersionSummary__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_agt_interfaces__msg__MapVersionSummary(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t max_serialized_size_agt_interfaces__msg__MapVersionSummary(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_std_msgs__msg__Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: map_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: map_version_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: parent_map_version_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: active
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: pinned
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: deleted
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: valid
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: map_hash
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: manifest_sha256
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: navigation_yaml_sha256
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: navigation_image_sha256
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: localization_pcd_sha256
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: navigation_yaml
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: localization_pcd
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: processing_record
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: tasks_directory
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: storage_bytes
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: created_at
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: validation_errors
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: validation_warnings
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = agt_interfaces__msg__MapVersionSummary;
    is_plain =
      (
      offsetof(DataType, validation_warnings) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _MapVersionSummary__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_agt_interfaces__msg__MapVersionSummary(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_MapVersionSummary = {
  "agt_interfaces::msg",
  "MapVersionSummary",
  _MapVersionSummary__cdr_serialize,
  _MapVersionSummary__cdr_deserialize,
  _MapVersionSummary__get_serialized_size,
  _MapVersionSummary__max_serialized_size
};

static rosidl_message_type_support_t _MapVersionSummary__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MapVersionSummary,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, MapVersionSummary)() {
  return &_MapVersionSummary__type_support;
}

#if defined(__cplusplus)
}
#endif
