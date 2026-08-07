#include <array>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

#include "agt_sensor_adapters/self_filter_geometry.hpp"
#include "gtest/gtest.h"
#include "livox_ros_driver2/msg/custom_msg.hpp"
#include "livox_ros_driver2/msg/custom_point.hpp"

namespace
{

std::string write_profile(const std::string & content)
{
  const auto path = std::string("/tmp/agt_self_filter_test_profile.yaml");
  std::ofstream stream(path);
  stream << content;
  return path;
}

}  // namespace

TEST(SelfFilterGeometry, GeneratesPhysicalChassisBoxAndExpandsPadding)
{
  const auto geometry = agt_sensor_adapters::load_self_filter_geometry(write_profile(R"yaml(
platform:
  geometry:
    length: 1.0
    width: 0.6
    height: 0.4
    self_filter:
      enabled: true
      frame: base_footprint
      padding: 0.03
      include_chassis_body: true
      boxes:
        - name: elevated
          min: [-0.2, -0.1, 0.3]
          max: [0.2, 0.1, 0.5]
          verified: false
)yaml"));

  ASSERT_EQ(geometry.boxes.size(), 2U);
  EXPECT_EQ(geometry.boxes.front().name, "chassis_body");
  EXPECT_TRUE(geometry.boxes.front().generated_from_platform_body);
  EXPECT_FALSE(geometry.boxes.back().generated_from_platform_body);
  EXPECT_DOUBLE_EQ(geometry.boxes.front().min[0], -0.5);
  EXPECT_DOUBLE_EQ(geometry.boxes.front().max[2], 0.4);
  const auto expanded = geometry.expanded_boxes();
  EXPECT_DOUBLE_EQ(expanded.front().min[0], -0.53);
  EXPECT_TRUE(expanded.front().contains({0.0, 0.0, 0.43}));
  EXPECT_TRUE(geometry.has_unverified_box());

  const auto supplemental = geometry.expanded_supplemental_boxes();
  ASSERT_EQ(supplemental.size(), 1U);
  EXPECT_EQ(supplemental.front().name, "elevated");
  EXPECT_DOUBLE_EQ(supplemental.front().min[0], -0.23);
  EXPECT_DOUBLE_EQ(supplemental.front().max[2], 0.53);
}

TEST(SelfFilterGeometry, BoxContainsInclusiveBoundariesAndRejectsOutsidePoints)
{
  agt_sensor_adapters::AxisAlignedBox box{
    "box", {-1.0, -2.0, 0.0}, {1.0, 2.0, 3.0}, true, ""};
  EXPECT_TRUE(box.contains({-1.0, -2.0, 0.0}));
  EXPECT_TRUE(box.contains({1.0, 2.0, 3.0}));
  EXPECT_FALSE(box.contains({1.0001, 0.0, 1.0}));
  EXPECT_FALSE(box.contains({0.0, -2.0001, 1.0}));
  EXPECT_FALSE(box.contains({0.0, 0.0, -0.0001}));
}

TEST(SelfFilterGeometry, SupportsMultipleBoxesAndNonFinitePointRejection)
{
  const auto geometry = agt_sensor_adapters::load_self_filter_geometry(write_profile(R"yaml(
platform:
  geometry:
    length: 1.0
    width: 0.6
    height: 0.4
    self_filter:
      enabled: true
      frame: base_footprint
      padding: 0.10
      include_chassis_body: false
      boxes:
        - name: first
          min: [-1.0, -1.0, 0.0]
          max: [-0.5, 1.0, 1.0]
          verified: true
        - name: second
          min: [0.5, -1.0, 0.0]
          max: [1.0, 1.0, 1.0]
          verified: true
)yaml"));
  const auto boxes = geometry.expanded_boxes();
  ASSERT_EQ(boxes.size(), 2U);
  EXPECT_TRUE(boxes[0].contains({-0.55, 0.0, 0.5}));
  EXPECT_TRUE(boxes[1].contains({0.55, 0.0, 0.5}));
  EXPECT_FALSE(boxes[0].contains({0.0, 0.0, 0.5}));
  EXPECT_FALSE(boxes[1].contains({0.0, 0.0, 0.5}));
  EXPECT_FALSE(boxes[0].contains({NAN, 0.0, 0.5}));
}

TEST(SelfFilterGeometry, RejectsMalformedBoxWithFieldName)
{
  try {
    (void)agt_sensor_adapters::load_self_filter_geometry(write_profile(R"yaml(
platform:
  geometry:
    length: 1.0
    width: 0.6
    height: 0.4
    self_filter:
      enabled: true
      frame: base_footprint
      padding: 0.03
      include_chassis_body: false
      boxes:
        - name: broken
          min: [0.0, 0.0]
          max: [1.0, 1.0, 1.0]
          verified: false
)yaml"));
    FAIL() << "malformed profile unexpectedly loaded";
  } catch (const std::runtime_error & error) {
    EXPECT_NE(std::string(error.what()).find("self_filter.boxes[0].min"), std::string::npos);
  }
}

TEST(SelfFilterGeometry, RejectsNonFiniteValues)
{
  try {
    (void)agt_sensor_adapters::load_self_filter_geometry(write_profile(R"yaml(
platform:
  geometry:
    length: .nan
    width: 0.6
    height: 0.4
    self_filter:
      enabled: true
      frame: base_footprint
      padding: 0.03
      include_chassis_body: true
      boxes: []
)yaml"));
    FAIL() << "non-finite profile unexpectedly loaded";
  } catch (const std::runtime_error & error) {
    EXPECT_NE(std::string(error.what()).find("platform.geometry.length"), std::string::npos);
  }
}

TEST(SelfFilterGeometry, PreservesCustomPointFieldsAndOrder)
{
  livox_ros_driver2::msg::CustomPoint first;
  first.offset_time = 11;
  first.x = 1.0F;
  first.reflectivity = 21;
  first.tag = 31;
  first.line = 41;
  livox_ros_driver2::msg::CustomPoint second;
  second.offset_time = 12;
  second.x = 2.0F;
  second.reflectivity = 22;
  second.tag = 32;
  second.line = 42;
  const std::vector<livox_ros_driver2::msg::CustomPoint> source{first, second};
  const auto selected = agt_sensor_adapters::copy_points_in_order(source, {1U});

  ASSERT_EQ(selected.size(), 1U);
  EXPECT_EQ(selected[0].offset_time, 12U);
  EXPECT_FLOAT_EQ(selected[0].x, 2.0F);
  EXPECT_EQ(selected[0].reflectivity, 22U);
  EXPECT_EQ(selected[0].tag, 32U);
  EXPECT_EQ(selected[0].line, 42U);

  livox_ros_driver2::msg::CustomMsg output;
  output.timebase = 1234;
  output.lidar_id = 7;
  output.points = selected;
  output.point_num = static_cast<uint32_t>(output.points.size());
  EXPECT_EQ(output.point_num, output.points.size());
  EXPECT_EQ(output.timebase, 1234U);
  EXPECT_EQ(output.lidar_id, 7U);
}
