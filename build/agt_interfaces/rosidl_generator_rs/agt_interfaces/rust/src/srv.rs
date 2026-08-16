#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to agt_interfaces__srv__EvaluateTaskReadiness_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EvaluateTaskReadiness_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub validate_task: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::EvaluateTaskReadiness_Request::default())
  }
}

impl rosidl_runtime_rs::Message for EvaluateTaskReadiness_Request {
  type RmwMsg = super::srv::rmw::EvaluateTaskReadiness_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        validate_task: msg.validate_task,
        task_id: msg.task_id.as_str().into(),
        gate_profile: msg.gate_profile,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      validate_task: msg.validate_task,
        task_id: msg.task_id.as_str().into(),
      gate_profile: msg.gate_profile,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      validate_task: msg.validate_task,
      task_id: msg.task_id.to_string(),
      gate_profile: msg.gate_profile,
    }
  }
}


// Corresponds to agt_interfaces__srv__EvaluateTaskReadiness_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EvaluateTaskReadiness_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub readiness: super::msg::TaskReadiness,

}



impl Default for EvaluateTaskReadiness_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::EvaluateTaskReadiness_Response::default())
  }
}

impl rosidl_runtime_rs::Message for EvaluateTaskReadiness_Response {
  type RmwMsg = super::srv::rmw::EvaluateTaskReadiness_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        readiness: super::msg::TaskReadiness::into_rmw_message(std::borrow::Cow::Owned(msg.readiness)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        readiness: super::msg::TaskReadiness::into_rmw_message(std::borrow::Cow::Borrowed(&msg.readiness)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      readiness: super::msg::TaskReadiness::from_rmw_message(msg.readiness),
    }
  }
}


// Corresponds to agt_interfaces__srv__GetSystemHealth_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetSystemHealth_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub include_optional: bool,

}



impl Default for GetSystemHealth_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetSystemHealth_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetSystemHealth_Request {
  type RmwMsg = super::srv::rmw::GetSystemHealth_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        include_optional: msg.include_optional,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      include_optional: msg.include_optional,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      include_optional: msg.include_optional,
    }
  }
}


// Corresponds to agt_interfaces__srv__GetSystemHealth_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetSystemHealth_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub health: super::msg::SystemHealth,

}



impl Default for GetSystemHealth_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetSystemHealth_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetSystemHealth_Response {
  type RmwMsg = super::srv::rmw::GetSystemHealth_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        health: super::msg::SystemHealth::into_rmw_message(std::borrow::Cow::Owned(msg.health)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        health: super::msg::SystemHealth::into_rmw_message(std::borrow::Cow::Borrowed(&msg.health)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      health: super::msg::SystemHealth::from_rmw_message(msg.health),
    }
  }
}


// Corresponds to agt_interfaces__srv__GetRobotState_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetRobotState_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub include_details: bool,

}



impl Default for GetRobotState_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetRobotState_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetRobotState_Request {
  type RmwMsg = super::srv::rmw::GetRobotState_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        include_details: msg.include_details,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      include_details: msg.include_details,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      include_details: msg.include_details,
    }
  }
}


// Corresponds to agt_interfaces__srv__GetRobotState_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub state: super::msg::RobotState,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for GetRobotState_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetRobotState_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetRobotState_Response {
  type RmwMsg = super::srv::rmw::GetRobotState_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        state: super::msg::RobotState::into_rmw_message(std::borrow::Cow::Owned(msg.state)).into_owned(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        state: super::msg::RobotState::into_rmw_message(std::borrow::Cow::Borrowed(&msg.state)).into_owned(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      state: super::msg::RobotState::from_rmw_message(msg.state),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__SetMissionRunState_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMissionRunState_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_id: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetMissionRunState_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetMissionRunState_Request {
  type RmwMsg = super::srv::rmw::SetMissionRunState_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        command: msg.command,
        mission_id: msg.mission_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      command: msg.command,
        mission_id: msg.mission_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      command: msg.command,
      mission_id: msg.mission_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__SetMissionRunState_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub status: super::msg::MissionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

}



impl Default for SetMissionRunState_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetMissionRunState_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetMissionRunState_Response {
  type RmwMsg = super::srv::rmw::SetMissionRunState_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.status)).into_owned(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        status: super::msg::MissionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.status)).into_owned(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      status: super::msg::MissionStatus::from_rmw_message(msg.status),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ActivateMapVersion_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ActivateMapVersion_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,

}



impl Default for ActivateMapVersion_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ActivateMapVersion_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ActivateMapVersion_Request {
  type RmwMsg = super::srv::rmw::ActivateMapVersion_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      client_request_id: msg.client_request_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ActivateMapVersion_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_codes: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blocker_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_messages: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub version: super::msg::MapVersionSummary,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ActivateMapVersion_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ActivateMapVersion_Response {
  type RmwMsg = super::srv::rmw::ActivateMapVersion_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        state: msg.state.as_str().into(),
        blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        operator_messages: msg.operator_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        technical_messages: msg.technical_messages
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        version: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Owned(msg.version)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        state: msg.state.as_str().into(),
        blocker_codes: msg.blocker_codes
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        blocker_messages: msg.blocker_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        operator_messages: msg.operator_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        technical_messages: msg.technical_messages
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        version: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Borrowed(&msg.version)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      state: msg.state.to_string(),
      blocker_codes: msg.blocker_codes
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      blocker_messages: msg.blocker_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      operator_messages: msg.operator_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      technical_messages: msg.technical_messages
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      version: super::msg::MapVersionSummary::from_rmw_message(msg.version),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListMapVersions_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListMapVersions_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub include_deleted: bool,

}



impl Default for ListMapVersions_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListMapVersions_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ListMapVersions_Request {
  type RmwMsg = super::srv::rmw::ListMapVersions_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        state: msg.state,
        include_deleted: msg.include_deleted,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
      state: msg.state,
      include_deleted: msg.include_deleted,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      state: msg.state,
      include_deleted: msg.include_deleted,
    }
  }
}


// Corresponds to agt_interfaces__srv__ListMapVersions_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub versions: Vec<super::msg::MapVersionSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListMapVersions_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ListMapVersions_Response {
  type RmwMsg = super::srv::rmw::ListMapVersions_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        versions: msg.versions
          .into_iter()
          .map(|elem| super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        versions: msg.versions
          .iter()
          .map(|elem| super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      versions: msg.versions
          .into_iter()
          .map(super::msg::MapVersionSummary::from_rmw_message)
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ManageMapVersion_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageMapVersion_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub confirm_destructive: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub candidate_map_yaml: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub localization_pcd: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub processing_record: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub parent_map_version_id: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ManageMapVersion_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMapVersion_Request {
  type RmwMsg = super::srv::rmw::ManageMapVersion_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        operation: msg.operation,
        map_version_id: msg.map_version_id.as_str().into(),
        confirm_destructive: msg.confirm_destructive,
        map_id: msg.map_id.as_str().into(),
        candidate_map_yaml: msg.candidate_map_yaml.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        parent_map_version_id: msg.parent_map_version_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      operation: msg.operation,
        map_version_id: msg.map_version_id.as_str().into(),
      confirm_destructive: msg.confirm_destructive,
        map_id: msg.map_id.as_str().into(),
        candidate_map_yaml: msg.candidate_map_yaml.as_str().into(),
        localization_pcd: msg.localization_pcd.as_str().into(),
        processing_record: msg.processing_record.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        parent_map_version_id: msg.parent_map_version_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      operation: msg.operation,
      map_version_id: msg.map_version_id.to_string(),
      confirm_destructive: msg.confirm_destructive,
      map_id: msg.map_id.to_string(),
      candidate_map_yaml: msg.candidate_map_yaml.to_string(),
      localization_pcd: msg.localization_pcd.to_string(),
      processing_record: msg.processing_record.to_string(),
      platform_profile: msg.platform_profile.to_string(),
      parent_map_version_id: msg.parent_map_version_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ManageMapVersion_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub version: super::msg::MapVersionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ManageMapVersion_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ManageMapVersion_Response {
  type RmwMsg = super::srv::rmw::ManageMapVersion_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        version: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Owned(msg.version)).into_owned(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        version: super::msg::MapVersionSummary::into_rmw_message(std::borrow::Cow::Borrowed(&msg.version)).into_owned(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      version: super::msg::MapVersionSummary::from_rmw_message(msg.version),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListTaskGroups_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListTaskGroups_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,

}



impl Default for ListTaskGroups_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListTaskGroups_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ListTaskGroups_Request {
  type RmwMsg = super::srv::rmw::ListTaskGroups_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListTaskGroups_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub blocker_code: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_ids: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revisions: Vec<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub enabled_point_counts: Vec<u32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub updated_at: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub validation_states: Vec<std::string::String>,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListTaskGroups_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ListTaskGroups_Response {
  type RmwMsg = super::srv::rmw::ListTaskGroups_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_ids: msg.task_group_ids
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        names: msg.names
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        revisions: msg.revisions.into(),
        content_sha256: msg.content_sha256
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        enabled_point_counts: msg.enabled_point_counts.into(),
        updated_at: msg.updated_at
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        validation_states: msg.validation_states
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_ids: msg.task_group_ids
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        names: msg.names
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        revisions: msg.revisions.as_slice().into(),
        content_sha256: msg.content_sha256
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        enabled_point_counts: msg.enabled_point_counts.as_slice().into(),
        updated_at: msg.updated_at
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        validation_states: msg.validation_states
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_ids: msg.task_group_ids
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      names: msg.names
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      revisions: msg.revisions
          .into_iter()
          .collect(),
      content_sha256: msg.content_sha256
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      enabled_point_counts: msg.enabled_point_counts
          .into_iter()
          .collect(),
      updated_at: msg.updated_at
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      validation_states: msg.validation_states
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
    }
  }
}


// Corresponds to agt_interfaces__srv__GetTaskGroup_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskGroup_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: std::string::String,

    /// 0 means latest revision.
    pub task_revision: u32,

}



impl Default for GetTaskGroup_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTaskGroup_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetTaskGroup_Request {
  type RmwMsg = super::srv::rmw::GetTaskGroup_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        task_revision: msg.task_revision,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      task_revision: msg.task_revision,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      task_revision: msg.task_revision,
    }
  }
}


// Corresponds to agt_interfaces__srv__GetTaskGroup_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub blocker_code: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub technical_message: std::string::String,


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
    pub revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTaskGroup_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetTaskGroup_Response {
  type RmwMsg = super::srv::rmw::GetTaskGroup_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        revision: msg.revision,
        content_sha256: msg.content_sha256.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      revision: msg.revision,
        content_sha256: msg.content_sha256.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      revision: msg.revision,
      content_sha256: msg.content_sha256.to_string(),
      task_json: msg.task_json.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__PutTaskGroup_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PutTaskGroup_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: std::string::String,

    /// Current robot-side revision expected by the client. 0 means create-only.
    pub expected_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: std::string::String,

}



impl Default for PutTaskGroup_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::PutTaskGroup_Request::default())
  }
}

impl rosidl_runtime_rs::Message for PutTaskGroup_Request {
  type RmwMsg = super::srv::rmw::PutTaskGroup_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        expected_revision: msg.expected_revision,
        client_request_id: msg.client_request_id.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      expected_revision: msg.expected_revision,
        client_request_id: msg.client_request_id.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      expected_revision: msg.expected_revision,
      client_request_id: msg.client_request_id.to_string(),
      task_json: msg.task_json.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__PutTaskGroup_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub content_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_json: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::PutTaskGroup_Response::default())
  }
}

impl rosidl_runtime_rs::Message for PutTaskGroup_Response {
  type RmwMsg = super::srv::rmw::PutTaskGroup_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        duplicate_request: msg.duplicate_request,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        revision: msg.revision,
        content_sha256: msg.content_sha256.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
      duplicate_request: msg.duplicate_request,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      revision: msg.revision,
        content_sha256: msg.content_sha256.as_str().into(),
        task_json: msg.task_json.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      duplicate_request: msg.duplicate_request,
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      revision: msg.revision,
      content_sha256: msg.content_sha256.to_string(),
      task_json: msg.task_json.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ArchiveTaskGroup_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ArchiveTaskGroup_Request {

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
    pub expected_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,

}



impl Default for ArchiveTaskGroup_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ArchiveTaskGroup_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ArchiveTaskGroup_Request {
  type RmwMsg = super::srv::rmw::ArchiveTaskGroup_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        expected_revision: msg.expected_revision,
        client_request_id: msg.client_request_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      expected_revision: msg.expected_revision,
        client_request_id: msg.client_request_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      expected_revision: msg.expected_revision,
      client_request_id: msg.client_request_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ArchiveTaskGroup_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_group_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub archived_revision: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub archived_relative_path: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ArchiveTaskGroup_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ArchiveTaskGroup_Response {
  type RmwMsg = super::srv::rmw::ArchiveTaskGroup_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
        duplicate_request: msg.duplicate_request,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
        archived_revision: msg.archived_revision,
        archived_relative_path: msg.archived_relative_path.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        blocker_code: msg.blocker_code.as_str().into(),
        operator_message: msg.operator_message.as_str().into(),
        technical_message: msg.technical_message.as_str().into(),
      duplicate_request: msg.duplicate_request,
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        task_group_id: msg.task_group_id.as_str().into(),
      archived_revision: msg.archived_revision,
        archived_relative_path: msg.archived_relative_path.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      blocker_code: msg.blocker_code.to_string(),
      operator_message: msg.operator_message.to_string(),
      technical_message: msg.technical_message.to_string(),
      duplicate_request: msg.duplicate_request,
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      task_group_id: msg.task_group_id.to_string(),
      archived_revision: msg.archived_revision,
      archived_relative_path: msg.archived_relative_path.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__GetNavigationSession_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetNavigationSession_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub session_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub client_request_id: std::string::String,

}



impl Default for GetNavigationSession_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetNavigationSession_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetNavigationSession_Request {
  type RmwMsg = super::srv::rmw::GetNavigationSession_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        session_id: msg.session_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        session_id: msg.session_id.as_str().into(),
        client_request_id: msg.client_request_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      session_id: msg.session_id.to_string(),
      client_request_id: msg.client_request_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__GetNavigationSession_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub status: super::msg::NavigationSessionStatus,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetNavigationSession_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetNavigationSession_Response {
  type RmwMsg = super::srv::rmw::GetNavigationSession_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Owned(msg.status)).into_owned(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        status: super::msg::NavigationSessionStatus::into_rmw_message(std::borrow::Cow::Borrowed(&msg.status)).into_owned(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      status: super::msg::NavigationSessionStatus::from_rmw_message(msg.status),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListBagSessions_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListBagSessions_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: std::string::String,

}



impl Default for ListBagSessions_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListBagSessions_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ListBagSessions_Request {
  type RmwMsg = super::srv::rmw::ListBagSessions_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state,
        experiment_id: msg.experiment_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      state: msg.state,
        experiment_id: msg.experiment_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state,
      experiment_id: msg.experiment_id.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListBagSessions_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub sessions: Vec<super::msg::BagSessionSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListBagSessions_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ListBagSessions_Response {
  type RmwMsg = super::srv::rmw::ListBagSessions_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        sessions: msg.sessions
          .into_iter()
          .map(|elem| super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        sessions: msg.sessions
          .iter()
          .map(|elem| super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      sessions: msg.sessions
          .into_iter()
          .map(super::msg::BagSessionSummary::from_rmw_message)
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ListExperiments_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListExperiments_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

}



impl Default for ListExperiments_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListExperiments_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ListExperiments_Request {
  type RmwMsg = super::srv::rmw::ListExperiments_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        state: msg.state,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      state: msg.state,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      state: msg.state,
    }
  }
}


// Corresponds to agt_interfaces__srv__ListExperiments_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub experiments: Vec<super::msg::ExperimentSummary>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListExperiments_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ListExperiments_Response {
  type RmwMsg = super::srv::rmw::ListExperiments_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        experiments: msg.experiments
          .into_iter()
          .map(|elem| super::msg::ExperimentSummary::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        experiments: msg.experiments
          .iter()
          .map(|elem| super::msg::ExperimentSummary::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      experiments: msg.experiments
          .into_iter()
          .map(super::msg::ExperimentSummary::from_rmw_message)
          .collect(),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ManageBagSession_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ManageBagSession_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub operation: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bag_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub experiment_title: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub objective: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub hypothesis: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tags_json: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_note: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub profile_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub playback_rate: f64,


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
    pub map_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_version_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub map_sha256: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub platform_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub calibration_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub nav2_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub launch_profile: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_experiment: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub event_type: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub metadata_json: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result_status: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ManageBagSession_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ManageBagSession_Request {
  type RmwMsg = super::srv::rmw::ManageBagSession_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        operation: msg.operation,
        bag_id: msg.bag_id.as_str().into(),
        experiment_id: msg.experiment_id.as_str().into(),
        experiment_title: msg.experiment_title.as_str().into(),
        objective: msg.objective.as_str().into(),
        hypothesis: msg.hypothesis.as_str().into(),
        tags_json: msg.tags_json.as_str().into(),
        operator_note: msg.operator_note.as_str().into(),
        profile_id: msg.profile_id.as_str().into(),
        playback_rate: msg.playback_rate,
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        mission_sha256: msg.mission_sha256.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_sha256: msg.map_sha256.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        calibration_profile: msg.calibration_profile.as_str().into(),
        nav2_profile: msg.nav2_profile.as_str().into(),
        launch_profile: msg.launch_profile.as_str().into(),
        start_experiment: msg.start_experiment,
        event_type: msg.event_type.as_str().into(),
        metadata_json: msg.metadata_json.as_str().into(),
        result_status: msg.result_status.as_str().into(),
        reason: msg.reason.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      operation: msg.operation,
        bag_id: msg.bag_id.as_str().into(),
        experiment_id: msg.experiment_id.as_str().into(),
        experiment_title: msg.experiment_title.as_str().into(),
        objective: msg.objective.as_str().into(),
        hypothesis: msg.hypothesis.as_str().into(),
        tags_json: msg.tags_json.as_str().into(),
        operator_note: msg.operator_note.as_str().into(),
        profile_id: msg.profile_id.as_str().into(),
      playback_rate: msg.playback_rate,
        mission_id: msg.mission_id.as_str().into(),
        mission_version: msg.mission_version.as_str().into(),
        mission_sha256: msg.mission_sha256.as_str().into(),
        map_id: msg.map_id.as_str().into(),
        map_version_id: msg.map_version_id.as_str().into(),
        map_sha256: msg.map_sha256.as_str().into(),
        platform_profile: msg.platform_profile.as_str().into(),
        calibration_profile: msg.calibration_profile.as_str().into(),
        nav2_profile: msg.nav2_profile.as_str().into(),
        launch_profile: msg.launch_profile.as_str().into(),
      start_experiment: msg.start_experiment,
        event_type: msg.event_type.as_str().into(),
        metadata_json: msg.metadata_json.as_str().into(),
        result_status: msg.result_status.as_str().into(),
        reason: msg.reason.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      operation: msg.operation,
      bag_id: msg.bag_id.to_string(),
      experiment_id: msg.experiment_id.to_string(),
      experiment_title: msg.experiment_title.to_string(),
      objective: msg.objective.to_string(),
      hypothesis: msg.hypothesis.to_string(),
      tags_json: msg.tags_json.to_string(),
      operator_note: msg.operator_note.to_string(),
      profile_id: msg.profile_id.to_string(),
      playback_rate: msg.playback_rate,
      mission_id: msg.mission_id.to_string(),
      mission_version: msg.mission_version.to_string(),
      mission_sha256: msg.mission_sha256.to_string(),
      map_id: msg.map_id.to_string(),
      map_version_id: msg.map_version_id.to_string(),
      map_sha256: msg.map_sha256.to_string(),
      platform_profile: msg.platform_profile.to_string(),
      calibration_profile: msg.calibration_profile.to_string(),
      nav2_profile: msg.nav2_profile.to_string(),
      launch_profile: msg.launch_profile.to_string(),
      start_experiment: msg.start_experiment,
      event_type: msg.event_type.to_string(),
      metadata_json: msg.metadata_json.to_string(),
      result_status: msg.result_status.to_string(),
      reason: msg.reason.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__ManageBagSession_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub session: super::msg::BagSessionSummary,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ManageBagSession_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ManageBagSession_Response {
  type RmwMsg = super::srv::rmw::ManageBagSession_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        session: super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Owned(msg.session)).into_owned(),
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
        session: super::msg::BagSessionSummary::into_rmw_message(std::borrow::Cow::Borrowed(&msg.session)).into_owned(),
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      session: super::msg::BagSessionSummary::from_rmw_message(msg.session),
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to agt_interfaces__srv__SetLocalizationMode_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetLocalizationMode_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetLocalizationMode_Request {
  type RmwMsg = super::srv::rmw::SetLocalizationMode_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
    }
  }
}


// Corresponds to agt_interfaces__srv__SetLocalizationMode_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub message: std::string::String,

}



impl Default for SetLocalizationMode_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetLocalizationMode_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetLocalizationMode_Response {
  type RmwMsg = super::srv::rmw::SetLocalizationMode_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        error_code: msg.error_code,
        active_mode: msg.active_mode,
        attempts: msg.attempts,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
      error_code: msg.error_code,
      active_mode: msg.active_mode,
      attempts: msg.attempts,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      error_code: msg.error_code,
      active_mode: msg.active_mode,
      attempts: msg.attempts,
      message: msg.message.to_string(),
    }
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


