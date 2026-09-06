#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace agt_asensing_driver
{
class SerialPort
{
public:
  ~SerialPort();
  bool open(const std::string & port, int baudrate);
  void close();
  bool is_open() const { return fd_ >= 0; }
  std::vector<uint8_t> read_available();
  bool write(const std::vector<uint8_t> & data);

private:
  int fd_{-1};
};
}  // namespace agt_asensing_driver
