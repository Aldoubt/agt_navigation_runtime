// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:action/ExecuteBehaviorTree.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_Goal_type_support_ids_t;

static const _ExecuteBehaviorTree_Goal_type_support_ids_t _ExecuteBehaviorTree_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_Goal_type_support_symbol_names_t _ExecuteBehaviorTree_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_Goal)),
  }
};

typedef struct _ExecuteBehaviorTree_Goal_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_Goal_type_support_data_t;

static _ExecuteBehaviorTree_Goal_type_support_data_t _ExecuteBehaviorTree_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_Goal_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_Goal_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Goal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_Goal)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Goal>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_Result_type_support_ids_t;

static const _ExecuteBehaviorTree_Result_type_support_ids_t _ExecuteBehaviorTree_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_Result_type_support_symbol_names_t _ExecuteBehaviorTree_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_Result)),
  }
};

typedef struct _ExecuteBehaviorTree_Result_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_Result_type_support_data_t;

static _ExecuteBehaviorTree_Result_type_support_data_t _ExecuteBehaviorTree_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_Result_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_Result_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_Result_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_Result_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Result>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_Result)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Result>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_Feedback_type_support_ids_t;

static const _ExecuteBehaviorTree_Feedback_type_support_ids_t _ExecuteBehaviorTree_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_Feedback_type_support_symbol_names_t _ExecuteBehaviorTree_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_Feedback)),
  }
};

typedef struct _ExecuteBehaviorTree_Feedback_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_Feedback_type_support_data_t;

static _ExecuteBehaviorTree_Feedback_type_support_data_t _ExecuteBehaviorTree_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_Feedback_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_Feedback_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Feedback>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_Feedback)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_Feedback>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_SendGoal_Request_type_support_ids_t;

static const _ExecuteBehaviorTree_SendGoal_Request_type_support_ids_t _ExecuteBehaviorTree_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_SendGoal_Request_type_support_symbol_names_t _ExecuteBehaviorTree_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)),
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_SendGoal_Request_type_support_data_t;

static _ExecuteBehaviorTree_SendGoal_Request_type_support_data_t _ExecuteBehaviorTree_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_SendGoal_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_SendGoal_Request_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Request>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_SendGoal_Response_type_support_ids_t;

static const _ExecuteBehaviorTree_SendGoal_Response_type_support_ids_t _ExecuteBehaviorTree_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_SendGoal_Response_type_support_symbol_names_t _ExecuteBehaviorTree_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)),
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_SendGoal_Response_type_support_data_t;

static _ExecuteBehaviorTree_SendGoal_Response_type_support_data_t _ExecuteBehaviorTree_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_SendGoal_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_SendGoal_Response_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_SendGoal_type_support_ids_t;

static const _ExecuteBehaviorTree_SendGoal_type_support_ids_t _ExecuteBehaviorTree_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_SendGoal_type_support_symbol_names_t _ExecuteBehaviorTree_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal)),
  }
};

typedef struct _ExecuteBehaviorTree_SendGoal_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_SendGoal_type_support_data_t;

static _ExecuteBehaviorTree_SendGoal_type_support_data_t _ExecuteBehaviorTree_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_SendGoal_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ExecuteBehaviorTree_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_SendGoal_service_typesupport_map),
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
get_service_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_GetResult_Request_type_support_ids_t;

static const _ExecuteBehaviorTree_GetResult_Request_type_support_ids_t _ExecuteBehaviorTree_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_GetResult_Request_type_support_symbol_names_t _ExecuteBehaviorTree_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)),
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_Request_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_GetResult_Request_type_support_data_t;

static _ExecuteBehaviorTree_GetResult_Request_type_support_data_t _ExecuteBehaviorTree_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_GetResult_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_GetResult_Request_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Request>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_GetResult_Response_type_support_ids_t;

static const _ExecuteBehaviorTree_GetResult_Response_type_support_ids_t _ExecuteBehaviorTree_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_GetResult_Response_type_support_symbol_names_t _ExecuteBehaviorTree_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)),
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_Response_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_GetResult_Response_type_support_data_t;

static _ExecuteBehaviorTree_GetResult_Response_type_support_data_t _ExecuteBehaviorTree_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_GetResult_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_GetResult_Response_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult_Response>();
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
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_GetResult_type_support_ids_t;

static const _ExecuteBehaviorTree_GetResult_type_support_ids_t _ExecuteBehaviorTree_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_GetResult_type_support_symbol_names_t _ExecuteBehaviorTree_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult)),
  }
};

typedef struct _ExecuteBehaviorTree_GetResult_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_GetResult_type_support_data_t;

static _ExecuteBehaviorTree_GetResult_type_support_data_t _ExecuteBehaviorTree_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_GetResult_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ExecuteBehaviorTree_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_GetResult_service_typesupport_map),
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
get_service_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

typedef struct _ExecuteBehaviorTree_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ExecuteBehaviorTree_FeedbackMessage_type_support_ids_t;

static const _ExecuteBehaviorTree_FeedbackMessage_type_support_ids_t _ExecuteBehaviorTree_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _ExecuteBehaviorTree_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ExecuteBehaviorTree_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ExecuteBehaviorTree_FeedbackMessage_type_support_symbol_names_t _ExecuteBehaviorTree_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, ExecuteBehaviorTree_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, ExecuteBehaviorTree_FeedbackMessage)),
  }
};

typedef struct _ExecuteBehaviorTree_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _ExecuteBehaviorTree_FeedbackMessage_type_support_data_t;

static _ExecuteBehaviorTree_FeedbackMessage_type_support_data_t _ExecuteBehaviorTree_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ExecuteBehaviorTree_FeedbackMessage_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_ExecuteBehaviorTree_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_ExecuteBehaviorTree_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_ExecuteBehaviorTree_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ExecuteBehaviorTree_FeedbackMessage_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree_FeedbackMessage)() {
  return get_message_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "agt_interfaces/action/detail/execute_behavior_tree__struct.hpp"
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

static rosidl_action_type_support_t ExecuteBehaviorTree_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree>()
{
  using ::agt_interfaces::action::rosidl_typesupport_cpp::ExecuteBehaviorTree_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  ExecuteBehaviorTree_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteBehaviorTree::Impl::SendGoalService>();
  ExecuteBehaviorTree_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteBehaviorTree::Impl::GetResultService>();
  ExecuteBehaviorTree_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::agt_interfaces::action::ExecuteBehaviorTree::Impl::CancelGoalService>();
  ExecuteBehaviorTree_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::agt_interfaces::action::ExecuteBehaviorTree::Impl::FeedbackMessage>();
  ExecuteBehaviorTree_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::agt_interfaces::action::ExecuteBehaviorTree::Impl::GoalStatusMessage>();
  return &ExecuteBehaviorTree_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, ExecuteBehaviorTree)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<agt_interfaces::action::ExecuteBehaviorTree>();
}

#ifdef __cplusplus
}
#endif
