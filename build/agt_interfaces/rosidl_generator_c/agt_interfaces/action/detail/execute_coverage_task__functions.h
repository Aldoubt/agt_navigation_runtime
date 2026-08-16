// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agt_interfaces:action/ExecuteCoverageTask.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__FUNCTIONS_H_
#define AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agt_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "agt_interfaces/action/detail/execute_coverage_task__struct.h"

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_Goal
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__init(agt_interfaces__action__ExecuteCoverageTask_Goal * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Goal__fini(agt_interfaces__action__ExecuteCoverageTask_Goal * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Goal *
agt_interfaces__action__ExecuteCoverageTask_Goal__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Goal__destroy(agt_interfaces__action__ExecuteCoverageTask_Goal * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Goal * lhs, const agt_interfaces__action__ExecuteCoverageTask_Goal * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Goal * input,
  agt_interfaces__action__ExecuteCoverageTask_Goal * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence *
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_Result
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__init(agt_interfaces__action__ExecuteCoverageTask_Result * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Result__fini(agt_interfaces__action__ExecuteCoverageTask_Result * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Result *
agt_interfaces__action__ExecuteCoverageTask_Result__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Result__destroy(agt_interfaces__action__ExecuteCoverageTask_Result * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Result * lhs, const agt_interfaces__action__ExecuteCoverageTask_Result * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Result * input,
  agt_interfaces__action__ExecuteCoverageTask_Result * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence *
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_Result__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_Feedback
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__init(agt_interfaces__action__ExecuteCoverageTask_Feedback * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Feedback__fini(agt_interfaces__action__ExecuteCoverageTask_Feedback * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Feedback *
agt_interfaces__action__ExecuteCoverageTask_Feedback__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Feedback__destroy(agt_interfaces__action__ExecuteCoverageTask_Feedback * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Feedback * lhs, const agt_interfaces__action__ExecuteCoverageTask_Feedback * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Feedback * input,
  agt_interfaces__action__ExecuteCoverageTask_Feedback * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence *
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__fini(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request *
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__destroy(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__are_equal(const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * lhs, const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__copy(
  const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * input,
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence *
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__fini(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response *
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__destroy(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__are_equal(const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * lhs, const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__copy(
  const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * input,
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence *
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__fini(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request *
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__destroy(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__are_equal(const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * lhs, const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__copy(
  const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * input,
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Request * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence *
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__fini(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response *
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__destroy(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__are_equal(const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * lhs, const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__copy(
  const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * input,
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Response * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence *
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence * output);

/// Initialize action/ExecuteCoverageTask message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage
 * )) before or use
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * msg);

/// Finalize action/ExecuteCoverageTask message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__fini(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * msg);

/// Create action/ExecuteCoverageTask message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage *
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__create();

/// Destroy action/ExecuteCoverageTask message.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__destroy(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * msg);

/// Check for action/ExecuteCoverageTask message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__are_equal(const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * lhs, const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * rhs);

/// Copy a action/ExecuteCoverageTask message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__copy(
  const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * input,
  agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage * output);

/// Initialize array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__init(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__fini(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * array);

/// Create array of action/ExecuteCoverageTask messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence *
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/ExecuteCoverageTask messages.
/**
 * It calls
 * agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__destroy(agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * array);

/// Check for action/ExecuteCoverageTask message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__are_equal(const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * lhs, const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/ExecuteCoverageTask messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__copy(
  const agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * input,
  agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__EXECUTE_COVERAGE_TASK__FUNCTIONS_H_
