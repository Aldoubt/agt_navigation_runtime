#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <stdexcept>
#include <vector>

namespace agt_sensor_adapters
{

struct AxisAlignedBox
{
  std::string name;
  std::array<double, 3> min;
  std::array<double, 3> max;
  bool verified{false};
  std::string note;

  bool contains(const std::array<double, 3> & point) const;
  AxisAlignedBox expanded(double padding) const;
};

struct SelfFilterGeometry
{
  bool enabled{false};
  std::string frame;
  double padding{0.0};
  bool include_chassis_body{false};
  std::vector<AxisAlignedBox> boxes;

  bool contains(const std::array<double, 3> & point) const;
  std::vector<AxisAlignedBox> expanded_boxes() const;
  bool has_unverified_box() const;
};

SelfFilterGeometry load_self_filter_geometry(const std::string & profile_path);

template<typename PointT>
std::vector<PointT> copy_points_in_order(
  const std::vector<PointT> & source, const std::vector<std::size_t> & indices)
{
  std::vector<PointT> result;
  result.reserve(indices.size());
  for (const auto index : indices) {
    if (index >= source.size()) {
      throw std::out_of_range("point selection index is outside the source message");
    }
    result.push_back(source[index]);
  }
  return result;
}

}  // namespace agt_sensor_adapters
