#pragma once

#include <stdexcept>
#include <string>

#include <sensor_msgs/msg/nav_sat_fix.hpp>

namespace agt_sensor_adapters
{

inline void validateNavSatTopics(
  const std::string & input_topic,
  const std::string & output_topic)
{
  if (input_topic.empty() || input_topic.front() != '/') {
    throw std::invalid_argument("input_topic must be a non-empty absolute topic");
  }
  if (output_topic.empty() || output_topic.front() != '/') {
    throw std::invalid_argument("output_topic must be a non-empty absolute topic");
  }
  if (input_topic == output_topic) {
    throw std::invalid_argument("input_topic must not equal output_topic");
  }
}

inline sensor_msgs::msg::NavSatFix normalizeNavSatFix(
  const sensor_msgs::msg::NavSatFix & input,
  const std::string & frame_id)
{
  auto output = input;
  output.header.frame_id = frame_id;
  return output;
}

}  // namespace agt_sensor_adapters
