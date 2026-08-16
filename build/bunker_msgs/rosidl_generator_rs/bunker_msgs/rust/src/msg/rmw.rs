#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "bunker_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerActuatorState() -> *const std::ffi::c_void;
}

#[link(name = "bunker_msgs__rosidl_generator_c")]
extern "C" {
    fn bunker_msgs__msg__BunkerActuatorState__init(msg: *mut BunkerActuatorState) -> bool;
    fn bunker_msgs__msg__BunkerActuatorState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BunkerActuatorState>, size: usize) -> bool;
    fn bunker_msgs__msg__BunkerActuatorState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BunkerActuatorState>);
    fn bunker_msgs__msg__BunkerActuatorState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BunkerActuatorState>, out_seq: *mut rosidl_runtime_rs::Sequence<BunkerActuatorState>) -> bool;
}

// Corresponds to bunker_msgs__msg__BunkerActuatorState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// define DRIVER_STATE_INPUT_VOLTAGE_LOW_MASK ((uint8_t)0x01)
/// define DRIVER_STATE_MOTOR_OVERHEAT_MASK ((uint8_t)0x02)
/// define DRIVER_STATE_DRIVER_OVERLOAD_MASK ((uint8_t)0x04)
/// define DRIVER_STATE_DRIVER_OVERHEAT_MASK ((uint8_t)0x08)
/// define DRIVER_STATE_SENSOR_FAULT_MASK ((uint8_t)0x10)
/// define DRIVER_STATE_DRIVER_FAULT_MASK ((uint8_t)0x20)
/// define DRIVER_STATE_DRIVER_ENABLED_MASK ((uint8_t)0x40)
/// define DRIVER_STATE_DRIVER_RESET_MASK ((uint8_t)0x80)

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bunker_msgs__msg__BunkerActuatorState__init(&mut msg as *mut _) {
        panic!("Call to bunker_msgs__msg__BunkerActuatorState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BunkerActuatorState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerActuatorState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerActuatorState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerActuatorState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BunkerActuatorState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BunkerActuatorState where Self: Sized {
  const TYPE_NAME: &'static str = "bunker_msgs/msg/BunkerActuatorState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerActuatorState() }
  }
}


#[link(name = "bunker_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerRCState() -> *const std::ffi::c_void;
}

#[link(name = "bunker_msgs__rosidl_generator_c")]
extern "C" {
    fn bunker_msgs__msg__BunkerRCState__init(msg: *mut BunkerRCState) -> bool;
    fn bunker_msgs__msg__BunkerRCState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BunkerRCState>, size: usize) -> bool;
    fn bunker_msgs__msg__BunkerRCState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BunkerRCState>);
    fn bunker_msgs__msg__BunkerRCState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BunkerRCState>, out_seq: *mut rosidl_runtime_rs::Sequence<BunkerRCState>) -> bool;
}

// Corresponds to bunker_msgs__msg__BunkerRCState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bunker_msgs__msg__BunkerRCState__init(&mut msg as *mut _) {
        panic!("Call to bunker_msgs__msg__BunkerRCState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BunkerRCState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerRCState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerRCState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerRCState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BunkerRCState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BunkerRCState where Self: Sized {
  const TYPE_NAME: &'static str = "bunker_msgs/msg/BunkerRCState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerRCState() }
  }
}


#[link(name = "bunker_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerStatus() -> *const std::ffi::c_void;
}

#[link(name = "bunker_msgs__rosidl_generator_c")]
extern "C" {
    fn bunker_msgs__msg__BunkerStatus__init(msg: *mut BunkerStatus) -> bool;
    fn bunker_msgs__msg__BunkerStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BunkerStatus>, size: usize) -> bool;
    fn bunker_msgs__msg__BunkerStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BunkerStatus>);
    fn bunker_msgs__msg__BunkerStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BunkerStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<BunkerStatus>) -> bool;
}

// Corresponds to bunker_msgs__msg__BunkerStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BunkerStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

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
    pub actuator_states: [super::super::msg::rmw::BunkerActuatorState; 2],

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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bunker_msgs__msg__BunkerStatus__init(&mut msg as *mut _) {
        panic!("Call to bunker_msgs__msg__BunkerStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BunkerStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bunker_msgs__msg__BunkerStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BunkerStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BunkerStatus where Self: Sized {
  const TYPE_NAME: &'static str = "bunker_msgs/msg/BunkerStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bunker_msgs__msg__BunkerStatus() }
  }
}


