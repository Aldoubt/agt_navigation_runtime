// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/SemanticWaypointArray.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/semantic_waypoint_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `schema_version`
// Member `map_id`
// Member `base_map_sha256`
#include "rosidl_runtime_c/string_functions.h"
// Member `waypoints`
#include "agt_interfaces/msg/detail/semantic_waypoint__functions.h"

bool
agt_interfaces__msg__SemanticWaypointArray__init(agt_interfaces__msg__SemanticWaypointArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
    return false;
  }
  // schema_version
  if (!rosidl_runtime_c__String__init(&msg->schema_version)) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
    return false;
  }
  // base_map_sha256
  if (!rosidl_runtime_c__String__init(&msg->base_map_sha256)) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
    return false;
  }
  // waypoints
  if (!agt_interfaces__msg__SemanticWaypoint__Sequence__init(&msg->waypoints, 0)) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__SemanticWaypointArray__fini(agt_interfaces__msg__SemanticWaypointArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // schema_version
  rosidl_runtime_c__String__fini(&msg->schema_version);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // base_map_sha256
  rosidl_runtime_c__String__fini(&msg->base_map_sha256);
  // waypoints
  agt_interfaces__msg__SemanticWaypoint__Sequence__fini(&msg->waypoints);
}

bool
agt_interfaces__msg__SemanticWaypointArray__are_equal(const agt_interfaces__msg__SemanticWaypointArray * lhs, const agt_interfaces__msg__SemanticWaypointArray * rhs)
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
  // schema_version
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->schema_version), &(rhs->schema_version)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // base_map_sha256
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->base_map_sha256), &(rhs->base_map_sha256)))
  {
    return false;
  }
  // waypoints
  if (!agt_interfaces__msg__SemanticWaypoint__Sequence__are_equal(
      &(lhs->waypoints), &(rhs->waypoints)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__msg__SemanticWaypointArray__copy(
  const agt_interfaces__msg__SemanticWaypointArray * input,
  agt_interfaces__msg__SemanticWaypointArray * output)
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
  // schema_version
  if (!rosidl_runtime_c__String__copy(
      &(input->schema_version), &(output->schema_version)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // base_map_sha256
  if (!rosidl_runtime_c__String__copy(
      &(input->base_map_sha256), &(output->base_map_sha256)))
  {
    return false;
  }
  // waypoints
  if (!agt_interfaces__msg__SemanticWaypoint__Sequence__copy(
      &(input->waypoints), &(output->waypoints)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__SemanticWaypointArray *
agt_interfaces__msg__SemanticWaypointArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypointArray * msg = (agt_interfaces__msg__SemanticWaypointArray *)allocator.allocate(sizeof(agt_interfaces__msg__SemanticWaypointArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__SemanticWaypointArray));
  bool success = agt_interfaces__msg__SemanticWaypointArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__SemanticWaypointArray__destroy(agt_interfaces__msg__SemanticWaypointArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__SemanticWaypointArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__SemanticWaypointArray__Sequence__init(agt_interfaces__msg__SemanticWaypointArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypointArray * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__SemanticWaypointArray *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__SemanticWaypointArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__SemanticWaypointArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__SemanticWaypointArray__fini(&data[i - 1]);
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
agt_interfaces__msg__SemanticWaypointArray__Sequence__fini(agt_interfaces__msg__SemanticWaypointArray__Sequence * array)
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
      agt_interfaces__msg__SemanticWaypointArray__fini(&array->data[i]);
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

agt_interfaces__msg__SemanticWaypointArray__Sequence *
agt_interfaces__msg__SemanticWaypointArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__SemanticWaypointArray__Sequence * array = (agt_interfaces__msg__SemanticWaypointArray__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__SemanticWaypointArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__SemanticWaypointArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__SemanticWaypointArray__Sequence__destroy(agt_interfaces__msg__SemanticWaypointArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__SemanticWaypointArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__SemanticWaypointArray__Sequence__are_equal(const agt_interfaces__msg__SemanticWaypointArray__Sequence * lhs, const agt_interfaces__msg__SemanticWaypointArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__SemanticWaypointArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__SemanticWaypointArray__Sequence__copy(
  const agt_interfaces__msg__SemanticWaypointArray__Sequence * input,
  agt_interfaces__msg__SemanticWaypointArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__SemanticWaypointArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__SemanticWaypointArray * data =
      (agt_interfaces__msg__SemanticWaypointArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__SemanticWaypointArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__SemanticWaypointArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__SemanticWaypointArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
