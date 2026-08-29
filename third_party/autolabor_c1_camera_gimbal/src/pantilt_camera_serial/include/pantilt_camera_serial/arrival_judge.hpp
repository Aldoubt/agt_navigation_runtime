#ifndef PANTILT_CAMERA_SERIAL__ARRIVAL_JUDGE_HPP_
#define PANTILT_CAMERA_SERIAL__ARRIVAL_JUDGE_HPP_

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace autolabor_driver
{

struct Angles
{
  double heading{0.0};
  double roll{0.0};
  double pitch{0.0};
};

class ArrivalJudge
{
public:
  ArrivalJudge() = default;

  ArrivalJudge(const Angles & target, double tolerance, std::uint32_t stable_samples)
  {
    reset(target, tolerance, stable_samples);
  }

  void reset(const Angles & target, double tolerance, std::uint32_t stable_samples)
  {
    target_ = target;
    tolerance_ = std::max(0.0, tolerance);
    stable_samples_required_ = std::max<std::uint32_t>(1U, stable_samples);
    stable_count_ = 0U;
    reached_ = false;
  }

  bool observe(const Angles & current)
  {
    if (max_error(current) <= tolerance_) {
      stable_count_++;
    } else {
      stable_count_ = 0U;
    }
    reached_ = stable_count_ >= stable_samples_required_;
    return reached_;
  }

  double max_error(const Angles & current) const
  {
    return std::max({
      std::abs(current.heading - target_.heading),
      std::abs(current.roll - target_.roll),
      std::abs(current.pitch - target_.pitch)});
  }

  std::uint32_t stable_count() const {return stable_count_;}
  std::uint32_t stable_samples_required() const {return stable_samples_required_;}
  bool reached() const {return reached_;}
  const Angles & target() const {return target_;}
  double tolerance() const {return tolerance_;}

private:
  Angles target_{};
  double tolerance_{1.0};
  std::uint32_t stable_samples_required_{3U};
  std::uint32_t stable_count_{0U};
  bool reached_{false};
};

}  // namespace autolabor_driver

#endif  // PANTILT_CAMERA_SERIAL__ARRIVAL_JUDGE_HPP_
