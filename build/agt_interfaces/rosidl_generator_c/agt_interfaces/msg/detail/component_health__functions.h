// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agt_interfaces:msg/ComponentHealth.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__FUNCTIONS_H_
#define AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agt_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "agt_interfaces/msg/detail/component_health__struct.h"

/// Initialize msg/ComponentHealth message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__msg__ComponentHealth
 * )) before or use
 * agt_interfaces__msg__ComponentHealth__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__ComponentHealth__init(agt_interfaces__msg__ComponentHealth * msg);

/// Finalize msg/ComponentHealth message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__ComponentHealth__fini(agt_interfaces__msg__ComponentHealth * msg);

/// Create msg/ComponentHealth message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__msg__ComponentHealth__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__msg__ComponentHealth *
agt_interfaces__msg__ComponentHealth__create();

/// Destroy msg/ComponentHealth message.
/**
 * It calls
 * agt_interfaces__msg__ComponentHealth__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__ComponentHealth__destroy(agt_interfaces__msg__ComponentHealth * msg);

/// Check for msg/ComponentHealth message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__ComponentHealth__are_equal(const agt_interfaces__msg__ComponentHealth * lhs, const agt_interfaces__msg__ComponentHealth * rhs);

/// Copy a msg/ComponentHealth message.
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
agt_interfaces__msg__ComponentHealth__copy(
  const agt_interfaces__msg__ComponentHealth * input,
  agt_interfaces__msg__ComponentHealth * output);

/// Initialize array of msg/ComponentHealth messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__msg__ComponentHealth__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__ComponentHealth__Sequence__init(agt_interfaces__msg__ComponentHealth__Sequence * array, size_t size);

/// Finalize array of msg/ComponentHealth messages.
/**
 * It calls
 * agt_interfaces__msg__ComponentHealth__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__ComponentHealth__Sequence__fini(agt_interfaces__msg__ComponentHealth__Sequence * array);

/// Create array of msg/ComponentHealth messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__msg__ComponentHealth__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__msg__ComponentHealth__Sequence *
agt_interfaces__msg__ComponentHealth__Sequence__create(size_t size);

/// Destroy array of msg/ComponentHealth messages.
/**
 * It calls
 * agt_interfaces__msg__ComponentHealth__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__ComponentHealth__Sequence__destroy(agt_interfaces__msg__ComponentHealth__Sequence * array);

/// Check for msg/ComponentHealth message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__ComponentHealth__Sequence__are_equal(const agt_interfaces__msg__ComponentHealth__Sequence * lhs, const agt_interfaces__msg__ComponentHealth__Sequence * rhs);

/// Copy an array of msg/ComponentHealth messages.
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
agt_interfaces__msg__ComponentHealth__Sequence__copy(
  const agt_interfaces__msg__ComponentHealth__Sequence * input,
  agt_interfaces__msg__ComponentHealth__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__COMPONENT_HEALTH__FUNCTIONS_H_
