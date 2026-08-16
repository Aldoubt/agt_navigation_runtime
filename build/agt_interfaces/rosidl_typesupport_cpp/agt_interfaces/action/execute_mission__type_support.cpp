// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:action/ExecuteMission.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "agt_interfaces/action/detail/execute_mission__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace agt_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_Goal_type_support_ids_t;

static const _ExecuteMission_Goal_type_support_ids_t _ExecuteMission_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_Goal_type_support_symbol_names_t _ExecuteMission_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_Goal)),
  }
};

typedef struct _ExecuteMission_Goal_type_support_data_t
{
  void * data[2];
} _ExecuteMission_Goal_type_support_data_t;

static _ExecuteMission_Goal_type_support_data_t _ExecuteMission_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_Goal_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_Goal_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Goal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_Goal)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Goal>();
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
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_Result_type_support_ids_t;

static const _ExecuteMission_Result_type_support_ids_t _ExecuteMission_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_Result_type_support_symbol_names_t _ExecuteMission_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_Result)),
  }
};

typedef struct _ExecuteMission_Result_type_support_data_t
{
  void * data[2];
} _ExecuteMission_Result_type_support_data_t;

static _ExecuteMission_Result_type_support_data_t _ExecuteMission_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_Result_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_Result_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_Result_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_Result_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Result>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_Result)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Result>();
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
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_Feedback_type_support_ids_t;

static const _ExecuteMission_Feedback_type_support_ids_t _ExecuteMission_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_Feedback_type_support_symbol_names_t _ExecuteMission_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_Feedback)),
  }
};

typedef struct _ExecuteMission_Feedback_type_support_data_t
{
  void * data[2];
} _ExecuteMission_Feedback_type_support_data_t;

static _ExecuteMission_Feedback_type_support_data_t _ExecuteMission_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_Feedback_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_Feedback_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Feedback>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_Feedback)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_Feedback>();
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
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_SendGoal_Request_type_support_ids_t;

static const _ExecuteMission_SendGoal_Request_type_support_ids_t _ExecuteMission_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_SendGoal_Request_type_support_symbol_names_t _ExecuteMission_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Request)),
  }
};

typedef struct _ExecuteMission_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _ExecuteMission_SendGoal_Request_type_support_data_t;

static _ExecuteMission_SendGoal_Request_type_support_data_t _ExecuteMission_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_SendGoal_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_SendGoal_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal_Request>();
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
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_SendGoal_Response_type_support_ids_t;

static const _ExecuteMission_SendGoal_Response_type_support_ids_t _ExecuteMission_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_SendGoal_Response_type_support_symbol_names_t _ExecuteMission_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Response)),
  }
};

typedef struct _ExecuteMission_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _ExecuteMission_SendGoal_Response_type_support_data_t;

static _ExecuteMission_SendGoal_Response_type_support_data_t _ExecuteMission_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_SendGoal_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_SendGoal_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_SendGoal_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_SendGoal_type_support_ids_t;

static const _ExecuteMission_SendGoal_type_support_ids_t _ExecuteMission_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_SendGoal_type_support_symbol_names_t _ExecuteMission_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_SendGoal)),
  }
};

typedef struct _ExecuteMission_SendGoal_type_support_data_t
{
  void * data[2];
} _ExecuteMission_SendGoal_type_support_data_t;

static _ExecuteMission_SendGoal_type_support_data_t _ExecuteMission_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_SendGoal_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ExecuteMission_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_SendGoal_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::ExecuteMission_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_GetResult_Request_type_support_ids_t;

static const _ExecuteMission_GetResult_Request_type_support_ids_t _ExecuteMission_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_GetResult_Request_type_support_symbol_names_t _ExecuteMission_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_GetResult_Request)),
  }
};

typedef struct _ExecuteMission_GetResult_Request_type_support_data_t
{
  void * data[2];
} _ExecuteMission_GetResult_Request_type_support_data_t;

static _ExecuteMission_GetResult_Request_type_support_data_t _ExecuteMission_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_GetResult_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_GetResult_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_GetResult_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult_Request>();
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
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_GetResult_Response_type_support_ids_t;

static const _ExecuteMission_GetResult_Response_type_support_ids_t _ExecuteMission_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_GetResult_Response_type_support_symbol_names_t _ExecuteMission_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_GetResult_Response)),
  }
};

typedef struct _ExecuteMission_GetResult_Response_type_support_data_t
{
  void * data[2];
} _ExecuteMission_GetResult_Response_type_support_data_t;

static _ExecuteMission_GetResult_Response_type_support_data_t _ExecuteMission_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_GetResult_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_GetResult_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_GetResult_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace agt_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_GetResult_type_support_ids_t;

static const _ExecuteMission_GetResult_type_support_ids_t _ExecuteMission_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_GetResult_type_support_symbol_names_t _ExecuteMission_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_GetResult)),
  }
};

typedef struct _ExecuteMission_GetResult_type_support_data_t
{
  void * data[2];
} _ExecuteMission_GetResult_type_support_data_t;

static _ExecuteMission_GetResult_type_support_data_t _ExecuteMission_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_GetResult_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ExecuteMission_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_GetResult_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::ExecuteMission_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
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

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _ExecuteMission_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteMission_FeedbackMessage_type_support_ids_t;

static const _ExecuteMission_FeedbackMessage_type_support_ids_t _ExecuteMission_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteMission_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteMission_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteMission_FeedbackMessage_type_support_symbol_names_t _ExecuteMission_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteMission_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteMission_FeedbackMessage)),
  }
};

typedef struct _ExecuteMission_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _ExecuteMission_FeedbackMessage_type_support_data_t;

static _ExecuteMission_FeedbackMessage_type_support_data_t _ExecuteMission_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteMission_FeedbackMessage_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteMission_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteMission_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteMission_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteMission_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteMission_FeedbackMessage_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agt_interfaces::action::ExecuteMission_FeedbackMessage>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission_FeedbackMessage)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteMission_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "agt_interfaces/action/detail/execute_mission__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace agt_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

static rosidl_action_type_support_t ExecuteMission_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<agt_interfaces::action::ExecuteMission>()
{
  using ::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteMission_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  ExecuteMission_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteMission::Impl::SendGoalService>();
  ExecuteMission_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteMission::Impl::GetResultService>();
  ExecuteMission_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteMission::Impl::CancelGoalService>();
  ExecuteMission_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::agt_interfaces::action::ExecuteMission::Impl::FeedbackMessage>();
  ExecuteMission_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::agt_interfaces::action::ExecuteMission::Impl::GoalStatusMessage>();
  return &ExecuteMission_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteMission)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<agt_interfaces::action::ExecuteMission>();
}

#ifdef __cplusplus
}
#endif
