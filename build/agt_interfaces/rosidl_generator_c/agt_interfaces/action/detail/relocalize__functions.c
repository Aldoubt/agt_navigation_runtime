// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/action/detail/relocalize__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `initial_pose`
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__functions.h"

bool
agt_interfaces__action__Relocalize_Goal__init(agt_interfaces__action__Relocalize_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  // use_initial_pose
  // initial_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->initial_pose)) {
    agt_interfaces__action__Relocalize_Goal__fini(msg);
    return false;
  }
  // use_last_valid_pose
  // use_configured_candidates
  // use_external_coarse_pose
  // max_candidates
  // publish_debug
  // timeout_s
  return true;
}

void
agt_interfaces__action__Relocalize_Goal__fini(agt_interfaces__action__Relocalize_Goal * msg)
{
  if (!msg) {
    return;
  }
  // mode
  // use_initial_pose
  // initial_pose
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->initial_pose);
  // use_last_valid_pose
  // use_configured_candidates
  // use_external_coarse_pose
  // max_candidates
  // publish_debug
  // timeout_s
}

bool
agt_interfaces__action__Relocalize_Goal__are_equal(const agt_interfaces__action__Relocalize_Goal * lhs, const agt_interfaces__action__Relocalize_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // use_initial_pose
  if (lhs->use_initial_pose != rhs->use_initial_pose) {
    return false;
  }
  // initial_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__are_equal(
      &(lhs->initial_pose), &(rhs->initial_pose)))
  {
    return false;
  }
  // use_last_valid_pose
  if (lhs->use_last_valid_pose != rhs->use_last_valid_pose) {
    return false;
  }
  // use_configured_candidates
  if (lhs->use_configured_candidates != rhs->use_configured_candidates) {
    return false;
  }
  // use_external_coarse_pose
  if (lhs->use_external_coarse_pose != rhs->use_external_coarse_pose) {
    return false;
  }
  // max_candidates
  if (lhs->max_candidates != rhs->max_candidates) {
    return false;
  }
  // publish_debug
  if (lhs->publish_debug != rhs->publish_debug) {
    return false;
  }
  // timeout_s
  if (lhs->timeout_s != rhs->timeout_s) {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Goal__copy(
  const agt_interfaces__action__Relocalize_Goal * input,
  agt_interfaces__action__Relocalize_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  output->mode = input->mode;
  // use_initial_pose
  output->use_initial_pose = input->use_initial_pose;
  // initial_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__copy(
      &(input->initial_pose), &(output->initial_pose)))
  {
    return false;
  }
  // use_last_valid_pose
  output->use_last_valid_pose = input->use_last_valid_pose;
  // use_configured_candidates
  output->use_configured_candidates = input->use_configured_candidates;
  // use_external_coarse_pose
  output->use_external_coarse_pose = input->use_external_coarse_pose;
  // max_candidates
  output->max_candidates = input->max_candidates;
  // publish_debug
  output->publish_debug = input->publish_debug;
  // timeout_s
  output->timeout_s = input->timeout_s;
  return true;
}

agt_interfaces__action__Relocalize_Goal *
agt_interfaces__action__Relocalize_Goal__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Goal * msg = (agt_interfaces__action__Relocalize_Goal *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_Goal));
  bool success = agt_interfaces__action__Relocalize_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_Goal__destroy(agt_interfaces__action__Relocalize_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_Goal__Sequence__init(agt_interfaces__action__Relocalize_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Goal * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_Goal *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_Goal__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_Goal__Sequence__fini(agt_interfaces__action__Relocalize_Goal__Sequence * array)
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
      agt_interfaces__action__Relocalize_Goal__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_Goal__Sequence *
agt_interfaces__action__Relocalize_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Goal__Sequence * array = (agt_interfaces__action__Relocalize_Goal__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_Goal__Sequence__destroy(agt_interfaces__action__Relocalize_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_Goal__Sequence__are_equal(const agt_interfaces__action__Relocalize_Goal__Sequence * lhs, const agt_interfaces__action__Relocalize_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Goal__Sequence__copy(
  const agt_interfaces__action__Relocalize_Goal__Sequence * input,
  agt_interfaces__action__Relocalize_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_Goal * data =
      (agt_interfaces__action__Relocalize_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `final_pose`
// already included above
// #include "geometry_msgs/msg/detail/pose_with_covariance_stamped__functions.h"
// Member `final_status`
#include "agt_interfaces/msg/detail/localization_status__functions.h"
// Member `failure_reason`
#include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__Relocalize_Result__init(agt_interfaces__action__Relocalize_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // final_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->final_pose)) {
    agt_interfaces__action__Relocalize_Result__fini(msg);
    return false;
  }
  // final_status
  if (!agt_interfaces__msg__LocalizationStatus__init(&msg->final_status)) {
    agt_interfaces__action__Relocalize_Result__fini(msg);
    return false;
  }
  // failure_reason
  if (!rosidl_runtime_c__String__init(&msg->failure_reason)) {
    agt_interfaces__action__Relocalize_Result__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_Result__fini(agt_interfaces__action__Relocalize_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // final_pose
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->final_pose);
  // final_status
  agt_interfaces__msg__LocalizationStatus__fini(&msg->final_status);
  // failure_reason
  rosidl_runtime_c__String__fini(&msg->failure_reason);
}

bool
agt_interfaces__action__Relocalize_Result__are_equal(const agt_interfaces__action__Relocalize_Result * lhs, const agt_interfaces__action__Relocalize_Result * rhs)
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
  // final_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__are_equal(
      &(lhs->final_pose), &(rhs->final_pose)))
  {
    return false;
  }
  // final_status
  if (!agt_interfaces__msg__LocalizationStatus__are_equal(
      &(lhs->final_status), &(rhs->final_status)))
  {
    return false;
  }
  // failure_reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->failure_reason), &(rhs->failure_reason)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Result__copy(
  const agt_interfaces__action__Relocalize_Result * input,
  agt_interfaces__action__Relocalize_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // final_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__copy(
      &(input->final_pose), &(output->final_pose)))
  {
    return false;
  }
  // final_status
  if (!agt_interfaces__msg__LocalizationStatus__copy(
      &(input->final_status), &(output->final_status)))
  {
    return false;
  }
  // failure_reason
  if (!rosidl_runtime_c__String__copy(
      &(input->failure_reason), &(output->failure_reason)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_Result *
agt_interfaces__action__Relocalize_Result__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Result * msg = (agt_interfaces__action__Relocalize_Result *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_Result));
  bool success = agt_interfaces__action__Relocalize_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_Result__destroy(agt_interfaces__action__Relocalize_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_Result__Sequence__init(agt_interfaces__action__Relocalize_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Result * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_Result *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_Result__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_Result__Sequence__fini(agt_interfaces__action__Relocalize_Result__Sequence * array)
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
      agt_interfaces__action__Relocalize_Result__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_Result__Sequence *
agt_interfaces__action__Relocalize_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Result__Sequence * array = (agt_interfaces__action__Relocalize_Result__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_Result__Sequence__destroy(agt_interfaces__action__Relocalize_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_Result__Sequence__are_equal(const agt_interfaces__action__Relocalize_Result__Sequence * lhs, const agt_interfaces__action__Relocalize_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Result__Sequence__copy(
  const agt_interfaces__action__Relocalize_Result__Sequence * input,
  agt_interfaces__action__Relocalize_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_Result * data =
      (agt_interfaces__action__Relocalize_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `best_candidate_source`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
agt_interfaces__action__Relocalize_Feedback__init(agt_interfaces__action__Relocalize_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // state
  // total_candidates
  // tested_candidates
  // best_fitness_score
  // best_candidate_source
  if (!rosidl_runtime_c__String__init(&msg->best_candidate_source)) {
    agt_interfaces__action__Relocalize_Feedback__fini(msg);
    return false;
  }
  // elapsed_s
  return true;
}

void
agt_interfaces__action__Relocalize_Feedback__fini(agt_interfaces__action__Relocalize_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // state
  // total_candidates
  // tested_candidates
  // best_fitness_score
  // best_candidate_source
  rosidl_runtime_c__String__fini(&msg->best_candidate_source);
  // elapsed_s
}

bool
agt_interfaces__action__Relocalize_Feedback__are_equal(const agt_interfaces__action__Relocalize_Feedback * lhs, const agt_interfaces__action__Relocalize_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // total_candidates
  if (lhs->total_candidates != rhs->total_candidates) {
    return false;
  }
  // tested_candidates
  if (lhs->tested_candidates != rhs->tested_candidates) {
    return false;
  }
  // best_fitness_score
  if (lhs->best_fitness_score != rhs->best_fitness_score) {
    return false;
  }
  // best_candidate_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->best_candidate_source), &(rhs->best_candidate_source)))
  {
    return false;
  }
  // elapsed_s
  if (lhs->elapsed_s != rhs->elapsed_s) {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Feedback__copy(
  const agt_interfaces__action__Relocalize_Feedback * input,
  agt_interfaces__action__Relocalize_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  output->state = input->state;
  // total_candidates
  output->total_candidates = input->total_candidates;
  // tested_candidates
  output->tested_candidates = input->tested_candidates;
  // best_fitness_score
  output->best_fitness_score = input->best_fitness_score;
  // best_candidate_source
  if (!rosidl_runtime_c__String__copy(
      &(input->best_candidate_source), &(output->best_candidate_source)))
  {
    return false;
  }
  // elapsed_s
  output->elapsed_s = input->elapsed_s;
  return true;
}

agt_interfaces__action__Relocalize_Feedback *
agt_interfaces__action__Relocalize_Feedback__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Feedback * msg = (agt_interfaces__action__Relocalize_Feedback *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_Feedback));
  bool success = agt_interfaces__action__Relocalize_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_Feedback__destroy(agt_interfaces__action__Relocalize_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_Feedback__Sequence__init(agt_interfaces__action__Relocalize_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Feedback * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_Feedback *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_Feedback__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_Feedback__Sequence__fini(agt_interfaces__action__Relocalize_Feedback__Sequence * array)
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
      agt_interfaces__action__Relocalize_Feedback__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_Feedback__Sequence *
agt_interfaces__action__Relocalize_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_Feedback__Sequence * array = (agt_interfaces__action__Relocalize_Feedback__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_Feedback__Sequence__destroy(agt_interfaces__action__Relocalize_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_Feedback__Sequence__are_equal(const agt_interfaces__action__Relocalize_Feedback__Sequence * lhs, const agt_interfaces__action__Relocalize_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_Feedback__Sequence__copy(
  const agt_interfaces__action__Relocalize_Feedback__Sequence * input,
  agt_interfaces__action__Relocalize_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_Feedback * data =
      (agt_interfaces__action__Relocalize_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "agt_interfaces/action/detail/relocalize__functions.h"

bool
agt_interfaces__action__Relocalize_SendGoal_Request__init(agt_interfaces__action__Relocalize_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__Relocalize_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!agt_interfaces__action__Relocalize_Goal__init(&msg->goal)) {
    agt_interfaces__action__Relocalize_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_SendGoal_Request__fini(agt_interfaces__action__Relocalize_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  agt_interfaces__action__Relocalize_Goal__fini(&msg->goal);
}

bool
agt_interfaces__action__Relocalize_SendGoal_Request__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Request * lhs, const agt_interfaces__action__Relocalize_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!agt_interfaces__action__Relocalize_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_SendGoal_Request__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Request * input,
  agt_interfaces__action__Relocalize_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!agt_interfaces__action__Relocalize_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_SendGoal_Request *
agt_interfaces__action__Relocalize_SendGoal_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Request * msg = (agt_interfaces__action__Relocalize_SendGoal_Request *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_SendGoal_Request));
  bool success = agt_interfaces__action__Relocalize_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_SendGoal_Request__destroy(agt_interfaces__action__Relocalize_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_SendGoal_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_SendGoal_Request__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array)
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
      agt_interfaces__action__Relocalize_SendGoal_Request__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_SendGoal_Request__Sequence *
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array = (agt_interfaces__action__Relocalize_SendGoal_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__destroy(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * lhs, const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * input,
  agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_SendGoal_Request * data =
      (agt_interfaces__action__Relocalize_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
agt_interfaces__action__Relocalize_SendGoal_Response__init(agt_interfaces__action__Relocalize_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    agt_interfaces__action__Relocalize_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_SendGoal_Response__fini(agt_interfaces__action__Relocalize_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
agt_interfaces__action__Relocalize_SendGoal_Response__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Response * lhs, const agt_interfaces__action__Relocalize_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_SendGoal_Response__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Response * input,
  agt_interfaces__action__Relocalize_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_SendGoal_Response *
agt_interfaces__action__Relocalize_SendGoal_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Response * msg = (agt_interfaces__action__Relocalize_SendGoal_Response *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_SendGoal_Response));
  bool success = agt_interfaces__action__Relocalize_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_SendGoal_Response__destroy(agt_interfaces__action__Relocalize_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_SendGoal_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_SendGoal_Response__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array)
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
      agt_interfaces__action__Relocalize_SendGoal_Response__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_SendGoal_Response__Sequence *
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array = (agt_interfaces__action__Relocalize_SendGoal_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__destroy(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * lhs, const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * input,
  agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_SendGoal_Response * data =
      (agt_interfaces__action__Relocalize_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
agt_interfaces__action__Relocalize_GetResult_Request__init(agt_interfaces__action__Relocalize_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__Relocalize_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_GetResult_Request__fini(agt_interfaces__action__Relocalize_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
agt_interfaces__action__Relocalize_GetResult_Request__are_equal(const agt_interfaces__action__Relocalize_GetResult_Request * lhs, const agt_interfaces__action__Relocalize_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_GetResult_Request__copy(
  const agt_interfaces__action__Relocalize_GetResult_Request * input,
  agt_interfaces__action__Relocalize_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_GetResult_Request *
agt_interfaces__action__Relocalize_GetResult_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Request * msg = (agt_interfaces__action__Relocalize_GetResult_Request *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_GetResult_Request));
  bool success = agt_interfaces__action__Relocalize_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_GetResult_Request__destroy(agt_interfaces__action__Relocalize_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Request * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_GetResult_Request *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_GetResult_Request__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array)
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
      agt_interfaces__action__Relocalize_GetResult_Request__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_GetResult_Request__Sequence *
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array = (agt_interfaces__action__Relocalize_GetResult_Request__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__destroy(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__are_equal(const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * lhs, const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__copy(
  const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * input,
  agt_interfaces__action__Relocalize_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_GetResult_Request * data =
      (agt_interfaces__action__Relocalize_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "agt_interfaces/action/detail/relocalize__functions.h"

bool
agt_interfaces__action__Relocalize_GetResult_Response__init(agt_interfaces__action__Relocalize_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!agt_interfaces__action__Relocalize_Result__init(&msg->result)) {
    agt_interfaces__action__Relocalize_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_GetResult_Response__fini(agt_interfaces__action__Relocalize_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  agt_interfaces__action__Relocalize_Result__fini(&msg->result);
}

bool
agt_interfaces__action__Relocalize_GetResult_Response__are_equal(const agt_interfaces__action__Relocalize_GetResult_Response * lhs, const agt_interfaces__action__Relocalize_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!agt_interfaces__action__Relocalize_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_GetResult_Response__copy(
  const agt_interfaces__action__Relocalize_GetResult_Response * input,
  agt_interfaces__action__Relocalize_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!agt_interfaces__action__Relocalize_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_GetResult_Response *
agt_interfaces__action__Relocalize_GetResult_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Response * msg = (agt_interfaces__action__Relocalize_GetResult_Response *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_GetResult_Response));
  bool success = agt_interfaces__action__Relocalize_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_GetResult_Response__destroy(agt_interfaces__action__Relocalize_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Response * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_GetResult_Response *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_GetResult_Response__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array)
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
      agt_interfaces__action__Relocalize_GetResult_Response__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_GetResult_Response__Sequence *
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array = (agt_interfaces__action__Relocalize_GetResult_Response__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__destroy(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__are_equal(const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * lhs, const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__copy(
  const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * input,
  agt_interfaces__action__Relocalize_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_GetResult_Response * data =
      (agt_interfaces__action__Relocalize_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "agt_interfaces/action/detail/relocalize__functions.h"

bool
agt_interfaces__action__Relocalize_FeedbackMessage__init(agt_interfaces__action__Relocalize_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    agt_interfaces__action__Relocalize_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!agt_interfaces__action__Relocalize_Feedback__init(&msg->feedback)) {
    agt_interfaces__action__Relocalize_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__action__Relocalize_FeedbackMessage__fini(agt_interfaces__action__Relocalize_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  agt_interfaces__action__Relocalize_Feedback__fini(&msg->feedback);
}

bool
agt_interfaces__action__Relocalize_FeedbackMessage__are_equal(const agt_interfaces__action__Relocalize_FeedbackMessage * lhs, const agt_interfaces__action__Relocalize_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!agt_interfaces__action__Relocalize_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_FeedbackMessage__copy(
  const agt_interfaces__action__Relocalize_FeedbackMessage * input,
  agt_interfaces__action__Relocalize_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!agt_interfaces__action__Relocalize_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

agt_interfaces__action__Relocalize_FeedbackMessage *
agt_interfaces__action__Relocalize_FeedbackMessage__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_FeedbackMessage * msg = (agt_interfaces__action__Relocalize_FeedbackMessage *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__action__Relocalize_FeedbackMessage));
  bool success = agt_interfaces__action__Relocalize_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__action__Relocalize_FeedbackMessage__destroy(agt_interfaces__action__Relocalize_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__action__Relocalize_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_FeedbackMessage * data = NULL;

  if (size) {
    data = (agt_interfaces__action__Relocalize_FeedbackMessage *)allocator.zero_allocate(size, sizeof(agt_interfaces__action__Relocalize_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__action__Relocalize_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__action__Relocalize_FeedbackMessage__fini(&data[i - 1]);
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
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array)
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
      agt_interfaces__action__Relocalize_FeedbackMessage__fini(&array->data[i]);
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

agt_interfaces__action__Relocalize_FeedbackMessage__Sequence *
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array = (agt_interfaces__action__Relocalize_FeedbackMessage__Sequence *)allocator.allocate(sizeof(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__destroy(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__are_equal(const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * lhs, const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__action__Relocalize_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__copy(
  const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * input,
  agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__action__Relocalize_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__action__Relocalize_FeedbackMessage * data =
      (agt_interfaces__action__Relocalize_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__action__Relocalize_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__action__Relocalize_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__action__Relocalize_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
