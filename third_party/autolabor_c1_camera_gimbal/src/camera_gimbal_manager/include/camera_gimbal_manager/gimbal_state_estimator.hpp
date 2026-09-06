#ifndef CAMERA_GIMBAL_MANAGER__GIMBAL_STATE_ESTIMATOR_HPP_
#define CAMERA_GIMBAL_MANAGER__GIMBAL_STATE_ESTIMATOR_HPP_

#include <chrono>
#include <cstddef>
#include <deque>
#include <vector>

namespace camera_gimbal_manager
{

struct Angles
{
  double heading{0.0};
  double roll{0.0};
  double pitch{0.0};
};

class GimbalStateEstimator
{
public:
  using Clock = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;

  GimbalStateEstimator(
    std::size_t filter_window_size = 5,
    std::size_t arrival_window_size = 10,
    double tolerance_deg = 1.5,
    double stable_duration_s = 0.5);

  static double median(std::vector<double> values);

  void update(const Angles & raw, const Angles & target, TimePoint now = Clock::now());
  const Angles & raw() const {return raw_;}
  const Angles & filtered() const {return filtered_;}
  bool stable() const {return stable_;}

private:
  struct Sample
  {
    Angles filtered;
    Angles target;
    TimePoint time;
  };

  static double axis_median(const std::deque<double> & values);
  static double axis_error(const Angles & a, const Angles & b);
  void trim_windows();

  std::size_t filter_window_size_;
  std::size_t arrival_window_size_;
  double tolerance_deg_;
  std::chrono::duration<double> stable_duration_;
  std::deque<double> heading_samples_;
  std::deque<double> roll_samples_;
  std::deque<double> pitch_samples_;
  std::deque<Sample> arrival_samples_;
  Angles raw_;
  Angles filtered_;
  bool stable_{false};
  bool qualifying_{false};
  TimePoint qualifying_since_{};
};

}  // namespace camera_gimbal_manager

#endif  // CAMERA_GIMBAL_MANAGER__GIMBAL_STATE_ESTIMATOR_HPP_
