#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to bunker_msgs__msg__BunkerActuatorState
/// define DRIVER_STATE_INPUT_VOLTAGE_LOW_MASK ((uint8_t)0x01)
/// define DRIVER_STATE_MOTOR_OVERHEAT_MASK ((uint8_t)0x02)
/// define DRIVER_STATE_DRIVER_OVERLOAD_MASK ((uint8_t)0x04)
/// define DRIVER_STATE_DRIVER_OVERHEAT_MASK ((uint8_t)0x08)
/// define DRIVER_STATE_SENSOR_FAULT_MASK ((uint8_t)0x10)
/// define DRIVER_STATE_DRIVER_FAULT_MASK ((uint8_t)0x20)
/// define DRIVER_STATE_DRIVER_ENABLED_MASK ((uint8_t)0x40)
/// define DRIVER_STATE_DRIVER_RESET_MASK ((uint8_t)0x80)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BunkerActuatorState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub motor_id: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rpm: i16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub current: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pulse_count: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub driver_voltage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub driver_temperature: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub motor_temperature: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub driver_state: u8,

}



impl Default for BunkerActuatorState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BunkerActuatorState::default())
  }
}

impl rosidl_runtime_rs::Message for BunkerActuatorState {
  type RmwMsg = super::msg::rmw::BunkerActuatorState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        motor_id: msg.motor_id,
        rpm: msg.rpm,
        current: msg.current,
        pulse_count: msg.pulse_count,
        driver_voltage: msg.driver_voltage,
        driver_temperature: msg.driver_temperature,
        motor_temperature: msg.motor_temperature,
        driver_state: msg.driver_state,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      motor_id: msg.motor_id,
      rpm: msg.rpm,
      current: msg.current,
      pulse_count: msg.pulse_count,
      driver_voltage: msg.driver_voltage,
      driver_temperature: msg.driver_temperature,
      motor_temperature: msg.motor_temperature,
      driver_state: msg.driver_state,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      motor_id: msg.motor_id,
      rpm: msg.rpm,
      current: msg.current,
      pulse_count: msg.pulse_count,
      driver_voltage: msg.driver_voltage,
      driver_temperature: msg.driver_temperature,
      motor_temperature: msg.motor_temperature,
      driver_state: msg.driver_state,
    }
  }
}


// Corresponds to bunker_msgs__msg__BunkerRCState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BunkerRCState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub swa: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub swb: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub swc: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub swd: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stick_right_v: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stick_right_h: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stick_left_v: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stick_left_h: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub var_a: i8,

}



impl Default for BunkerRCState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BunkerRCState::default())
  }
}

impl rosidl_runtime_rs::Message for BunkerRCState {
  type RmwMsg = super::msg::rmw::BunkerRCState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        swa: msg.swa,
        swb: msg.swb,
        swc: msg.swc,
        swd: msg.swd,
        stick_right_v: msg.stick_right_v,
        stick_right_h: msg.stick_right_h,
        stick_left_v: msg.stick_left_v,
        stick_left_h: msg.stick_left_h,
        var_a: msg.var_a,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      swa: msg.swa,
      swb: msg.swb,
      swc: msg.swc,
      swd: msg.swd,
      stick_right_v: msg.stick_right_v,
      stick_right_h: msg.stick_right_h,
      stick_left_v: msg.stick_left_v,
      stick_left_h: msg.stick_left_h,
      var_a: msg.var_a,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      swa: msg.swa,
      swb: msg.swb,
      swc: msg.swc,
      swd: msg.swd,
      stick_right_v: msg.stick_right_v,
      stick_right_h: msg.stick_right_h,
      stick_left_v: msg.stick_left_v,
      stick_left_h: msg.stick_left_h,
      var_a: msg.var_a,
    }
  }
}


// Corresponds to bunker_msgs__msg__BunkerStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BunkerStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// motion state
    pub linear_velocity: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angular_velocity: f64,

    /// base state
    pub vehicle_state: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub control_mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub error_code: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_voltage: f64,

    /// motor state
    pub actuator_states: [super::msg::BunkerActuatorState; 2],

}

impl BunkerStatus {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MOTOR_ID_FRONT_RIGHT: i8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MOTOR_ID_FRONT_LEFT: i8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MOTOR_ID_REAR_RIGHT: i8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const MOTOR_ID_REAR_LEFT: i8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const LIGHT_ID_FRONT: i8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const LIGHT_ID_REAR: i8 = 1;

}


impl Default for BunkerStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BunkerStatus::default())
  }
}

impl rosidl_runtime_rs::Message for BunkerStatus {
  type RmwMsg = super::msg::rmw::BunkerStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        linear_velocity: msg.linear_velocity,
        angular_velocity: msg.angular_velocity,
        vehicle_state: msg.vehicle_state,
        control_mode: msg.control_mode,
        error_code: msg.error_code,
        battery_voltage: msg.battery_voltage,
        actuator_states: msg.actuator_states
          .map(|elem| super::msg::BunkerActuatorState::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      linear_velocity: msg.linear_velocity,
      angular_velocity: msg.angular_velocity,
      vehicle_state: msg.vehicle_state,
      control_mode: msg.control_mode,
      error_code: msg.error_code,
      battery_voltage: msg.battery_voltage,
        actuator_states: msg.actuator_states
          .iter()
          .map(|elem| super::msg::BunkerActuatorState::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      linear_velocity: msg.linear_velocity,
      angular_velocity: msg.angular_velocity,
      vehicle_state: msg.vehicle_state,
      control_mode: msg.control_mode,
      error_code: msg.error_code,
      battery_voltage: msg.battery_voltage,
      actuator_states: msg.actuator_states
        .map(super::msg::BunkerActuatorState::from_rmw_message),
    }
  }
}


