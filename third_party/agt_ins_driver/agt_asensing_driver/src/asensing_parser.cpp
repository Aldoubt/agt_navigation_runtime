#include "agt_asensing_driver/asensing_parser.hpp"
#include <cmath>

namespace agt_asensing_driver
{
namespace
{
constexpr std::size_t kMainLength = 58;
constexpr std::size_t kExtendedLength = 63;
constexpr uint8_t kHeader[] = {0xbd, 0xdb, 0x0b};

uint16_t u16(const std::vector<uint8_t> & b, std::size_t i)
{ return static_cast<uint16_t>(b[i]) | (static_cast<uint16_t>(b[i + 1]) << 8); }
int16_t i16(const std::vector<uint8_t> & b, std::size_t i)
{ return static_cast<int16_t>(u16(b, i)); }
int32_t i32(const std::vector<uint8_t> & b, std::size_t i)
{
  return static_cast<int32_t>(static_cast<uint32_t>(b[i]) | (static_cast<uint32_t>(b[i + 1]) << 8) |
    (static_cast<uint32_t>(b[i + 2]) << 16) | (static_cast<uint32_t>(b[i + 3]) << 24));
}
uint32_t u32(const std::vector<uint8_t> & b, std::size_t i)
{ return static_cast<uint32_t>(i32(b, i)); }
bool xor_ok(const std::vector<uint8_t> & b, std::size_t length)
{
  uint8_t checksum = 0;
  for (std::size_t i = 0; i < length - 1; ++i) checksum ^= b[i];
  return checksum == b[length - 1];
}
}

std::vector<INSData> ASENSINGParser::feed(
  const uint8_t * data, std::size_t size)
{
  if (size == 0) return {};
  buffer_.insert(buffer_.end(), data, data + size);
  std::vector<INSData> result;
  while (buffer_.size() >= 3) {
    if (buffer_[0] != kHeader[0] || buffer_[1] != kHeader[1] || buffer_[2] != kHeader[2]) {
      buffer_.erase(buffer_.begin());
      continue;
    }
    if (buffer_.size() < kMainLength) break;
    if (!xor_ok(buffer_, kMainLength)) { buffer_.erase(buffer_.begin()); continue; }

    INSData d;
    d.roll = i16(buffer_, 3) * (360.0 / 32768.0) * M_PI / 180.0;
    d.pitch = i16(buffer_, 5) * (360.0 / 32768.0) * M_PI / 180.0;
    d.yaw = i16(buffer_, 7) * (360.0 / 32768.0) * M_PI / 180.0;
    for (int n = 0; n < 3; ++n) {
      d.gyro[n] = i16(buffer_, 9 + n * 2) * 300.0 / 32768.0 * M_PI / 180.0;
      d.accel[n] = i16(buffer_, 15 + n * 2) * 12.0 / 32768.0 * 9.80665;
    }
    d.latitude = i32(buffer_, 21) * 1e-7;
    d.longitude = i32(buffer_, 25) * 1e-7;
    d.altitude = i32(buffer_, 29) * 1e-3;
    d.north_velocity = i16(buffer_, 33) * 100.0 / 32768.0;
    d.east_velocity = i16(buffer_, 35) * 100.0 / 32768.0;
    d.ground_velocity = i16(buffer_, 37) * 100.0 / 32768.0;
    d.ins_status = buffer_[39] & 0x0f;
    const auto value = [](int16_t x) { return std::exp(static_cast<double>(x) / 100.0); };
    const int16_t data1 = i16(buffer_, 46), data2 = i16(buffer_, 48), data3 = i16(buffer_, 50);
    switch (buffer_[56]) {
      case 0: d.latitude_std = value(data1); d.longitude_std = value(data2); d.altitude_std = value(data3); break;
      case 1: d.north_velocity_std = value(data1); d.east_velocity_std = value(data2); d.ground_velocity_std = value(data3); break;
      case 2: d.roll_std = value(data1) * M_PI / 180.0; d.pitch_std = value(data2) * M_PI / 180.0; d.yaw_std = value(data3) * M_PI / 180.0; break;
      case 22: d.temperature = static_cast<float>(data1 * 200.0 / 32768.0); break;
      case 32: d.position_type = data1; d.num_sv = data2; d.heading_type = data3; d.has_position_status = true; break;
      case 33: d.wheel_speed_status = static_cast<uint8_t>(data2); break;
      default: break;
    }
    // GPS time is a 0.25 ms counter in bytes 52..55 of the main packet.
    d.gps_time_ms = static_cast<uint32_t>(u32(buffer_, 52) * 0.25);
    // Bytes 58..62 are the GPS-week extension in the original driver.
    if (buffer_.size() >= kExtendedLength && xor_ok(buffer_, kExtendedLength)) {
      d.gps_week = u32(buffer_, 58);
      buffer_.erase(buffer_.begin(), buffer_.begin() + kExtendedLength);
    } else {
      buffer_.erase(buffer_.begin(), buffer_.begin() + kMainLength);
    }
    result.push_back(d);
  }
  return result;
}
}  // namespace agt_asensing_driver
