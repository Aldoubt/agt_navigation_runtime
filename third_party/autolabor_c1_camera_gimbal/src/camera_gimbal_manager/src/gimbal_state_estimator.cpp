#include "camera_gimbal_manager/gimbal_state_estimator.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

namespace camera_gimbal_manager
{

GimbalStateEstimator::GimbalStateEstimator(
  std::size_t filter_window_size, std::size_t arrival_window_size,
  double tolerance_deg, double stable_duration_s)
: filter_window_size_(std::max<std::size_t>(1, filter_window_size)),
  arrival_window_size_(std::max<std::size_t>(1, arrival_window_size)),
  tolerance_deg_(std::max(0.0, tolerance_deg)),
  stable_duration_(std::chrono::duration<double>(std::max(0.0, stable_duration_s)))
{
}

double GimbalStateEstimator::median(std::vector<double> values)
{
  if (values.empty()) {
    return std::numeric_limits<double>::quiet_NaN();
  }
  const auto middle = values.begin() + static_cast<std::ptrdiff_t>(values.size() / 2);
  std::nth_element(values.begin(), middle, values.end());
  if (values.size() % 2U != 0U) {
    return *middle;
  }
  const double upper = *middle;
  const auto lower = std::max_element(values.begin(), middle);
  return (*lower + upper) / 2.0;
}

double GimbalStateEstimator::axis_median(const std::deque<double> & values)
{
  return median(std::vector<double>(values.begin(), values.end()));
}

double GimbalStateEstimator::axis_error(const Angles & a, const Angles & b)
{
  return std::max({std::abs(a.heading - b.heading), std::abs(a.roll - b.roll),
    std::abs(a.pitch - b.pitch)});
}

void GimbalStateEstimator::trim_windows()
{
  while (heading_samples_.size() > filter_window_size_) {heading_samples_.pop_front();}
  while (roll_samples_.size() > filter_window_size_) {roll_samples_.pop_front();}
  while (pitch_samples_.size() > filter_window_size_) {pitch_samples_.pop_front();}
  while (arrival_samples_.size() > arrival_window_size_) {arrival_samples_.pop_front();}
}

void GimbalStateEstimator::update(const Angles & raw, const Angles & target, TimePoint now)
{
  raw_ = raw;
  heading_samples_.push_back(raw.heading);
  roll_samples_.push_back(raw.roll);
  pitch_samples_.push_back(raw.pitch);
  while (heading_samples_.size() > filter_window_size_) {heading_samples_.pop_front();}
  while (roll_samples_.size() > filter_window_size_) {roll_samples_.pop_front();}
  while (pitch_samples_.size() > filter_window_size_) {pitch_samples_.pop_front();}
  filtered_ = {axis_median(heading_samples_), axis_median(roll_samples_), axis_median(pitch_samples_)};
  arrival_samples_.push_back({filtered_, target, now});
  trim_windows();

  const Angles recent_median{
    median([&]() {std::vector<double> v; for (const auto & s : arrival_samples_) v.push_back(s.filtered.heading); return v;}()),
    median([&]() {std::vector<double> v; for (const auto & s : arrival_samples_) v.push_back(s.filtered.roll); return v;}()),
    median([&]() {std::vector<double> v; for (const auto & s : arrival_samples_) v.push_back(s.filtered.pitch); return v;}())};
  double heading_min = std::numeric_limits<double>::infinity();
  double heading_max = -std::numeric_limits<double>::infinity();
  double roll_min = heading_min;
  double roll_max = heading_max;
  double pitch_min = heading_min;
  double pitch_max = heading_max;
  for (const auto & sample : arrival_samples_) {
    heading_min = std::min(heading_min, sample.filtered.heading);
    heading_max = std::max(heading_max, sample.filtered.heading);
    roll_min = std::min(roll_min, sample.filtered.roll);
    roll_max = std::max(roll_max, sample.filtered.roll);
    pitch_min = std::min(pitch_min, sample.filtered.pitch);
    pitch_max = std::max(pitch_max, sample.filtered.pitch);
  }
  const double max_span = std::max({heading_max - heading_min, roll_max - roll_min,
    pitch_max - pitch_min});
  const bool within_tolerance = arrival_samples_.size() >= arrival_window_size_ &&
    axis_error(recent_median, target) < tolerance_deg_ &&
    axis_error(filtered_, target) < tolerance_deg_ && max_span < tolerance_deg_;
  if (!within_tolerance) {
    qualifying_ = false;
    stable_ = false;
  } else if (!qualifying_) {
    qualifying_ = true;
    // The window represents the interval over which the condition has held.
    // Start timing at its oldest sample, so a full window can satisfy the
    // configured duration as soon as it is received.
    qualifying_since_ = arrival_samples_.front().time;
    stable_ = now - qualifying_since_ >= stable_duration_;
  } else {
    stable_ = now - qualifying_since_ >= stable_duration_;
  }
}

}  // namespace camera_gimbal_manager
