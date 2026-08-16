// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from agt_interfaces:action/OptimizeMap.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_Goal_type_support_ids_t;

static const _OptimizeMap_Goal_type_support_ids_t _OptimizeMap_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_Goal_type_support_symbol_names_t _OptimizeMap_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_Goal)),
  }
};

typedef struct _OptimizeMap_Goal_type_support_data_t
{
  void * data[2];
} _OptimizeMap_Goal_type_support_data_t;

static _OptimizeMap_Goal_type_support_data_t _OptimizeMap_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_Goal_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_Goal_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Goal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_Goal)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Goal>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_Result_type_support_ids_t;

static const _OptimizeMap_Result_type_support_ids_t _OptimizeMap_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_Result_type_support_symbol_names_t _OptimizeMap_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_Result)),
  }
};

typedef struct _OptimizeMap_Result_type_support_data_t
{
  void * data[2];
} _OptimizeMap_Result_type_support_data_t;

static _OptimizeMap_Result_type_support_data_t _OptimizeMap_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_Result_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_Result_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_Result_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_Result_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Result>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_Result)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Result>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_Feedback_type_support_ids_t;

static const _OptimizeMap_Feedback_type_support_ids_t _OptimizeMap_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_Feedback_type_support_symbol_names_t _OptimizeMap_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_Feedback)),
  }
};

typedef struct _OptimizeMap_Feedback_type_support_data_t
{
  void * data[2];
} _OptimizeMap_Feedback_type_support_data_t;

static _OptimizeMap_Feedback_type_support_data_t _OptimizeMap_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_Feedback_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_Feedback_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Feedback>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_Feedback)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_Feedback>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_SendGoal_Request_type_support_ids_t;

static const _OptimizeMap_SendGoal_Request_type_support_ids_t _OptimizeMap_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_SendGoal_Request_type_support_symbol_names_t _OptimizeMap_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Request)),
  }
};

typedef struct _OptimizeMap_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _OptimizeMap_SendGoal_Request_type_support_data_t;

static _OptimizeMap_SendGoal_Request_type_support_data_t _OptimizeMap_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_SendGoal_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_SendGoal_Request_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal_Request>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_SendGoal_Response_type_support_ids_t;

static const _OptimizeMap_SendGoal_Response_type_support_ids_t _OptimizeMap_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_SendGoal_Response_type_support_symbol_names_t _OptimizeMap_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Response)),
  }
};

typedef struct _OptimizeMap_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _OptimizeMap_SendGoal_Response_type_support_data_t;

static _OptimizeMap_SendGoal_Response_type_support_data_t _OptimizeMap_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_SendGoal_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_SendGoal_Response_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_SendGoal_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_SendGoal_type_support_ids_t;

static const _OptimizeMap_SendGoal_type_support_ids_t _OptimizeMap_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_SendGoal_type_support_symbol_names_t _OptimizeMap_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_SendGoal)),
  }
};

typedef struct _OptimizeMap_SendGoal_type_support_data_t
{
  void * data[2];
} _OptimizeMap_SendGoal_type_support_data_t;

static _OptimizeMap_SendGoal_type_support_data_t _OptimizeMap_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_SendGoal_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t OptimizeMap_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_SendGoal_service_typesupport_map),
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
get_service_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::OptimizeMap_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_GetResult_Request_type_support_ids_t;

static const _OptimizeMap_GetResult_Request_type_support_ids_t _OptimizeMap_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_GetResult_Request_type_support_symbol_names_t _OptimizeMap_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_GetResult_Request)),
  }
};

typedef struct _OptimizeMap_GetResult_Request_type_support_data_t
{
  void * data[2];
} _OptimizeMap_GetResult_Request_type_support_data_t;

static _OptimizeMap_GetResult_Request_type_support_data_t _OptimizeMap_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_GetResult_Request_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_GetResult_Request_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult_Request>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_GetResult_Request)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult_Request>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_GetResult_Response_type_support_ids_t;

static const _OptimizeMap_GetResult_Response_type_support_ids_t _OptimizeMap_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_GetResult_Response_type_support_symbol_names_t _OptimizeMap_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_GetResult_Response)),
  }
};

typedef struct _OptimizeMap_GetResult_Response_type_support_data_t
{
  void * data[2];
} _OptimizeMap_GetResult_Response_type_support_data_t;

static _OptimizeMap_GetResult_Response_type_support_data_t _OptimizeMap_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_GetResult_Response_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_GetResult_Response_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult_Response>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_GetResult_Response)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult_Response>();
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
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_GetResult_type_support_ids_t;

static const _OptimizeMap_GetResult_type_support_ids_t _OptimizeMap_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_GetResult_type_support_symbol_names_t _OptimizeMap_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_GetResult)),
  }
};

typedef struct _OptimizeMap_GetResult_type_support_data_t
{
  void * data[2];
} _OptimizeMap_GetResult_type_support_data_t;

static _OptimizeMap_GetResult_type_support_data_t _OptimizeMap_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_GetResult_service_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t OptimizeMap_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_GetResult_service_typesupport_map),
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
get_service_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<agt_interfaces::action::OptimizeMap_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

typedef struct _OptimizeMap_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _OptimizeMap_FeedbackMessage_type_support_ids_t;

static const _OptimizeMap_FeedbackMessage_type_support_ids_t _OptimizeMap_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _OptimizeMap_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _OptimizeMap_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _OptimizeMap_FeedbackMessage_type_support_symbol_names_t _OptimizeMap_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, agt_interfaces, action, OptimizeMap_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agt_interfaces, action, OptimizeMap_FeedbackMessage)),
  }
};

typedef struct _OptimizeMap_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _OptimizeMap_FeedbackMessage_type_support_data_t;

static _OptimizeMap_FeedbackMessage_type_support_data_t _OptimizeMap_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _OptimizeMap_FeedbackMessage_message_typesupport_map = {
  2,
  "agt_interfaces",
  &_OptimizeMap_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_OptimizeMap_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_OptimizeMap_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t OptimizeMap_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_OptimizeMap_FeedbackMessage_message_typesupport_map),
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
get_message_type_support_handle<agt_interfaces::action::OptimizeMap_FeedbackMessage>()
{
  return &::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap_FeedbackMessage)() {
  return get_message_type_support_handle<agt_interfaces::action::OptimizeMap_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "agt_interfaces/action/detail/optimize_map__struct.hpp"
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

static rosidl_action_type_support_t OptimizeMap_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace agt_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<agt_interfaces::action::OptimizeMap>()
{
  using ::agt_interfaces::action::rosidl_typesupport_cpp::OptimizeMap_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  OptimizeMap_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::agt_interfaces::action::OptimizeMap::Impl::SendGoalService>();
  OptimizeMap_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::agt_interfaces::action::OptimizeMap::Impl::GetResultService>();
  OptimizeMap_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::agt_interfaces::action::OptimizeMap::Impl::CancelGoalService>();
  OptimizeMap_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::agt_interfaces::action::OptimizeMap::Impl::FeedbackMessage>();
  OptimizeMap_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::agt_interfaces::action::OptimizeMap::Impl::GoalStatusMessage>();
  return &OptimizeMap_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, agt_interfaces, action, OptimizeMap)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<agt_interfaces::action::OptimizeMap>();
}

#ifdef __cplusplus
}
#endif
