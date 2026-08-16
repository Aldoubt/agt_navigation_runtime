// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/bag_session_summary__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "agt_interfaces/msg/detail/bag_session_summary__struct.h"
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"
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

#include "rosidl_runtime_c/string.h"  // bag_id, experiment_id, message, profile_id, relative_uri, started_at, storage_identifier, updated_at
#include "rosidl_runtime_c/string_functions.h"  // bag_id, experiment_id, message, profile_id, relative_uri, started_at, storage_identifier, updated_at
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


using _BagSessionSummary__ros_msg_type = agt_interfaces__msg__BagSessionSummary;

static bool _BagSessionSummary__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _BagSessionSummary__ros_msg_type * ros_message = static_cast<const _BagSessionSummary__ros_msg_type *>(untyped_ros_message);
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

  // Field name: state
  {
    cdr << ros_message->state;
  }

  // Field name: bag_id
  {
    const rosidl_runtime_c__String * str = &ros_message->bag_id;
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

  // Field name: experiment_id
  {
    const rosidl_runtime_c__String * str = &ros_message->experiment_id;
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

  // Field name: profile_id
  {
    const rosidl_runtime_c__String * str = &ros_message->profile_id;
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

  // Field name: relative_uri
  {
    const rosidl_runtime_c__String * str = &ros_message->relative_uri;
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

  // Field name: complete
  {
    cdr << (ros_message->complete ? true : false);
  }

  // Field name: simulation
  {
    cdr << (ros_message->simulation ? true : false);
  }

  // Field name: playback_rate
  {
    cdr << ros_message->playback_rate;
  }

  // Field name: storage_bytes
  {
    cdr << ros_message->storage_bytes;
  }

  // Field name: started_at
  {
    const rosidl_runtime_c__String * str = &ros_message->started_at;
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

  // Field name: updated_at
  {
    const rosidl_runtime_c__String * str = &ros_message->updated_at;
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

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
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

  // Field name: process_id
  {
    cdr << ros_message->process_id;
  }

  // Field name: message_count
  {
    cdr << ros_message->message_count;
  }

  // Field name: storage_identifier
  {
    const rosidl_runtime_c__String * str = &ros_message->storage_identifier;
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

  // Field name: mapping_input_ready
  {
    cdr << (ros_message->mapping_input_ready ? true : false);
  }

  // Field name: contains_mapping_outputs
  {
    cdr << (ros_message->contains_mapping_outputs ? true : false);
  }

  // Field name: contains_navigation_outputs
  {
    cdr << (ros_message->contains_navigation_outputs ? true : false);
  }

  return true;
}

static bool _BagSessionSummary__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _BagSessionSummary__ros_msg_type * ros_message = static_cast<_BagSessionSummary__ros_msg_type *>(untyped_ros_message);
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

  // Field name: state
  {
    cdr >> ros_message->state;
  }

  // Field name: bag_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->bag_id.data) {
      rosidl_runtime_c__String__init(&ros_message->bag_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->bag_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'bag_id'\n");
      return false;
    }
  }

  // Field name: experiment_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->experiment_id.data) {
      rosidl_runtime_c__String__init(&ros_message->experiment_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->experiment_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'experiment_id'\n");
      return false;
    }
  }

  // Field name: profile_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->profile_id.data) {
      rosidl_runtime_c__String__init(&ros_message->profile_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->profile_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'profile_id'\n");
      return false;
    }
  }

  // Field name: relative_uri
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->relative_uri.data) {
      rosidl_runtime_c__String__init(&ros_message->relative_uri);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->relative_uri,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'relative_uri'\n");
      return false;
    }
  }

  // Field name: complete
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->complete = tmp ? true : false;
  }

  // Field name: simulation
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->simulation = tmp ? true : false;
  }

  // Field name: playback_rate
  {
    cdr >> ros_message->playback_rate;
  }

  // Field name: storage_bytes
  {
    cdr >> ros_message->storage_bytes;
  }

  // Field name: started_at
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->started_at.data) {
      rosidl_runtime_c__String__init(&ros_message->started_at);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->started_at,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'started_at'\n");
      return false;
    }
  }

  // Field name: updated_at
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->updated_at.data) {
      rosidl_runtime_c__String__init(&ros_message->updated_at);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->updated_at,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'updated_at'\n");
      return false;
    }
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
  }

  // Field name: process_id
  {
    cdr >> ros_message->process_id;
  }

  // Field name: message_count
  {
    cdr >> ros_message->message_count;
  }

  // Field name: storage_identifier
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->storage_identifier.data) {
      rosidl_runtime_c__String__init(&ros_message->storage_identifier);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->storage_identifier,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'storage_identifier'\n");
      return false;
    }
  }

  // Field name: mapping_input_ready
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->mapping_input_ready = tmp ? true : false;
  }

  // Field name: contains_mapping_outputs
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->contains_mapping_outputs = tmp ? true : false;
  }

  // Field name: contains_navigation_outputs
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->contains_navigation_outputs = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t get_serialized_size_agt_interfaces__msg__BagSessionSummary(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BagSessionSummary__ros_msg_type * ros_message = static_cast<const _BagSessionSummary__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name state
  {
    size_t item_size = sizeof(ros_message->state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name bag_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->bag_id.size + 1);
  // field.name experiment_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->experiment_id.size + 1);
  // field.name profile_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->profile_id.size + 1);
  // field.name relative_uri
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->relative_uri.size + 1);
  // field.name complete
  {
    size_t item_size = sizeof(ros_message->complete);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name simulation
  {
    size_t item_size = sizeof(ros_message->simulation);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name playback_rate
  {
    size_t item_size = sizeof(ros_message->playback_rate);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name storage_bytes
  {
    size_t item_size = sizeof(ros_message->storage_bytes);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name started_at
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->started_at.size + 1);
  // field.name updated_at
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->updated_at.size + 1);
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);
  // field.name process_id
  {
    size_t item_size = sizeof(ros_message->process_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message_count
  {
    size_t item_size = sizeof(ros_message->message_count);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name storage_identifier
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->storage_identifier.size + 1);
  // field.name mapping_input_ready
  {
    size_t item_size = sizeof(ros_message->mapping_input_ready);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name contains_mapping_outputs
  {
    size_t item_size = sizeof(ros_message->contains_mapping_outputs);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name contains_navigation_outputs
  {
    size_t item_size = sizeof(ros_message->contains_navigation_outputs);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _BagSessionSummary__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_agt_interfaces__msg__BagSessionSummary(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t max_serialized_size_agt_interfaces__msg__BagSessionSummary(
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
  // member: state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: bag_id
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
  // member: experiment_id
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
  // member: profile_id
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
  // member: relative_uri
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
  // member: complete
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: simulation
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: playback_rate
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: storage_bytes
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: started_at
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
  // member: updated_at
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
  // member: message
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
  // member: process_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: message_count
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: storage_identifier
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
  // member: mapping_input_ready
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: contains_mapping_outputs
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: contains_navigation_outputs
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = agt_interfaces__msg__BagSessionSummary;
    is_plain =
      (
      offsetof(DataType, contains_navigation_outputs) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _BagSessionSummary__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_agt_interfaces__msg__BagSessionSummary(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_BagSessionSummary = {
  "agt_interfaces::msg",
  "BagSessionSummary",
  _BagSessionSummary__cdr_serialize,
  _BagSessionSummary__cdr_deserialize,
  _BagSessionSummary__get_serialized_size,
  _BagSessionSummary__max_serialized_size
};

static rosidl_message_type_support_t _BagSessionSummary__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_BagSessionSummary,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, BagSessionSummary)() {
  return &_BagSessionSummary__type_support;
}

#if defined(__cplusplus)
}
#endif
