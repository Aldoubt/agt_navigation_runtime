// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:srv/ListBagSessions.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/srv/detail/list_bag_sessions__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `experiment_id`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ListBagSessions_Request__init(agt_interfaces__srv__ListBagSessions_Request * msg)
{
  if (!msg) {
    return false;
  }
  // state
  // experiment_id
  if (!rosidl_runtime_c__String__init(&msg->experiment_id)) {
    agt_interfaces__srv__ListBagSessions_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ListBagSessions_Request__fini(agt_interfaces__srv__ListBagSessions_Request * msg)
{
  if (!msg) {
    return;
  }
  // state
  // experiment_id
  rosidl_runtime_c__String__fini(&msg->experiment_id);
}

bool
agt_interfaces__srv__ListBagSessions_Request__are_equal(const agt_interfaces__srv__ListBagSessions_Request * lhs, const agt_interfaces__srv__ListBagSessions_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // experiment_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->experiment_id), &(rhs->experiment_id)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ListBagSessions_Request__copy(
  const agt_interfaces__srv__ListBagSessions_Request * input,
  agt_interfaces__srv__ListBagSessions_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  output->state = input->state;
  // experiment_id
  if (!rosidl_runtime_c__String__copy(
      &(input->experiment_id), &(output->experiment_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ListBagSessions_Request *
agt_interfaces__srv__ListBagSessions_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Request * msg = (agt_interfaces__srv__ListBagSessions_Request *)allocator.allocate(sizeof(agt_interfaces__srv__ListBagSessions_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ListBagSessions_Request));
  bool success = agt_interfaces__srv__ListBagSessions_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ListBagSessions_Request__destroy(agt_interfaces__srv__ListBagSessions_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ListBagSessions_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ListBagSessions_Request__Sequence__init(agt_interfaces__srv__ListBagSessions_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ListBagSessions_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ListBagSessions_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ListBagSessions_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ListBagSessions_Request__fini(&data[i - 1]);
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
agt_interfaces__srv__ListBagSessions_Request__Sequence__fini(agt_interfaces__srv__ListBagSessions_Request__Sequence * array)
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
      agt_interfaces__srv__ListBagSessions_Request__fini(&array->data[i]);
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

agt_interfaces__srv__ListBagSessions_Request__Sequence *
agt_interfaces__srv__ListBagSessions_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Request__Sequence * array = (agt_interfaces__srv__ListBagSessions_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ListBagSessions_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ListBagSessions_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ListBagSessions_Request__Sequence__destroy(agt_interfaces__srv__ListBagSessions_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ListBagSessions_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ListBagSessions_Request__Sequence__are_equal(const agt_interfaces__srv__ListBagSessions_Request__Sequence * lhs, const agt_interfaces__srv__ListBagSessions_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ListBagSessions_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ListBagSessions_Request__Sequence__copy(
  const agt_interfaces__srv__ListBagSessions_Request__Sequence * input,
  agt_interfaces__srv__ListBagSessions_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ListBagSessions_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ListBagSessions_Request * data =
      (agt_interfaces__srv__ListBagSessions_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ListBagSessions_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ListBagSessions_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ListBagSessions_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `sessions`
#include "agt_interfaces/msg/detail/bag_session_summary__functions.h"
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__srv__ListBagSessions_Response__init(agt_interfaces__srv__ListBagSessions_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // sessions
  if (!agt_interfaces__msg__BagSessionSummary__Sequence__init(&msg->sessions, 0)) {
    agt_interfaces__srv__ListBagSessions_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__srv__ListBagSessions_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__srv__ListBagSessions_Response__fini(agt_interfaces__srv__ListBagSessions_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // sessions
  agt_interfaces__msg__BagSessionSummary__Sequence__fini(&msg->sessions);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__srv__ListBagSessions_Response__are_equal(const agt_interfaces__srv__ListBagSessions_Response * lhs, const agt_interfaces__srv__ListBagSessions_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // sessions
  if (!agt_interfaces__msg__BagSessionSummary__Sequence__are_equal(
      &(lhs->sessions), &(rhs->sessions)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__srv__ListBagSessions_Response__copy(
  const agt_interfaces__srv__ListBagSessions_Response * input,
  agt_interfaces__srv__ListBagSessions_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // sessions
  if (!agt_interfaces__msg__BagSessionSummary__Sequence__copy(
      &(input->sessions), &(output->sessions)))
  {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__srv__ListBagSessions_Response *
agt_interfaces__srv__ListBagSessions_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Response * msg = (agt_interfaces__srv__ListBagSessions_Response *)allocator.allocate(sizeof(agt_interfaces__srv__ListBagSessions_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__srv__ListBagSessions_Response));
  bool success = agt_interfaces__srv__ListBagSessions_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__srv__ListBagSessions_Response__destroy(agt_interfaces__srv__ListBagSessions_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__srv__ListBagSessions_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__srv__ListBagSessions_Response__Sequence__init(agt_interfaces__srv__ListBagSessions_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__srv__ListBagSessions_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__srv__ListBagSessions_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__srv__ListBagSessions_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__srv__ListBagSessions_Response__fini(&data[i - 1]);
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
agt_interfaces__srv__ListBagSessions_Response__Sequence__fini(agt_interfaces__srv__ListBagSessions_Response__Sequence * array)
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
      agt_interfaces__srv__ListBagSessions_Response__fini(&array->data[i]);
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

agt_interfaces__srv__ListBagSessions_Response__Sequence *
agt_interfaces__srv__ListBagSessions_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__srv__ListBagSessions_Response__Sequence * array = (agt_interfaces__srv__ListBagSessions_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__srv__ListBagSessions_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__srv__ListBagSessions_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__srv__ListBagSessions_Response__Sequence__destroy(agt_interfaces__srv__ListBagSessions_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__srv__ListBagSessions_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__srv__ListBagSessions_Response__Sequence__are_equal(const agt_interfaces__srv__ListBagSessions_Response__Sequence * lhs, const agt_interfaces__srv__ListBagSessions_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__srv__ListBagSessions_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__srv__ListBagSessions_Response__Sequence__copy(
  const agt_interfaces__srv__ListBagSessions_Response__Sequence * input,
  agt_interfaces__srv__ListBagSessions_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__srv__ListBagSessions_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__srv__ListBagSessions_Response * data =
      (agt_interfaces__srv__ListBagSessions_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__srv__ListBagSessions_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__srv__ListBagSessions_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__srv__ListBagSessions_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
