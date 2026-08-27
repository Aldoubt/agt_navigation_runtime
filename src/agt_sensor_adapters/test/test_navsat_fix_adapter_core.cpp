#include <gtest/gtest.h>

#include <stdexcept>

#include "agt_sensor_adapters/navsat_fix_adapter_core.hpp"

TEST(NavSatFixAdapterCore, PreservesFixAndOnlyNormalizesFrame)
{
  sensor_msgs::msg::NavSatFix input;
  input.header.stamp.sec = 123;
  input.header.stamp.nanosec = 456789;
  input.header.frame_id = "receiver_native_frame";
  input.status.status = sensor_msgs::msg::NavSatStatus::STATUS_GBAS_FIX;
  input.status.service =
    sensor_msgs::msg::NavSatStatus::SERVICE_GPS |
    sensor_msgs::msg::NavSatStatus::SERVICE_GALILEO;
  input.latitude = 23.123456789;
  input.longitude = 113.987654321;
  input.altitude = 42.75;
  input.position_covariance = {
    0.01, 0.002, 0.003,
    0.002, 0.04, 0.005,
    0.003, 0.005, 0.09};
  input.position_covariance_type =
    sensor_msgs::msg::NavSatFix::COVARIANCE_TYPE_KNOWN;

  const auto output = agt_sensor_adapters::normalizeNavSatFix(input, "gps_link");

  EXPECT_EQ(output.header.stamp.sec, input.header.stamp.sec);
  EXPECT_EQ(output.header.stamp.nanosec, input.header.stamp.nanosec);
  EXPECT_EQ(output.header.frame_id, "gps_link");
  EXPECT_EQ(output.status.status, input.status.status);
  EXPECT_EQ(output.status.service, input.status.service);
  EXPECT_DOUBLE_EQ(output.latitude, input.latitude);
  EXPECT_DOUBLE_EQ(output.longitude, input.longitude);
  EXPECT_DOUBLE_EQ(output.altitude, input.altitude);
  EXPECT_EQ(output.position_covariance, input.position_covariance);
  EXPECT_EQ(output.position_covariance_type, input.position_covariance_type);
}

TEST(NavSatFixAdapterCore, RejectsMalformedOrSelfLoopingTopics)
{
  EXPECT_NO_THROW(
    agt_sensor_adapters::validateNavSatTopics(
      "/receiver/navsat_fix", "/agt/sensors/gnss/fix"));
  EXPECT_THROW(
    agt_sensor_adapters::validateNavSatTopics("", "/agt/sensors/gnss/fix"),
    std::invalid_argument);
  EXPECT_THROW(
    agt_sensor_adapters::validateNavSatTopics(
      "receiver/navsat_fix", "/agt/sensors/gnss/fix"),
    std::invalid_argument);
  EXPECT_THROW(
    agt_sensor_adapters::validateNavSatTopics(
      "/receiver/navsat_fix", "agt/sensors/gnss/fix"),
    std::invalid_argument);
  EXPECT_THROW(
    agt_sensor_adapters::validateNavSatTopics(
      "/agt/sensors/gnss/fix", "/agt/sensors/gnss/fix"),
    std::invalid_argument);
}
