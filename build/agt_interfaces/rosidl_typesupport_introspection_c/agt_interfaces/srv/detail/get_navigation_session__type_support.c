// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agt_interfaces:srv/GetNavigationSession.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agt_interfaces/srv/detail/get_navigation_session__rosidl_typesupport_introspection_c.h"
#include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agt_interfaces/srv/detail/get_navigation_session__functions.h"
#include "agt_interfaces/srv/detail/get_navigation_session__struct.h"


// Include directives for member types
// Member `session_id`
// Member `client_request_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__GetNavigationSession_Request__init(message_memory);
}

void agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_fini_function(void * message_memory)
{
  agt_interfaces__srv__GetNavigationSession_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_member_array[2] = {
  {
    "session_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Request, session_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "client_request_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Request, client_request_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_members = {
  "agt_interfaces__srv",  // message namespace
  "GetNavigationSession_Request",  // message name
  2,  // number of fields
  sizeof(agt_interfaces__srv__GetNavigationSession_Request),
  agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_member_array,  // message members
  agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_type_support_handle = {
  0,
  &agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Request)() {
  if (!agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__GetNavigationSession_Request__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "agt_interfaces/srv/detail/get_navigation_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "agt_interfaces/srv/detail/get_navigation_session__functions.h"
// already included above
// #include "agt_interfaces/srv/detail/get_navigation_session__struct.h"


// Include directives for member types
// Member `status`
#include "agt_interfaces/msg/navigation_session_status.h"
// Member `status`
#include "agt_interfaces/msg/detail/navigation_session_status__rosidl_typesupport_introspection_c.h"
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agt_interfaces__srv__GetNavigationSession_Response__init(message_memory);
}

void agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_fini_function(void * message_memory)
{
  agt_interfaces__srv__GetNavigationSession_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_member_array[4] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Response, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agt_interfaces__srv__GetNavigationSession_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_members = {
  "agt_interfaces__srv",  // message namespace
  "GetNavigationSession_Response",  // message name
  4,  // number of fields
  sizeof(agt_interfaces__srv__GetNavigationSession_Response),
  agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_member_array,  // message members
  agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_type_support_handle = {
  0,
  &agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Response)() {
  agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, msg, NavigationSessionStatus)();
  if (!agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agt_interfaces__srv__GetNavigationSession_Response__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "agt_interfaces/srv/detail/get_navigation_session__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_members = {
  "agt_interfaces__srv",  // service namespace
  "GetNavigationSession",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_Request_message_type_support_handle,
  NULL  // response message
  // agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_Response_message_type_support_handle
};

static rosidl_service_type_support_t agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_type_support_handle = {
  0,
  &agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agt_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession)() {
  if (!agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_type_support_handle.typesupport_identifier) {
    agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agt_interfaces, srv, GetNavigationSession_Response)()->data;
  }

  return &agt_interfaces__srv__detail__get_navigation_session__rosidl_typesupport_introspection_c__GetNavigationSession_service_type_support_handle;
}
