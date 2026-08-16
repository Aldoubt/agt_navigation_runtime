// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/GetNavigationSession.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'session_id'
// Member 'client_request_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetNavigationSession in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetNavigationSession_Request
{
  rosidl_runtime_c__String session_id;
  rosidl_runtime_c__String client_request_id;
} agt_interfaces__srv__GetNavigationSession_Request;

// Struct for a sequence of agt_interfaces__srv__GetNavigationSession_Request.
typedef struct agt_interfaces__srv__GetNavigationSession_Request__Sequence
{
  agt_interfaces__srv__GetNavigationSession_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetNavigationSession_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__GetNavigationSession_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_NOT_FOUND'.
enum
{
  agt_interfaces__srv__GetNavigationSession_Response__ERROR_NOT_FOUND = 1
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__GetNavigationSession_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'status'
#include "agt_interfaces/msg/detail/navigation_session_status__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetNavigationSession in the package agt_interfaces.
typedef struct agt_interfaces__srv__GetNavigationSession_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__NavigationSessionStatus status;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__GetNavigationSession_Response;

// Struct for a sequence of agt_interfaces__srv__GetNavigationSession_Response.
typedef struct agt_interfaces__srv__GetNavigationSession_Response__Sequence
{
  agt_interfaces__srv__GetNavigationSession_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__GetNavigationSession_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__GET_NAVIGATION_SESSION__STRUCT_H_
