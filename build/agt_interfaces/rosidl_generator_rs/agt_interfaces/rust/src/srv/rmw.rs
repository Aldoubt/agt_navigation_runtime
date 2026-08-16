#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__EvaluateTaskReadiness_Request__init(msg: *mut EvaluateTaskReadiness_Request) -> bool;
    fn agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Request>);
    fn agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__EvaluateTaskReadiness_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EvaluateTaskReadiness_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub validate_task: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gate_profile: u8,

}

impl EvaluateTaskReadiness_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PROFILE_TASK_EXECUTION: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PROFILE_RELOCALIZATION: u8 = 1;

}


impl Default for EvaluateTaskReadiness_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__EvaluateTaskReadiness_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__EvaluateTaskReadiness_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EvaluateTaskReadiness_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EvaluateTaskReadiness_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EvaluateTaskReadiness_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/EvaluateTaskReadiness_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__EvaluateTaskReadiness_Response__init(msg: *mut EvaluateTaskReadiness_Response) -> bool;
    fn agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Response>);
    fn agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<EvaluateTaskReadiness_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__EvaluateTaskReadiness_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EvaluateTaskReadiness_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub readiness: super::super::msg::rmw::TaskReadiness,

}



impl Default for EvaluateTaskReadiness_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__EvaluateTaskReadiness_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__EvaluateTaskReadiness_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EvaluateTaskReadiness_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__EvaluateTaskReadiness_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EvaluateTaskReadiness_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EvaluateTaskReadiness_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/EvaluateTaskReadiness_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetSystemHealth_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetSystemHealth_Request__init(msg: *mut GetSystemHealth_Request) -> bool;
    fn agt_interfaces__srv__GetSystemHealth_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__GetSystemHealth_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Request>);
    fn agt_interfaces__srv__GetSystemHealth_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetSystemHealth_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetSystemHealth_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetSystemHealth_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub include_optional: bool,

}



impl Default for GetSystemHealth_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetSystemHealth_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetSystemHealth_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetSystemHealth_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetSystemHealth_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetSystemHealth_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetSystemHealth_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetSystemHealth_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetSystemHealth_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetSystemHealth_Response__init(msg: *mut GetSystemHealth_Response) -> bool;
    fn agt_interfaces__srv__GetSystemHealth_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__GetSystemHealth_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Response>);
    fn agt_interfaces__srv__GetSystemHealth_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetSystemHealth_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetSystemHealth_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetSystemHealth_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetSystemHealth_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub health: super::super::msg::rmw::SystemHealth,

}



impl Default for GetSystemHealth_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetSystemHealth_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetSystemHealth_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetSystemHealth_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetSystemHealth_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetSystemHealth_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetSystemHealth_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetSystemHealth_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetSystemHealth_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetRobotState_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetRobotState_Request__init(msg: *mut GetRobotState_Request) -> bool;
    fn agt_interfaces__srv__GetRobotState_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__GetRobotState_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Request>);
    fn agt_interfaces__srv__GetRobotState_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetRobotState_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetRobotState_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetRobotState_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub include_details: bool,

}



impl Default for GetRobotState_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetRobotState_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetRobotState_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetRobotState_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetRobotState_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetRobotState_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetRobotState_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetRobotState_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetRobotState_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetRobotState_Response__init(msg: *mut GetRobotState_Response) -> bool;
    fn agt_interfaces__srv__GetRobotState_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__GetRobotState_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Response>);
    fn agt_interfaces__srv__GetRobotState_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetRobotState_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetRobotState_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetRobotState_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetRobotState_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: super::super::msg::rmw::RobotState,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for GetRobotState_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetRobotState_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetRobotState_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetRobotState_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetRobotState_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetRobotState_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetRobotState_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetRobotState_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetRobotState_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetMissionRunState_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__SetMissionRunState_Request__init(msg: *mut SetMissionRunState_Request) -> bool;
    fn agt_interfaces__srv__SetMissionRunState_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__SetMissionRunState_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Request>);
    fn agt_interfaces__srv__SetMissionRunState_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetMissionRunState_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__SetMissionRunState_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMissionRunState_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: rosidl_runtime_rs::String,

}

impl SetMissionRunState_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const COMMAND_PAUSE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const COMMAND_RESUME: u8 = 2;

}


impl Default for SetMissionRunState_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__SetMissionRunState_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__SetMissionRunState_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetMissionRunState_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetMissionRunState_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetMissionRunState_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/SetMissionRunState_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetMissionRunState_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetMissionRunState_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__SetMissionRunState_Response__init(msg: *mut SetMissionRunState_Response) -> bool;
    fn agt_interfaces__srv__SetMissionRunState_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__SetMissionRunState_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Response>);
    fn agt_interfaces__srv__SetMissionRunState_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetMissionRunState_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetMissionRunState_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__SetMissionRunState_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMissionRunState_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: super::super::msg::rmw::MissionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetMissionRunState_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__SetMissionRunState_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__SetMissionRunState_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetMissionRunState_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetMissionRunState_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetMissionRunState_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetMissionRunState_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/SetMissionRunState_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetMissionRunState_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ActivateMapVersion_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ActivateMapVersion_Request__init(msg: *mut ActivateMapVersion_Request) -> bool;
    fn agt_interfaces__srv__ActivateMapVersion_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ActivateMapVersion_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Request>);
    fn agt_interfaces__srv__ActivateMapVersion_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ActivateMapVersion_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ActivateMapVersion_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ActivateMapVersion_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,

}



impl Default for ActivateMapVersion_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ActivateMapVersion_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ActivateMapVersion_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ActivateMapVersion_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ActivateMapVersion_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ActivateMapVersion_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ActivateMapVersion_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ActivateMapVersion_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ActivateMapVersion_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ActivateMapVersion_Response__init(msg: *mut ActivateMapVersion_Response) -> bool;
    fn agt_interfaces__srv__ActivateMapVersion_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ActivateMapVersion_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Response>);
    fn agt_interfaces__srv__ActivateMapVersion_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ActivateMapVersion_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ActivateMapVersion_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ActivateMapVersion_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ActivateMapVersion_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub version: super::super::msg::rmw::MapVersionSummary,

}

impl ActivateMapVersion_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_VALIDATION_FAILED: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ActivateMapVersion_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ActivateMapVersion_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ActivateMapVersion_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ActivateMapVersion_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ActivateMapVersion_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ActivateMapVersion_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ActivateMapVersion_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ActivateMapVersion_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ActivateMapVersion_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListMapVersions_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListMapVersions_Request__init(msg: *mut ListMapVersions_Request) -> bool;
    fn agt_interfaces__srv__ListMapVersions_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ListMapVersions_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Request>);
    fn agt_interfaces__srv__ListMapVersions_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListMapVersions_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListMapVersions_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListMapVersions_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub include_deleted: bool,

}



impl Default for ListMapVersions_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListMapVersions_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListMapVersions_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListMapVersions_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListMapVersions_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListMapVersions_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListMapVersions_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListMapVersions_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListMapVersions_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListMapVersions_Response__init(msg: *mut ListMapVersions_Response) -> bool;
    fn agt_interfaces__srv__ListMapVersions_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ListMapVersions_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Response>);
    fn agt_interfaces__srv__ListMapVersions_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListMapVersions_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ListMapVersions_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListMapVersions_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListMapVersions_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub versions: rosidl_runtime_rs::Sequence<super::super::msg::rmw::MapVersionSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ListMapVersions_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ListMapVersions_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListMapVersions_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListMapVersions_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListMapVersions_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListMapVersions_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListMapVersions_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListMapVersions_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListMapVersions_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListMapVersions_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageMapVersion_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ManageMapVersion_Request__init(msg: *mut ManageMapVersion_Request) -> bool;
    fn agt_interfaces__srv__ManageMapVersion_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ManageMapVersion_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Request>);
    fn agt_interfaces__srv__ManageMapVersion_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMapVersion_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ManageMapVersion_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMapVersion_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub confirm_destructive: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_yaml: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub parent_map_version_id: rosidl_runtime_rs::String,

}

impl ManageMapVersion_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_GET_ACTIVE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_VALIDATE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_ACTIVATE: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_PIN: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_UNPIN: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_ARCHIVE: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_SOFT_DELETE: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_PURGE: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_IMPORT_CANDIDATE: u8 = 8;

}


impl Default for ManageMapVersion_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ManageMapVersion_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ManageMapVersion_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMapVersion_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMapVersion_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMapVersion_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ManageMapVersion_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageMapVersion_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageMapVersion_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ManageMapVersion_Response__init(msg: *mut ManageMapVersion_Response) -> bool;
    fn agt_interfaces__srv__ManageMapVersion_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ManageMapVersion_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Response>);
    fn agt_interfaces__srv__ManageMapVersion_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMapVersion_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMapVersion_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ManageMapVersion_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMapVersion_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub version: super::super::msg::rmw::MapVersionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ManageMapVersion_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CONFLICT: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_VALIDATION_FAILED: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CONFIRMATION_REQUIRED: u16 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ManageMapVersion_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ManageMapVersion_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ManageMapVersion_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMapVersion_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageMapVersion_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMapVersion_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMapVersion_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ManageMapVersion_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageMapVersion_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListTaskGroups_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListTaskGroups_Request__init(msg: *mut ListTaskGroups_Request) -> bool;
    fn agt_interfaces__srv__ListTaskGroups_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ListTaskGroups_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Request>);
    fn agt_interfaces__srv__ListTaskGroups_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListTaskGroups_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListTaskGroups_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListTaskGroups_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,

}



impl Default for ListTaskGroups_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListTaskGroups_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListTaskGroups_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListTaskGroups_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListTaskGroups_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListTaskGroups_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListTaskGroups_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListTaskGroups_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListTaskGroups_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListTaskGroups_Response__init(msg: *mut ListTaskGroups_Response) -> bool;
    fn agt_interfaces__srv__ListTaskGroups_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ListTaskGroups_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Response>);
    fn agt_interfaces__srv__ListTaskGroups_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListTaskGroups_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ListTaskGroups_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListTaskGroups_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListTaskGroups_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_ids: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revisions: rosidl_runtime_rs::Sequence<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enabled_point_counts: rosidl_runtime_rs::Sequence<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_states: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}

impl ListTaskGroups_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_NOT_READY: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ListTaskGroups_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListTaskGroups_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListTaskGroups_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListTaskGroups_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListTaskGroups_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListTaskGroups_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListTaskGroups_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListTaskGroups_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListTaskGroups_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetTaskGroup_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetTaskGroup_Request__init(msg: *mut GetTaskGroup_Request) -> bool;
    fn agt_interfaces__srv__GetTaskGroup_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__GetTaskGroup_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Request>);
    fn agt_interfaces__srv__GetTaskGroup_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTaskGroup_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetTaskGroup_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskGroup_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,

    /// 0 means latest revision.
    pub task_revision: u32,

}



impl Default for GetTaskGroup_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetTaskGroup_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetTaskGroup_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTaskGroup_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTaskGroup_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTaskGroup_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetTaskGroup_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetTaskGroup_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetTaskGroup_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetTaskGroup_Response__init(msg: *mut GetTaskGroup_Response) -> bool;
    fn agt_interfaces__srv__GetTaskGroup_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__GetTaskGroup_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Response>);
    fn agt_interfaces__srv__GetTaskGroup_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTaskGroup_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTaskGroup_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetTaskGroup_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskGroup_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: rosidl_runtime_rs::String,

}

impl GetTaskGroup_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_REVISION_CONFLICT: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_SCHEMA_INVALID: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for GetTaskGroup_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetTaskGroup_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetTaskGroup_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTaskGroup_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetTaskGroup_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTaskGroup_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTaskGroup_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetTaskGroup_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetTaskGroup_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__PutTaskGroup_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__PutTaskGroup_Request__init(msg: *mut PutTaskGroup_Request) -> bool;
    fn agt_interfaces__srv__PutTaskGroup_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__PutTaskGroup_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Request>);
    fn agt_interfaces__srv__PutTaskGroup_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PutTaskGroup_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__PutTaskGroup_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PutTaskGroup_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,

    /// Current robot-side revision expected by the client. 0 means create-only.
    pub expected_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: rosidl_runtime_rs::String,

}



impl Default for PutTaskGroup_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__PutTaskGroup_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__PutTaskGroup_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PutTaskGroup_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PutTaskGroup_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PutTaskGroup_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/PutTaskGroup_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__PutTaskGroup_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__PutTaskGroup_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__PutTaskGroup_Response__init(msg: *mut PutTaskGroup_Response) -> bool;
    fn agt_interfaces__srv__PutTaskGroup_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__PutTaskGroup_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Response>);
    fn agt_interfaces__srv__PutTaskGroup_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PutTaskGroup_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<PutTaskGroup_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__PutTaskGroup_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PutTaskGroup_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub duplicate_request: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: rosidl_runtime_rs::String,

}

impl PutTaskGroup_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_REVISION_CONFLICT: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CONTENT_HASH_MISMATCH: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_SCHEMA_INVALID: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_NOT_READY: u16 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for PutTaskGroup_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__PutTaskGroup_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__PutTaskGroup_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PutTaskGroup_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__PutTaskGroup_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PutTaskGroup_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PutTaskGroup_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/PutTaskGroup_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__PutTaskGroup_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ArchiveTaskGroup_Request__init(msg: *mut ArchiveTaskGroup_Request) -> bool;
    fn agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Request>);
    fn agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ArchiveTaskGroup_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArchiveTaskGroup_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub expected_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,

}



impl Default for ArchiveTaskGroup_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ArchiveTaskGroup_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ArchiveTaskGroup_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArchiveTaskGroup_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArchiveTaskGroup_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArchiveTaskGroup_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ArchiveTaskGroup_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ArchiveTaskGroup_Response__init(msg: *mut ArchiveTaskGroup_Response) -> bool;
    fn agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Response>);
    fn agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ArchiveTaskGroup_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ArchiveTaskGroup_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArchiveTaskGroup_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub duplicate_request: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub archived_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub archived_relative_path: rosidl_runtime_rs::String,

}

impl ArchiveTaskGroup_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_REVISION_CONFLICT: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_NOT_READY: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ArchiveTaskGroup_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ArchiveTaskGroup_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ArchiveTaskGroup_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ArchiveTaskGroup_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ArchiveTaskGroup_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ArchiveTaskGroup_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ArchiveTaskGroup_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ArchiveTaskGroup_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetNavigationSession_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetNavigationSession_Request__init(msg: *mut GetNavigationSession_Request) -> bool;
    fn agt_interfaces__srv__GetNavigationSession_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__GetNavigationSession_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Request>);
    fn agt_interfaces__srv__GetNavigationSession_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetNavigationSession_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetNavigationSession_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetNavigationSession_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,

}



impl Default for GetNavigationSession_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetNavigationSession_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetNavigationSession_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetNavigationSession_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetNavigationSession_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetNavigationSession_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetNavigationSession_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetNavigationSession_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetNavigationSession_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__GetNavigationSession_Response__init(msg: *mut GetNavigationSession_Response) -> bool;
    fn agt_interfaces__srv__GetNavigationSession_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__GetNavigationSession_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Response>);
    fn agt_interfaces__srv__GetNavigationSession_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetNavigationSession_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetNavigationSession_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__GetNavigationSession_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetNavigationSession_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: super::super::msg::rmw::NavigationSessionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl GetNavigationSession_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for GetNavigationSession_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__GetNavigationSession_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__GetNavigationSession_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetNavigationSession_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__GetNavigationSession_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetNavigationSession_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetNavigationSession_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/GetNavigationSession_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__GetNavigationSession_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListBagSessions_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListBagSessions_Request__init(msg: *mut ListBagSessions_Request) -> bool;
    fn agt_interfaces__srv__ListBagSessions_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ListBagSessions_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Request>);
    fn agt_interfaces__srv__ListBagSessions_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListBagSessions_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListBagSessions_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListBagSessions_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: rosidl_runtime_rs::String,

}



impl Default for ListBagSessions_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListBagSessions_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListBagSessions_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListBagSessions_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListBagSessions_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListBagSessions_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListBagSessions_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListBagSessions_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListBagSessions_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListBagSessions_Response__init(msg: *mut ListBagSessions_Response) -> bool;
    fn agt_interfaces__srv__ListBagSessions_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ListBagSessions_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Response>);
    fn agt_interfaces__srv__ListBagSessions_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListBagSessions_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ListBagSessions_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListBagSessions_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListBagSessions_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sessions: rosidl_runtime_rs::Sequence<super::super::msg::rmw::BagSessionSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ListBagSessions_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ListBagSessions_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListBagSessions_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListBagSessions_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListBagSessions_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListBagSessions_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListBagSessions_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListBagSessions_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListBagSessions_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListBagSessions_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListExperiments_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListExperiments_Request__init(msg: *mut ListExperiments_Request) -> bool;
    fn agt_interfaces__srv__ListExperiments_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ListExperiments_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Request>);
    fn agt_interfaces__srv__ListExperiments_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListExperiments_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListExperiments_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListExperiments_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

}



impl Default for ListExperiments_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListExperiments_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListExperiments_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListExperiments_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListExperiments_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListExperiments_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListExperiments_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListExperiments_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListExperiments_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ListExperiments_Response__init(msg: *mut ListExperiments_Response) -> bool;
    fn agt_interfaces__srv__ListExperiments_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ListExperiments_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Response>);
    fn agt_interfaces__srv__ListExperiments_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ListExperiments_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ListExperiments_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ListExperiments_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListExperiments_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiments: rosidl_runtime_rs::Sequence<super::super::msg::rmw::ExperimentSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ListExperiments_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ListExperiments_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ListExperiments_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ListExperiments_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ListExperiments_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ListExperiments_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ListExperiments_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ListExperiments_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ListExperiments_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ListExperiments_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageBagSession_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ManageBagSession_Request__init(msg: *mut ManageBagSession_Request) -> bool;
    fn agt_interfaces__srv__ManageBagSession_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__ManageBagSession_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Request>);
    fn agt_interfaces__srv__ManageBagSession_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageBagSession_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__ManageBagSession_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageBagSession_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_title: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub objective: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub hypothesis: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tags_json: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_note: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub playback_rate: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub calibration_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub nav2_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub launch_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_experiment: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub event_type: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub metadata_json: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result_status: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: rosidl_runtime_rs::String,

}

impl ManageBagSession_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_STATUS: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_START_RECORDING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_STOP_RECORDING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_START_PLAYBACK: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_STOP_PLAYBACK: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_CREATE_EXPERIMENT: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_COMPLETE_EXPERIMENT: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_INTERRUPT_EXPERIMENT: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_START_EXPERIMENT: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_MARK_EXPERIMENT_INVALID: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_ADD_EXPERIMENT_EVENT: u8 = 10;

}


impl Default for ManageBagSession_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ManageBagSession_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ManageBagSession_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageBagSession_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageBagSession_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageBagSession_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ManageBagSession_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageBagSession_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageBagSession_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__ManageBagSession_Response__init(msg: *mut ManageBagSession_Response) -> bool;
    fn agt_interfaces__srv__ManageBagSession_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__ManageBagSession_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Response>);
    fn agt_interfaces__srv__ManageBagSession_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageBagSession_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageBagSession_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__ManageBagSession_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageBagSession_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session: super::super::msg::rmw::BagSessionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ManageBagSession_Response {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CONFLICT: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_PROFILE_INVALID: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ManageBagSession_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__ManageBagSession_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__ManageBagSession_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageBagSession_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__ManageBagSession_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageBagSession_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageBagSession_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/ManageBagSession_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__ManageBagSession_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetLocalizationMode_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__SetLocalizationMode_Request__init(msg: *mut SetLocalizationMode_Request) -> bool;
    fn agt_interfaces__srv__SetLocalizationMode_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Request>, size: usize) -> bool;
    fn agt_interfaces__srv__SetLocalizationMode_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Request>);
    fn agt_interfaces__srv__SetLocalizationMode_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetLocalizationMode_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Request>) -> bool;
}

// Corresponds to agt_interfaces__srv__SetLocalizationMode_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetLocalizationMode_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,

}

impl SetLocalizationMode_Request {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MANUAL_ONLY: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_AUTO_ON_START: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_AUTO_RECOVERY: u8 = 2;

}


impl Default for SetLocalizationMode_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__SetLocalizationMode_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__SetLocalizationMode_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetLocalizationMode_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetLocalizationMode_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetLocalizationMode_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/SetLocalizationMode_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetLocalizationMode_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetLocalizationMode_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__srv__SetLocalizationMode_Response__init(msg: *mut SetLocalizationMode_Response) -> bool;
    fn agt_interfaces__srv__SetLocalizationMode_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Response>, size: usize) -> bool;
    fn agt_interfaces__srv__SetLocalizationMode_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Response>);
    fn agt_interfaces__srv__SetLocalizationMode_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetLocalizationMode_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetLocalizationMode_Response>) -> bool;
}

// Corresponds to agt_interfaces__srv__SetLocalizationMode_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetLocalizationMode_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub attempts: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetLocalizationMode_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__srv__SetLocalizationMode_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__srv__SetLocalizationMode_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetLocalizationMode_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__srv__SetLocalizationMode_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetLocalizationMode_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetLocalizationMode_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/srv/SetLocalizationMode_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__srv__SetLocalizationMode_Response() }
  }
}






#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__EvaluateTaskReadiness
#[allow(missing_docs, non_camel_case_types)]
pub struct EvaluateTaskReadiness;

impl rosidl_runtime_rs::Service for EvaluateTaskReadiness {
    type Request = EvaluateTaskReadiness_Request;
    type Response = EvaluateTaskReadiness_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__EvaluateTaskReadiness() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetSystemHealth() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__GetSystemHealth
#[allow(missing_docs, non_camel_case_types)]
pub struct GetSystemHealth;

impl rosidl_runtime_rs::Service for GetSystemHealth {
    type Request = GetSystemHealth_Request;
    type Response = GetSystemHealth_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetSystemHealth() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetRobotState() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__GetRobotState
#[allow(missing_docs, non_camel_case_types)]
pub struct GetRobotState;

impl rosidl_runtime_rs::Service for GetRobotState {
    type Request = GetRobotState_Request;
    type Response = GetRobotState_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetRobotState() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__SetMissionRunState() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__SetMissionRunState
#[allow(missing_docs, non_camel_case_types)]
pub struct SetMissionRunState;

impl rosidl_runtime_rs::Service for SetMissionRunState {
    type Request = SetMissionRunState_Request;
    type Response = SetMissionRunState_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__SetMissionRunState() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ActivateMapVersion() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ActivateMapVersion
#[allow(missing_docs, non_camel_case_types)]
pub struct ActivateMapVersion;

impl rosidl_runtime_rs::Service for ActivateMapVersion {
    type Request = ActivateMapVersion_Request;
    type Response = ActivateMapVersion_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ActivateMapVersion() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListMapVersions() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ListMapVersions
#[allow(missing_docs, non_camel_case_types)]
pub struct ListMapVersions;

impl rosidl_runtime_rs::Service for ListMapVersions {
    type Request = ListMapVersions_Request;
    type Response = ListMapVersions_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListMapVersions() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ManageMapVersion() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ManageMapVersion
#[allow(missing_docs, non_camel_case_types)]
pub struct ManageMapVersion;

impl rosidl_runtime_rs::Service for ManageMapVersion {
    type Request = ManageMapVersion_Request;
    type Response = ManageMapVersion_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ManageMapVersion() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListTaskGroups() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ListTaskGroups
#[allow(missing_docs, non_camel_case_types)]
pub struct ListTaskGroups;

impl rosidl_runtime_rs::Service for ListTaskGroups {
    type Request = ListTaskGroups_Request;
    type Response = ListTaskGroups_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListTaskGroups() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetTaskGroup() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__GetTaskGroup
#[allow(missing_docs, non_camel_case_types)]
pub struct GetTaskGroup;

impl rosidl_runtime_rs::Service for GetTaskGroup {
    type Request = GetTaskGroup_Request;
    type Response = GetTaskGroup_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetTaskGroup() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__PutTaskGroup() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__PutTaskGroup
#[allow(missing_docs, non_camel_case_types)]
pub struct PutTaskGroup;

impl rosidl_runtime_rs::Service for PutTaskGroup {
    type Request = PutTaskGroup_Request;
    type Response = PutTaskGroup_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__PutTaskGroup() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ArchiveTaskGroup
#[allow(missing_docs, non_camel_case_types)]
pub struct ArchiveTaskGroup;

impl rosidl_runtime_rs::Service for ArchiveTaskGroup {
    type Request = ArchiveTaskGroup_Request;
    type Response = ArchiveTaskGroup_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ArchiveTaskGroup() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetNavigationSession() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__GetNavigationSession
#[allow(missing_docs, non_camel_case_types)]
pub struct GetNavigationSession;

impl rosidl_runtime_rs::Service for GetNavigationSession {
    type Request = GetNavigationSession_Request;
    type Response = GetNavigationSession_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__GetNavigationSession() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListBagSessions() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ListBagSessions
#[allow(missing_docs, non_camel_case_types)]
pub struct ListBagSessions;

impl rosidl_runtime_rs::Service for ListBagSessions {
    type Request = ListBagSessions_Request;
    type Response = ListBagSessions_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListBagSessions() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListExperiments() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ListExperiments
#[allow(missing_docs, non_camel_case_types)]
pub struct ListExperiments;

impl rosidl_runtime_rs::Service for ListExperiments {
    type Request = ListExperiments_Request;
    type Response = ListExperiments_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ListExperiments() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ManageBagSession() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__ManageBagSession
#[allow(missing_docs, non_camel_case_types)]
pub struct ManageBagSession;

impl rosidl_runtime_rs::Service for ManageBagSession {
    type Request = ManageBagSession_Request;
    type Response = ManageBagSession_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__ManageBagSession() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__SetLocalizationMode() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__srv__SetLocalizationMode
#[allow(missing_docs, non_camel_case_types)]
pub struct SetLocalizationMode;

impl rosidl_runtime_rs::Service for SetLocalizationMode {
    type Request = SetLocalizationMode_Request;
    type Response = SetLocalizationMode_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__srv__SetLocalizationMode() }
    }
}


