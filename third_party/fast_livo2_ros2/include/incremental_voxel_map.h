#ifndef FAST_LIVO__INCREMENTAL_VOXEL_MAP_H_
#define FAST_LIVO__INCREMENTAL_VOXEL_MAP_H_

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace fast_livo
{

struct IncrementalVoxelMapStats
{
  std::uint64_t input_points{0};
  std::uint64_t accepted_points{0};
  std::uint64_t rejected_nonfinite{0};
  std::uint64_t rejected_coordinate_range{0};
  std::size_t occupied_voxels{0};
  std::array<double, 3> min_xyz{{0.0, 0.0, 0.0}};
  std::array<double, 3> max_xyz{{0.0, 0.0, 0.0}};
  bool has_bounds{false};
};

class IncrementalVoxelMap
{
public:
  explicit IncrementalVoxelMap(double leaf_size, double max_abs_coordinate = 10000.0);

  bool addPoint(double x, double y, double z, double intensity);
  pcl::PointCloud<pcl::PointXYZI>::Ptr toPointCloud() const;

  double leafSize() const;
  double maxAbsCoordinate() const;
  IncrementalVoxelMapStats stats() const;

private:
  struct VoxelKey
  {
    std::int64_t x;
    std::int64_t y;
    std::int64_t z;

    bool operator==(const VoxelKey & other) const;
  };

  struct VoxelKeyHash
  {
    std::size_t operator()(const VoxelKey & key) const;
  };

  struct Accumulator
  {
    double x_sum{0.0};
    double y_sum{0.0};
    double z_sum{0.0};
    double intensity_sum{0.0};
    std::uint64_t count{0};
  };

  bool coordinateToIndex(double coordinate, std::int64_t & index) const;

  double leaf_size_;
  double inverse_leaf_size_;
  double max_abs_coordinate_;
  std::unordered_map<VoxelKey, Accumulator, VoxelKeyHash> voxels_;
  IncrementalVoxelMapStats stats_;
};

}  // namespace fast_livo

#endif  // FAST_LIVO__INCREMENTAL_VOXEL_MAP_H_
