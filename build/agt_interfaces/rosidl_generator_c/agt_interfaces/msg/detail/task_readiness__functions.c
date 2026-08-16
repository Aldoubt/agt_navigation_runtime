// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/TaskReadiness.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/task_readiness__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `active_mode`
// Member `map_id`
// Member `map_version_id`
// Member `localization_state`
// Member `blocker_codes`
// Member `blocker_messages`
// Member `warning_codes`
// Member `warning_messages`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__TaskReadiness__init(agt_interfaces__msg__TaskReadiness * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // ready
  // active_mode
  if (!rosidl_runtime_c__String__init(&msg->active_mode)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__init(&msg->map_version_id)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // localization_state
  if (!rosidl_runtime_c__String__init(&msg->localization_state)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // health_revision
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_codes, 0)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_messages, 0)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // warning_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->warning_codes, 0)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  // warning_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->warning_messages, 0)) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__TaskReadiness__fini(agt_interfaces__msg__TaskReadiness * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // ready
  // active_mode
  rosidl_runtime_c__String__fini(&msg->active_mode);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_version_id
  rosidl_runtime_c__String__fini(&msg->map_version_id);
  // localization_state
  rosidl_runtime_c__String__fini(&msg->localization_state);
  // health_revision
  // blocker_codes
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_codes);
  // blocker_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->blocker_messages);
  // warning_codes
  rosidl_runtime_c__String__Sequence__fini(&msg->warning_codes);
  // warning_messages
  rosidl_runtime_c__String__Sequence__fini(&msg->warning_messages);
}

bool
agt_interfaces__msg__TaskReadiness__are_equal(const agt_interfaces__msg__TaskReadiness * lhs, const agt_interfaces__msg__TaskReadiness * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // ready
  if (lhs->ready != rhs->ready) {
    return false;
  }
  // active_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->active_mode), &(rhs->active_mode)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_version_id), &(rhs->map_version_id)))
  {
    return false;
  }
  // localization_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->localization_state), &(rhs->localization_state)))
  {
    return false;
  }
  // health_revision
  if (lhs->health_revision != rhs->health_revision) {
    return false;
  }
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->blocker_codes), &(rhs->blocker_codes)))
  {
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->blocker_messages), &(rhs->blocker_messages)))
  {
    return false;
  }
  // warning_codes
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->warning_codes), &(rhs->warning_codes)))
  {
    return false;
  }
  // warning_messages
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->warning_messages), &(rhs->warning_messages)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__TaskReadiness__copy(
  const agt_interfaces__msg__TaskReadiness * input,
  agt_interfaces__msg__TaskReadiness * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // ready
  output->ready = input->ready;
  // active_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->active_mode), &(output->active_mode)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // map_version_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_version_id), &(output->map_version_id)))
  {
    return false;
  }
  // localization_state
  if (!rosidl_runtime_c__String__copy(
      &(input->localization_state), &(output->localization_state)))
  {
    return false;
  }
  // health_revision
  output->health_revision = input->health_revision;
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->blocker_codes), &(output->blocker_codes)))
  {
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->blocker_messages), &(output->blocker_messages)))
  {
    return false;
  }
  // warning_codes
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->warning_codes), &(output->warning_codes)))
  {
    return false;
  }
  // warning_messages
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->warning_messages), &(output->warning_messages)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__TaskReadiness *
agt_interfaces__msg__TaskReadiness__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__TaskReadiness * msg = (agt_interfaces__msg__TaskReadiness *)allocator.allocate(sizeof(agt_interfaces__msg__TaskReadiness), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__TaskReadiness));
  bool success = agt_interfaces__msg__TaskReadiness__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__TaskReadiness__destroy(agt_interfaces__msg__TaskReadiness * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__TaskReadiness__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__TaskReadiness__Sequence__init(agt_interfaces__msg__TaskReadiness__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__TaskReadiness * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__TaskReadiness *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__TaskReadiness), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__TaskReadiness__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__TaskReadiness__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
agt_interfaces__msg__TaskReadiness__Sequence__fini(agt_interfaces__msg__TaskReadiness__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      agt_interfaces__msg__TaskReadiness__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

agt_interfaces__msg__TaskReadiness__Sequence *
agt_interfaces__msg__TaskReadiness__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__TaskReadiness__Sequence * array = (agt_interfaces__msg__TaskReadiness__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__TaskReadiness__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__TaskReadiness__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__TaskReadiness__Sequence__destroy(agt_interfaces__msg__TaskReadiness__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__TaskReadiness__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__TaskReadiness__Sequence__are_equal(const agt_interfaces__msg__TaskReadiness__Sequence * lhs, const agt_interfaces__msg__TaskReadiness__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__TaskReadiness__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__TaskReadiness__Sequence__copy(
  const agt_interfaces__msg__TaskReadiness__Sequence * input,
  agt_interfaces__msg__TaskReadiness__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__TaskReadiness);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__TaskReadiness * data =
      (agt_interfaces__msg__TaskReadiness *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__TaskReadiness__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__TaskReadiness__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__TaskReadiness__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
