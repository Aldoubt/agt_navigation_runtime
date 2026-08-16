// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:srv/ArchiveTaskGroup.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "agt_interfaces/srv/detail/archive_task_group__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _ArchiveTaskGroup_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ArchiveTaskGroup_Request_type_support_ids_t;

static const _ArchiveTaskGroup_Request_type_support_ids_t _ArchiveTaskGroup_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ArchiveTaskGroup_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ArchiveTaskGroup_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ArchiveTaskGroup_Request_type_support_symbol_names_t _ArchiveTaskGroup_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, srv, ArchiveTaskGroup_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ArchiveTaskGroup_Request)),
  }
};

typedef struct _ArchiveTaskGroup_Request_type_support_data_t
{
  void * data[2];
} _ArchiveTaskGroup_Request_type_support_data_t;

static _ArchiveTaskGroup_Request_type_support_data_t _ArchiveTaskGroup_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ArchiveTaskGroup_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ArchiveTaskGroup_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ArchiveTaskGroup_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ArchiveTaskGroup_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ArchiveTaskGroup_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ArchiveTaskGroup_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup_Request>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_cpp::ArchiveTaskGroup_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, srv, ArchiveTaskGroup_Request)() {
  return get_message_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/srv/detail/archive_task_group__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _ArchiveTaskGroup_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ArchiveTaskGroup_Response_type_support_ids_t;

static const _ArchiveTaskGroup_Response_type_support_ids_t _ArchiveTaskGroup_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ArchiveTaskGroup_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ArchiveTaskGroup_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ArchiveTaskGroup_Response_type_support_symbol_names_t _ArchiveTaskGroup_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, srv, ArchiveTaskGroup_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ArchiveTaskGroup_Response)),
  }
};

typedef struct _ArchiveTaskGroup_Response_type_support_data_t
{
  void * data[2];
} _ArchiveTaskGroup_Response_type_support_data_t;

static _ArchiveTaskGroup_Response_type_support_data_t _ArchiveTaskGroup_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ArchiveTaskGroup_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ArchiveTaskGroup_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ArchiveTaskGroup_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ArchiveTaskGroup_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ArchiveTaskGroup_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ArchiveTaskGroup_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup_Response>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_cpp::ArchiveTaskGroup_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, srv, ArchiveTaskGroup_Response)() {
  return get_message_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/srv/detail/archive_task_group__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace agt_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _ArchiveTaskGroup_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ArchiveTaskGroup_type_support_ids_t;

static const _ArchiveTaskGroup_type_support_ids_t _ArchiveTaskGroup_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ArchiveTaskGroup_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ArchiveTaskGroup_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ArchiveTaskGroup_type_support_symbol_names_t _ArchiveTaskGroup_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, srv, ArchiveTaskGroup)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, srv, ArchiveTaskGroup)),
  }
};

typedef struct _ArchiveTaskGroup_type_support_data_t
{
  void * data[2];
} _ArchiveTaskGroup_type_support_data_t;

static _ArchiveTaskGroup_type_support_data_t _ArchiveTaskGroup_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ArchiveTaskGroup_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_ArchiveTaskGroup_service_typesupport_ids.typesupport_identifier[0],
  &_ArchiveTaskGroup_service_typesupport_symbol_names.symbol_name[0],
  &_ArchiveTaskGroup_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ArchiveTaskGroup_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ArchiveTaskGroup_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup>()
{
  return &::agt_interfaces::srv::rosidl_typesupport_cpp::ArchiveTaskGroup_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, srv, ArchiveTaskGroup)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::srv::ArchiveTaskGroup>();
}

#ifdef __cplusplus
}
#endif
