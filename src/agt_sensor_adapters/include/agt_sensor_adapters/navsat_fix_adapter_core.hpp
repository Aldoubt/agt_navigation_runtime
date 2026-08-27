#pragma once

#include <string>

#include <sensor_msgs/msg/nav_sat_fix.hpp>

namespace agt_sensor_adapters
{

inline sensor_msgs::msg::NavSatFix normalizeNavSatFix(
  const sensor_msgs::msg::NavSatFix & input,
  const std::string & frame_id)
{
  auto output = input;
  output.header.frame_id = frame_id;
  return output;
}

}  // namespace agt_sensor_adapters
