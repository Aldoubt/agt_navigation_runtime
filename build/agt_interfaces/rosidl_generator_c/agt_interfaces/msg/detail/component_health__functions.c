// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/component_health__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `component_id`
// Member `display_name`
// Member `missing_topics`
// Member `missing_frames`
// Member `missing_nodes`
// Member `lifecycle_failures`
// Member `condition_failures`
// Member `warnings`
// Member `errors`
// Member `detail`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__ComponentHealth__init(agt_interfaces__msg__ComponentHealth * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // component_id
  if (!rosidl_runtime_c__String__init(&msg->component_id)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // display_name
  if (!rosidl_runtime_c__String__init(&msg->display_name)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // state
  // required
  // present
  // observed_rate_hz
  // message_age_sec
  // message_count
  // missing_topics
  if (!rosidl_runtime_c__String__Sequence__init(&msg->missing_topics, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // missing_frames
  if (!rosidl_runtime_c__String__Sequence__init(&msg->missing_frames, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // missing_nodes
  if (!rosidl_runtime_c__String__Sequence__init(&msg->missing_nodes, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // lifecycle_failures
  if (!rosidl_runtime_c__String__Sequence__init(&msg->lifecycle_failures, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // condition_failures
  if (!rosidl_runtime_c__String__Sequence__init(&msg->condition_failures, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // warnings
  if (!rosidl_runtime_c__String__Sequence__init(&msg->warnings, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // errors
  if (!rosidl_runtime_c__String__Sequence__init(&msg->errors, 0)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__init(&msg->detail)) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__ComponentHealth__fini(agt_interfaces__msg__ComponentHealth * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // component_id
  rosidl_runtime_c__String__fini(&msg->component_id);
  // display_name
  rosidl_runtime_c__String__fini(&msg->display_name);
  // state
  // required
  // present
  // observed_rate_hz
  // message_age_sec
  // message_count
  // missing_topics
  rosidl_runtime_c__String__Sequence__fini(&msg->missing_topics);
  // missing_frames
  rosidl_runtime_c__String__Sequence__fini(&msg->missing_frames);
  // missing_nodes
  rosidl_runtime_c__String__Sequence__fini(&msg->missing_nodes);
  // lifecycle_failures
  rosidl_runtime_c__String__Sequence__fini(&msg->lifecycle_failures);
  // condition_failures
  rosidl_runtime_c__String__Sequence__fini(&msg->condition_failures);
  // warnings
  rosidl_runtime_c__String__Sequence__fini(&msg->warnings);
  // errors
  rosidl_runtime_c__String__Sequence__fini(&msg->errors);
  // detail
  rosidl_runtime_c__String__fini(&msg->detail);
}

bool
agt_interfaces__msg__ComponentHealth__are_equal(const agt_interfaces__msg__ComponentHealth * lhs, const agt_interfaces__msg__ComponentHealth * rhs)
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
  // component_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->component_id), &(rhs->component_id)))
  {
    return false;
  }
  // display_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->display_name), &(rhs->display_name)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // required
  if (lhs->required != rhs->required) {
    return false;
  }
  // present
  if (lhs->present != rhs->present) {
    return false;
  }
  // observed_rate_hz
  if (lhs->observed_rate_hz != rhs->observed_rate_hz) {
    return false;
  }
  // message_age_sec
  if (lhs->message_age_sec != rhs->message_age_sec) {
    return false;
  }
  // message_count
  if (lhs->message_count != rhs->message_count) {
    return false;
  }
  // missing_topics
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->missing_topics), &(rhs->missing_topics)))
  {
    return false;
  }
  // missing_frames
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->missing_frames), &(rhs->missing_frames)))
  {
    return false;
  }
  // missing_nodes
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->missing_nodes), &(rhs->missing_nodes)))
  {
    return false;
  }
  // lifecycle_failures
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->lifecycle_failures), &(rhs->lifecycle_failures)))
  {
    return false;
  }
  // condition_failures
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->condition_failures), &(rhs->condition_failures)))
  {
    return false;
  }
  // warnings
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->warnings), &(rhs->warnings)))
  {
    return false;
  }
  // errors
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->errors), &(rhs->errors)))
  {
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detail), &(rhs->detail)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__ComponentHealth__copy(
  const agt_interfaces__msg__ComponentHealth * input,
  agt_interfaces__msg__ComponentHealth * output)
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
  // component_id
  if (!rosidl_runtime_c__String__copy(
      &(input->component_id), &(output->component_id)))
  {
    return false;
  }
  // display_name
  if (!rosidl_runtime_c__String__copy(
      &(input->display_name), &(output->display_name)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // required
  output->required = input->required;
  // present
  output->present = input->present;
  // observed_rate_hz
  output->observed_rate_hz = input->observed_rate_hz;
  // message_age_sec
  output->message_age_sec = input->message_age_sec;
  // message_count
  output->message_count = input->message_count;
  // missing_topics
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->missing_topics), &(output->missing_topics)))
  {
    return false;
  }
  // missing_frames
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->missing_frames), &(output->missing_frames)))
  {
    return false;
  }
  // missing_nodes
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->missing_nodes), &(output->missing_nodes)))
  {
    return false;
  }
  // lifecycle_failures
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->lifecycle_failures), &(output->lifecycle_failures)))
  {
    return false;
  }
  // condition_failures
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->condition_failures), &(output->condition_failures)))
  {
    return false;
  }
  // warnings
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->warnings), &(output->warnings)))
  {
    return false;
  }
  // errors
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->errors), &(output->errors)))
  {
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__copy(
      &(input->detail), &(output->detail)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__ComponentHealth *
agt_interfaces__msg__ComponentHealth__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ComponentHealth * msg = (agt_interfaces__msg__ComponentHealth *)allocator.allocate(sizeof(agt_interfaces__msg__ComponentHealth), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__ComponentHealth));
  bool success = agt_interfaces__msg__ComponentHealth__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__ComponentHealth__destroy(agt_interfaces__msg__ComponentHealth * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__ComponentHealth__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__ComponentHealth__Sequence__init(agt_interfaces__msg__ComponentHealth__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ComponentHealth * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__ComponentHealth *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__ComponentHealth), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__ComponentHealth__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__ComponentHealth__fini(&data[i - 1]);
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
agt_interfaces__msg__ComponentHealth__Sequence__fini(agt_interfaces__msg__ComponentHealth__Sequence * array)
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
      agt_interfaces__msg__ComponentHealth__fini(&array->data[i]);
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

agt_interfaces__msg__ComponentHealth__Sequence *
agt_interfaces__msg__ComponentHealth__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__ComponentHealth__Sequence * array = (agt_interfaces__msg__ComponentHealth__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__ComponentHealth__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__ComponentHealth__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__ComponentHealth__Sequence__destroy(agt_interfaces__msg__ComponentHealth__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__ComponentHealth__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__ComponentHealth__Sequence__are_equal(const agt_interfaces__msg__ComponentHealth__Sequence * lhs, const agt_interfaces__msg__ComponentHealth__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__ComponentHealth__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__ComponentHealth__Sequence__copy(
  const agt_interfaces__msg__ComponentHealth__Sequence * input,
  agt_interfaces__msg__ComponentHealth__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__ComponentHealth);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__ComponentHealth * data =
      (agt_interfaces__msg__ComponentHealth *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__ComponentHealth__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__ComponentHealth__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__ComponentHealth__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
