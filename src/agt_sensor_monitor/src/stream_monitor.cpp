#include "agt_sensor_monitor/stream_monitor.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

namespace agt_sensor_monitor
{

StreamMonitor::StreamMonitor(StreamConfig config, std::size_t window_size,
  double rollback_tolerance_sec)
: config_(std::move(config)), window_size_(std::max<std::size_t>(2U, window_size)),
  tolerance_(std::max(0.0, rollback_tolerance_sec))
{}

void StreamMonitor::observe(double stamp, double receive)
{
  if (!received_) {
    first_receive_ = receive;
    first_stamp_ = stamp;
    received_ = true;
  } else {
    const double delta = stamp - last_stamp_;
    if (delta < -tolerance_) {
      ++rollback_count_;
      monotonic_ = false;
    } else if (std::abs(delta) <= tolerance_) {
      ++duplicate_count_;
    }
  }
  last_receive_ = receive;
  last_stamp_ = stamp;
  ++count_;
  receive_window_.push_back(receive);
  while (receive_window_.size() > window_size_) receive_window_.pop_front();
}

StreamStatus StreamMonitor::status(double now_ros, double now_steady,
  double startup_elapsed, double startup_grace) const
{
  StreamStatus result;
  result.enabled = config_.enabled;
  result.required = config_.required;
  result.received_count = count_;
  result.first_receive_time = first_receive_;
  result.last_receive_time = last_receive_;
  result.first_message_stamp = first_stamp_;
  result.last_message_stamp = last_stamp_;
  result.received_once = received_;
  result.timestamp_monotonic = monotonic_;
  result.rollback_count = rollback_count_;
  result.duplicate_stamp_count = duplicate_count_;
  if (!received_) {
    result.receive_age_sec = std::numeric_limits<double>::infinity();
    result.message_age_sec = std::numeric_limits<double>::infinity();
  } else {
    result.receive_age_sec = std::max(0.0, now_steady - last_receive_);
    result.message_age_sec = std::max(0.0, now_ros - last_stamp_);
  }
  result.stale = !received_ || result.receive_age_sec > config_.max_stale_sec ||
    result.message_age_sec > config_.max_message_age_sec;
  if (receive_window_.size() >= 2U) {
    const double span = receive_window_.back() - receive_window_.front();
    if (span > 0.0) result.estimated_rate_hz = (receive_window_.size() - 1U) / span;
  }
  const bool warming = startup_elapsed < startup_grace;
  result.rate_ok = warming || (receive_window_.size() < 2U) ||
    result.estimated_rate_hz >= config_.min_rate_hz;
  const bool fatal_timestamp = !result.timestamp_monotonic && config_.rollback_fatal;
  const bool fatal_duplicate = config_.duplicate_fatal && result.duplicate_stamp_count > 0U;
  result.healthy = config_.enabled && result.received_once && !result.stale &&
    result.rate_ok && !fatal_timestamp && !fatal_duplicate;
  return result;
}

}  // namespace agt_sensor_monitor
