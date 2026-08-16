// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agt_interfaces:action/Relocalize.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__FUNCTIONS_H_
#define AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agt_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "agt_interfaces/action/detail/relocalize__struct.h"

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_Goal
 * )) before or use
 * agt_interfaces__action__Relocalize_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Goal__init(agt_interfaces__action__Relocalize_Goal * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Goal__fini(agt_interfaces__action__Relocalize_Goal * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Goal *
agt_interfaces__action__Relocalize_Goal__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Goal__destroy(agt_interfaces__action__Relocalize_Goal * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Goal__are_equal(const agt_interfaces__action__Relocalize_Goal * lhs, const agt_interfaces__action__Relocalize_Goal * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_Goal__copy(
  const agt_interfaces__action__Relocalize_Goal * input,
  agt_interfaces__action__Relocalize_Goal * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Goal__Sequence__init(agt_interfaces__action__Relocalize_Goal__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Goal__Sequence__fini(agt_interfaces__action__Relocalize_Goal__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Goal__Sequence *
agt_interfaces__action__Relocalize_Goal__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Goal__Sequence__destroy(agt_interfaces__action__Relocalize_Goal__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Goal__Sequence__are_equal(const agt_interfaces__action__Relocalize_Goal__Sequence * lhs, const agt_interfaces__action__Relocalize_Goal__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_Goal__Sequence__copy(
  const agt_interfaces__action__Relocalize_Goal__Sequence * input,
  agt_interfaces__action__Relocalize_Goal__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_Result
 * )) before or use
 * agt_interfaces__action__Relocalize_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Result__init(agt_interfaces__action__Relocalize_Result * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Result__fini(agt_interfaces__action__Relocalize_Result * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Result *
agt_interfaces__action__Relocalize_Result__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Result__destroy(agt_interfaces__action__Relocalize_Result * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Result__are_equal(const agt_interfaces__action__Relocalize_Result * lhs, const agt_interfaces__action__Relocalize_Result * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_Result__copy(
  const agt_interfaces__action__Relocalize_Result * input,
  agt_interfaces__action__Relocalize_Result * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Result__Sequence__init(agt_interfaces__action__Relocalize_Result__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Result__Sequence__fini(agt_interfaces__action__Relocalize_Result__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Result__Sequence *
agt_interfaces__action__Relocalize_Result__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Result__Sequence__destroy(agt_interfaces__action__Relocalize_Result__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Result__Sequence__are_equal(const agt_interfaces__action__Relocalize_Result__Sequence * lhs, const agt_interfaces__action__Relocalize_Result__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_Result__Sequence__copy(
  const agt_interfaces__action__Relocalize_Result__Sequence * input,
  agt_interfaces__action__Relocalize_Result__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_Feedback
 * )) before or use
 * agt_interfaces__action__Relocalize_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Feedback__init(agt_interfaces__action__Relocalize_Feedback * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Feedback__fini(agt_interfaces__action__Relocalize_Feedback * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Feedback *
agt_interfaces__action__Relocalize_Feedback__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Feedback__destroy(agt_interfaces__action__Relocalize_Feedback * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Feedback__are_equal(const agt_interfaces__action__Relocalize_Feedback * lhs, const agt_interfaces__action__Relocalize_Feedback * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_Feedback__copy(
  const agt_interfaces__action__Relocalize_Feedback * input,
  agt_interfaces__action__Relocalize_Feedback * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Feedback__Sequence__init(agt_interfaces__action__Relocalize_Feedback__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Feedback__Sequence__fini(agt_interfaces__action__Relocalize_Feedback__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_Feedback__Sequence *
agt_interfaces__action__Relocalize_Feedback__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_Feedback__Sequence__destroy(agt_interfaces__action__Relocalize_Feedback__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_Feedback__Sequence__are_equal(const agt_interfaces__action__Relocalize_Feedback__Sequence * lhs, const agt_interfaces__action__Relocalize_Feedback__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_Feedback__Sequence__copy(
  const agt_interfaces__action__Relocalize_Feedback__Sequence * input,
  agt_interfaces__action__Relocalize_Feedback__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_SendGoal_Request
 * )) before or use
 * agt_interfaces__action__Relocalize_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Request__init(agt_interfaces__action__Relocalize_SendGoal_Request * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Request__fini(agt_interfaces__action__Relocalize_SendGoal_Request * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_SendGoal_Request *
agt_interfaces__action__Relocalize_SendGoal_Request__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Request__destroy(agt_interfaces__action__Relocalize_SendGoal_Request * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Request__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Request * lhs, const agt_interfaces__action__Relocalize_SendGoal_Request * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_SendGoal_Request__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Request * input,
  agt_interfaces__action__Relocalize_SendGoal_Request * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence *
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__destroy(agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * lhs, const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * input,
  agt_interfaces__action__Relocalize_SendGoal_Request__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_SendGoal_Response
 * )) before or use
 * agt_interfaces__action__Relocalize_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Response__init(agt_interfaces__action__Relocalize_SendGoal_Response * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Response__fini(agt_interfaces__action__Relocalize_SendGoal_Response * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_SendGoal_Response *
agt_interfaces__action__Relocalize_SendGoal_Response__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Response__destroy(agt_interfaces__action__Relocalize_SendGoal_Response * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Response__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Response * lhs, const agt_interfaces__action__Relocalize_SendGoal_Response * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_SendGoal_Response__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Response * input,
  agt_interfaces__action__Relocalize_SendGoal_Response * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence *
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__destroy(agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__are_equal(const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * lhs, const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__copy(
  const agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * input,
  agt_interfaces__action__Relocalize_SendGoal_Response__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_GetResult_Request
 * )) before or use
 * agt_interfaces__action__Relocalize_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Request__init(agt_interfaces__action__Relocalize_GetResult_Request * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Request__fini(agt_interfaces__action__Relocalize_GetResult_Request * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_GetResult_Request *
agt_interfaces__action__Relocalize_GetResult_Request__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Request__destroy(agt_interfaces__action__Relocalize_GetResult_Request * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Request__are_equal(const agt_interfaces__action__Relocalize_GetResult_Request * lhs, const agt_interfaces__action__Relocalize_GetResult_Request * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_GetResult_Request__copy(
  const agt_interfaces__action__Relocalize_GetResult_Request * input,
  agt_interfaces__action__Relocalize_GetResult_Request * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_GetResult_Request__Sequence *
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__destroy(agt_interfaces__action__Relocalize_GetResult_Request__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__are_equal(const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * lhs, const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_GetResult_Request__Sequence__copy(
  const agt_interfaces__action__Relocalize_GetResult_Request__Sequence * input,
  agt_interfaces__action__Relocalize_GetResult_Request__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_GetResult_Response
 * )) before or use
 * agt_interfaces__action__Relocalize_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Response__init(agt_interfaces__action__Relocalize_GetResult_Response * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Response__fini(agt_interfaces__action__Relocalize_GetResult_Response * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_GetResult_Response *
agt_interfaces__action__Relocalize_GetResult_Response__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Response__destroy(agt_interfaces__action__Relocalize_GetResult_Response * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Response__are_equal(const agt_interfaces__action__Relocalize_GetResult_Response * lhs, const agt_interfaces__action__Relocalize_GetResult_Response * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_GetResult_Response__copy(
  const agt_interfaces__action__Relocalize_GetResult_Response * input,
  agt_interfaces__action__Relocalize_GetResult_Response * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_GetResult_Response__Sequence *
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__destroy(agt_interfaces__action__Relocalize_GetResult_Response__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__are_equal(const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * lhs, const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_GetResult_Response__Sequence__copy(
  const agt_interfaces__action__Relocalize_GetResult_Response__Sequence * input,
  agt_interfaces__action__Relocalize_GetResult_Response__Sequence * output);

/// Initialize action/Relocalize message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__action__Relocalize_FeedbackMessage
 * )) before or use
 * agt_interfaces__action__Relocalize_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_FeedbackMessage__init(agt_interfaces__action__Relocalize_FeedbackMessage * msg);

/// Finalize action/Relocalize message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_FeedbackMessage__fini(agt_interfaces__action__Relocalize_FeedbackMessage * msg);

/// Create action/Relocalize message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_FeedbackMessage *
agt_interfaces__action__Relocalize_FeedbackMessage__create();

/// Destroy action/Relocalize message.
/**
 * It calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_FeedbackMessage__destroy(agt_interfaces__action__Relocalize_FeedbackMessage * msg);

/// Check for action/Relocalize message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_FeedbackMessage__are_equal(const agt_interfaces__action__Relocalize_FeedbackMessage * lhs, const agt_interfaces__action__Relocalize_FeedbackMessage * rhs);

/// Copy a action/Relocalize message.
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
agt_interfaces__action__Relocalize_FeedbackMessage__copy(
  const agt_interfaces__action__Relocalize_FeedbackMessage * input,
  agt_interfaces__action__Relocalize_FeedbackMessage * output);

/// Initialize array of action/Relocalize messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array);

/// Create array of action/Relocalize messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence *
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/Relocalize messages.
/**
 * It calls
 * agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__destroy(agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * array);

/// Check for action/Relocalize message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__are_equal(const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * lhs, const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/Relocalize messages.
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
agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__copy(
  const agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * input,
  agt_interfaces__action__Relocalize_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__ACTION__DETAIL__RELOCALIZE__FUNCTIONS_H_
