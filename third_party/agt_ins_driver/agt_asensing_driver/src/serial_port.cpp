#include "agt_asensing_driver/serial_port.hpp"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cerrno>

namespace agt_asensing_driver
{
SerialPort::~SerialPort() { close(); }

bool SerialPort::open(const std::string & port, int baudrate)
{
  close();
  fd_ = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (fd_ < 0) return false;
  termios options{};
  if (tcgetattr(fd_, &options) != 0) { close(); return false; }
  cfmakeraw(&options);
  speed_t speed = B230400;
  if (baudrate == 9600) speed = B9600; else if (baudrate == 19200) speed = B19200;
  else if (baudrate == 38400) speed = B38400; else if (baudrate == 57600) speed = B57600;
  else if (baudrate == 115200) speed = B115200;
  else if (baudrate != 230400) { close(); return false; }
  cfsetispeed(&options, speed); cfsetospeed(&options, speed);
  options.c_cflag |= (CLOCAL | CREAD);
  options.c_cflag &= ~CSTOPB; options.c_cflag &= ~CRTSCTS; options.c_cflag &= ~PARENB;
  if (tcsetattr(fd_, TCSANOW, &options) != 0) { close(); return false; }
  return true;
}

void SerialPort::close() { if (fd_ >= 0) { ::close(fd_); fd_ = -1; } }

std::vector<uint8_t> SerialPort::read_available()
{
  std::vector<uint8_t> data(4096); if (fd_ < 0) return {};
  const ssize_t n = ::read(fd_, data.data(), data.size());
  if (n <= 0) return {}; data.resize(static_cast<std::size_t>(n)); return data;
}

bool SerialPort::write(const std::vector<uint8_t> & data)
{ return fd_ >= 0 && ::write(fd_, data.data(), data.size()) == static_cast<ssize_t>(data.size()); }
}  // namespace agt_asensing_driver
