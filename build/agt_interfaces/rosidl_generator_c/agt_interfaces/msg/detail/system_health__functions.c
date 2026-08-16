// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/SystemHealth.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/system_health__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `components`
#include "agt_interfaces/msg/detail/component_health__functions.h"
// Member `blocker_codes`
// Member `blocker_messages`
// Member `warning_codes`
// Member `warning_messages`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__SystemHealth__init(agt_interfaces__msg__SystemHealth * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  // overall_state
  // revision
  // components
  if (!agt_interfaces__msg__ComponentHealth__Sequence__init(&msg->components, 0)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  // blocker_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_codes, 0)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  // blocker_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->blocker_messages, 0)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  // warning_codes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->warning_codes, 0)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  // warning_messages
  if (!rosidl_runtime_c__String__Sequence__init(&msg->warning_messages, 0)) {
    agt_interfaces__msg__SystemHealth__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__SystemHealth__fini(agt_interfaces__msg__SystemHealth * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // overall_state
  // revision
  // components
  agt_interfaces__msg__ComponentHealth__Sequence__fini(&msg->components);
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
agt_interfaces__msg__SystemHealth__are_equal(const agt_interfaces__msg__SystemHealth * lhs, const agt_interfaces__msg__SystemHealth * rhs)
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
  // overall_state
  if (lhs->overall_state != rhs->overall_state) {
    return false;
  }
  // revision
  if (lhs->revision != rhs->revision) {
    return false;
  }
  // components
  if (!agt_interfaces__msg__ComponentHealth__Sequence__are_equal(
      &(lhs->components), &(rhs->components)))
  {
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
agt_interfaces__msg__SystemHealth__copy(
  const agt_interfaces__msg__SystemHealth * input,
  agt_interfaces__msg__SystemHealth * output)
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
  // overall_state
  output->overall_state = input->overall_state;
  // revision
  output->revision = input->revision;
  // components
  if (!agt_interfaces__msg__ComponentHealth__Sequence__copy(
      &(input->components), &(output->components)))
  {
    return false;
  }
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

agt_interfaces__msg__SystemHealth *
agt_interfaces__msg__SystemHealth__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SystemHealth * msg = (agt_interfaces__msg__SystemHealth *)allocator.allocate(sizeof(agt_interfaces__msg__SystemHealth), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__SystemHealth));
  bool success = agt_interfaces__msg__SystemHealth__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__SystemHealth__destroy(agt_interfaces__msg__SystemHealth * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__SystemHealth__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__SystemHealth__Sequence__init(agt_interfaces__msg__SystemHealth__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SystemHealth * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__SystemHealth *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__SystemHealth), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__SystemHealth__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__SystemHealth__fini(&data[i - 1]);
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
agt_interfaces__msg__SystemHealth__Sequence__fini(agt_interfaces__msg__SystemHealth__Sequence * array)
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
      agt_interfaces__msg__SystemHealth__fini(&array->data[i]);
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

agt_interfaces__msg__SystemHealth__Sequence *
agt_interfaces__msg__SystemHealth__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SystemHealth__Sequence * array = (agt_interfaces__msg__SystemHealth__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__SystemHealth__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__SystemHealth__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__SystemHealth__Sequence__destroy(agt_interfaces__msg__SystemHealth__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__SystemHealth__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__SystemHealth__Sequence__are_equal(const agt_interfaces__msg__SystemHealth__Sequence * lhs, const agt_interfaces__msg__SystemHealth__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__SystemHealth__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__SystemHealth__Sequence__copy(
  const agt_interfaces__msg__SystemHealth__Sequence * input,
  agt_interfaces__msg__SystemHealth__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__SystemHealth);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__SystemHealth * data =
      (agt_interfaces__msg__SystemHealth *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__SystemHealth__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__SystemHealth__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__SystemHealth__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
