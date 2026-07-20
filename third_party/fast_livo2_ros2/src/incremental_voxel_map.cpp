#include "incremental_voxel_map.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace fast_livo
{
namespace
{

std::uint64_t mix64(std::uint64_t value)
{
  value += 0x9e3779b97f4a7c15ULL;
  value = (value ^ (value >> 30U)) * 0xbf58476d1ce4e5b9ULL;
  value = (value ^ (value >> 27U)) * 0x94d049bb133111ebULL;
  return value ^ (value >> 31U);
}

}  // namespace

IncrementalVoxelMap::IncrementalVoxelMap(double leaf_size, double max_abs_coordinate)
: leaf_size_(leaf_size), inverse_leaf_size_(0.0),
  max_abs_coordinate_(max_abs_coordinate)
{
  if (!std::isfinite(leaf_size) || leaf_size <= 0.0) {
    throw std::invalid_argument("incremental voxel leaf size must be finite and positive");
  }
  if (!std::isfinite(max_abs_coordinate) || max_abs_coordinate <= 0.0) {
    throw std::invalid_argument("maximum absolute coordinate must be finite and positive");
  }
  inverse_leaf_size_ = 1.0 / leaf_size_;
}

bool IncrementalVoxelMap::VoxelKey::operator==(const VoxelKey & other) const
{
  return x == other.x && y == other.y && z == other.z;
}

std::size_t IncrementalVoxelMap::VoxelKeyHash::operator()(const VoxelKey & key) const
{
  const auto x_hash = mix64(static_cast<std::uint64_t>(key.x));
  const auto y_hash = mix64(static_cast<std::uint64_t>(key.y));
  const auto z_hash = mix64(static_cast<std::uint64_t>(key.z));
  return static_cast<std::size_t>(x_hash ^ (y_hash << 1U) ^ (z_hash >> 1U));
}

bool IncrementalVoxelMap::coordinateToIndex(double coordinate, std::int64_t & index) const
{
  const long double scaled = std::floor(
    static_cast<long double>(coordinate) * static_cast<long double>(inverse_leaf_size_));
  if (!std::isfinite(scaled) ||
    scaled < static_cast<long double>(std::numeric_limits<std::int64_t>::min()) ||
    scaled > static_cast<long double>(std::numeric_limits<std::int64_t>::max()))
  {
    return false;
  }
  index = static_cast<std::int64_t>(scaled);
  return true;
}

bool IncrementalVoxelMap::addPoint(double x, double y, double z, double intensity)
{
  ++stats_.input_points;
  if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z) ||
    !std::isfinite(intensity))
  {
    ++stats_.rejected_nonfinite;
    return false;
  }
  if (std::abs(x) > max_abs_coordinate_ || std::abs(y) > max_abs_coordinate_ ||
    std::abs(z) > max_abs_coordinate_)
  {
    ++stats_.rejected_coordinate_range;
    return false;
  }

  VoxelKey key{};
  if (!coordinateToIndex(x, key.x) || !coordinateToIndex(y, key.y) ||
    !coordinateToIndex(z, key.z))
  {
    ++stats_.rejected_coordinate_range;
    return false;
  }

  auto & accumulator = voxels_[key];
  accumulator.x_sum += x;
  accumulator.y_sum += y;
  accumulator.z_sum += z;
  accumulator.intensity_sum += intensity;
  ++accumulator.count;
  ++stats_.accepted_points;

  if (!stats_.has_bounds) {
    stats_.min_xyz = {{x, y, z}};
    stats_.max_xyz = {{x, y, z}};
    stats_.has_bounds = true;
  } else {
    stats_.min_xyz[0] = std::min(stats_.min_xyz[0], x);
    stats_.min_xyz[1] = std::min(stats_.min_xyz[1], y);
    stats_.min_xyz[2] = std::min(stats_.min_xyz[2], z);
    stats_.max_xyz[0] = std::max(stats_.max_xyz[0], x);
    stats_.max_xyz[1] = std::max(stats_.max_xyz[1], y);
    stats_.max_xyz[2] = std::max(stats_.max_xyz[2], z);
  }
  return true;
}

pcl::PointCloud<pcl::PointXYZI>::Ptr IncrementalVoxelMap::toPointCloud() const
{
  using Entry = std::unordered_map<VoxelKey, Accumulator, VoxelKeyHash>::value_type;
  std::vector<const Entry *> ordered_entries;
  ordered_entries.reserve(voxels_.size());
  for (const auto & entry : voxels_) {
    ordered_entries.push_back(&entry);
  }
  std::sort(
    ordered_entries.begin(), ordered_entries.end(),
    [](const Entry * lhs, const Entry * rhs) {
      if (lhs->first.x != rhs->first.x) {
        return lhs->first.x < rhs->first.x;
      }
      if (lhs->first.y != rhs->first.y) {
        return lhs->first.y < rhs->first.y;
      }
      return lhs->first.z < rhs->first.z;
    });

  auto cloud = pcl::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
  cloud->reserve(ordered_entries.size());
  for (const Entry * entry : ordered_entries) {
    const auto & accumulator = entry->second;
    const double inverse_count = 1.0 / static_cast<double>(accumulator.count);
    pcl::PointXYZI point;
    point.x = static_cast<float>(accumulator.x_sum * inverse_count);
    point.y = static_cast<float>(accumulator.y_sum * inverse_count);
    point.z = static_cast<float>(accumulator.z_sum * inverse_count);
    point.intensity = static_cast<float>(accumulator.intensity_sum * inverse_count);
    cloud->push_back(point);
  }
  cloud->width = static_cast<std::uint32_t>(cloud->size());
  cloud->height = 1U;
  cloud->is_dense = true;
  return cloud;
}

double IncrementalVoxelMap::leafSize() const
{
  return leaf_size_;
}

double IncrementalVoxelMap::maxAbsCoordinate() const
{
  return max_abs_coordinate_;
}

IncrementalVoxelMapStats IncrementalVoxelMap::stats() const
{
  auto result = stats_;
  result.occupied_voxels = voxels_.size();
  return result;
}

}  // namespace fast_livo
