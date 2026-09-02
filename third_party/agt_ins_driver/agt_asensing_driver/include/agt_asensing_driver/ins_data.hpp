#pragma once

#include <cstdint>
#include <Eigen/Core>

namespace agt_asensing_driver
{
struct INSData
{
  double latitude{0.0};
  double longitude{0.0};
  double altitude{0.0};
  double roll{0.0};
  double pitch{0.0};
  double yaw{0.0};
  double north_velocity{0.0};
  double east_velocity{0.0};
  double ground_velocity{0.0};
  Eigen::Vector3d gyro{Eigen::Vector3d::Zero()};
  Eigen::Vector3d accel{Eigen::Vector3d::Zero()};
  uint8_t ins_status{0};
  uint8_t position_type{0};
  uint8_t heading_type{0};
  uint8_t num_sv{0};
  double latitude_std{0.0};
  double longitude_std{0.0};
  double altitude_std{0.0};
  double north_velocity_std{0.0};
  double east_velocity_std{0.0};
  double ground_velocity_std{0.0};
  double roll_std{0.0};
  double pitch_std{0.0};
  double yaw_std{0.0};
  uint32_t gps_week{0};
  uint32_t gps_time_ms{0};
  float temperature{0.0F};
  uint8_t wheel_speed_status{0};
  bool has_position_status{false};
};
}  // namespace agt_asensing_driver
