// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agt_interfaces:srv/ListBagSessions.idl
// generated code does not contain a copyright notice

#ifndef AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__STRUCT_H_
#define AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'experiment_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListBagSessions in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListBagSessions_Request
{
  uint8_t state;
  rosidl_runtime_c__String experiment_id;
} agt_interfaces__srv__ListBagSessions_Request;

// Struct for a sequence of agt_interfaces__srv__ListBagSessions_Request.
typedef struct agt_interfaces__srv__ListBagSessions_Request__Sequence
{
  agt_interfaces__srv__ListBagSessions_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListBagSessions_Request__Sequence;


// Constants defined in the message

/// Constant 'ERROR_NONE'.
enum
{
  agt_interfaces__srv__ListBagSessions_Response__ERROR_NONE = 0
};

/// Constant 'ERROR_INVALID_REQUEST'.
enum
{
  agt_interfaces__srv__ListBagSessions_Response__ERROR_INVALID_REQUEST = 1
};

/// Constant 'ERROR_INTERNAL'.
enum
{
  agt_interfaces__srv__ListBagSessions_Response__ERROR_INTERNAL = 255
};

// Include directives for member types
// Member 'sessions'
#include "agt_interfaces/msg/detail/bag_session_summary__struct.h"
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListBagSessions in the package agt_interfaces.
typedef struct agt_interfaces__srv__ListBagSessions_Response
{
  bool success;
  uint16_t error_code;
  agt_interfaces__msg__BagSessionSummary__Sequence sessions;
  rosidl_runtime_c__String message;
} agt_interfaces__srv__ListBagSessions_Response;

// Struct for a sequence of agt_interfaces__srv__ListBagSessions_Response.
typedef struct agt_interfaces__srv__ListBagSessions_Response__Sequence
{
  agt_interfaces__srv__ListBagSessions_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agt_interfaces__srv__ListBagSessions_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGT_INTERFACES__SRV__DETAIL__LIST_BAG_SESSIONS__STRUCT_H_
