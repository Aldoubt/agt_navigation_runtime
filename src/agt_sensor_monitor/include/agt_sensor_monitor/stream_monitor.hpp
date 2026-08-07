#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>

namespace agt_sensor_monitor
{

struct StreamConfig
{
  bool enabled{true};
  bool required{true};
  std::string name;
  std::string topic;
  double min_rate_hz{0.0};
  double max_stale_sec{1.0};
  double max_message_age_sec{1.0};
  bool duplicate_fatal{false};
  bool rollback_fatal{true};
};

struct StreamStatus
{
  bool enabled{false};
  bool required{false};
  std::uint64_t received_count{0};
  double first_receive_time{0.0};
  double last_receive_time{0.0};
  double first_message_stamp{0.0};
  double last_message_stamp{0.0};
  double estimated_rate_hz{0.0};
  double message_age_sec{0.0};
  double receive_age_sec{0.0};
  bool timestamp_monotonic{true};
  std::uint64_t rollback_count{0};
  std::uint64_t duplicate_stamp_count{0};
  bool stale{true};
  bool rate_ok{false};
  bool received_once{false};
  bool healthy{false};
};

class StreamMonitor
{
public:
  explicit StreamMonitor(StreamConfig config, std::size_t window_size = 50U,
    double rollback_tolerance_sec = 1e-6);

  void observe(double message_stamp_sec, double receive_steady_sec);
  StreamStatus status(double now_ros_sec, double now_steady_sec,
    double startup_elapsed_sec, double startup_grace_sec) const;
  const StreamConfig & config() const { return config_; }

private:
  StreamConfig config_;
  std::size_t window_size_;
  double tolerance_;
  std::uint64_t count_{0};
  double first_receive_{0.0};
  double last_receive_{0.0};
  double first_stamp_{0.0};
  double last_stamp_{0.0};
  bool received_{false};
  bool monotonic_{true};
  std::uint64_t rollback_count_{0};
  std::uint64_t duplicate_count_{0};
  std::deque<double> receive_window_;
};

}  // namespace agt_sensor_monitor
