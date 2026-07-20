#include <cmath>
#include <limits>
#include <stdexcept>

#include <gtest/gtest.h>

#include "incremental_voxel_map.h"

namespace
{

TEST(IncrementalVoxelMapTest, RejectsInvalidLeafSizes)
{
  EXPECT_THROW(fast_livo::IncrementalVoxelMap(0.0), std::invalid_argument);
  EXPECT_THROW(fast_livo::IncrementalVoxelMap(-0.25), std::invalid_argument);
  EXPECT_THROW(
    fast_livo::IncrementalVoxelMap(std::numeric_limits<double>::infinity()),
    std::invalid_argument);
  EXPECT_THROW(fast_livo::IncrementalVoxelMap(0.25, 0.0), std::invalid_argument);
  EXPECT_THROW(
    fast_livo::IncrementalVoxelMap(
      0.25, std::numeric_limits<double>::quiet_NaN()),
    std::invalid_argument);
}

TEST(IncrementalVoxelMapTest, RejectsNonfinitePoints)
{
  fast_livo::IncrementalVoxelMap map(0.25);
  EXPECT_TRUE(map.addPoint(1.0, 2.0, 3.0, 4.0));
  EXPECT_FALSE(map.addPoint(std::numeric_limits<double>::quiet_NaN(), 0.0, 0.0, 1.0));
  EXPECT_FALSE(map.addPoint(0.0, std::numeric_limits<double>::infinity(), 0.0, 1.0));

  const auto stats = map.stats();
  EXPECT_EQ(stats.input_points, 3U);
  EXPECT_EQ(stats.accepted_points, 1U);
  EXPECT_EQ(stats.rejected_nonfinite, 2U);
  EXPECT_EQ(stats.occupied_voxels, 1U);
}

TEST(IncrementalVoxelMapTest, ProducesOneCentroidPerVoxel)
{
  fast_livo::IncrementalVoxelMap map(1.0);
  ASSERT_TRUE(map.addPoint(0.1, 0.2, 0.3, 10.0));
  ASSERT_TRUE(map.addPoint(0.3, 0.4, 0.5, 14.0));
  ASSERT_TRUE(map.addPoint(-0.1, -0.2, -0.3, 20.0));

  const auto cloud = map.toPointCloud();
  ASSERT_EQ(cloud->size(), 2U);
  EXPECT_NEAR(cloud->points[0].x, -0.1, 1e-6);
  EXPECT_NEAR(cloud->points[0].intensity, 20.0, 1e-6);
  EXPECT_NEAR(cloud->points[1].x, 0.2, 1e-6);
  EXPECT_NEAR(cloud->points[1].y, 0.3, 1e-6);
  EXPECT_NEAR(cloud->points[1].z, 0.4, 1e-6);
  EXPECT_NEAR(cloud->points[1].intensity, 12.0, 1e-6);
}

TEST(IncrementalVoxelMapTest, SupportsMapsBeyondPclInt32GridVolume)
{
  fast_livo::IncrementalVoxelMap map(0.1, 10000.0);
  ASSERT_TRUE(map.addPoint(-5000.0, -5000.0, -5000.0, 1.0));
  ASSERT_TRUE(map.addPoint(5000.0, 5000.0, 5000.0, 2.0));

  const auto stats = map.stats();
  EXPECT_EQ(stats.accepted_points, 2U);
  EXPECT_EQ(stats.occupied_voxels, 2U);
  EXPECT_EQ(map.toPointCloud()->size(), 2U);
}

TEST(IncrementalVoxelMapTest, RejectsCoordinatesOutsideInt64VoxelRange)
{
  fast_livo::IncrementalVoxelMap map(0.1);
  EXPECT_FALSE(map.addPoint(std::numeric_limits<double>::max(), 0.0, 0.0, 1.0));

  const auto stats = map.stats();
  EXPECT_EQ(stats.rejected_coordinate_range, 1U);
  EXPECT_EQ(stats.occupied_voxels, 0U);
}

TEST(IncrementalVoxelMapTest, RejectsFiniteCoordinatesOutsideConfiguredMapRange)
{
  fast_livo::IncrementalVoxelMap map(0.25, 1000.0);
  EXPECT_TRUE(map.addPoint(999.0, -999.0, 0.0, 1.0));
  EXPECT_FALSE(map.addPoint(1000.1, 0.0, 0.0, 1.0));

  const auto stats = map.stats();
  EXPECT_EQ(stats.accepted_points, 1U);
  EXPECT_EQ(stats.rejected_coordinate_range, 1U);
  EXPECT_DOUBLE_EQ(map.maxAbsCoordinate(), 1000.0);
}

}  // namespace
