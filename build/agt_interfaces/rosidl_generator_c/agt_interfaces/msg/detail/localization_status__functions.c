// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agt_interfaces:msg/LocalizationStatus.idl
// generated code does not contain a copyright notice
#include "agt_interfaces/msg/detail/localization_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `backend`
// Member `candidate_source`
// Member `candidate_id`
// Member `map_id`
// Member `map_hash`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `global_pose`
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__functions.h"

bool
agt_interfaces__msg__LocalizationStatus__init(agt_interfaces__msg__LocalizationStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // state
  // pose_valid
  // localization_accepted
  // has_converged
  // ambiguous_result
  // status_stale
  // error_code
  // backend
  if (!rosidl_runtime_c__String__init(&msg->backend)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // candidate_source
  if (!rosidl_runtime_c__String__init(&msg->candidate_source)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // candidate_id
  if (!rosidl_runtime_c__String__init(&msg->candidate_id)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // map_hash
  if (!rosidl_runtime_c__String__init(&msg->map_hash)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // correction_generation
  // global_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->global_pose)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  // fitness_score
  // overlap_ratio
  // inlier_ratio
  // ambiguity_score
  // translation_innovation
  // yaw_innovation
  // runtime_ms
  // tested_candidates
  // total_candidates
  // consecutive_successes
  // consecutive_failures
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
    return false;
  }
  return true;
}

void
agt_interfaces__msg__LocalizationStatus__fini(agt_interfaces__msg__LocalizationStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
  // pose_valid
  // localization_accepted
  // has_converged
  // ambiguous_result
  // status_stale
  // error_code
  // backend
  rosidl_runtime_c__String__fini(&msg->backend);
  // candidate_source
  rosidl_runtime_c__String__fini(&msg->candidate_source);
  // candidate_id
  rosidl_runtime_c__String__fini(&msg->candidate_id);
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // map_hash
  rosidl_runtime_c__String__fini(&msg->map_hash);
  // correction_generation
  // global_pose
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->global_pose);
  // fitness_score
  // overlap_ratio
  // inlier_ratio
  // ambiguity_score
  // translation_innovation
  // yaw_innovation
  // runtime_ms
  // tested_candidates
  // total_candidates
  // consecutive_successes
  // consecutive_failures
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
agt_interfaces__msg__LocalizationStatus__are_equal(const agt_interfaces__msg__LocalizationStatus * lhs, const agt_interfaces__msg__LocalizationStatus * rhs)
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
  // pose_valid
  if (lhs->pose_valid != rhs->pose_valid) {
    return false;
  }
  // localization_accepted
  if (lhs->localization_accepted != rhs->localization_accepted) {
    return false;
  }
  // has_converged
  if (lhs->has_converged != rhs->has_converged) {
    return false;
  }
  // ambiguous_result
  if (lhs->ambiguous_result != rhs->ambiguous_result) {
    return false;
  }
  // status_stale
  if (lhs->status_stale != rhs->status_stale) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // backend
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->backend), &(rhs->backend)))
  {
    return false;
  }
  // candidate_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->candidate_source), &(rhs->candidate_source)))
  {
    return false;
  }
  // candidate_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->candidate_id), &(rhs->candidate_id)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // map_hash
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_hash), &(rhs->map_hash)))
  {
    return false;
  }
  // correction_generation
  if (lhs->correction_generation != rhs->correction_generation) {
    return false;
  }
  // global_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__are_equal(
      &(lhs->global_pose), &(rhs->global_pose)))
  {
    return false;
  }
  // fitness_score
  if (lhs->fitness_score != rhs->fitness_score) {
    return false;
  }
  // overlap_ratio
  if (lhs->overlap_ratio != rhs->overlap_ratio) {
    return false;
  }
  // inlier_ratio
  if (lhs->inlier_ratio != rhs->inlier_ratio) {
    return false;
  }
  // ambiguity_score
  if (lhs->ambiguity_score != rhs->ambiguity_score) {
    return false;
  }
  // translation_innovation
  if (lhs->translation_innovation != rhs->translation_innovation) {
    return false;
  }
  // yaw_innovation
  if (lhs->yaw_innovation != rhs->yaw_innovation) {
    return false;
  }
  // runtime_ms
  if (lhs->runtime_ms != rhs->runtime_ms) {
    return false;
  }
  // tested_candidates
  if (lhs->tested_candidates != rhs->tested_candidates) {
    return false;
  }
  // total_candidates
  if (lhs->total_candidates != rhs->total_candidates) {
    return false;
  }
  // consecutive_successes
  if (lhs->consecutive_successes != rhs->consecutive_successes) {
    return false;
  }
  // consecutive_failures
  if (lhs->consecutive_failures != rhs->consecutive_failures) {
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
agt_interfaces__msg__LocalizationStatus__copy(
  const agt_interfaces__msg__LocalizationStatus * input,
  agt_interfaces__msg__LocalizationStatus * output)
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
  // pose_valid
  output->pose_valid = input->pose_valid;
  // localization_accepted
  output->localization_accepted = input->localization_accepted;
  // has_converged
  output->has_converged = input->has_converged;
  // ambiguous_result
  output->ambiguous_result = input->ambiguous_result;
  // status_stale
  output->status_stale = input->status_stale;
  // error_code
  output->error_code = input->error_code;
  // backend
  if (!rosidl_runtime_c__String__copy(
      &(input->backend), &(output->backend)))
  {
    return false;
  }
  // candidate_source
  if (!rosidl_runtime_c__String__copy(
      &(input->candidate_source), &(output->candidate_source)))
  {
    return false;
  }
  // candidate_id
  if (!rosidl_runtime_c__String__copy(
      &(input->candidate_id), &(output->candidate_id)))
  {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // map_hash
  if (!rosidl_runtime_c__String__copy(
      &(input->map_hash), &(output->map_hash)))
  {
    return false;
  }
  // correction_generation
  output->correction_generation = input->correction_generation;
  // global_pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__copy(
      &(input->global_pose), &(output->global_pose)))
  {
    return false;
  }
  // fitness_score
  output->fitness_score = input->fitness_score;
  // overlap_ratio
  output->overlap_ratio = input->overlap_ratio;
  // inlier_ratio
  output->inlier_ratio = input->inlier_ratio;
  // ambiguity_score
  output->ambiguity_score = input->ambiguity_score;
  // translation_innovation
  output->translation_innovation = input->translation_innovation;
  // yaw_innovation
  output->yaw_innovation = input->yaw_innovation;
  // runtime_ms
  output->runtime_ms = input->runtime_ms;
  // tested_candidates
  output->tested_candidates = input->tested_candidates;
  // total_candidates
  output->total_candidates = input->total_candidates;
  // consecutive_successes
  output->consecutive_successes = input->consecutive_successes;
  // consecutive_failures
  output->consecutive_failures = input->consecutive_failures;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

agt_interfaces__msg__LocalizationStatus *
agt_interfaces__msg__LocalizationStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__LocalizationStatus * msg = (agt_interfaces__msg__LocalizationStatus *)allocator.allocate(sizeof(agt_interfaces__msg__LocalizationStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agt_interfaces__msg__LocalizationStatus));
  bool success = agt_interfaces__msg__LocalizationStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agt_interfaces__msg__LocalizationStatus__destroy(agt_interfaces__msg__LocalizationStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agt_interfaces__msg__LocalizationStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agt_interfaces__msg__LocalizationStatus__Sequence__init(agt_interfaces__msg__LocalizationStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__LocalizationStatus * data = NULL;

  if (size) {
    data = (agt_interfaces__msg__LocalizationStatus *)allocator.zero_allocate(size, sizeof(agt_interfaces__msg__LocalizationStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agt_interfaces__msg__LocalizationStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agt_interfaces__msg__LocalizationStatus__fini(&data[i - 1]);
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
agt_interfaces__msg__LocalizationStatus__Sequence__fini(agt_interfaces__msg__LocalizationStatus__Sequence * array)
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
      agt_interfaces__msg__LocalizationStatus__fini(&array->data[i]);
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

agt_interfaces__msg__LocalizationStatus__Sequence *
agt_interfaces__msg__LocalizationStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agt_interfaces__msg__LocalizationStatus__Sequence * array = (agt_interfaces__msg__LocalizationStatus__Sequence *)allocator.allocate(sizeof(agt_interfaces__msg__LocalizationStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agt_interfaces__msg__LocalizationStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agt_interfaces__msg__LocalizationStatus__Sequence__destroy(agt_interfaces__msg__LocalizationStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agt_interfaces__msg__LocalizationStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agt_interfaces__msg__LocalizationStatus__Sequence__are_equal(const agt_interfaces__msg__LocalizationStatus__Sequence * lhs, const agt_interfaces__msg__LocalizationStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agt_interfaces__msg__LocalizationStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agt_interfaces__msg__LocalizationStatus__Sequence__copy(
  const agt_interfaces__msg__LocalizationStatus__Sequence * input,
  agt_interfaces__msg__LocalizationStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agt_interfaces__msg__LocalizationStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agt_interfaces__msg__LocalizationStatus * data =
      (agt_interfaces__msg__LocalizationStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agt_interfaces__msg__LocalizationStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agt_interfaces__msg__LocalizationStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agt_interfaces__msg__LocalizationStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
