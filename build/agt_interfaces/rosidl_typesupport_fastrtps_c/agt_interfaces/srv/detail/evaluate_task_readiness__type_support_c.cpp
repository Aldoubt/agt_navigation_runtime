// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from agt_interfaces:srv/EvaluateTaskReadiness.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/srv/detail/evaluate_task_readiness__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.h"
#include "agt_interfaces/srv/detail/evaluate_task_readiness__functions.h"
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

#include "rosidl_runtime_c/string.h"  // task_id
#include "rosidl_runtime_c/string_functions.h"  // task_id

// forward declare type support functions


using _EvaluateTaskReadiness_Request__ros_msg_type = agt_interfaces__srv__EvaluateTaskReadiness_Request;

static bool _EvaluateTaskReadiness_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _EvaluateTaskReadiness_Request__ros_msg_type * ros_message = static_cast<const _EvaluateTaskReadiness_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: validate_task
  {
    cdr << (ros_message->validate_task ? true : false);
  }

  // Field name: task_id
  {
    const rosidl_runtime_c__String * str = &ros_message->task_id;
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

  // Field name: gate_profile
  {
    cdr << ros_message->gate_profile;
  }

  return true;
}

static bool _EvaluateTaskReadiness_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _EvaluateTaskReadiness_Request__ros_msg_type * ros_message = static_cast<_EvaluateTaskReadiness_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: validate_task
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->validate_task = tmp ? true : false;
  }

  // Field name: task_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->task_id.data) {
      rosidl_runtime_c__String__init(&ros_message->task_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->task_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'task_id'\n");
      return false;
    }
  }

  // Field name: gate_profile
  {
    cdr >> ros_message->gate_profile;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t get_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EvaluateTaskReadiness_Request__ros_msg_type * ros_message = static_cast<const _EvaluateTaskReadiness_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name validate_task
  {
    size_t item_size = sizeof(ros_message->validate_task);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name task_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->task_id.size + 1);
  // field.name gate_profile
  {
    size_t item_size = sizeof(ros_message->gate_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _EvaluateTaskReadiness_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t max_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Request(
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

  // member: validate_task
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: task_id
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
  // member: gate_profile
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
    using DataType = agt_interfaces__srv__EvaluateTaskReadiness_Request;
    is_plain =
      (
      offsetof(DataType, gate_profile) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _EvaluateTaskReadiness_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_EvaluateTaskReadiness_Request = {
  "agt_interfaces::srv",
  "EvaluateTaskReadiness_Request",
  _EvaluateTaskReadiness_Request__cdr_serialize,
  _EvaluateTaskReadiness_Request__cdr_deserialize,
  _EvaluateTaskReadiness_Request__get_serialized_size,
  _EvaluateTaskReadiness_Request__max_serialized_size
};

static rosidl_message_type_support_t _EvaluateTaskReadiness_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_EvaluateTaskReadiness_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, srv, EvaluateTaskReadiness_Request)() {
  return &_EvaluateTaskReadiness_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/evaluate_task_readiness__struct.h"
// already included above
// #include "agt_interfaces/srv/detail/evaluate_task_readiness__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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

#include "agt_interfaces/msg/detail/task_readiness__functions.h"  // readiness

// forward declare type support functions
size_t get_serialized_size_agt_interfaces__msg__TaskReadiness(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_agt_interfaces__msg__TaskReadiness(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness)();


using _EvaluateTaskReadiness_Response__ros_msg_type = agt_interfaces__srv__EvaluateTaskReadiness_Response;

static bool _EvaluateTaskReadiness_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _EvaluateTaskReadiness_Response__ros_msg_type * ros_message = static_cast<const _EvaluateTaskReadiness_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: readiness
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->readiness, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _EvaluateTaskReadiness_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _EvaluateTaskReadiness_Response__ros_msg_type * ros_message = static_cast<_EvaluateTaskReadiness_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: readiness
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, agt_interfaces, msg, TaskReadiness
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->readiness))
    {
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t get_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EvaluateTaskReadiness_Response__ros_msg_type * ros_message = static_cast<const _EvaluateTaskReadiness_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name readiness

  current_alignment += get_serialized_size_agt_interfaces__msg__TaskReadiness(
    &(ros_message->readiness), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _EvaluateTaskReadiness_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_agt_interfaces
size_t max_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Response(
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

  // member: readiness
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_agt_interfaces__msg__TaskReadiness(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = agt_interfaces__srv__EvaluateTaskReadiness_Response;
    is_plain =
      (
      offsetof(DataType, readiness) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _EvaluateTaskReadiness_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_agt_interfaces__srv__EvaluateTaskReadiness_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_EvaluateTaskReadiness_Response = {
  "agt_interfaces::srv",
  "EvaluateTaskReadiness_Response",
  _EvaluateTaskReadiness_Response__cdr_serialize,
  _EvaluateTaskReadiness_Response__cdr_deserialize,
  _EvaluateTaskReadiness_Response__get_serialized_size,
  _EvaluateTaskReadiness_Response__max_serialized_size
};

static rosidl_message_type_support_t _EvaluateTaskReadiness_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_EvaluateTaskReadiness_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, srv, EvaluateTaskReadiness_Response)() {
  return &_EvaluateTaskReadiness_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "agt_interfaces/srv/evaluate_task_readiness.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t EvaluateTaskReadiness__callbacks = {
  "agt_interfaces::srv",
  "EvaluateTaskReadiness",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, srv, EvaluateTaskReadiness_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, srv, EvaluateTaskReadiness_Response)(),
};

static rosidl_service_type_support_t EvaluateTaskReadiness__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &EvaluateTaskReadiness__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, agt_interfaces, srv, EvaluateTaskReadiness)() {
  return &EvaluateTaskReadiness__handle;
}

#if defined(__cplusplus)
}
#endif
