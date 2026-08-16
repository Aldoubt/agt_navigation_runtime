#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to agt_interfaces__msg__ComponentHealth
/// Machine-readable health result for one configured component.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ComponentHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub component_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub display_name: std::string::String,


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
    pub missing_topics: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missing_frames: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missing_nodes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub lifecycle_failures: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub condition_failures: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warnings: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub errors: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detail: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ComponentHealth::default())
  }
}

impl rosidl_runtime_rs::Message for ComponentHealth {
  type RmwMsg = super::msg::rmw::ComponentHealth;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        component_id: msg.component_id.as_str().into(),
        display_name: msg.display_name.as_str().into(),
        state: msg.state,
        required: msg.required,
        present: msg.present,
        observed_rate_hz: msg.observed_rate_hz,
        message_age_sec: msg.message_age_sec,
        message_count: msg.message_count,
        missing_topics: msg.missing_topics
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        missing_frames: msg.missing_frames
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        missing_nodes: msg.missing_nodes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        lifecycle_failures: msg.lifecycle_failures
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        condition_failures: msg.condition_failures
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warnings: msg.warnings
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        errors: msg.errors
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        detail: msg.detail.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        component_id: msg.component_id.as_str().into(),
        display_name: msg.display_name.as_str().into(),
      state: msg.state,
      required: msg.required,
      present: msg.present,
      observed_rate_hz: msg.observed_rate_hz,
      message_age_sec: msg.message_age_sec,
      message_count: msg.message_count,
        missing_topics: msg.missing_topics
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        missing_frames: msg.missing_frames
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        missing_nodes: msg.missing_nodes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        lifecycle_failures: msg.lifecycle_failures
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        condition_failures: msg.condition_failures
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warnings: msg.warnings
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        errors: msg.errors
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        detail: msg.detail.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      component_id: msg.component_id.to_string(),
      display_name: msg.display_name.to_string(),
      state: msg.state,
      required: msg.required,
      present: msg.present,
      observed_rate_hz: msg.observed_rate_hz,
      message_age_sec: msg.message_age_sec,
      message_count: msg.message_count,
      missing_topics: msg.missing_topics
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      missing_frames: msg.missing_frames
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      missing_nodes: msg.missing_nodes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      lifecycle_failures: msg.lifecycle_failures
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      condition_failures: msg.condition_failures
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      warnings: msg.warnings
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      errors: msg.errors
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      detail: msg.detail.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__LocalizationStatus
/// Machine-readable global localization state. The string status topic remains
/// a human-facing compatibility channel and is not part of the control contract.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocalizationStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    pub backend: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_hash: std::string::String,

    /// 0 means no accepted GlobalCorrectionManager correction (or relocalization evidence).
    /// >0 is the accepted map->odom correction generation in canonical localization status.
    pub correction_generation: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub global_pose: geometry_msgs::msg::PoseWithCovarianceStamped,


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
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::LocalizationStatus::default())
  }
}

impl rosidl_runtime_rs::Message for LocalizationStatus {
  type RmwMsg = super::msg::rmw::LocalizationStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        state: msg.state,
        pose_valid: msg.pose_valid,
        localization_accepted: msg.localization_accepted,
        has_converged: msg.has_converged,
        ambiguous_result: msg.ambiguous_result,
        status_stale: msg.status_stale,
        error_code: msg.error_code,
        backend: msg.backend.as_str().into(),
        candidate_source: msg.candidate_source.as_str().into(),
        candidate_id: msg.candidate_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_hash: msg.map_hash.as_str().into(),
        correction_generation: msg.correction_generation,
        global_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Owned(msg.global_pose)).into_owned(),
        fitness_score: msg.fitness_score,
        overlap_ratio: msg.overlap_ratio,
        inlier_ratio: msg.inlier_ratio,
        ambiguity_score: msg.ambiguity_score,
        translation_innovation: msg.translation_innovation,
        yaw_innovation: msg.yaw_innovation,
        runtime_ms: msg.runtime_ms,
        tested_candidates: msg.tested_candidates,
        total_candidates: msg.total_candidates,
        consecutive_successes: msg.consecutive_successes,
        consecutive_failures: msg.consecutive_failures,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      state: msg.state,
      pose_valid: msg.pose_valid,
      localization_accepted: msg.localization_accepted,
      has_converged: msg.has_converged,
      ambiguous_result: msg.ambiguous_result,
      status_stale: msg.status_stale,
      error_code: msg.error_code,
        backend: msg.backend.as_str().into(),
        candidate_source: msg.candidate_source.as_str().into(),
        candidate_id: msg.candidate_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_hash: msg.map_hash.as_str().into(),
      correction_generation: msg.correction_generation,
        global_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.global_pose)).into_owned(),
      fitness_score: msg.fitness_score,
      overlap_ratio: msg.overlap_ratio,
      inlier_ratio: msg.inlier_ratio,
      ambiguity_score: msg.ambiguity_score,
      translation_innovation: msg.translation_innovation,
      yaw_innovation: msg.yaw_innovation,
      runtime_ms: msg.runtime_ms,
      tested_candidates: msg.tested_candidates,
      total_candidates: msg.total_candidates,
      consecutive_successes: msg.consecutive_successes,
      consecutive_failures: msg.consecutive_failures,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      state: msg.state,
      pose_valid: msg.pose_valid,
      localization_accepted: msg.localization_accepted,
      has_converged: msg.has_converged,
      ambiguous_result: msg.ambiguous_result,
      status_stale: msg.status_stale,
      error_code: msg.error_code,
      backend: msg.backend.to_string(),
      candidate_source: msg.candidate_source.to_string(),
      candidate_id: msg.candidate_id.to_string(),
      map_id: msg.map_id.to_string(),
      map_hash: msg.map_hash.to_string(),
      correction_generation: msg.correction_generation,
      global_pose: geometry_msgs::msg::PoseWithCovarianceStamped::from_rmw_message(msg.global_pose),
      fitness_score: msg.fitness_score,
      overlap_ratio: msg.overlap_ratio,
      inlier_ratio: msg.inlier_ratio,
      ambiguity_score: msg.ambiguity_score,
      translation_innovation: msg.translation_innovation,
      yaw_innovation: msg.yaw_innovation,
      runtime_ms: msg.runtime_ms,
      tested_candidates: msg.tested_candidates,
      total_candidates: msg.total_candidates,
      consecutive_successes: msg.consecutive_successes,
      consecutive_failures: msg.consecutive_failures,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__MissionStatus
/// Authoritative status for one finite sequential mission.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MissionStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_manifest_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_step_index: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_steps: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current_step_id: std::string::String,


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
    pub blocker_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MissionStatus::default())
  }
}

impl rosidl_runtime_rs::Message for MissionStatus {
  type RmwMsg = super::msg::rmw::MissionStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        state: msg.state,
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        content_sha256: msg.content_sha256.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_manifest_sha256: msg.map_manifest_sha256.as_str().into(),
        current_step_index: msg.current_step_index,
        total_steps: msg.total_steps,
        current_step_id: msg.current_step_id.as_str().into(),
        current_step_type: msg.current_step_type,
        current_waypoint: msg.current_waypoint,
        total_waypoints: msg.total_waypoints,
        step_elapsed_s: msg.step_elapsed_s,
        step_remaining_s: msg.step_remaining_s,
        error_code: msg.error_code,
        blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      state: msg.state,
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        content_sha256: msg.content_sha256.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_manifest_sha256: msg.map_manifest_sha256.as_str().into(),
      current_step_index: msg.current_step_index,
      total_steps: msg.total_steps,
        current_step_id: msg.current_step_id.as_str().into(),
      current_step_type: msg.current_step_type,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
      step_elapsed_s: msg.step_elapsed_s,
      step_remaining_s: msg.step_remaining_s,
      error_code: msg.error_code,
        blocker_codes: msg.blocker_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      state: msg.state,
      mission_id: msg.mission_id.to_string(),
      mission_version: msg.mission_version.to_string(),
      content_sha256: msg.content_sha256.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      map_manifest_sha256: msg.map_manifest_sha256.to_string(),
      current_step_index: msg.current_step_index,
      total_steps: msg.total_steps,
      current_step_id: msg.current_step_id.to_string(),
      current_step_type: msg.current_step_type,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
      step_elapsed_s: msg.step_elapsed_s,
      step_remaining_s: msg.step_remaining_s,
      error_code: msg.error_code,
      blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__MissionEvent
/// Timestamped external event consumed by finite WAIT_EVENT mission steps.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MissionEvent {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub event_type: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub correlation_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: std::string::String,

    /// Extension data only. Core event identity is represented by typed fields above.
    pub metadata_json: std::string::String,

}



impl Default for MissionEvent {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MissionEvent::default())
  }
}

impl rosidl_runtime_rs::Message for MissionEvent {
  type RmwMsg = super::msg::rmw::MissionEvent;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        event_type: msg.event_type.as_str().into(),
        source: msg.source.as_str().into(),
        correlation_id: msg.correlation_id.as_str().into(),
        mission_id: msg.mission_id.as_str().into(),
        metadata_json: msg.metadata_json.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        event_type: msg.event_type.as_str().into(),
        source: msg.source.as_str().into(),
        correlation_id: msg.correlation_id.as_str().into(),
        mission_id: msg.mission_id.as_str().into(),
        metadata_json: msg.metadata_json.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      event_type: msg.event_type.to_string(),
      source: msg.source.to_string(),
      correlation_id: msg.correlation_id.to_string(),
      mission_id: msg.mission_id.to_string(),
      metadata_json: msg.metadata_json.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__MapVersionSummary
/// Manager-owned map identity and validation summary.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct MapVersionSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub parent_map_version_id: std::string::String,


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
    pub map_hash: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub manifest_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_yaml_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_image_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub navigation_yaml: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks_directory: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub storage_bytes: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub created_at: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_errors: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_warnings: Vec<std::string::String>,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::MapVersionSummary::default())
  }
}

impl rosidl_runtime_rs::Message for MapVersionSummary {
  type RmwMsg = super::msg::rmw::MapVersionSummary;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        parent_map_version_id: msg.parent_map_version_id.as_str().into(),
        state: msg.state,
        active: msg.active,
        pinned: msg.pinned,
        deleted: msg.deleted,
        valid: msg.valid,
        map_hash: msg.map_hash.as_str().into(),
        manifest_sha256: msg.manifest_sha256.as_str().into(),
        navigation_yaml_sha256: msg.navigation_yaml_sha256.as_str().into(),
        navigation_image_sha256: msg.navigation_image_sha256.as_str().into(),
        localization_pcd_sha256: msg.localization_pcd_sha256.as_str().into(),
        navigation_yaml: msg.navigation_yaml.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        tasks_directory: msg.tasks_directory.as_str().into(),
        storage_bytes: msg.storage_bytes,
        created_at: msg.created_at.as_str().into(),
        validation_errors: msg.validation_errors
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        validation_warnings: msg.validation_warnings
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        parent_map_version_id: msg.parent_map_version_id.as_str().into(),
      state: msg.state,
      active: msg.active,
      pinned: msg.pinned,
      deleted: msg.deleted,
      valid: msg.valid,
        map_hash: msg.map_hash.as_str().into(),
        manifest_sha256: msg.manifest_sha256.as_str().into(),
        navigation_yaml_sha256: msg.navigation_yaml_sha256.as_str().into(),
        navigation_image_sha256: msg.navigation_image_sha256.as_str().into(),
        localization_pcd_sha256: msg.localization_pcd_sha256.as_str().into(),
        navigation_yaml: msg.navigation_yaml.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        tasks_directory: msg.tasks_directory.as_str().into(),
      storage_bytes: msg.storage_bytes,
        created_at: msg.created_at.as_str().into(),
        validation_errors: msg.validation_errors
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        validation_warnings: msg.validation_warnings
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      parent_map_version_id: msg.parent_map_version_id.to_string(),
      state: msg.state,
      active: msg.active,
      pinned: msg.pinned,
      deleted: msg.deleted,
      valid: msg.valid,
      map_hash: msg.map_hash.to_string(),
      manifest_sha256: msg.manifest_sha256.to_string(),
      navigation_yaml_sha256: msg.navigation_yaml_sha256.to_string(),
      navigation_image_sha256: msg.navigation_image_sha256.to_string(),
      localization_pcd_sha256: msg.localization_pcd_sha256.to_string(),
      navigation_yaml: msg.navigation_yaml.to_string(),
      localization_pcd: msg.localization_pcd.to_string(),
      processing_record: msg.processing_record.to_string(),
      tasks_directory: msg.tasks_directory.to_string(),
      storage_bytes: msg.storage_bytes,
      created_at: msg.created_at.to_string(),
      validation_errors: msg.validation_errors
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      validation_warnings: msg.validation_warnings
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


// Corresponds to agt_interfaces__msg__NavigationSessionStatus
/// Authoritative waypoint-task session state owned by agt_navigation.
/// Published reliable + transient_local on /agt/navigation/session_status.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavigationSessionStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_content_sha256: std::string::String,


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
    pub missed_waypoints: Vec<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub started_at: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: builtin_interfaces::msg::Time,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::NavigationSessionStatus::default())
  }
}

impl rosidl_runtime_rs::Message for NavigationSessionStatus {
  type RmwMsg = super::msg::rmw::NavigationSessionStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        session_id: msg.session_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        task_revision: msg.task_revision,
        task_content_sha256: msg.task_content_sha256.as_str().into(),
        state: msg.state,
        loop_index: msg.loop_index,
        current_waypoint: msg.current_waypoint,
        total_waypoints: msg.total_waypoints,
        missed_waypoints: msg.missed_waypoints.into(),
        error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        started_at: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.started_at)).into_owned(),
        updated_at: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.updated_at)).into_owned(),
        terminal: msg.terminal,
        success: msg.success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        session_id: msg.session_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      task_revision: msg.task_revision,
        task_content_sha256: msg.task_content_sha256.as_str().into(),
      state: msg.state,
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
        missed_waypoints: msg.missed_waypoints.as_slice().into(),
      error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        started_at: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.started_at)).into_owned(),
        updated_at: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.updated_at)).into_owned(),
      terminal: msg.terminal,
      success: msg.success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      session_id: msg.session_id.to_string(),
      client_request_id: msg.client_request_id.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      task_revision: msg.task_revision,
      task_content_sha256: msg.task_content_sha256.to_string(),
      state: msg.state,
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
      missed_waypoints: msg.missed_waypoints
          .into_iter()
          .collect(),
      error_code: msg.error_code,
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      started_at: builtin_interfaces::msg::Time::from_rmw_message(msg.started_at),
      updated_at: builtin_interfaces::msg::Time::from_rmw_message(msg.updated_at),
      terminal: msg.terminal,
      success: msg.success,
    }
  }
}


// Corresponds to agt_interfaces__msg__BagSessionSummary
/// Manager-owned rosbag or experiment session summary.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BagSessionSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub relative_uri: std::string::String,


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
    pub started_at: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub process_id: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message_count: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub storage_identifier: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BagSessionSummary::default())
  }
}

impl rosidl_runtime_rs::Message for BagSessionSummary {
  type RmwMsg = super::msg::rmw::BagSessionSummary;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        state: msg.state,
        bag_id: msg.bag_id.as_str().into(),
        experiment_id: msg.experiment_id.as_str().into(),
        profile_id: msg.profile_id.as_str().into(),
        relative_uri: msg.relative_uri.as_str().into(),
        complete: msg.complete,
        simulation: msg.simulation,
        playback_rate: msg.playback_rate,
        storage_bytes: msg.storage_bytes,
        started_at: msg.started_at.as_str().into(),
        updated_at: msg.updated_at.as_str().into(),
        message: msg.message.as_str().into(),
        process_id: msg.process_id,
        message_count: msg.message_count,
        storage_identifier: msg.storage_identifier.as_str().into(),
        mapping_input_ready: msg.mapping_input_ready,
        contains_mapping_outputs: msg.contains_mapping_outputs,
        contains_navigation_outputs: msg.contains_navigation_outputs,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      state: msg.state,
        bag_id: msg.bag_id.as_str().into(),
        experiment_id: msg.experiment_id.as_str().into(),
        profile_id: msg.profile_id.as_str().into(),
        relative_uri: msg.relative_uri.as_str().into(),
      complete: msg.complete,
      simulation: msg.simulation,
      playback_rate: msg.playback_rate,
      storage_bytes: msg.storage_bytes,
        started_at: msg.started_at.as_str().into(),
        updated_at: msg.updated_at.as_str().into(),
        message: msg.message.as_str().into(),
      process_id: msg.process_id,
      message_count: msg.message_count,
        storage_identifier: msg.storage_identifier.as_str().into(),
      mapping_input_ready: msg.mapping_input_ready,
      contains_mapping_outputs: msg.contains_mapping_outputs,
      contains_navigation_outputs: msg.contains_navigation_outputs,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      state: msg.state,
      bag_id: msg.bag_id.to_string(),
      experiment_id: msg.experiment_id.to_string(),
      profile_id: msg.profile_id.to_string(),
      relative_uri: msg.relative_uri.to_string(),
      complete: msg.complete,
      simulation: msg.simulation,
      playback_rate: msg.playback_rate,
      storage_bytes: msg.storage_bytes,
      started_at: msg.started_at.to_string(),
      updated_at: msg.updated_at.to_string(),
      message: msg.message.to_string(),
      process_id: msg.process_id,
      message_count: msg.message_count,
      storage_identifier: msg.storage_identifier.to_string(),
      mapping_input_ready: msg.mapping_input_ready,
      contains_mapping_outputs: msg.contains_mapping_outputs,
      contains_navigation_outputs: msg.contains_navigation_outputs,
    }
  }
}


// Corresponds to agt_interfaces__msg__ExperimentSummary
/// Manager-owned experiment lifecycle summary.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExperimentSummary {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub title: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub created_at: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_time: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub end_time: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_hash: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub launch_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result_status: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config_snapshot_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ExperimentSummary::default())
  }
}

impl rosidl_runtime_rs::Message for ExperimentSummary {
  type RmwMsg = super::msg::rmw::ExperimentSummary;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        experiment_id: msg.experiment_id.as_str().into(),
        title: msg.title.as_str().into(),
        state: msg.state,
        created_at: msg.created_at.as_str().into(),
        start_time: msg.start_time.as_str().into(),
        end_time: msg.end_time.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_hash: msg.map_hash.as_str().into(),
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        mission_sha256: msg.mission_sha256.as_str().into(),
        launch_profile: msg.launch_profile.as_str().into(),
        result_status: msg.result_status.as_str().into(),
        config_snapshot_count: msg.config_snapshot_count,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        experiment_id: msg.experiment_id.as_str().into(),
        title: msg.title.as_str().into(),
      state: msg.state,
        created_at: msg.created_at.as_str().into(),
        start_time: msg.start_time.as_str().into(),
        end_time: msg.end_time.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_hash: msg.map_hash.as_str().into(),
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        mission_sha256: msg.mission_sha256.as_str().into(),
        launch_profile: msg.launch_profile.as_str().into(),
        result_status: msg.result_status.as_str().into(),
      config_snapshot_count: msg.config_snapshot_count,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      experiment_id: msg.experiment_id.to_string(),
      title: msg.title.to_string(),
      state: msg.state,
      created_at: msg.created_at.to_string(),
      start_time: msg.start_time.to_string(),
      end_time: msg.end_time.to_string(),
      platform_profile: msg.platform_profile.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      map_hash: msg.map_hash.to_string(),
      mission_id: msg.mission_id.to_string(),
      mission_version: msg.mission_version.to_string(),
      mission_sha256: msg.mission_sha256.to_string(),
      launch_profile: msg.launch_profile.to_string(),
      result_status: msg.result_status.to_string(),
      config_snapshot_count: msg.config_snapshot_count,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__RobotState
/// Unified read model for interchangeable operator clients.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RobotState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub system_mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_profile: std::string::String,


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
    pub system_health: super::msg::SystemHealth,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_readiness: super::msg::TaskReadiness,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_map: super::msg::MapVersionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization: super::msg::LocalizationStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_status_known: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_freshness_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission: super::msg::MissionStatus,


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
    pub bag_session: super::msg::BagSessionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RobotState::default())
  }
}

impl rosidl_runtime_rs::Message for RobotState {
  type RmwMsg = super::msg::rmw::RobotState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        revision: msg.revision,
        system_mode: msg.system_mode,
        active_profile: msg.active_profile.as_str().into(),
        managed_process_count: msg.managed_process_count,
        running_process_count: msg.running_process_count,
        system_health_known: msg.system_health_known,
        system_health_freshness_s: msg.system_health_freshness_s,
        system_health: super::msg::SystemHealth::into_rmw_message(std::borrow::Cow::Owned(msg.system_health)).into_owned(),
        task_readiness_known: msg.task_readiness_known,
        task_readiness_freshness_s: msg.task_readiness_freshness_s,
        task_readiness: super::msg::TaskReadiness::into_rmw_message(std::borrow::Cow::Owned(msg.task_readiness)).into_owned(),
        active_map_known: msg.active_map_known,
        active_map_freshness_s: msg.active_map_freshness_s,
        active_map: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Owned(msg.active_map)).into_owned(),
        localization_status_known: msg.localization_status_known,
        localization_freshness_s: msg.localization_freshness_s,
        localization: super::msg::LocalizationStatus::into_rmw_message(std::borrow::Cow::Owned(msg.localization)).into_owned(),
        mission_status_known: msg.mission_status_known,
        mission_freshness_s: msg.mission_freshness_s,
        mission: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.mission)).into_owned(),
        nav2_state: msg.nav2_state,
        nav2_freshness_s: msg.nav2_freshness_s,
        safety_status_known: msg.safety_status_known,
        safety_motion_enabled: msg.safety_motion_enabled,
        emergency_stop: msg.emergency_stop,
        estop_latched: msg.estop_latched,
        navigation_ready: msg.navigation_ready,
        safety_freshness_s: msg.safety_freshness_s,
        chassis_status_known: msg.chassis_status_known,
        chassis_connected: msg.chassis_connected,
        chassis_control_mode: msg.chassis_control_mode,
        chassis_status_freshness_s: msg.chassis_status_freshness_s,
        chassis_odometry_freshness_s: msg.chassis_odometry_freshness_s,
        bag_status_known: msg.bag_status_known,
        bag_freshness_s: msg.bag_freshness_s,
        bag_session: super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Owned(msg.bag_session)).into_owned(),
        error_code: msg.error_code,
        blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      revision: msg.revision,
      system_mode: msg.system_mode,
        active_profile: msg.active_profile.as_str().into(),
      managed_process_count: msg.managed_process_count,
      running_process_count: msg.running_process_count,
      system_health_known: msg.system_health_known,
      system_health_freshness_s: msg.system_health_freshness_s,
        system_health: super::msg::SystemHealth::into_rmw_message(std::borrow::Cow::Borrowed(&msg.system_health)).into_owned(),
      task_readiness_known: msg.task_readiness_known,
      task_readiness_freshness_s: msg.task_readiness_freshness_s,
        task_readiness: super::msg::TaskReadiness::into_rmw_message(std::borrow::Cow::Borrowed(&msg.task_readiness)).into_owned(),
      active_map_known: msg.active_map_known,
      active_map_freshness_s: msg.active_map_freshness_s,
        active_map: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Borrowed(&msg.active_map)).into_owned(),
      localization_status_known: msg.localization_status_known,
      localization_freshness_s: msg.localization_freshness_s,
        localization: super::msg::LocalizationStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.localization)).into_owned(),
      mission_status_known: msg.mission_status_known,
      mission_freshness_s: msg.mission_freshness_s,
        mission: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.mission)).into_owned(),
      nav2_state: msg.nav2_state,
      nav2_freshness_s: msg.nav2_freshness_s,
      safety_status_known: msg.safety_status_known,
      safety_motion_enabled: msg.safety_motion_enabled,
      emergency_stop: msg.emergency_stop,
      estop_latched: msg.estop_latched,
      navigation_ready: msg.navigation_ready,
      safety_freshness_s: msg.safety_freshness_s,
      chassis_status_known: msg.chassis_status_known,
      chassis_connected: msg.chassis_connected,
      chassis_control_mode: msg.chassis_control_mode,
      chassis_status_freshness_s: msg.chassis_status_freshness_s,
      chassis_odometry_freshness_s: msg.chassis_odometry_freshness_s,
      bag_status_known: msg.bag_status_known,
      bag_freshness_s: msg.bag_freshness_s,
        bag_session: super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Borrowed(&msg.bag_session)).into_owned(),
      error_code: msg.error_code,
        blocker_codes: msg.blocker_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      revision: msg.revision,
      system_mode: msg.system_mode,
      active_profile: msg.active_profile.to_string(),
      managed_process_count: msg.managed_process_count,
      running_process_count: msg.running_process_count,
      system_health_known: msg.system_health_known,
      system_health_freshness_s: msg.system_health_freshness_s,
      system_health: super::msg::SystemHealth::from_rmw_message(msg.system_health),
      task_readiness_known: msg.task_readiness_known,
      task_readiness_freshness_s: msg.task_readiness_freshness_s,
      task_readiness: super::msg::TaskReadiness::from_rmw_message(msg.task_readiness),
      active_map_known: msg.active_map_known,
      active_map_freshness_s: msg.active_map_freshness_s,
      active_map: super::msg::MapVersionSummary::from_rmw_message(msg.active_map),
      localization_status_known: msg.localization_status_known,
      localization_freshness_s: msg.localization_freshness_s,
      localization: super::msg::LocalizationStatus::from_rmw_message(msg.localization),
      mission_status_known: msg.mission_status_known,
      mission_freshness_s: msg.mission_freshness_s,
      mission: super::msg::MissionStatus::from_rmw_message(msg.mission),
      nav2_state: msg.nav2_state,
      nav2_freshness_s: msg.nav2_freshness_s,
      safety_status_known: msg.safety_status_known,
      safety_motion_enabled: msg.safety_motion_enabled,
      emergency_stop: msg.emergency_stop,
      estop_latched: msg.estop_latched,
      navigation_ready: msg.navigation_ready,
      safety_freshness_s: msg.safety_freshness_s,
      chassis_status_known: msg.chassis_status_known,
      chassis_connected: msg.chassis_connected,
      chassis_control_mode: msg.chassis_control_mode,
      chassis_status_freshness_s: msg.chassis_status_freshness_s,
      chassis_odometry_freshness_s: msg.chassis_odometry_freshness_s,
      bag_status_known: msg.bag_status_known,
      bag_freshness_s: msg.bag_freshness_s,
      bag_session: super::msg::BagSessionSummary::from_rmw_message(msg.bag_session),
      error_code: msg.error_code,
      blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__msg__SemanticWaypoint
/// Named semantic navigation anchor stored in the map frame.
/// This is map semantics, not an execution sequence.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SemanticWaypoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub role: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::Pose,


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
    pub tags: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enabled: bool,

}



impl Default for SemanticWaypoint {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SemanticWaypoint::default())
  }
}

impl rosidl_runtime_rs::Message for SemanticWaypoint {
  type RmwMsg = super::msg::rmw::SemanticWaypoint;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id.as_str().into(),
        name: msg.name.as_str().into(),
        role: msg.role.as_str().into(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(msg.pose)).into_owned(),
        position_tolerance: msg.position_tolerance,
        yaw_tolerance: msg.yaw_tolerance,
        preferred_speed: msg.preferred_speed,
        tags: msg.tags
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        enabled: msg.enabled,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id.as_str().into(),
        name: msg.name.as_str().into(),
        role: msg.role.as_str().into(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(&msg.pose)).into_owned(),
      position_tolerance: msg.position_tolerance,
      yaw_tolerance: msg.yaw_tolerance,
      preferred_speed: msg.preferred_speed,
        tags: msg.tags
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      enabled: msg.enabled,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id.to_string(),
      name: msg.name.to_string(),
      role: msg.role.to_string(),
      pose: geometry_msgs::msg::Pose::from_rmw_message(msg.pose),
      position_tolerance: msg.position_tolerance,
      yaw_tolerance: msg.yaw_tolerance,
      preferred_speed: msg.preferred_speed,
      tags: msg.tags
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      enabled: msg.enabled,
    }
  }
}


// Corresponds to agt_interfaces__msg__SemanticWaypointArray
/// Versioned semantic waypoint library for one map.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SemanticWaypointArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub schema_version: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub base_map_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub waypoints: Vec<super::msg::SemanticWaypoint>,

}



impl Default for SemanticWaypointArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SemanticWaypointArray::default())
  }
}

impl rosidl_runtime_rs::Message for SemanticWaypointArray {
  type RmwMsg = super::msg::rmw::SemanticWaypointArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        schema_version: msg.schema_version.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        base_map_sha256: msg.base_map_sha256.as_str().into(),
        waypoints: msg.waypoints
          .into_iter()
          .map(|elem| super::msg::SemanticWaypoint::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        schema_version: msg.schema_version.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        base_map_sha256: msg.base_map_sha256.as_str().into(),
        waypoints: msg.waypoints
          .iter()
          .map(|elem| super::msg::SemanticWaypoint::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      schema_version: msg.schema_version.to_string(),
      map_id: msg.map_id.to_string(),
      base_map_sha256: msg.base_map_sha256.to_string(),
      waypoints: msg.waypoints
          .into_iter()
          .map(super::msg::SemanticWaypoint::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to agt_interfaces__msg__SystemHealth
/// Snapshot of all configured component health results.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SystemHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub overall_state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub components: Vec<super::msg::ComponentHealth>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_messages: Vec<std::string::String>,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SystemHealth::default())
  }
}

impl rosidl_runtime_rs::Message for SystemHealth {
  type RmwMsg = super::msg::rmw::SystemHealth;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        overall_state: msg.overall_state,
        revision: msg.revision,
        components: msg.components
          .into_iter()
          .map(|elem| super::msg::ComponentHealth::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_codes: msg.warning_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_messages: msg.warning_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      overall_state: msg.overall_state,
      revision: msg.revision,
        components: msg.components
          .iter()
          .map(|elem| super::msg::ComponentHealth::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        blocker_codes: msg.blocker_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_codes: msg.warning_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_messages: msg.warning_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      overall_state: msg.overall_state,
      revision: msg.revision,
      components: msg.components
          .into_iter()
          .map(super::msg::ComponentHealth::from_rmw_message)
          .collect(),
      blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      warning_codes: msg.warning_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      warning_messages: msg.warning_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


// Corresponds to agt_interfaces__msg__TaskReadiness
/// Shared fail-closed task dispatch decision.

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskReadiness {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ready: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_mode: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub health_revision: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub warning_messages: Vec<std::string::String>,

}



impl Default for TaskReadiness {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TaskReadiness::default())
  }
}

impl rosidl_runtime_rs::Message for TaskReadiness {
  type RmwMsg = super::msg::rmw::TaskReadiness;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        ready: msg.ready,
        active_mode: msg.active_mode.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        localization_state: msg.localization_state.as_str().into(),
        health_revision: msg.health_revision,
        blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_codes: msg.warning_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_messages: msg.warning_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      ready: msg.ready,
        active_mode: msg.active_mode.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        localization_state: msg.localization_state.as_str().into(),
      health_revision: msg.health_revision,
        blocker_codes: msg.blocker_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_codes: msg.warning_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        warning_messages: msg.warning_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      ready: msg.ready,
      active_mode: msg.active_mode.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      localization_state: msg.localization_state.to_string(),
      health_revision: msg.health_revision,
      blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      warning_codes: msg.warning_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      warning_messages: msg.warning_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


