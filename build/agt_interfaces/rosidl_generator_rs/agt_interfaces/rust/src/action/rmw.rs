
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_Goal__init(msg: *mut Relocalize_Goal) -> bool;
    fn agt_interfaces__action__Relocalize_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Goal>);
    fn agt_interfaces__action__Relocalize_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub use_initial_pose: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub initial_pose: geometry_msgs::msg::rmw::PoseWithCovarianceStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub use_last_valid_pose: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub use_configured_candidates: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub use_external_coarse_pose: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub max_candidates: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub publish_debug: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub timeout_s: f64,

}

impl Relocalize_Goal {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_AUTO_SEARCH: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_SINGLE_INITIAL_POSE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_LOCAL_CANDIDATES: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_EXTERNAL_COARSE_POSE: u8 = 3;

}


impl Default for Relocalize_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_Result__init(msg: *mut Relocalize_Result) -> bool;
    fn agt_interfaces__action__Relocalize_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Result>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Result>);
    fn agt_interfaces__action__Relocalize_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_pose: geometry_msgs::msg::rmw::PoseWithCovarianceStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_status: super::super::msg::rmw::LocalizationStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failure_reason: rosidl_runtime_rs::String,

}



impl Default for Relocalize_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_Feedback__init(msg: *mut Relocalize_Feedback) -> bool;
    fn agt_interfaces__action__Relocalize_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Feedback>);
    fn agt_interfaces__action__Relocalize_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_candidates: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tested_candidates: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub best_fitness_score: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub best_candidate_source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub elapsed_s: f64,

}



impl Default for Relocalize_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_FeedbackMessage__init(msg: *mut Relocalize_FeedbackMessage) -> bool;
    fn agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_FeedbackMessage>);
    fn agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::Relocalize_Feedback,

}



impl Default for Relocalize_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_Goal__init(msg: *mut ChangeSystemMode_Goal) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Goal>);
    fn agt_interfaces__action__ChangeSystemMode_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_keys: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_values: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub wait_for_health: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub startup_timeout_s: f64,

}

impl ChangeSystemMode_Goal {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_IDLE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_SENSOR_ONLY: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MAPPING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_LOCALIZATION_DEBUG: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_NAVIGATION: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_ERROR: u8 = 5;

}


impl Default for ChangeSystemMode_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_Result__init(msg: *mut ChangeSystemMode_Result) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Result>);
    fn agt_interfaces__action__ChangeSystemMode_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_mode: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub process_ids: rosidl_runtime_rs::Sequence<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub log_paths: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ChangeSystemMode_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_Feedback__init(msg: *mut ChangeSystemMode_Feedback) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Feedback>);
    fn agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ChangeSystemMode_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_FeedbackMessage__init(msg: *mut ChangeSystemMode_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_FeedbackMessage>);
    fn agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ChangeSystemMode_Feedback,

}



impl Default for ChangeSystemMode_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_Goal__init(msg: *mut ManageMappingSession_Goal) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Goal>);
    fn agt_interfaces__action__ManageMappingSession_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,

    /// Required for START. A safe portable identifier, not a filesystem path.
    pub map_id: rosidl_runtime_rs::String,

    /// Required for operations on an existing session. STATUS may leave it empty to
    /// query the newest managed session.
    pub session_id: rosidl_runtime_rs::String,

    /// START-only mapping profile arguments. The server injects and owns runtime_dir,
    /// map_name, mapping_output_dir, record_bag, and bag_profile.
    pub argument_keys: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_values: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

    /// COMMIT-only. Activation still performs the full map-registry validation.
    pub activate_after_commit: bool,

    /// Bounded wait for map save, normal shutdown, PCD readiness, and offline candidate build.
    pub timeout_s: f64,

}

impl ManageMappingSession_Goal {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_STATUS: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_START: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_FINALIZE_CAPTURE: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_COMMIT: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OP_DISCARD: u8 = 4;

}


impl Default for ManageMappingSession_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_Result__init(msg: *mut ManageMappingSession_Result) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Result>);
    fn agt_interfaces__action__ManageMappingSession_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_file: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_yaml: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_image: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_directory: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub registered_map_yaml: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks_directory: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ManageMappingSession_Result {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_SERVER_UNAVAILABLE: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_START_FAILED: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_GRID_SAVE_FAILED: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_STOP_FAILED: u16 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_ASSET_TIMEOUT: u16 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_COMMIT_FAILED: u16 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_STATE: u16 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NOT_FOUND: u16 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ManageMappingSession_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_Feedback__init(msg: *mut ManageMappingSession_Feedback) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Feedback>);
    fn agt_interfaces__action__ManageMappingSession_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ManageMappingSession_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(msg: *mut ManageMappingSession_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_FeedbackMessage>);
    fn agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ManageMappingSession_Feedback,

}



impl Default for ManageMappingSession_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_Goal__init(msg: *mut ExecuteCoverageTask_Goal) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Goal>);
    fn agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub semantic_map_uri: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub field_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub planning_mode: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub controller_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub allow_repair: bool,

}



impl Default for ExecuteCoverageTask_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_Result__init(msg: *mut ExecuteCoverageTask_Result) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Result>);
    fn agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage_rate: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub overlap_rate: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub executed_length: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub repaired_segment_count: u32,

}



impl Default for ExecuteCoverageTask_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_Feedback__init(msg: *mut ExecuteCoverageTask_Feedback) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Feedback>);
    fn agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_stage: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_swath_index: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_swaths: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_remaining: f64,

}



impl Default for ExecuteCoverageTask_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init(msg: *mut ExecuteCoverageTask_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_FeedbackMessage>);
    fn agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ExecuteCoverageTask_Feedback,

}



impl Default for ExecuteCoverageTask_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_Goal__init(msg: *mut ExecuteWaypointTask_Goal) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Goal>);
    fn agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_Goal {

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
    pub task_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub expected_content_sha256: rosidl_runtime_rs::String,

    /// A loop count is always finite. 1 executes the task once.
    pub loop_count: u32,

    /// Idempotency key generated by the client for a start request.
    pub client_request_id: rosidl_runtime_rs::String,

    /// Deprecated compatibility inputs. Disabled by default on the server and limited
    /// to same-machine CLI/debug when explicitly enabled.
    pub task_file: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::PoseStamped>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_: bool,

}



impl Default for ExecuteWaypointTask_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_Result__init(msg: *mut ExecuteWaypointTask_Result) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Result>);
    fn agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: rosidl_runtime_rs::String,


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
    pub missed_waypoints: rosidl_runtime_rs::Sequence<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_status: super::super::msg::rmw::NavigationSessionStatus,

}



impl Default for ExecuteWaypointTask_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_Feedback__init(msg: *mut ExecuteWaypointTask_Feedback) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Feedback>);
    fn agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_index: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_waypoint: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: super::super::msg::rmw::NavigationSessionStatus,

}



impl Default for ExecuteWaypointTask_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__init(msg: *mut ExecuteWaypointTask_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_FeedbackMessage>);
    fn agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ExecuteWaypointTask_Feedback,

}



impl Default for ExecuteWaypointTask_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_Goal__init(msg: *mut OptimizeMap_Goal) -> bool;
    fn agt_interfaces__action__OptimizeMap_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Goal>);
    fn agt_interfaces__action__OptimizeMap_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub source_map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_experiment_ids: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub backend: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub options_yaml: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub activate_on_success: bool,

}



impl Default for OptimizeMap_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_Result__init(msg: *mut OptimizeMap_Result) -> bool;
    fn agt_interfaces__action__OptimizeMap_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Result>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Result>);
    fn agt_interfaces__action__OptimizeMap_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub new_map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trajectory_path: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub optimized_pcd_path: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub report_path: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for OptimizeMap_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_Feedback__init(msg: *mut OptimizeMap_Feedback) -> bool;
    fn agt_interfaces__action__OptimizeMap_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Feedback>);
    fn agt_interfaces__action__OptimizeMap_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for OptimizeMap_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_FeedbackMessage__init(msg: *mut OptimizeMap_FeedbackMessage) -> bool;
    fn agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_FeedbackMessage>);
    fn agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::OptimizeMap_Feedback,

}



impl Default for OptimizeMap_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_Goal__init(msg: *mut ExecuteMission_Goal) -> bool;
    fn agt_interfaces__action__ExecuteMission_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Goal>);
    fn agt_interfaces__action__ExecuteMission_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: rosidl_runtime_rs::String,

    /// Optional optimistic-lock check. Empty accepts the stored content hash.
    pub expected_content_sha256: rosidl_runtime_rs::String,

}



impl Default for ExecuteMission_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_Result__init(msg: *mut ExecuteMission_Result) -> bool;
    fn agt_interfaces__action__ExecuteMission_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Result>);
    fn agt_interfaces__action__ExecuteMission_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_status: super::super::msg::rmw::MissionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub audit_log_uri: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for ExecuteMission_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_Feedback__init(msg: *mut ExecuteMission_Feedback) -> bool;
    fn agt_interfaces__action__ExecuteMission_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Feedback>);
    fn agt_interfaces__action__ExecuteMission_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: super::super::msg::rmw::MissionStatus,

}



impl Default for ExecuteMission_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_FeedbackMessage__init(msg: *mut ExecuteMission_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_FeedbackMessage>);
    fn agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ExecuteMission_Feedback,

}



impl Default for ExecuteMission_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_FeedbackMessage() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Goal() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_Goal__init(msg: *mut ExecuteBehaviorTree_Goal) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Goal>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Goal>);
    fn agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Goal>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tree_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub execution_id: rosidl_runtime_rs::String,


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
    pub task_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub expected_content_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,

}

impl ExecuteBehaviorTree_Goal {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_TREE_NOT_ALLOWED: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_TREE_FAILED: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CANCELED: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for ExecuteBehaviorTree_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_Goal__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Goal() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Result() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_Result__init(msg: *mut ExecuteBehaviorTree_Result) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Result>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Result>);
    fn agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Result>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_message: rosidl_runtime_rs::String,

}



impl Default for ExecuteBehaviorTree_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_Result__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_Result where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Result() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(msg: *mut ExecuteBehaviorTree_Feedback) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Feedback>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Feedback>);
    fn agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_Feedback>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tree_state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_node: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_index: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_waypoint: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,

}



impl Default for ExecuteBehaviorTree_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_Feedback__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_Feedback() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(msg: *mut ExecuteBehaviorTree_FeedbackMessage) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_FeedbackMessage>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_FeedbackMessage>);
    fn agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_FeedbackMessage>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::ExecuteBehaviorTree_Feedback,

}



impl Default for ExecuteBehaviorTree_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage() }
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_SendGoal_Request__init(msg: *mut Relocalize_SendGoal_Request) -> bool;
    fn agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Request>);
    fn agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::Relocalize_Goal,

}



impl Default for Relocalize_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_SendGoal_Response__init(msg: *mut Relocalize_SendGoal_Response) -> bool;
    fn agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Response>);
    fn agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for Relocalize_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_GetResult_Request__init(msg: *mut Relocalize_GetResult_Request) -> bool;
    fn agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Request>);
    fn agt_interfaces__action__Relocalize_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for Relocalize_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__Relocalize_GetResult_Response__init(msg: *mut Relocalize_GetResult_Response) -> bool;
    fn agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Response>);
    fn agt_interfaces__action__Relocalize_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Relocalize_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<Relocalize_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__Relocalize_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::Relocalize_Result,

}



impl Default for Relocalize_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__Relocalize_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__Relocalize_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Relocalize_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__Relocalize_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Relocalize_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Relocalize_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/Relocalize_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__Relocalize_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Request__init(msg: *mut ChangeSystemMode_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Request>);
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ChangeSystemMode_Goal,

}



impl Default for ChangeSystemMode_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Response__init(msg: *mut ChangeSystemMode_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Response>);
    fn agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ChangeSystemMode_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Request__init(msg: *mut ChangeSystemMode_GetResult_Request) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Request>);
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ChangeSystemMode_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Response__init(msg: *mut ChangeSystemMode_GetResult_Response) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Response>);
    fn agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ChangeSystemMode_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ChangeSystemMode_Result,

}



impl Default for ChangeSystemMode_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ChangeSystemMode_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ChangeSystemMode_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChangeSystemMode_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ChangeSystemMode_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChangeSystemMode_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ChangeSystemMode_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(msg: *mut ManageMappingSession_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Request>);
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ManageMappingSession_Goal,

}



impl Default for ManageMappingSession_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(msg: *mut ManageMappingSession_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Response>);
    fn agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ManageMappingSession_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_GetResult_Request__init(msg: *mut ManageMappingSession_GetResult_Request) -> bool;
    fn agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Request>);
    fn agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ManageMappingSession_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ManageMappingSession_GetResult_Response__init(msg: *mut ManageMappingSession_GetResult_Response) -> bool;
    fn agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Response>);
    fn agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ManageMappingSession_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ManageMappingSession_Result,

}



impl Default for ManageMappingSession_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ManageMappingSession_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ManageMappingSession_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ManageMappingSession_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ManageMappingSession_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ManageMappingSession_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ManageMappingSession_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init(msg: *mut ExecuteCoverageTask_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Request>);
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ExecuteCoverageTask_Goal,

}



impl Default for ExecuteCoverageTask_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init(msg: *mut ExecuteCoverageTask_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Response>);
    fn agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ExecuteCoverageTask_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init(msg: *mut ExecuteCoverageTask_GetResult_Request) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Request>);
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ExecuteCoverageTask_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init(msg: *mut ExecuteCoverageTask_GetResult_Response) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Response>);
    fn agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteCoverageTask_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ExecuteCoverageTask_Result,

}



impl Default for ExecuteCoverageTask_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteCoverageTask_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteCoverageTask_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteCoverageTask_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteCoverageTask_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__init(msg: *mut ExecuteWaypointTask_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Request>);
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ExecuteWaypointTask_Goal,

}



impl Default for ExecuteWaypointTask_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__init(msg: *mut ExecuteWaypointTask_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Response>);
    fn agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ExecuteWaypointTask_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__init(msg: *mut ExecuteWaypointTask_GetResult_Request) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Request>);
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ExecuteWaypointTask_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__init(msg: *mut ExecuteWaypointTask_GetResult_Response) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Response>);
    fn agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteWaypointTask_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ExecuteWaypointTask_Result,

}



impl Default for ExecuteWaypointTask_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteWaypointTask_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteWaypointTask_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteWaypointTask_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteWaypointTask_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_SendGoal_Request__init(msg: *mut OptimizeMap_SendGoal_Request) -> bool;
    fn agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Request>);
    fn agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::OptimizeMap_Goal,

}



impl Default for OptimizeMap_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_SendGoal_Response__init(msg: *mut OptimizeMap_SendGoal_Response) -> bool;
    fn agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Response>);
    fn agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for OptimizeMap_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_GetResult_Request__init(msg: *mut OptimizeMap_GetResult_Request) -> bool;
    fn agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Request>);
    fn agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for OptimizeMap_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__OptimizeMap_GetResult_Response__init(msg: *mut OptimizeMap_GetResult_Response) -> bool;
    fn agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Response>);
    fn agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<OptimizeMap_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__OptimizeMap_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::OptimizeMap_Result,

}



impl Default for OptimizeMap_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__OptimizeMap_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__OptimizeMap_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OptimizeMap_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__OptimizeMap_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OptimizeMap_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/OptimizeMap_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_SendGoal_Request__init(msg: *mut ExecuteMission_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Request>);
    fn agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ExecuteMission_Goal,

}



impl Default for ExecuteMission_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_SendGoal_Response__init(msg: *mut ExecuteMission_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Response>);
    fn agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ExecuteMission_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_GetResult_Request__init(msg: *mut ExecuteMission_GetResult_Request) -> bool;
    fn agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Request>);
    fn agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ExecuteMission_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteMission_GetResult_Response__init(msg: *mut ExecuteMission_GetResult_Response) -> bool;
    fn agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Response>);
    fn agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteMission_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteMission_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ExecuteMission_Result,

}



impl Default for ExecuteMission_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteMission_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteMission_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteMission_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteMission_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteMission_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteMission_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(msg: *mut ExecuteBehaviorTree_SendGoal_Request) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Request>);
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::ExecuteBehaviorTree_Goal,

}



impl Default for ExecuteBehaviorTree_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(msg: *mut ExecuteBehaviorTree_SendGoal_Response) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Response>);
    fn agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_SendGoal_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for ExecuteBehaviorTree_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(msg: *mut ExecuteBehaviorTree_GetResult_Request) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Request>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Request>);
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Request>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for ExecuteBehaviorTree_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(msg: *mut ExecuteBehaviorTree_GetResult_Response) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Response>, size: usize) -> bool;
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Response>);
    fn agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<ExecuteBehaviorTree_GetResult_Response>) -> bool;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::ExecuteBehaviorTree_Result,

}



impl Default for ExecuteBehaviorTree_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExecuteBehaviorTree_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExecuteBehaviorTree_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/action/ExecuteBehaviorTree_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response() }
  }
}






#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__Relocalize_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__Relocalize_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct Relocalize_SendGoal;

impl rosidl_runtime_rs::Service for Relocalize_SendGoal {
    type Request = Relocalize_SendGoal_Request;
    type Response = Relocalize_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__Relocalize_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__Relocalize_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__Relocalize_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct Relocalize_GetResult;

impl rosidl_runtime_rs::Service for Relocalize_GetResult {
    type Request = Relocalize_GetResult_Request;
    type Response = Relocalize_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__Relocalize_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ChangeSystemMode_SendGoal;

impl rosidl_runtime_rs::Service for ChangeSystemMode_SendGoal {
    type Request = ChangeSystemMode_SendGoal_Request;
    type Response = ChangeSystemMode_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ChangeSystemMode_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ChangeSystemMode_GetResult;

impl rosidl_runtime_rs::Service for ChangeSystemMode_GetResult {
    type Request = ChangeSystemMode_GetResult_Request;
    type Response = ChangeSystemMode_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ChangeSystemMode_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ManageMappingSession_SendGoal;

impl rosidl_runtime_rs::Service for ManageMappingSession_SendGoal {
    type Request = ManageMappingSession_SendGoal_Request;
    type Response = ManageMappingSession_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ManageMappingSession_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ManageMappingSession_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ManageMappingSession_GetResult;

impl rosidl_runtime_rs::Service for ManageMappingSession_GetResult {
    type Request = ManageMappingSession_GetResult_Request;
    type Response = ManageMappingSession_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ManageMappingSession_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteCoverageTask_SendGoal;

impl rosidl_runtime_rs::Service for ExecuteCoverageTask_SendGoal {
    type Request = ExecuteCoverageTask_SendGoal_Request;
    type Response = ExecuteCoverageTask_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteCoverageTask_GetResult;

impl rosidl_runtime_rs::Service for ExecuteCoverageTask_GetResult {
    type Request = ExecuteCoverageTask_GetResult_Request;
    type Response = ExecuteCoverageTask_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteCoverageTask_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteWaypointTask_SendGoal;

impl rosidl_runtime_rs::Service for ExecuteWaypointTask_SendGoal {
    type Request = ExecuteWaypointTask_SendGoal_Request;
    type Response = ExecuteWaypointTask_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteWaypointTask_GetResult;

impl rosidl_runtime_rs::Service for ExecuteWaypointTask_GetResult {
    type Request = ExecuteWaypointTask_GetResult_Request;
    type Response = ExecuteWaypointTask_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteWaypointTask_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__OptimizeMap_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct OptimizeMap_SendGoal;

impl rosidl_runtime_rs::Service for OptimizeMap_SendGoal {
    type Request = OptimizeMap_SendGoal_Request;
    type Response = OptimizeMap_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__OptimizeMap_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__OptimizeMap_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct OptimizeMap_GetResult;

impl rosidl_runtime_rs::Service for OptimizeMap_GetResult {
    type Request = OptimizeMap_GetResult_Request;
    type Response = OptimizeMap_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__OptimizeMap_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteMission_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteMission_SendGoal;

impl rosidl_runtime_rs::Service for ExecuteMission_SendGoal {
    type Request = ExecuteMission_SendGoal_Request;
    type Response = ExecuteMission_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteMission_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteMission_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteMission_GetResult;

impl rosidl_runtime_rs::Service for ExecuteMission_GetResult {
    type Request = ExecuteMission_GetResult_Request;
    type Response = ExecuteMission_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteMission_GetResult() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteBehaviorTree_SendGoal;

impl rosidl_runtime_rs::Service for ExecuteBehaviorTree_SendGoal {
    type Request = ExecuteBehaviorTree_SendGoal_Request;
    type Response = ExecuteBehaviorTree_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_SendGoal() }
    }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteBehaviorTree_GetResult;

impl rosidl_runtime_rs::Service for ExecuteBehaviorTree_GetResult {
    type Request = ExecuteBehaviorTree_GetResult_Request;
    type Response = ExecuteBehaviorTree_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree_GetResult() }
    }
}


