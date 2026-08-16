// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/MissionEvent.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/mission_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `event_type`
// Member `source`
// Member `correlation_id`
// Member `mission_id`
// Member `metadata_json`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__MissionEvent__init(agt_interfaces__msg__MissionEvent * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  // event_type
  if (!rosidl_runtime_c__String__init(&msg->event_type)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__init(&msg->source)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  // correlation_id
  if (!rosidl_runtime_c__String__init(&msg->correlation_id)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__init(&msg->mission_id)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__init(&msg->metadata_json)) {
    agt_interfaces__msg__MissionEvent__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__MissionEvent__fini(agt_interfaces__msg__MissionEvent * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // event_type
  rosidl_runtime_c__String__fini(&msg->event_type);
  // source
  rosidl_runtime_c__String__fini(&msg->source);
  // correlation_id
  rosidl_runtime_c__String__fini(&msg->correlation_id);
  // mission_id
  rosidl_runtime_c__String__fini(&msg->mission_id);
  // metadata_json
  rosidl_runtime_c__String__fini(&msg->metadata_json);
}

bool
agt_interfaces__msg__MissionEvent__are_equal(const agt_interfaces__msg__MissionEvent * lhs, const agt_interfaces__msg__MissionEvent * rhs)
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
  // event_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->event_type), &(rhs->event_type)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source), &(rhs->source)))
  {
    return false;
  }
  // correlation_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->correlation_id), &(rhs->correlation_id)))
  {
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mission_id), &(rhs->mission_id)))
  {
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->metadata_json), &(rhs->metadata_json)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__MissionEvent__copy(
  const agt_interfaces__msg__MissionEvent * input,
  agt_interfaces__msg__MissionEvent * output)
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
  // event_type
  if (!rosidl_runtime_c__String__copy(
      &(input->event_type), &(output->event_type)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__copy(
      &(input->source), &(output->source)))
  {
    return false;
  }
  // correlation_id
  if (!rosidl_runtime_c__String__copy(
      &(input->correlation_id), &(output->correlation_id)))
  {
    return false;
  }
  // mission_id
  if (!rosidl_runtime_c__String__copy(
      &(input->mission_id), &(output->mission_id)))
  {
    return false;
  }
  // metadata_json
  if (!rosidl_runtime_c__String__copy(
      &(input->metadata_json), &(output->metadata_json)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__MissionEvent *
agt_interfaces__msg__MissionEvent__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionEvent * msg = (agt_interfaces__msg__MissionEvent *)allocator.allocate(sizeof(agt_interfaces__msg__MissionEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__MissionEvent));
  bool success = agt_interfaces__msg__MissionEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__MissionEvent__destroy(agt_interfaces__msg__MissionEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__MissionEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__MissionEvent__Sequence__init(agt_interfaces__msg__MissionEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionEvent * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__MissionEvent *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__MissionEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__MissionEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__MissionEvent__fini(&data[i - 1]);
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
agt_interfaces__msg__MissionEvent__Sequence__fini(agt_interfaces__msg__MissionEvent__Sequence * array)
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
      agt_interfaces__msg__MissionEvent__fini(&array->data[i]);
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

agt_interfaces__msg__MissionEvent__Sequence *
agt_interfaces__msg__MissionEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__MissionEvent__Sequence * array = (agt_interfaces__msg__MissionEvent__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__MissionEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__MissionEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__MissionEvent__Sequence__destroy(agt_interfaces__msg__MissionEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__MissionEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__MissionEvent__Sequence__are_equal(const agt_interfaces__msg__MissionEvent__Sequence * lhs, const agt_interfaces__msg__MissionEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__MissionEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__MissionEvent__Sequence__copy(
  const agt_interfaces__msg__MissionEvent__Sequence * input,
  agt_interfaces__msg__MissionEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__MissionEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__MissionEvent * data =
      (agt_interfaces__msg__MissionEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__MissionEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__MissionEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__MissionEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
