#ifndef PANTILT_CAMERA_SERIAL__SERIAL_PROTOCOL_HPP_
#define PANTILT_CAMERA_SERIAL__SERIAL_PROTOCOL_HPP_

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "pantilt_camera_serial/arrival_judge.hpp"

namespace autolabor_driver
{

struct CommandInfo
{
  std::uint8_t cmd;
  std::vector<std::uint8_t> params;
};

struct ParsedPantiltAngles
{
  Angles ground;
  Angles encoder;
};

class PantiltProtocol
{
public:
  static constexpr std::uint8_t HEADER = 0xAA;
  static constexpr std::uint8_t FEEDBACK_HEADER = 0x55;
  static constexpr std::size_t LENGTH_IDX = 1U;
  static constexpr std::size_t COMMAND_IDX = 2U;

  static constexpr double MAX_HEADING = 160.0;
  static constexpr double MIN_HEADING = -160.0;
  static constexpr double MAX_ROLL = 40.0;
  static constexpr double MIN_ROLL = -40.0;
  static constexpr double MAX_PITCH = 90.0;
  static constexpr double MIN_PITCH = -90.0;
  static constexpr double MAX_COMMAND_SPEED = 2.0;

  enum Error : std::uint8_t
  {
    NO_ERROR = 0x00,
    NO_HEADER = 0x01,
    NO_VALID_COMMAND = 0x02,
    PARAMETER_MISMATCH = 0x03,
    CHECKSUM_ERROR = 0x04
  };

  static const std::map<std::string, CommandInfo> & command_map()
  {
    static const std::map<std::string, CommandInfo> map = {
      {"GetCameraVersion", {0x00, {0x01}}},
      {"GetProtocolVersion", {0x00, {0x02}}},
      {"GetCameraMode", {0x00, {0x03}}},
      {"GetPantiltMode", {0x00, {0x05, 0x01}}},
      {"GetPantiltPose", {0x00, {0x05, 0x02}}},
      {"SetLockMode", {0x05, {0x01, 0x00}}},
      {"SetHeadingFollow", {0x05, {0x01, 0x01}}},
      {"SetHeadingPitchFollow", {0x05, {0x01, 0x02}}},
      {"SetFullFollowMode", {0x05, {0x01, 0x03}}},
      {"BackToCenter", {0x05, {0x02}}},
      {"SetPantiltSpeed", {0x05, {0x06}}},
      {"SetPantiltAngle", {0x05, {0x05}}}
    };
    return map;
  }
};

class PantiltUtils
{
public:
  static bool is_known_command(const std::string & command_name)
  {
    return PantiltProtocol::command_map().find(command_name) != PantiltProtocol::command_map().end();
  }

  static bool is_mutating_command(const std::string & command_name)
  {
    return command_name.rfind("Set", 0U) == 0U || command_name == "BackToCenter";
  }

  static std::uint8_t crc8_calculate(const std::vector<std::uint8_t> & data)
  {
    std::uint8_t crc = 0;
    for (const auto byte : data) {
      crc ^= byte;
      for (int i = 0; i < 8; ++i) {
        crc = (crc & 0x80U) ? static_cast<std::uint8_t>((crc << 1U) ^ 0xD5U) :
          static_cast<std::uint8_t>(crc << 1U);
      }
    }
    return crc;
  }

  static std::vector<std::uint8_t> build_command(
    const std::string & command_name,
    const std::vector<std::uint8_t> & data)
  {
    const auto it = PantiltProtocol::command_map().find(command_name);
    if (it == PantiltProtocol::command_map().end()) {
      return {};
    }

    std::vector<std::uint8_t> command;
    command.reserve(4U + it->second.params.size() + data.size());
    command.push_back(PantiltProtocol::HEADER);
    const auto length = static_cast<std::uint8_t>(4U + it->second.params.size() + data.size());
    command.push_back(length);
    command.push_back(it->second.cmd);
    command.insert(command.end(), it->second.params.begin(), it->second.params.end());
    command.insert(command.end(), data.begin(), data.end());
    command.push_back(crc8_calculate(command));
    return command;
  }

  static bool angles_in_range(double heading, double roll, double pitch)
  {
    return std::isfinite(heading) && std::isfinite(roll) && std::isfinite(pitch) &&
           heading >= PantiltProtocol::MIN_HEADING && heading <= PantiltProtocol::MAX_HEADING &&
           roll >= PantiltProtocol::MIN_ROLL && roll <= PantiltProtocol::MAX_ROLL &&
           pitch >= PantiltProtocol::MIN_PITCH && pitch <= PantiltProtocol::MAX_PITCH;
  }

  static bool speeds_in_range(double heading_speed, double pitch_speed)
  {
    return std::isfinite(heading_speed) && std::isfinite(pitch_speed) &&
           std::abs(heading_speed) <= PantiltProtocol::MAX_COMMAND_SPEED &&
           std::abs(pitch_speed) <= PantiltProtocol::MAX_COMMAND_SPEED;
  }

  // Preserve the original driver's outgoing byte order exactly: high byte first.
  static std::vector<std::uint8_t> int16_to_protocol_bytes(std::int16_t value)
  {
    const auto raw = static_cast<std::uint16_t>(value);
    return {
      static_cast<std::uint8_t>((raw >> 8U) & 0xFFU),
      static_cast<std::uint8_t>(raw & 0xFFU)};
  }

  static std::vector<std::uint8_t> prepare_motion_data(double heading, double roll, double pitch)
  {
    if (!angles_in_range(heading, roll, pitch)) {
      return {};
    }
    std::vector<std::uint8_t> data;
    for (const double angle : {heading, roll, pitch}) {
      const auto bytes = int16_to_protocol_bytes(static_cast<std::int16_t>(angle * 10.0));
      data.insert(data.end(), bytes.begin(), bytes.end());
    }
    data.push_back(0x01);
    return data;
  }

  static std::vector<std::uint8_t> prepare_speed_data(double heading_speed, double pitch_speed)
  {
    if (!speeds_in_range(heading_speed, pitch_speed)) {
      return {};
    }
    const auto heading_bytes = int16_to_protocol_bytes(
      static_cast<std::int16_t>(-heading_speed * 50.0));
    const auto pitch_bytes = int16_to_protocol_bytes(
      static_cast<std::int16_t>(-pitch_speed * 50.0));
    std::vector<std::uint8_t> data;
    data.insert(data.end(), heading_bytes.begin(), heading_bytes.end());
    data.insert(data.end(), pitch_bytes.begin(), pitch_bytes.end());
    return data;
  }

  // Preserve the original driver's incoming decode convention: low byte first.
  static std::int16_t parse_int16_le(const std::vector<std::uint8_t> & data, std::size_t index)
  {
    const auto low = static_cast<std::uint16_t>(data.at(index));
    const auto high = static_cast<std::uint16_t>(data.at(index + 1U));
    const std::uint16_t raw = static_cast<std::uint16_t>(low | (high << 8U));
    const std::int32_t signed_value = raw >= 0x8000U ?
      static_cast<std::int32_t>(raw) - 0x10000 : static_cast<std::int32_t>(raw);
    return static_cast<std::int16_t>(signed_value);
  }

  static std::optional<ParsedPantiltAngles> parse_angles(const std::vector<std::uint8_t> & frame)
  {
    if (frame.size() < 16U) {
      return std::nullopt;
    }
    ParsedPantiltAngles angles;
    angles.ground.heading = parse_int16_le(frame, 4U) / 100.0;
    angles.ground.roll = parse_int16_le(frame, 6U) / 100.0;
    angles.ground.pitch = parse_int16_le(frame, 8U) / 100.0;
    angles.encoder.heading = parse_int16_le(frame, 10U) / 100.0;
    angles.encoder.roll = parse_int16_le(frame, 12U) / 100.0;
    angles.encoder.pitch = parse_int16_le(frame, 14U) / 100.0;
    return angles;
  }

  static std::pair<bool, std::string> check_frame_error(const std::vector<std::uint8_t> & frame)
  {
    if (frame.size() < 4U) {
      return {false, "frame too short"};
    }
    switch (frame[3U]) {
      case PantiltProtocol::NO_ERROR: return {true, "no error"};
      case PantiltProtocol::NO_HEADER: return {false, "device reported missing 0xAA header"};
      case PantiltProtocol::NO_VALID_COMMAND: return {false, "device rejected command"};
      case PantiltProtocol::PARAMETER_MISMATCH: return {false, "device reported parameter mismatch"};
      case PantiltProtocol::CHECKSUM_ERROR: return {false, "device reported checksum error"};
      default: return {false, "device reported unknown protocol error"};
    }
  }
};

}  // namespace autolabor_driver

#endif  // PANTILT_CAMERA_SERIAL__SERIAL_PROTOCOL_HPP_
