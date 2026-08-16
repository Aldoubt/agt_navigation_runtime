#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__ComponentHealth() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__ComponentHealth__init(msg: *mut ComponentHealth) -> bool;
    fn agt_interfaces__msg__ComponentHealth__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ComponentHealth>, size: usize) -> bool;
    fn agt_interfaces__msg__ComponentHealth__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ComponentHealth>);
    fn agt_interfaces__msg__ComponentHealth__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ComponentHealth>, out_seq: *mut rosidl_runtime_rs::Sequence<ComponentHealth>) -> bool;
}

// Corresponds to agt_interfaces__msg__ComponentHealth
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Machine-readable health result for one configured component.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ComponentHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub component_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub display_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub required: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub present: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub observed_rate_hz: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message_age_sec: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message_count: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missing_topics: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missing_frames: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missing_nodes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub lifecycle_failures: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub condition_failures: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warnings: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub errors: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detail: rosidl_runtime_rs::String,

}

impl ComponentHealth {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_OK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_WARN: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ERROR: u8 = 3;

}


impl Default for ComponentHealth {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__ComponentHealth__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__ComponentHealth__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ComponentHealth {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ComponentHealth__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ComponentHealth__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ComponentHealth__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ComponentHealth {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ComponentHealth where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/ComponentHealth";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__ComponentHealth() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__LocalizationStatus() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__LocalizationStatus__init(msg: *mut LocalizationStatus) -> bool;
    fn agt_interfaces__msg__LocalizationStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocalizationStatus>, size: usize) -> bool;
    fn agt_interfaces__msg__LocalizationStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocalizationStatus>);
    fn agt_interfaces__msg__LocalizationStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocalizationStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<LocalizationStatus>) -> bool;
}

// Corresponds to agt_interfaces__msg__LocalizationStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Machine-readable global localization state. The string status topic remains
/// a human-facing compatibility channel and is not part of the control contract.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocalizationStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose_valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub has_converged: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ambiguous_result: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status_stale: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub backend: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_hash: rosidl_runtime_rs::String,

    /// 0 means no accepted GlobalCorrectionManager correction (or relocalization evidence).
    /// >0 is the accepted map->odom correction generation in canonical localization status.
    pub correction_generation: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub global_pose: geometry_msgs::msg::rmw::PoseWithCovarianceStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fitness_score: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub overlap_ratio: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub inlier_ratio: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ambiguity_score: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub translation_innovation: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_innovation: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub runtime_ms: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tested_candidates: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_candidates: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub consecutive_successes: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub consecutive_failures: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl LocalizationStatus {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNINITIALIZED: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_SEARCHING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_VERIFYING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_TRACKING: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_DEGRADED: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RECOVERING: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_LOST: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ERROR: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_NOT_READY: u16 = 100;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_SCAN_TOO_SMALL: u16 = 101;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_BACKEND_FAILED: u16 = 102;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_FITNESS_REJECTED: u16 = 103;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_INITIAL_GUESS: u16 = 104;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_REQUEST: u16 = 105;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_TIMEOUT: u16 = 106;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CANCELED: u16 = 107;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_AMBIGUOUS_RESULT: u16 = 108;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_STALE_STATUS: u16 = 109;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_TF_UNAVAILABLE: u16 = 110;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_HASH_MISMATCH: u16 = 111;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NO_CANDIDATES: u16 = 112;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_STALE_SCAN: u16 = 113;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_SCAN_TIMESTAMP: u16 = 114;

}


impl Default for LocalizationStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__LocalizationStatus__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__LocalizationStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocalizationStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__LocalizationStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__LocalizationStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__LocalizationStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocalizationStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocalizationStatus where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/LocalizationStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__LocalizationStatus() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MissionStatus() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__MissionStatus__init(msg: *mut MissionStatus) -> bool;
    fn agt_interfaces__msg__MissionStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MissionStatus>, size: usize) -> bool;
    fn agt_interfaces__msg__MissionStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MissionStatus>);
    fn agt_interfaces__msg__MissionStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MissionStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<MissionStatus>) -> bool;
}

// Corresponds to agt_interfaces__msg__MissionStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Authoritative status for one finite sequential mission.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MissionStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_manifest_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_step_index: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_steps: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_step_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_step_type: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_waypoint: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub step_elapsed_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub step_remaining_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl MissionStatus {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_IDLE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_VALIDATING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RUNNING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_WAITING_DURATION: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_WAITING_EVENT: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_PAUSING: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_PAUSED: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RESUMING: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_CANCELING: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_SUCCEEDED: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_FAILED: u8 = 10;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_CANCELED: u8 = 11;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_INTERRUPTED: u8 = 12;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STEP_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STEP_WAYPOINT_TASK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STEP_WAIT_DURATION: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STEP_WAIT_EVENT: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_NONE: u16 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INVALID_MISSION: u16 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_MAP_MISMATCH: u16 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_READINESS_LOST: u16 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_LOCALIZATION_LOST: u16 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CHILD_REJECTED: u16 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CHILD_FAILED: u16 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_EVENT_TIMEOUT: u16 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_CANCELED: u16 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_RESUME_BLOCKED: u16 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR_INTERNAL: u16 = 255;

}


impl Default for MissionStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__MissionStatus__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__MissionStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MissionStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MissionStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MissionStatus where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/MissionStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MissionStatus() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MissionEvent() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__MissionEvent__init(msg: *mut MissionEvent) -> bool;
    fn agt_interfaces__msg__MissionEvent__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MissionEvent>, size: usize) -> bool;
    fn agt_interfaces__msg__MissionEvent__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MissionEvent>);
    fn agt_interfaces__msg__MissionEvent__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MissionEvent>, out_seq: *mut rosidl_runtime_rs::Sequence<MissionEvent>) -> bool;
}

// Corresponds to agt_interfaces__msg__MissionEvent
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Timestamped external event consumed by finite WAIT_EVENT mission steps.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MissionEvent {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub event_type: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub correlation_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: rosidl_runtime_rs::String,

    /// Extension data only. Core event identity is represented by typed fields above.
    pub metadata_json: rosidl_runtime_rs::String,

}



impl Default for MissionEvent {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__MissionEvent__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__MissionEvent__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MissionEvent {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionEvent__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionEvent__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MissionEvent__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MissionEvent {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MissionEvent where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/MissionEvent";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MissionEvent() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MapVersionSummary() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__MapVersionSummary__init(msg: *mut MapVersionSummary) -> bool;
    fn agt_interfaces__msg__MapVersionSummary__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<MapVersionSummary>, size: usize) -> bool;
    fn agt_interfaces__msg__MapVersionSummary__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<MapVersionSummary>);
    fn agt_interfaces__msg__MapVersionSummary__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<MapVersionSummary>, out_seq: *mut rosidl_runtime_rs::Sequence<MapVersionSummary>) -> bool;
}

// Corresponds to agt_interfaces__msg__MapVersionSummary
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Manager-owned map identity and validation summary.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MapVersionSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub parent_map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pinned: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub deleted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub valid: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_hash: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub manifest_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_yaml_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_image_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_yaml: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks_directory: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub storage_bytes: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub created_at: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_errors: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_warnings: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}

impl MapVersionSummary {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_DRAFT: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_PROCESSING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_READY: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_INVALID: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ARCHIVED: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_DELETED: u8 = 6;

}


impl Default for MapVersionSummary {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__MapVersionSummary__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__MapVersionSummary__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for MapVersionSummary {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MapVersionSummary__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MapVersionSummary__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__MapVersionSummary__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for MapVersionSummary {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for MapVersionSummary where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/MapVersionSummary";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__MapVersionSummary() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__NavigationSessionStatus() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__NavigationSessionStatus__init(msg: *mut NavigationSessionStatus) -> bool;
    fn agt_interfaces__msg__NavigationSessionStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavigationSessionStatus>, size: usize) -> bool;
    fn agt_interfaces__msg__NavigationSessionStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavigationSessionStatus>);
    fn agt_interfaces__msg__NavigationSessionStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavigationSessionStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<NavigationSessionStatus>) -> bool;
}

// Corresponds to agt_interfaces__msg__NavigationSessionStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Authoritative waypoint-task session state owned by agt_navigation.
/// Published reliable + transient_local on /agt/navigation/session_status.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigationSessionStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: rosidl_runtime_rs::String,


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
    pub task_content_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


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
    pub missed_waypoints: rosidl_runtime_rs::Sequence<u32>,


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
    pub started_at: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub terminal: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,

}

impl NavigationSessionStatus {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_IDLE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_VALIDATING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_REJECTED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ACCEPTED: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RUNNING: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_CANCELING: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_SUCCEEDED: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_FAILED: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_CANCELED: u8 = 8;

}


impl Default for NavigationSessionStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__NavigationSessionStatus__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__NavigationSessionStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavigationSessionStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__NavigationSessionStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__NavigationSessionStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__NavigationSessionStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavigationSessionStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavigationSessionStatus where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/NavigationSessionStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__NavigationSessionStatus() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__BagSessionSummary() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__BagSessionSummary__init(msg: *mut BagSessionSummary) -> bool;
    fn agt_interfaces__msg__BagSessionSummary__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BagSessionSummary>, size: usize) -> bool;
    fn agt_interfaces__msg__BagSessionSummary__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BagSessionSummary>);
    fn agt_interfaces__msg__BagSessionSummary__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BagSessionSummary>, out_seq: *mut rosidl_runtime_rs::Sequence<BagSessionSummary>) -> bool;
}

// Corresponds to agt_interfaces__msg__BagSessionSummary
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Manager-owned rosbag or experiment session summary.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BagSessionSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub relative_uri: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub complete: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub simulation: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub playback_rate: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub storage_bytes: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub started_at: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub process_id: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message_count: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub storage_identifier: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mapping_input_ready: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub contains_mapping_outputs: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub contains_navigation_outputs: bool,

}

impl BagSessionSummary {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_IDLE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RECORDING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_PLAYING: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_COMPLETED: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_INTERRUPTED: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ERROR: u8 = 6;

}


impl Default for BagSessionSummary {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__BagSessionSummary__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__BagSessionSummary__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BagSessionSummary {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__BagSessionSummary__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__BagSessionSummary__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__BagSessionSummary__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BagSessionSummary {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BagSessionSummary where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/BagSessionSummary";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__BagSessionSummary() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__ExperimentSummary() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__ExperimentSummary__init(msg: *mut ExperimentSummary) -> bool;
    fn agt_interfaces__msg__ExperimentSummary__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ExperimentSummary>, size: usize) -> bool;
    fn agt_interfaces__msg__ExperimentSummary__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ExperimentSummary>);
    fn agt_interfaces__msg__ExperimentSummary__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ExperimentSummary>, out_seq: *mut rosidl_runtime_rs::Sequence<ExperimentSummary>) -> bool;
}

// Corresponds to agt_interfaces__msg__ExperimentSummary
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Manager-owned experiment lifecycle summary.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExperimentSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub title: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub created_at: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_time: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub end_time: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_hash: rosidl_runtime_rs::String,


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
    pub launch_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result_status: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config_snapshot_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl ExperimentSummary {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_CREATED: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_RUNNING: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_COMPLETED: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_INTERRUPTED: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_INVALID: u8 = 5;

}


impl Default for ExperimentSummary {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__ExperimentSummary__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__ExperimentSummary__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ExperimentSummary {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ExperimentSummary__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ExperimentSummary__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__ExperimentSummary__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ExperimentSummary {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ExperimentSummary where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/ExperimentSummary";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__ExperimentSummary() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__RobotState() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__RobotState__init(msg: *mut RobotState) -> bool;
    fn agt_interfaces__msg__RobotState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RobotState>, size: usize) -> bool;
    fn agt_interfaces__msg__RobotState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RobotState>);
    fn agt_interfaces__msg__RobotState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RobotState>, out_seq: *mut rosidl_runtime_rs::Sequence<RobotState>) -> bool;
}

// Corresponds to agt_interfaces__msg__RobotState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Unified read model for interchangeable operator clients.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RobotState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub system_mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_profile: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub managed_process_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub running_process_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub system_health_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub system_health_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub system_health: super::super::msg::rmw::SystemHealth,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness: super::super::msg::rmw::TaskReadiness,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map: super::super::msg::rmw::MapVersionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization: super::super::msg::rmw::LocalizationStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission: super::super::msg::rmw::MissionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub nav2_state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub nav2_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub safety_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub safety_motion_enabled: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub emergency_stop: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub estop_latched: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_ready: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub safety_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub chassis_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub chassis_connected: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub chassis_control_mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub chassis_status_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub chassis_odometry_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_session: super::super::msg::rmw::BagSessionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}

impl RobotState {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_IDLE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_SENSOR_ONLY: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_MAPPING: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_LOCALIZATION_DEBUG: u8 = 4;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_NAVIGATION: u8 = 5;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MODE_ERROR: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const NAV2_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const NAV2_INACTIVE: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const NAV2_ACTIVE: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const NAV2_ERROR: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CHASSIS_MODE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CHASSIS_MODE_MONITOR: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const CHASSIS_MODE_CONTROL: u8 = 2;

}


impl Default for RobotState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__RobotState__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__RobotState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RobotState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__RobotState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__RobotState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__RobotState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RobotState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RobotState where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/RobotState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__RobotState() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SemanticWaypoint() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__SemanticWaypoint__init(msg: *mut SemanticWaypoint) -> bool;
    fn agt_interfaces__msg__SemanticWaypoint__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypoint>, size: usize) -> bool;
    fn agt_interfaces__msg__SemanticWaypoint__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypoint>);
    fn agt_interfaces__msg__SemanticWaypoint__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SemanticWaypoint>, out_seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypoint>) -> bool;
}

// Corresponds to agt_interfaces__msg__SemanticWaypoint
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Named semantic navigation anchor stored in the map frame.
/// This is map semantics, not an execution sequence.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SemanticWaypoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub role: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::rmw::Pose,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_tolerance: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_tolerance: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub preferred_speed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tags: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enabled: bool,

}



impl Default for SemanticWaypoint {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__SemanticWaypoint__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__SemanticWaypoint__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SemanticWaypoint {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypoint__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypoint__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypoint__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SemanticWaypoint {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SemanticWaypoint where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/SemanticWaypoint";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SemanticWaypoint() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SemanticWaypointArray() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__SemanticWaypointArray__init(msg: *mut SemanticWaypointArray) -> bool;
    fn agt_interfaces__msg__SemanticWaypointArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypointArray>, size: usize) -> bool;
    fn agt_interfaces__msg__SemanticWaypointArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypointArray>);
    fn agt_interfaces__msg__SemanticWaypointArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SemanticWaypointArray>, out_seq: *mut rosidl_runtime_rs::Sequence<SemanticWaypointArray>) -> bool;
}

// Corresponds to agt_interfaces__msg__SemanticWaypointArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Versioned semantic waypoint library for one map.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SemanticWaypointArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub base_map_sha256: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub waypoints: rosidl_runtime_rs::Sequence<super::super::msg::rmw::SemanticWaypoint>,

}



impl Default for SemanticWaypointArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__SemanticWaypointArray__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__SemanticWaypointArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SemanticWaypointArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypointArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypointArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SemanticWaypointArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SemanticWaypointArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SemanticWaypointArray where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/SemanticWaypointArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SemanticWaypointArray() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SystemHealth() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__SystemHealth__init(msg: *mut SystemHealth) -> bool;
    fn agt_interfaces__msg__SystemHealth__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SystemHealth>, size: usize) -> bool;
    fn agt_interfaces__msg__SystemHealth__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SystemHealth>);
    fn agt_interfaces__msg__SystemHealth__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SystemHealth>, out_seq: *mut rosidl_runtime_rs::Sequence<SystemHealth>) -> bool;
}

// Corresponds to agt_interfaces__msg__SystemHealth
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Snapshot of all configured component health results.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SystemHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub overall_state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub components: rosidl_runtime_rs::Sequence<super::super::msg::rmw::ComponentHealth>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}

impl SystemHealth {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_OK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_WARN: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const STATE_ERROR: u8 = 3;

}


impl Default for SystemHealth {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__SystemHealth__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__SystemHealth__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SystemHealth {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SystemHealth__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SystemHealth__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__SystemHealth__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SystemHealth {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SystemHealth where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/SystemHealth";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__SystemHealth() }
  }
}


#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__TaskReadiness() -> *const std::ffi::c_void;
}

#[link(name = "agt_interfaces__rosidl_generator_c")]
extern "C" {
    fn agt_interfaces__msg__TaskReadiness__init(msg: *mut TaskReadiness) -> bool;
    fn agt_interfaces__msg__TaskReadiness__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TaskReadiness>, size: usize) -> bool;
    fn agt_interfaces__msg__TaskReadiness__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TaskReadiness>);
    fn agt_interfaces__msg__TaskReadiness__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TaskReadiness>, out_seq: *mut rosidl_runtime_rs::Sequence<TaskReadiness>) -> bool;
}

// Corresponds to agt_interfaces__msg__TaskReadiness
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Shared fail-closed task dispatch decision.

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskReadiness {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ready: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_mode: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_state: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub health_revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_codes: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_messages: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,

}



impl Default for TaskReadiness {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agt_interfaces__msg__TaskReadiness__init(&mut msg as *mut _) {
        panic!("Call to agt_interfaces__msg__TaskReadiness__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TaskReadiness {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__TaskReadiness__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__TaskReadiness__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agt_interfaces__msg__TaskReadiness__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TaskReadiness {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TaskReadiness where Self: Sized {
  const TYPE_NAME: &'static str = "agt_interfaces/msg/TaskReadiness";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agt_interfaces__msg__TaskReadiness() }
  }
}


