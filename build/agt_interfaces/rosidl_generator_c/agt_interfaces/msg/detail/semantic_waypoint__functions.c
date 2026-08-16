// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/semantic_waypoint__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `id`
// Member `name`
// Member `role`
// Member `tags`
#include "rosidl_runtime_c/string_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
agt_interfaces__msg__SemanticWaypoint__init(agt_interfaces__msg__SemanticWaypoint * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
    return false;
  }
  // role
  if (!rosidl_runtime_c__String__init(&msg->role)) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
    return false;
  }
  // position_tolerance
  // yaw_tolerance
  // preferred_speed
  // tags
  if (!rosidl_runtime_c__String__Sequence__init(&msg->tags, 0)) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
    return false;
  }
  // enabled
  return true;
}

void
agt_interfaces__msg__SemanticWaypoint__fini(agt_interfaces__msg__SemanticWaypoint * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // role
  rosidl_runtime_c__String__fini(&msg->role);
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // position_tolerance
  // yaw_tolerance
  // preferred_speed
  // tags
  rosidl_runtime_c__String__Sequence__fini(&msg->tags);
  // enabled
}

bool
agt_interfaces__msg__SemanticWaypoint__are_equal(const agt_interfaces__msg__SemanticWaypoint * lhs, const agt_interfaces__msg__SemanticWaypoint * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->id), &(rhs->id)))
  {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // role
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->role), &(rhs->role)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // position_tolerance
  if (lhs->position_tolerance != rhs->position_tolerance) {
    return false;
  }
  // yaw_tolerance
  if (lhs->yaw_tolerance != rhs->yaw_tolerance) {
    return false;
  }
  // preferred_speed
  if (lhs->preferred_speed != rhs->preferred_speed) {
    return false;
  }
  // tags
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->tags), &(rhs->tags)))
  {
    return false;
  }
  // enabled
  if (lhs->enabled != rhs->enabled) {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__SemanticWaypoint__copy(
  const agt_interfaces__msg__SemanticWaypoint * input,
  agt_interfaces__msg__SemanticWaypoint * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__copy(
      &(input->id), &(output->id)))
  {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // role
  if (!rosidl_runtime_c__String__copy(
      &(input->role), &(output->role)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // position_tolerance
  output->position_tolerance = input->position_tolerance;
  // yaw_tolerance
  output->yaw_tolerance = input->yaw_tolerance;
  // preferred_speed
  output->preferred_speed = input->preferred_speed;
  // tags
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->tags), &(output->tags)))
  {
    return false;
  }
  // enabled
  output->enabled = input->enabled;
  return true;
}

agt_interfaces__msg__SemanticWaypoint *
agt_interfaces__msg__SemanticWaypoint__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypoint * msg = (agt_interfaces__msg__SemanticWaypoint *)allocator.allocate(sizeof(agt_interfaces__msg__SemanticWaypoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__SemanticWaypoint));
  bool success = agt_interfaces__msg__SemanticWaypoint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__SemanticWaypoint__destroy(agt_interfaces__msg__SemanticWaypoint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__SemanticWaypoint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__SemanticWaypoint__Sequence__init(agt_interfaces__msg__SemanticWaypoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypoint * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__SemanticWaypoint *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__SemanticWaypoint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__SemanticWaypoint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__SemanticWaypoint__fini(&data[i - 1]);
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
agt_interfaces__msg__SemanticWaypoint__Sequence__fini(agt_interfaces__msg__SemanticWaypoint__Sequence * array)
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
      agt_interfaces__msg__SemanticWaypoint__fini(&array->data[i]);
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

agt_interfaces__msg__SemanticWaypoint__Sequence *
agt_interfaces__msg__SemanticWaypoint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypoint__Sequence * array = (agt_interfaces__msg__SemanticWaypoint__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__SemanticWaypoint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__SemanticWaypoint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__SemanticWaypoint__Sequence__destroy(agt_interfaces__msg__SemanticWaypoint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__SemanticWaypoint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__SemanticWaypoint__Sequence__are_equal(const agt_interfaces__msg__SemanticWaypoint__Sequence * lhs, const agt_interfaces__msg__SemanticWaypoint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__SemanticWaypoint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__SemanticWaypoint__Sequence__copy(
  const agt_interfaces__msg__SemanticWaypoint__Sequence * input,
  agt_interfaces__msg__SemanticWaypoint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__SemanticWaypoint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__SemanticWaypoint * data =
      (agt_interfaces__msg__SemanticWaypoint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__SemanticWaypoint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__SemanticWaypoint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__SemanticWaypoint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
