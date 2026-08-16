// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agt_interfaces:msg/SemanticWaypoint.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__FUNCTIONS_H_
#define AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agt_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "agt_interfaces/msg/detail/semantic_waypoint__struct.h"

/// Initialize msg/SemanticWaypoint message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agt_interfaces__msg__SemanticWaypoint
 * )) before or use
 * agt_interfaces__msg__SemanticWaypoint__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__SemanticWaypoint__init(agt_interfaces__msg__SemanticWaypoint * msg);

/// Finalize msg/SemanticWaypoint message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__SemanticWaypoint__fini(agt_interfaces__msg__SemanticWaypoint * msg);

/// Create msg/SemanticWaypoint message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agt_interfaces__msg__SemanticWaypoint__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__msg__SemanticWaypoint *
agt_interfaces__msg__SemanticWaypoint__create();

/// Destroy msg/SemanticWaypoint message.
/**
 * It calls
 * agt_interfaces__msg__SemanticWaypoint__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__SemanticWaypoint__destroy(agt_interfaces__msg__SemanticWaypoint * msg);

/// Check for msg/SemanticWaypoint message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__SemanticWaypoint__are_equal(const agt_interfaces__msg__SemanticWaypoint * lhs, const agt_interfaces__msg__SemanticWaypoint * rhs);

/// Copy a msg/SemanticWaypoint message.
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
agt_interfaces__msg__SemanticWaypoint__copy(
  const agt_interfaces__msg__SemanticWaypoint * input,
  agt_interfaces__msg__SemanticWaypoint * output);

/// Initialize array of msg/SemanticWaypoint messages.
/**
 * It allocates the memory for the number of elements and calls
 * agt_interfaces__msg__SemanticWaypoint__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__SemanticWaypoint__Sequence__init(agt_interfaces__msg__SemanticWaypoint__Sequence * array, size_t size);

/// Finalize array of msg/SemanticWaypoint messages.
/**
 * It calls
 * agt_interfaces__msg__SemanticWaypoint__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__SemanticWaypoint__Sequence__fini(agt_interfaces__msg__SemanticWaypoint__Sequence * array);

/// Create array of msg/SemanticWaypoint messages.
/**
 * It allocates the memory for the array and calls
 * agt_interfaces__msg__SemanticWaypoint__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
agt_interfaces__msg__SemanticWaypoint__Sequence *
agt_interfaces__msg__SemanticWaypoint__Sequence__create(size_t size);

/// Destroy array of msg/SemanticWaypoint messages.
/**
 * It calls
 * agt_interfaces__msg__SemanticWaypoint__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
void
agt_interfaces__msg__SemanticWaypoint__Sequence__destroy(agt_interfaces__msg__SemanticWaypoint__Sequence * array);

/// Check for msg/SemanticWaypoint message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agt_interfaces
bool
agt_interfaces__msg__SemanticWaypoint__Sequence__are_equal(const agt_interfaces__msg__SemanticWaypoint__Sequence * lhs, const agt_interfaces__msg__SemanticWaypoint__Sequence * rhs);

/// Copy an array of msg/SemanticWaypoint messages.
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
agt_interfaces__msg__SemanticWaypoint__Sequence__copy(
  const agt_interfaces__msg__SemanticWaypoint__Sequence * input,
  agt_interfaces__msg__SemanticWaypoint__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__MSG__DETAIL__SEMANTIC_WAYPOINT__FUNCTIONS_H_
