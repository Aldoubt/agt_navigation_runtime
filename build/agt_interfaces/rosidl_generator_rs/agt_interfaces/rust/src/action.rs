
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to agt_interfaces__action__Relocalize_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub initial_pose: geometry_msgs::msg::PoseWithCovarianceStamped,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Goal {
  type RmwMsg = super::action::rmw::Relocalize_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
        use_initial_pose: msg.use_initial_pose,
        initial_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Owned(msg.initial_pose)).into_owned(),
        use_last_valid_pose: msg.use_last_valid_pose,
        use_configured_candidates: msg.use_configured_candidates,
        use_external_coarse_pose: msg.use_external_coarse_pose,
        max_candidates: msg.max_candidates,
        publish_debug: msg.publish_debug,
        timeout_s: msg.timeout_s,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
      use_initial_pose: msg.use_initial_pose,
        initial_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.initial_pose)).into_owned(),
      use_last_valid_pose: msg.use_last_valid_pose,
      use_configured_candidates: msg.use_configured_candidates,
      use_external_coarse_pose: msg.use_external_coarse_pose,
      max_candidates: msg.max_candidates,
      publish_debug: msg.publish_debug,
      timeout_s: msg.timeout_s,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
      use_initial_pose: msg.use_initial_pose,
      initial_pose: geometry_msgs::msg::PoseWithCovarianceStamped::from_rmw_message(msg.initial_pose),
      use_last_valid_pose: msg.use_last_valid_pose,
      use_configured_candidates: msg.use_configured_candidates,
      use_external_coarse_pose: msg.use_external_coarse_pose,
      max_candidates: msg.max_candidates,
      publish_debug: msg.publish_debug,
      timeout_s: msg.timeout_s,
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub final_pose: geometry_msgs::msg::PoseWithCovarianceStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_status: super::msg::LocalizationStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failure_reason: std::string::String,

}



impl Default for Relocalize_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_Result::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Result {
  type RmwMsg = super::action::rmw::Relocalize_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        final_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Owned(msg.final_pose)).into_owned(),
        final_status: super::msg::LocalizationStatus::into_rmw_message(std::borrow::Cow::Owned(msg.final_status)).into_owned(),
        failure_reason: msg.failure_reason.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        final_pose: geometry_msgs::msg::PoseWithCovarianceStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.final_pose)).into_owned(),
        final_status: super::msg::LocalizationStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.final_status)).into_owned(),
        failure_reason: msg.failure_reason.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      final_pose: geometry_msgs::msg::PoseWithCovarianceStamped::from_rmw_message(msg.final_pose),
      final_status: super::msg::LocalizationStatus::from_rmw_message(msg.final_status),
      failure_reason: msg.failure_reason.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub best_candidate_source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub elapsed_s: f64,

}



impl Default for Relocalize_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_Feedback {
  type RmwMsg = super::action::rmw::Relocalize_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state,
        total_candidates: msg.total_candidates,
        tested_candidates: msg.tested_candidates,
        best_fitness_score: msg.best_fitness_score,
        best_candidate_source: msg.best_candidate_source.as_str().into(),
        elapsed_s: msg.elapsed_s,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      state: msg.state,
      total_candidates: msg.total_candidates,
      tested_candidates: msg.tested_candidates,
      best_fitness_score: msg.best_fitness_score,
        best_candidate_source: msg.best_candidate_source.as_str().into(),
      elapsed_s: msg.elapsed_s,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state,
      total_candidates: msg.total_candidates,
      tested_candidates: msg.tested_candidates,
      best_fitness_score: msg.best_fitness_score,
      best_candidate_source: msg.best_candidate_source.to_string(),
      elapsed_s: msg.elapsed_s,
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::Relocalize_Feedback,

}



impl Default for Relocalize_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_FeedbackMessage {
  type RmwMsg = super::action::rmw::Relocalize_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::Relocalize_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::Relocalize_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::Relocalize_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_keys: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_values: Vec<std::string::String>,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Goal {
  type RmwMsg = super::action::rmw::ChangeSystemMode_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
        profile: msg.profile.as_str().into(),
        argument_keys: msg.argument_keys
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        argument_values: msg.argument_values
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        wait_for_health: msg.wait_for_health,
        startup_timeout_s: msg.startup_timeout_s,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
        profile: msg.profile.as_str().into(),
        argument_keys: msg.argument_keys
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        argument_values: msg.argument_values
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      wait_for_health: msg.wait_for_health,
      startup_timeout_s: msg.startup_timeout_s,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
      profile: msg.profile.to_string(),
      argument_keys: msg.argument_keys
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      argument_values: msg.argument_values
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      wait_for_health: msg.wait_for_health,
      startup_timeout_s: msg.startup_timeout_s,
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub active_mode: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub process_ids: Vec<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub log_paths: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ChangeSystemMode_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Result {
  type RmwMsg = super::action::rmw::ChangeSystemMode_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        active_mode: msg.active_mode.as_str().into(),
        profile: msg.profile.as_str().into(),
        process_ids: msg.process_ids.into(),
        log_paths: msg.log_paths
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        active_mode: msg.active_mode.as_str().into(),
        profile: msg.profile.as_str().into(),
        process_ids: msg.process_ids.as_slice().into(),
        log_paths: msg.log_paths
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      active_mode: msg.active_mode.to_string(),
      profile: msg.profile.to_string(),
      process_ids: msg.process_ids
          .into_iter()
          .collect(),
      log_paths: msg.log_paths
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ChangeSystemMode_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_Feedback {
  type RmwMsg = super::action::rmw::ChangeSystemMode_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
        progress: msg.progress,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
      progress: msg.progress,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state.to_string(),
      progress: msg.progress,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ChangeSystemMode_Feedback,

}



impl Default for ChangeSystemMode_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_FeedbackMessage {
  type RmwMsg = super::action::rmw::ChangeSystemMode_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ChangeSystemMode_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ChangeSystemMode_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ChangeSystemMode_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,

    /// Required for START. A safe portable identifier, not a filesystem path.
    pub map_id: std::string::String,

    /// Required for operations on an existing session. STATUS may leave it empty to
    /// query the newest managed session.
    pub session_id: std::string::String,

    /// START-only mapping profile arguments. The server injects and owns runtime_dir,
    /// map_name, mapping_output_dir, record_bag, and bag_profile.
    pub argument_keys: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub argument_values: Vec<std::string::String>,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Goal {
  type RmwMsg = super::action::rmw::ManageMappingSession_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        operation: msg.operation,
        map_id: msg.map_id.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        argument_keys: msg.argument_keys
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        argument_values: msg.argument_values
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        activate_after_commit: msg.activate_after_commit,
        timeout_s: msg.timeout_s,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      operation: msg.operation,
        map_id: msg.map_id.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        argument_keys: msg.argument_keys
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        argument_values: msg.argument_values
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      activate_after_commit: msg.activate_after_commit,
      timeout_s: msg.timeout_s,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      operation: msg.operation,
      map_id: msg.map_id.to_string(),
      session_id: msg.session_id.to_string(),
      argument_keys: msg.argument_keys
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      argument_values: msg.argument_values
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      activate_after_commit: msg.activate_after_commit,
      timeout_s: msg.timeout_s,
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_file: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_yaml: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_image: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_directory: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub registered_map_yaml: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tasks_directory: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Result {
  type RmwMsg = super::action::rmw::ManageMappingSession_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        state: msg.state.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        session_file: msg.session_file.as_str().into(),
        candidate_map_yaml: msg.candidate_map_yaml.as_str().into(),
        candidate_map_image: msg.candidate_map_image.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        bag_directory: msg.bag_directory.as_str().into(),
        registered_map_yaml: msg.registered_map_yaml.as_str().into(),
        tasks_directory: msg.tasks_directory.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        state: msg.state.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        session_file: msg.session_file.as_str().into(),
        candidate_map_yaml: msg.candidate_map_yaml.as_str().into(),
        candidate_map_image: msg.candidate_map_image.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        bag_directory: msg.bag_directory.as_str().into(),
        registered_map_yaml: msg.registered_map_yaml.as_str().into(),
        tasks_directory: msg.tasks_directory.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      state: msg.state.to_string(),
      session_id: msg.session_id.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      session_file: msg.session_file.to_string(),
      candidate_map_yaml: msg.candidate_map_yaml.to_string(),
      candidate_map_image: msg.candidate_map_image.to_string(),
      localization_pcd: msg.localization_pcd.to_string(),
      processing_record: msg.processing_record.to_string(),
      bag_directory: msg.bag_directory.to_string(),
      registered_map_yaml: msg.registered_map_yaml.to_string(),
      tasks_directory: msg.tasks_directory.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ManageMappingSession_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_Feedback {
  type RmwMsg = super::action::rmw::ManageMappingSession_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
        progress: msg.progress,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
      progress: msg.progress,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state.to_string(),
      progress: msg.progress,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ManageMappingSession_Feedback,

}



impl Default for ManageMappingSession_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_FeedbackMessage {
  type RmwMsg = super::action::rmw::ManageMappingSession_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ManageMappingSession_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ManageMappingSession_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ManageMappingSession_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub semantic_map_uri: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub field_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub planning_mode: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub controller_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub allow_repair: bool,

}



impl Default for ExecuteCoverageTask_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Goal {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        semantic_map_uri: msg.semantic_map_uri.as_str().into(),
        field_id: msg.field_id.as_str().into(),
        planning_mode: msg.planning_mode.as_str().into(),
        controller_id: msg.controller_id.as_str().into(),
        allow_repair: msg.allow_repair,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        semantic_map_uri: msg.semantic_map_uri.as_str().into(),
        field_id: msg.field_id.as_str().into(),
        planning_mode: msg.planning_mode.as_str().into(),
        controller_id: msg.controller_id.as_str().into(),
      allow_repair: msg.allow_repair,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      semantic_map_uri: msg.semantic_map_uri.to_string(),
      field_id: msg.field_id.to_string(),
      planning_mode: msg.planning_mode.to_string(),
      controller_id: msg.controller_id.to_string(),
      allow_repair: msg.allow_repair,
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub message: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Result {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        message: msg.message.as_str().into(),
        coverage_rate: msg.coverage_rate,
        overlap_rate: msg.overlap_rate,
        executed_length: msg.executed_length,
        repaired_segment_count: msg.repaired_segment_count,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        message: msg.message.as_str().into(),
      coverage_rate: msg.coverage_rate,
      overlap_rate: msg.overlap_rate,
      executed_length: msg.executed_length,
      repaired_segment_count: msg.repaired_segment_count,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      message: msg.message.to_string(),
      coverage_rate: msg.coverage_rate,
      overlap_rate: msg.overlap_rate,
      executed_length: msg.executed_length,
      repaired_segment_count: msg.repaired_segment_count,
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub current_stage: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_Feedback {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        current_stage: msg.current_stage.as_str().into(),
        current_swath_index: msg.current_swath_index,
        total_swaths: msg.total_swaths,
        distance_remaining: msg.distance_remaining,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        current_stage: msg.current_stage.as_str().into(),
      current_swath_index: msg.current_swath_index,
      total_swaths: msg.total_swaths,
      distance_remaining: msg.distance_remaining,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      current_stage: msg.current_stage.to_string(),
      current_swath_index: msg.current_swath_index,
      total_swaths: msg.total_swaths,
      distance_remaining: msg.distance_remaining,
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ExecuteCoverageTask_Feedback,

}



impl Default for ExecuteCoverageTask_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_FeedbackMessage {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteCoverageTask_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteCoverageTask_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ExecuteCoverageTask_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_Goal {

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
    pub expected_content_sha256: std::string::String,

    /// A loop count is always finite. 1 executes the task once.
    pub loop_count: u32,

    /// Idempotency key generated by the client for a start request.
    pub client_request_id: std::string::String,

    /// Deprecated compatibility inputs. Disabled by default on the server and limited
    /// to same-machine CLI/debug when explicitly enabled.
    pub task_file: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: Vec<geometry_msgs::msg::PoseStamped>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_: bool,

}



impl Default for ExecuteWaypointTask_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Goal {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        task_revision: msg.task_revision,
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
        loop_count: msg.loop_count,
        client_request_id: msg.client_request_id.as_str().into(),
        task_file: msg.task_file.as_str().into(),
        poses: msg.poses
          .into_iter()
          .map(|elem| geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        loop_: msg.loop_,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      task_revision: msg.task_revision,
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
      loop_count: msg.loop_count,
        client_request_id: msg.client_request_id.as_str().into(),
        task_file: msg.task_file.as_str().into(),
        poses: msg.poses
          .iter()
          .map(|elem| geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      loop_: msg.loop_,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      task_revision: msg.task_revision,
      expected_content_sha256: msg.expected_content_sha256.to_string(),
      loop_count: msg.loop_count,
      client_request_id: msg.client_request_id.to_string(),
      task_file: msg.task_file.to_string(),
      poses: msg.poses
          .into_iter()
          .map(geometry_msgs::msg::PoseStamped::from_rmw_message)
          .collect(),
      loop_: msg.loop_,
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: std::string::String,


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
    pub duplicate_request: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub missed_waypoints: Vec<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub final_status: super::msg::NavigationSessionStatus,

}



impl Default for ExecuteWaypointTask_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Result {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        message: msg.message.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        duplicate_request: msg.duplicate_request,
        missed_waypoints: msg.missed_waypoints.into(),
        final_status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.final_status)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        message: msg.message.as_str().into(),
        session_id: msg.session_id.as_str().into(),
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
      duplicate_request: msg.duplicate_request,
        missed_waypoints: msg.missed_waypoints.as_slice().into(),
        final_status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.final_status)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      message: msg.message.to_string(),
      session_id: msg.session_id.to_string(),
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      duplicate_request: msg.duplicate_request,
      missed_waypoints: msg.missed_waypoints
          .into_iter()
          .collect(),
      final_status: super::msg::NavigationSessionStatus::from_rmw_message(msg.final_status),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


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
    pub status: super::msg::NavigationSessionStatus,

}



impl Default for ExecuteWaypointTask_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_Feedback {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
        loop_index: msg.loop_index,
        current_waypoint: msg.current_waypoint,
        total_waypoints: msg.total_waypoints,
        status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.status)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state.as_str().into(),
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
        status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.status)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state.to_string(),
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
      status: super::msg::NavigationSessionStatus::from_rmw_message(msg.status),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ExecuteWaypointTask_Feedback,

}



impl Default for ExecuteWaypointTask_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_FeedbackMessage {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteWaypointTask_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteWaypointTask_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ExecuteWaypointTask_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub source_map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source_experiment_ids: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub backend: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub options_yaml: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub activate_on_success: bool,

}



impl Default for OptimizeMap_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Goal {
  type RmwMsg = super::action::rmw::OptimizeMap_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        source_map_id: msg.source_map_id.as_str().into(),
        source_map_version_id: msg.source_map_version_id.as_str().into(),
        source_experiment_ids: msg.source_experiment_ids
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        backend: msg.backend.as_str().into(),
        options_yaml: msg.options_yaml.as_str().into(),
        activate_on_success: msg.activate_on_success,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        source_map_id: msg.source_map_id.as_str().into(),
        source_map_version_id: msg.source_map_version_id.as_str().into(),
        source_experiment_ids: msg.source_experiment_ids
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        backend: msg.backend.as_str().into(),
        options_yaml: msg.options_yaml.as_str().into(),
      activate_on_success: msg.activate_on_success,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      source_map_id: msg.source_map_id.to_string(),
      source_map_version_id: msg.source_map_version_id.to_string(),
      source_experiment_ids: msg.source_experiment_ids
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      backend: msg.backend.to_string(),
      options_yaml: msg.options_yaml.to_string(),
      activate_on_success: msg.activate_on_success,
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub new_map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub trajectory_path: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub optimized_pcd_path: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub report_path: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for OptimizeMap_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_Result::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Result {
  type RmwMsg = super::action::rmw::OptimizeMap_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        new_map_version_id: msg.new_map_version_id.as_str().into(),
        trajectory_path: msg.trajectory_path.as_str().into(),
        optimized_pcd_path: msg.optimized_pcd_path.as_str().into(),
        report_path: msg.report_path.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        new_map_version_id: msg.new_map_version_id.as_str().into(),
        trajectory_path: msg.trajectory_path.as_str().into(),
        optimized_pcd_path: msg.optimized_pcd_path.as_str().into(),
        report_path: msg.report_path.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      new_map_version_id: msg.new_map_version_id.to_string(),
      trajectory_path: msg.trajectory_path.to_string(),
      optimized_pcd_path: msg.optimized_pcd_path.to_string(),
      report_path: msg.report_path.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stage: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub progress: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for OptimizeMap_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_Feedback {
  type RmwMsg = super::action::rmw::OptimizeMap_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stage: msg.stage.as_str().into(),
        progress: msg.progress,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stage: msg.stage.as_str().into(),
      progress: msg.progress,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stage: msg.stage.to_string(),
      progress: msg.progress,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::OptimizeMap_Feedback,

}



impl Default for OptimizeMap_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_FeedbackMessage {
  type RmwMsg = super::action::rmw::OptimizeMap_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::OptimizeMap_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::OptimizeMap_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::OptimizeMap_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_version: std::string::String,

    /// Optional optimistic-lock check. Empty accepts the stored content hash.
    pub expected_content_sha256: std::string::String,

}



impl Default for ExecuteMission_Goal {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Goal {
  type RmwMsg = super::action::rmw::ExecuteMission_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mission_id: msg.mission_id.to_string(),
      mission_version: msg.mission_version.to_string(),
      expected_content_sha256: msg.expected_content_sha256.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub final_status: super::msg::MissionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub audit_log_uri: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for ExecuteMission_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Result {
  type RmwMsg = super::action::rmw::ExecuteMission_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        final_status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.final_status)).into_owned(),
        audit_log_uri: msg.audit_log_uri.as_str().into(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        final_status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.final_status)).into_owned(),
        audit_log_uri: msg.audit_log_uri.as_str().into(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      final_status: super::msg::MissionStatus::from_rmw_message(msg.final_status),
      audit_log_uri: msg.audit_log_uri.to_string(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: super::msg::MissionStatus,

}



impl Default for ExecuteMission_Feedback {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_Feedback {
  type RmwMsg = super::action::rmw::ExecuteMission_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.status)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.status)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: super::msg::MissionStatus::from_rmw_message(msg.status),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ExecuteMission_Feedback,

}



impl Default for ExecuteMission_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_FeedbackMessage {
  type RmwMsg = super::action::rmw::ExecuteMission_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteMission_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteMission_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ExecuteMission_Feedback::from_rmw_message(msg.feedback),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Goal

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tree_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub execution_id: std::string::String,


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
    pub expected_content_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub loop_count: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_Goal::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Goal {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tree_id: msg.tree_id.as_str().into(),
        execution_id: msg.execution_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        task_revision: msg.task_revision,
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
        loop_count: msg.loop_count,
        client_request_id: msg.client_request_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tree_id: msg.tree_id.as_str().into(),
        execution_id: msg.execution_id.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      task_revision: msg.task_revision,
        expected_content_sha256: msg.expected_content_sha256.as_str().into(),
      loop_count: msg.loop_count,
        client_request_id: msg.client_request_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      tree_id: msg.tree_id.to_string(),
      execution_id: msg.execution_id.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      task_revision: msg.task_revision,
      expected_content_sha256: msg.expected_content_sha256.to_string(),
      loop_count: msg.loop_count,
      client_request_id: msg.client_request_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Result

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_code: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_message: std::string::String,

}



impl Default for ExecuteBehaviorTree_Result {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_Result::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Result {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_Result;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        message: msg.message.as_str().into(),
        blocker_code: msg.blocker_code.as_str().into(),
        blocker_message: msg.blocker_message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        message: msg.message.as_str().into(),
        blocker_code: msg.blocker_code.as_str().into(),
        blocker_message: msg.blocker_message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      message: msg.message.to_string(),
      blocker_code: msg.blocker_code.to_string(),
      blocker_message: msg.blocker_message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_Feedback

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tree_state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub active_node: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_Feedback::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_Feedback {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_Feedback;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tree_state: msg.tree_state.as_str().into(),
        active_node: msg.active_node.as_str().into(),
        loop_index: msg.loop_index,
        current_waypoint: msg.current_waypoint,
        total_waypoints: msg.total_waypoints,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tree_state: msg.tree_state.as_str().into(),
        active_node: msg.active_node.as_str().into(),
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      tree_state: msg.tree_state.to_string(),
      active_node: msg.active_node.to_string(),
      loop_index: msg.loop_index,
      current_waypoint: msg.current_waypoint,
      total_waypoints: msg.total_waypoints,
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_FeedbackMessage

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::action::ExecuteBehaviorTree_Feedback,

}



impl Default for ExecuteBehaviorTree_FeedbackMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_FeedbackMessage::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_FeedbackMessage {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_FeedbackMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteBehaviorTree_Feedback::into_rmw_message(std::borrow::Cow::Owned(msg.feedback)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        feedback: super::action::ExecuteBehaviorTree_Feedback::into_rmw_message(std::borrow::Cow::Borrowed(&msg.feedback)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      feedback: super::action::ExecuteBehaviorTree_Feedback::from_rmw_message(msg.feedback),
    }
  }
}






// Corresponds to agt_interfaces__action__Relocalize_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::Relocalize_Goal,

}



impl Default for Relocalize_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_SendGoal_Request {
  type RmwMsg = super::action::rmw::Relocalize_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::Relocalize_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::Relocalize_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::Relocalize_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for Relocalize_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_SendGoal_Response {
  type RmwMsg = super::action::rmw::Relocalize_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for Relocalize_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_GetResult_Request {
  type RmwMsg = super::action::rmw::Relocalize_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__Relocalize_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Relocalize_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::Relocalize_Result,

}



impl Default for Relocalize_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::Relocalize_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for Relocalize_GetResult_Response {
  type RmwMsg = super::action::rmw::Relocalize_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::Relocalize_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::Relocalize_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::Relocalize_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ChangeSystemMode_Goal,

}



impl Default for ChangeSystemMode_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_SendGoal_Request {
  type RmwMsg = super::action::rmw::ChangeSystemMode_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ChangeSystemMode_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ChangeSystemMode_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ChangeSystemMode_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ChangeSystemMode_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_SendGoal_Response {
  type RmwMsg = super::action::rmw::ChangeSystemMode_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ChangeSystemMode_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_GetResult_Request {
  type RmwMsg = super::action::rmw::ChangeSystemMode_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ChangeSystemMode_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChangeSystemMode_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ChangeSystemMode_Result,

}



impl Default for ChangeSystemMode_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ChangeSystemMode_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ChangeSystemMode_GetResult_Response {
  type RmwMsg = super::action::rmw::ChangeSystemMode_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ChangeSystemMode_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ChangeSystemMode_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ChangeSystemMode_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ManageMappingSession_Goal,

}



impl Default for ManageMappingSession_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_SendGoal_Request {
  type RmwMsg = super::action::rmw::ManageMappingSession_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ManageMappingSession_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ManageMappingSession_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ManageMappingSession_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ManageMappingSession_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_SendGoal_Response {
  type RmwMsg = super::action::rmw::ManageMappingSession_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ManageMappingSession_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_GetResult_Request {
  type RmwMsg = super::action::rmw::ManageMappingSession_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ManageMappingSession_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMappingSession_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ManageMappingSession_Result,

}



impl Default for ManageMappingSession_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ManageMappingSession_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMappingSession_GetResult_Response {
  type RmwMsg = super::action::rmw::ManageMappingSession_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ManageMappingSession_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ManageMappingSession_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ManageMappingSession_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ExecuteCoverageTask_Goal,

}



impl Default for ExecuteCoverageTask_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_SendGoal_Request {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ExecuteCoverageTask_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ExecuteCoverageTask_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ExecuteCoverageTask_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ExecuteCoverageTask_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_SendGoal_Response {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ExecuteCoverageTask_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_GetResult_Request {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteCoverageTask_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteCoverageTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ExecuteCoverageTask_Result,

}



impl Default for ExecuteCoverageTask_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteCoverageTask_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteCoverageTask_GetResult_Response {
  type RmwMsg = super::action::rmw::ExecuteCoverageTask_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ExecuteCoverageTask_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ExecuteCoverageTask_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ExecuteCoverageTask_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ExecuteWaypointTask_Goal,

}



impl Default for ExecuteWaypointTask_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_SendGoal_Request {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ExecuteWaypointTask_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ExecuteWaypointTask_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ExecuteWaypointTask_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ExecuteWaypointTask_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_SendGoal_Response {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ExecuteWaypointTask_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_GetResult_Request {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteWaypointTask_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteWaypointTask_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ExecuteWaypointTask_Result,

}



impl Default for ExecuteWaypointTask_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteWaypointTask_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteWaypointTask_GetResult_Response {
  type RmwMsg = super::action::rmw::ExecuteWaypointTask_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ExecuteWaypointTask_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ExecuteWaypointTask_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ExecuteWaypointTask_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::OptimizeMap_Goal,

}



impl Default for OptimizeMap_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_SendGoal_Request {
  type RmwMsg = super::action::rmw::OptimizeMap_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::OptimizeMap_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::OptimizeMap_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::OptimizeMap_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for OptimizeMap_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_SendGoal_Response {
  type RmwMsg = super::action::rmw::OptimizeMap_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for OptimizeMap_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_GetResult_Request {
  type RmwMsg = super::action::rmw::OptimizeMap_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__OptimizeMap_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OptimizeMap_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::OptimizeMap_Result,

}



impl Default for OptimizeMap_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::OptimizeMap_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for OptimizeMap_GetResult_Response {
  type RmwMsg = super::action::rmw::OptimizeMap_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::OptimizeMap_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::OptimizeMap_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::OptimizeMap_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ExecuteMission_Goal,

}



impl Default for ExecuteMission_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_SendGoal_Request {
  type RmwMsg = super::action::rmw::ExecuteMission_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ExecuteMission_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ExecuteMission_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ExecuteMission_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ExecuteMission_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_SendGoal_Response {
  type RmwMsg = super::action::rmw::ExecuteMission_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ExecuteMission_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_GetResult_Request {
  type RmwMsg = super::action::rmw::ExecuteMission_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteMission_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteMission_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ExecuteMission_Result,

}



impl Default for ExecuteMission_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteMission_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteMission_GetResult_Response {
  type RmwMsg = super::action::rmw::ExecuteMission_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ExecuteMission_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ExecuteMission_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ExecuteMission_Result::from_rmw_message(msg.result),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::action::ExecuteBehaviorTree_Goal,

}



impl Default for ExecuteBehaviorTree_SendGoal_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_SendGoal_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_SendGoal_Request {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_SendGoal_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
        goal: super::action::ExecuteBehaviorTree_Goal::into_rmw_message(std::borrow::Cow::Owned(msg.goal)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
        goal: super::action::ExecuteBehaviorTree_Goal::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
      goal: super::action::ExecuteBehaviorTree_Goal::from_rmw_message(msg.goal),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_SendGoal_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,

}



impl Default for ExecuteBehaviorTree_SendGoal_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_SendGoal_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_SendGoal_Response {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_SendGoal_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      accepted: msg.accepted,
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      accepted: msg.accepted,
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::UUID,

}



impl Default for ExecuteBehaviorTree_GetResult_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_GetResult_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_GetResult_Request {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_GetResult_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Owned(msg.goal_id)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        goal_id: unique_identifier_msgs::msg::UUID::into_rmw_message(std::borrow::Cow::Borrowed(&msg.goal_id)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      goal_id: unique_identifier_msgs::msg::UUID::from_rmw_message(msg.goal_id),
    }
  }
}


// Corresponds to agt_interfaces__action__ExecuteBehaviorTree_GetResult_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ExecuteBehaviorTree_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::action::ExecuteBehaviorTree_Result,

}



impl Default for ExecuteBehaviorTree_GetResult_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::action::rmw::ExecuteBehaviorTree_GetResult_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ExecuteBehaviorTree_GetResult_Response {
  type RmwMsg = super::action::rmw::ExecuteBehaviorTree_GetResult_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        status: msg.status,
        result: super::action::ExecuteBehaviorTree_Result::into_rmw_message(std::borrow::Cow::Owned(msg.result)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      status: msg.status,
        result: super::action::ExecuteBehaviorTree_Result::into_rmw_message(std::borrow::Cow::Borrowed(&msg.result)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      status: msg.status,
      result: super::action::ExecuteBehaviorTree_Result::from_rmw_message(msg.result),
    }
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






#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__Relocalize() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__Relocalize
#[allow(missing_docs, non_camel_case_types)]
pub struct Relocalize;

impl rosidl_runtime_rs::Action for Relocalize {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = Relocalize_Goal;

  /// The result message defined in the action definition.
  type Result = Relocalize_Result;

  /// The feedback message defined in the action definition.
  type Feedback = Relocalize_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::Relocalize_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::Relocalize_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::Relocalize_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__Relocalize() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::Relocalize_Goal,
  ) -> super::action::rmw::Relocalize_SendGoal_Request {
   super::action::rmw::Relocalize_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::Relocalize_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::Relocalize_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::Relocalize_SendGoal_Response {
   super::action::rmw::Relocalize_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::Relocalize_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::Relocalize_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::Relocalize_Feedback,
  ) -> super::action::rmw::Relocalize_FeedbackMessage {
    let mut message = super::action::rmw::Relocalize_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::Relocalize_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::Relocalize_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::Relocalize_GetResult_Request {
   super::action::rmw::Relocalize_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::Relocalize_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::Relocalize_Result,
  ) -> super::action::rmw::Relocalize_GetResult_Response {
   super::action::rmw::Relocalize_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::Relocalize_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::Relocalize_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ChangeSystemMode() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ChangeSystemMode
#[allow(missing_docs, non_camel_case_types)]
pub struct ChangeSystemMode;

impl rosidl_runtime_rs::Action for ChangeSystemMode {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ChangeSystemMode_Goal;

  /// The result message defined in the action definition.
  type Result = ChangeSystemMode_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ChangeSystemMode_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ChangeSystemMode_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ChangeSystemMode_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ChangeSystemMode_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ChangeSystemMode() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ChangeSystemMode_Goal,
  ) -> super::action::rmw::ChangeSystemMode_SendGoal_Request {
   super::action::rmw::ChangeSystemMode_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ChangeSystemMode_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ChangeSystemMode_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ChangeSystemMode_SendGoal_Response {
   super::action::rmw::ChangeSystemMode_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ChangeSystemMode_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ChangeSystemMode_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ChangeSystemMode_Feedback,
  ) -> super::action::rmw::ChangeSystemMode_FeedbackMessage {
    let mut message = super::action::rmw::ChangeSystemMode_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ChangeSystemMode_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ChangeSystemMode_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ChangeSystemMode_GetResult_Request {
   super::action::rmw::ChangeSystemMode_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ChangeSystemMode_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ChangeSystemMode_Result,
  ) -> super::action::rmw::ChangeSystemMode_GetResult_Response {
   super::action::rmw::ChangeSystemMode_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ChangeSystemMode_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ChangeSystemMode_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ManageMappingSession() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ManageMappingSession
#[allow(missing_docs, non_camel_case_types)]
pub struct ManageMappingSession;

impl rosidl_runtime_rs::Action for ManageMappingSession {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ManageMappingSession_Goal;

  /// The result message defined in the action definition.
  type Result = ManageMappingSession_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ManageMappingSession_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ManageMappingSession_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ManageMappingSession_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ManageMappingSession_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ManageMappingSession() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ManageMappingSession_Goal,
  ) -> super::action::rmw::ManageMappingSession_SendGoal_Request {
   super::action::rmw::ManageMappingSession_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ManageMappingSession_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ManageMappingSession_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ManageMappingSession_SendGoal_Response {
   super::action::rmw::ManageMappingSession_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ManageMappingSession_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ManageMappingSession_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ManageMappingSession_Feedback,
  ) -> super::action::rmw::ManageMappingSession_FeedbackMessage {
    let mut message = super::action::rmw::ManageMappingSession_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ManageMappingSession_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ManageMappingSession_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ManageMappingSession_GetResult_Request {
   super::action::rmw::ManageMappingSession_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ManageMappingSession_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ManageMappingSession_Result,
  ) -> super::action::rmw::ManageMappingSession_GetResult_Response {
   super::action::rmw::ManageMappingSession_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ManageMappingSession_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ManageMappingSession_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteCoverageTask() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteCoverageTask
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteCoverageTask;

impl rosidl_runtime_rs::Action for ExecuteCoverageTask {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ExecuteCoverageTask_Goal;

  /// The result message defined in the action definition.
  type Result = ExecuteCoverageTask_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ExecuteCoverageTask_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ExecuteCoverageTask_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ExecuteCoverageTask_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ExecuteCoverageTask_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteCoverageTask() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ExecuteCoverageTask_Goal,
  ) -> super::action::rmw::ExecuteCoverageTask_SendGoal_Request {
   super::action::rmw::ExecuteCoverageTask_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ExecuteCoverageTask_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteCoverageTask_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ExecuteCoverageTask_SendGoal_Response {
   super::action::rmw::ExecuteCoverageTask_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ExecuteCoverageTask_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ExecuteCoverageTask_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ExecuteCoverageTask_Feedback,
  ) -> super::action::rmw::ExecuteCoverageTask_FeedbackMessage {
    let mut message = super::action::rmw::ExecuteCoverageTask_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ExecuteCoverageTask_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteCoverageTask_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ExecuteCoverageTask_GetResult_Request {
   super::action::rmw::ExecuteCoverageTask_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ExecuteCoverageTask_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ExecuteCoverageTask_Result,
  ) -> super::action::rmw::ExecuteCoverageTask_GetResult_Response {
   super::action::rmw::ExecuteCoverageTask_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ExecuteCoverageTask_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ExecuteCoverageTask_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteWaypointTask() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteWaypointTask
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteWaypointTask;

impl rosidl_runtime_rs::Action for ExecuteWaypointTask {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ExecuteWaypointTask_Goal;

  /// The result message defined in the action definition.
  type Result = ExecuteWaypointTask_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ExecuteWaypointTask_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ExecuteWaypointTask_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ExecuteWaypointTask_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ExecuteWaypointTask_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteWaypointTask() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ExecuteWaypointTask_Goal,
  ) -> super::action::rmw::ExecuteWaypointTask_SendGoal_Request {
   super::action::rmw::ExecuteWaypointTask_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ExecuteWaypointTask_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteWaypointTask_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ExecuteWaypointTask_SendGoal_Response {
   super::action::rmw::ExecuteWaypointTask_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ExecuteWaypointTask_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ExecuteWaypointTask_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ExecuteWaypointTask_Feedback,
  ) -> super::action::rmw::ExecuteWaypointTask_FeedbackMessage {
    let mut message = super::action::rmw::ExecuteWaypointTask_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ExecuteWaypointTask_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteWaypointTask_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ExecuteWaypointTask_GetResult_Request {
   super::action::rmw::ExecuteWaypointTask_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ExecuteWaypointTask_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ExecuteWaypointTask_Result,
  ) -> super::action::rmw::ExecuteWaypointTask_GetResult_Response {
   super::action::rmw::ExecuteWaypointTask_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ExecuteWaypointTask_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ExecuteWaypointTask_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__OptimizeMap() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__OptimizeMap
#[allow(missing_docs, non_camel_case_types)]
pub struct OptimizeMap;

impl rosidl_runtime_rs::Action for OptimizeMap {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = OptimizeMap_Goal;

  /// The result message defined in the action definition.
  type Result = OptimizeMap_Result;

  /// The feedback message defined in the action definition.
  type Feedback = OptimizeMap_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::OptimizeMap_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::OptimizeMap_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::OptimizeMap_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__OptimizeMap() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::OptimizeMap_Goal,
  ) -> super::action::rmw::OptimizeMap_SendGoal_Request {
   super::action::rmw::OptimizeMap_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::OptimizeMap_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::OptimizeMap_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::OptimizeMap_SendGoal_Response {
   super::action::rmw::OptimizeMap_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::OptimizeMap_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::OptimizeMap_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::OptimizeMap_Feedback,
  ) -> super::action::rmw::OptimizeMap_FeedbackMessage {
    let mut message = super::action::rmw::OptimizeMap_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::OptimizeMap_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::OptimizeMap_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::OptimizeMap_GetResult_Request {
   super::action::rmw::OptimizeMap_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::OptimizeMap_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::OptimizeMap_Result,
  ) -> super::action::rmw::OptimizeMap_GetResult_Response {
   super::action::rmw::OptimizeMap_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::OptimizeMap_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::OptimizeMap_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteMission() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteMission
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteMission;

impl rosidl_runtime_rs::Action for ExecuteMission {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ExecuteMission_Goal;

  /// The result message defined in the action definition.
  type Result = ExecuteMission_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ExecuteMission_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ExecuteMission_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ExecuteMission_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ExecuteMission_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteMission() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ExecuteMission_Goal,
  ) -> super::action::rmw::ExecuteMission_SendGoal_Request {
   super::action::rmw::ExecuteMission_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ExecuteMission_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteMission_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ExecuteMission_SendGoal_Response {
   super::action::rmw::ExecuteMission_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ExecuteMission_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ExecuteMission_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ExecuteMission_Feedback,
  ) -> super::action::rmw::ExecuteMission_FeedbackMessage {
    let mut message = super::action::rmw::ExecuteMission_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ExecuteMission_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteMission_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ExecuteMission_GetResult_Request {
   super::action::rmw::ExecuteMission_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ExecuteMission_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ExecuteMission_Result,
  ) -> super::action::rmw::ExecuteMission_GetResult_Response {
   super::action::rmw::ExecuteMission_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ExecuteMission_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ExecuteMission_Result,
  ) {
    (response.status, response.result)
  }
}




#[link(name = "agt_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree() -> *const std::ffi::c_void;
}

// Corresponds to agt_interfaces__action__ExecuteBehaviorTree
#[allow(missing_docs, non_camel_case_types)]
pub struct ExecuteBehaviorTree;

impl rosidl_runtime_rs::Action for ExecuteBehaviorTree {
  // --- Associated types for client library users ---
  /// The goal message defined in the action definition.
  type Goal = ExecuteBehaviorTree_Goal;

  /// The result message defined in the action definition.
  type Result = ExecuteBehaviorTree_Result;

  /// The feedback message defined in the action definition.
  type Feedback = ExecuteBehaviorTree_Feedback;

  // --- Associated types for client library implementation ---
  /// The feedback message with generic fields which wraps the feedback message.
  type FeedbackMessage = super::action::ExecuteBehaviorTree_FeedbackMessage;

  /// The send_goal service using a wrapped version of the goal message as a request.
  type SendGoalService = super::action::ExecuteBehaviorTree_SendGoal;

  /// The generic service to cancel a goal.
  type CancelGoalService = action_msgs::srv::rmw::CancelGoal;

  /// The get_result service using a wrapped version of the result message as a response.
  type GetResultService = super::action::ExecuteBehaviorTree_GetResult;

  // --- Methods for client library implementation ---
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_action_type_support_handle__agt_interfaces__action__ExecuteBehaviorTree() }
  }

  fn create_goal_request(
    goal_id: &[u8; 16],
    goal: super::action::rmw::ExecuteBehaviorTree_Goal,
  ) -> super::action::rmw::ExecuteBehaviorTree_SendGoal_Request {
   super::action::rmw::ExecuteBehaviorTree_SendGoal_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
      goal,
    }
  }

  fn split_goal_request(
    request: super::action::rmw::ExecuteBehaviorTree_SendGoal_Request,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteBehaviorTree_Goal,
  ) {
    (request.goal_id.uuid, request.goal)
  }

  fn create_goal_response(
    accepted: bool,
    stamp: (i32, u32),
  ) -> super::action::rmw::ExecuteBehaviorTree_SendGoal_Response {
   super::action::rmw::ExecuteBehaviorTree_SendGoal_Response {
      accepted,
      stamp: builtin_interfaces::msg::rmw::Time {
        sec: stamp.0,
        nanosec: stamp.1,
      },
    }
  }

  fn get_goal_response_accepted(
    response: &super::action::rmw::ExecuteBehaviorTree_SendGoal_Response,
  ) -> bool {
    response.accepted
  }

  fn get_goal_response_stamp(
    response: &super::action::rmw::ExecuteBehaviorTree_SendGoal_Response,
  ) -> (i32, u32) {
    (response.stamp.sec, response.stamp.nanosec)
  }

  fn create_feedback_message(
    goal_id: &[u8; 16],
    feedback: super::action::rmw::ExecuteBehaviorTree_Feedback,
  ) -> super::action::rmw::ExecuteBehaviorTree_FeedbackMessage {
    let mut message = super::action::rmw::ExecuteBehaviorTree_FeedbackMessage::default();
    message.goal_id.uuid = *goal_id;
    message.feedback = feedback;
    message
  }

  fn split_feedback_message(
    feedback: super::action::rmw::ExecuteBehaviorTree_FeedbackMessage,
  ) -> (
    [u8; 16],
   super::action::rmw::ExecuteBehaviorTree_Feedback,
  ) {
    (feedback.goal_id.uuid, feedback.feedback)
  }

  fn create_result_request(
    goal_id: &[u8; 16],
  ) -> super::action::rmw::ExecuteBehaviorTree_GetResult_Request {
   super::action::rmw::ExecuteBehaviorTree_GetResult_Request {
      goal_id: unique_identifier_msgs::msg::rmw::UUID { uuid: *goal_id },
    }
  }

  fn get_result_request_uuid(
    request: &super::action::rmw::ExecuteBehaviorTree_GetResult_Request,
  ) -> &[u8; 16] {
    &request.goal_id.uuid
  }

  fn create_result_response(
    status: i8,
    result: super::action::rmw::ExecuteBehaviorTree_Result,
  ) -> super::action::rmw::ExecuteBehaviorTree_GetResult_Response {
   super::action::rmw::ExecuteBehaviorTree_GetResult_Response {
      status,
      result,
    }
  }

  fn split_result_response(
    response: super::action::rmw::ExecuteBehaviorTree_GetResult_Response
  ) -> (
    i8,
   super::action::rmw::ExecuteBehaviorTree_Result,
  ) {
    (response.status, response.result)
  }
}


