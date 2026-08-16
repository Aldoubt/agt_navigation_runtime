// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/BagSessionSummary.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `bag_id`
// Member `experiment_id`
// Member `profile_id`
// Member `relative_uri`
// Member `started_at`
// Member `updated_at`
// Member `message`
// Member `storage_identifier`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__msg__BagSessionSummary__init(agt_interfaces__msg__BagSessionSummary * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // state
  // bag_id
  if (!rosidl_runtime_c__String__init(&msg->bag_id)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__init(&msg->experiment_id)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__init(&msg->profile_id)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // relative_uri
  if (!rosidl_runtime_c__String__init(&msg->relative_uri)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // complete
  // simulation
  // playback_rate
  // storage_bytes
  // started_at
  if (!rosidl_runtime_c__String__init(&msg->started_at)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // updated_at
  if (!rosidl_runtime_c__String__init(&msg->updated_at)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // process_id
  // message_count
  // storage_identifier
  if (!rosidl_runtime_c__String__init(&msg->storage_identifier)) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
    return false;
  }
  // mapping_input_ready
  // contains_mapping_outputs
  // contains_navigation_outputs
  return true;
}

void
agt_interfaces__msg__BagSessionSummary__fini(agt_interfaces__msg__BagSessionSummary * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
  // bag_id
  rosidl_runtime_c__String__fini(&msg->bag_id);
  // experiment_id
  rosidl_runtime_c__String__fini(&msg->experiment_id);
  // profile_id
  rosidl_runtime_c__String__fini(&msg->profile_id);
  // relative_uri
  rosidl_runtime_c__String__fini(&msg->relative_uri);
  // complete
  // simulation
  // playback_rate
  // storage_bytes
  // started_at
  rosidl_runtime_c__String__fini(&msg->started_at);
  // updated_at
  rosidl_runtime_c__String__fini(&msg->updated_at);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // process_id
  // message_count
  // storage_identifier
  rosidl_runtime_c__String__fini(&msg->storage_identifier);
  // mapping_input_ready
  // contains_mapping_outputs
  // contains_navigation_outputs
}

bool
agt_interfaces__msg__BagSessionSummary__are_equal(const agt_interfaces__msg__BagSessionSummary * lhs, const agt_interfaces__msg__BagSessionSummary * rhs)
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
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // bag_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->bag_id), &(rhs->bag_id)))
  {
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->experiment_id), &(rhs->experiment_id)))
  {
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->profile_id), &(rhs->profile_id)))
  {
    return false;
  }
  // relative_uri
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->relative_uri), &(rhs->relative_uri)))
  {
    return false;
  }
  // complete
  if (lhs->complete != rhs->complete) {
    return false;
  }
  // simulation
  if (lhs->simulation != rhs->simulation) {
    return false;
  }
  // playback_rate
  if (lhs->playback_rate != rhs->playback_rate) {
    return false;
  }
  // storage_bytes
  if (lhs->storage_bytes != rhs->storage_bytes) {
    return false;
  }
  // started_at
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->started_at), &(rhs->started_at)))
  {
    return false;
  }
  // updated_at
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->updated_at), &(rhs->updated_at)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // process_id
  if (lhs->process_id != rhs->process_id) {
    return false;
  }
  // message_count
  if (lhs->message_count != rhs->message_count) {
    return false;
  }
  // storage_identifier
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->storage_identifier), &(rhs->storage_identifier)))
  {
    return false;
  }
  // mapping_input_ready
  if (lhs->mapping_input_ready != rhs->mapping_input_ready) {
    return false;
  }
  // contains_mapping_outputs
  if (lhs->contains_mapping_outputs != rhs->contains_mapping_outputs) {
    return false;
  }
  // contains_navigation_outputs
  if (lhs->contains_navigation_outputs != rhs->contains_navigation_outputs) {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__BagSessionSummary__copy(
  const agt_interfaces__msg__BagSessionSummary * input,
  agt_interfaces__msg__BagSessionSummary * output)
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
  // state
  output->state = input->state;
  // bag_id
  if (!rosidl_runtime_c__String__copy(
      &(input->bag_id), &(output->bag_id)))
  {
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__copy(
      &(input->experiment_id), &(output->experiment_id)))
  {
    return false;
  }
  // profile_id
  if (!rosidl_runtime_c__String__copy(
      &(input->profile_id), &(output->profile_id)))
  {
    return false;
  }
  // relative_uri
  if (!rosidl_runtime_c__String__copy(
      &(input->relative_uri), &(output->relative_uri)))
  {
    return false;
  }
  // complete
  output->complete = input->complete;
  // simulation
  output->simulation = input->simulation;
  // playback_rate
  output->playback_rate = input->playback_rate;
  // storage_bytes
  output->storage_bytes = input->storage_bytes;
  // started_at
  if (!rosidl_runtime_c__String__copy(
      &(input->started_at), &(output->started_at)))
  {
    return false;
  }
  // updated_at
  if (!rosidl_runtime_c__String__copy(
      &(input->updated_at), &(output->updated_at)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // process_id
  output->process_id = input->process_id;
  // message_count
  output->message_count = input->message_count;
  // storage_identifier
  if (!rosidl_runtime_c__String__copy(
      &(input->storage_identifier), &(output->storage_identifier)))
  {
    return false;
  }
  // mapping_input_ready
  output->mapping_input_ready = input->mapping_input_ready;
  // contains_mapping_outputs
  output->contains_mapping_outputs = input->contains_mapping_outputs;
  // contains_navigation_outputs
  output->contains_navigation_outputs = input->contains_navigation_outputs;
  return true;
}

agt_interfaces__msg__BagSessionSummary *
agt_interfaces__msg__BagSessionSummary__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__BagSessionSummary * msg = (agt_interfaces__msg__BagSessionSummary *)allocator.allocate(sizeof(agt_interfaces__msg__BagSessionSummary), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__BagSessionSummary));
  bool success = agt_interfaces__msg__BagSessionSummary__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__BagSessionSummary__destroy(agt_interfaces__msg__BagSessionSummary * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__BagSessionSummary__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__BagSessionSummary__Sequence__init(agt_interfaces__msg__BagSessionSummary__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__BagSessionSummary * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__BagSessionSummary *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__BagSessionSummary), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__BagSessionSummary__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__BagSessionSummary__fini(&data[i - 1]);
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
agt_interfaces__msg__BagSessionSummary__Sequence__fini(agt_interfaces__msg__BagSessionSummary__Sequence * array)
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
      agt_interfaces__msg__BagSessionSummary__fini(&array->data[i]);
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

agt_interfaces__msg__BagSessionSummary__Sequence *
agt_interfaces__msg__BagSessionSummary__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__BagSessionSummary__Sequence * array = (agt_interfaces__msg__BagSessionSummary__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__BagSessionSummary__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__BagSessionSummary__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__BagSessionSummary__Sequence__destroy(agt_interfaces__msg__BagSessionSummary__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__BagSessionSummary__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__BagSessionSummary__Sequence__are_equal(const agt_interfaces__msg__BagSessionSummary__Sequence * lhs, const agt_interfaces__msg__BagSessionSummary__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__BagSessionSummary__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__BagSessionSummary__Sequence__copy(
  const agt_interfaces__msg__BagSessionSummary__Sequence * input,
  agt_interfaces__msg__BagSessionSummary__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__BagSessionSummary);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__BagSessionSummary * data =
      (agt_interfaces__msg__BagSessionSummary *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__BagSessionSummary__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__BagSessionSummary__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__BagSessionSummary__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
