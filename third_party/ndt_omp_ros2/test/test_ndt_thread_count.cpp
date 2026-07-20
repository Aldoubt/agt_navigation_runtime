#include <gtest/gtest.h>
#include <pcl/point_types.h>

#include "pclomp/ndt_omp.h"

namespace
{

using Ndt = pclomp::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ>;

TEST(NdtThreadCountTest, ConstructorUsesPositiveThreadCount)
{
  Ndt ndt;
  EXPECT_GE(ndt.getNumThreads(), 1);
}

TEST(NdtThreadCountTest, ClampsNonPositiveValues)
{
  Ndt ndt;

  ndt.setNumThreads(0);
  EXPECT_EQ(ndt.getNumThreads(), 1);

  ndt.setNumThreads(-4);
  EXPECT_EQ(ndt.getNumThreads(), 1);
}

TEST(NdtThreadCountTest, PreservesPositiveValues)
{
  Ndt ndt;
  ndt.setNumThreads(4);
  EXPECT_EQ(ndt.getNumThreads(), 4);
}

}  // namespace
