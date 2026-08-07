#include <algorithm>
#include <stdexcept>
#include <string>

#include "agt_sensor_adapters/urdf_self_filter_geometry.hpp"
#include "gtest/gtest.h"

TEST(UrdfSelfFilterGeometry, ParsesPrimitiveCollisionGeometry)
{
  const auto geometry = agt_sensor_adapters::parse_urdf_self_filter_geometry(R"urdf(
<robot name="test_robot">
  <link name="base_link">
    <collision>
      <origin xyz="0.10 -0.20 0.30" rpy="0 0 0"/>
      <geometry>
        <box size="1.0 0.6 0.4"/>
      </geometry>
    </collision>
  </link>
  <link name="sphere_link">
    <collision>
      <geometry>
        <sphere radius="0.15"/>
      </geometry>
    </collision>
  </link>
  <joint name="base_to_sphere" type="fixed">
    <parent link="base_link"/>
    <child link="sphere_link"/>
    <origin xyz="0 0 0.5" rpy="0 0 0"/>
  </joint>
</robot>
)urdf");

  ASSERT_EQ(geometry.primitives.size(), 2U);
  const auto base_it = std::find_if(
    geometry.primitives.begin(), geometry.primitives.end(),
    [](const auto & primitive) { return primitive.link_name == "base_link"; });
  const auto sphere_it = std::find_if(
    geometry.primitives.begin(), geometry.primitives.end(),
    [](const auto & primitive) { return primitive.link_name == "sphere_link"; });

  ASSERT_NE(base_it, geometry.primitives.end());
  ASSERT_NE(sphere_it, geometry.primitives.end());
  EXPECT_EQ(base_it->type, agt_sensor_adapters::UrdfPrimitiveType::BOX);
  EXPECT_DOUBLE_EQ(base_it->dimensions[0], 1.0);
  EXPECT_DOUBLE_EQ(base_it->dimensions[1], 0.6);
  EXPECT_DOUBLE_EQ(base_it->dimensions[2], 0.4);
  EXPECT_DOUBLE_EQ(base_it->origin_xyz[0], 0.10);
  EXPECT_DOUBLE_EQ(base_it->origin_xyz[1], -0.20);
  EXPECT_DOUBLE_EQ(base_it->origin_xyz[2], 0.30);

  EXPECT_EQ(sphere_it->type, agt_sensor_adapters::UrdfPrimitiveType::SPHERE);
  EXPECT_DOUBLE_EQ(sphere_it->dimensions[0], 0.15);
}

TEST(UrdfSelfFilterGeometry, PrimitiveContainmentHonorsPadding)
{
  agt_sensor_adapters::UrdfCollisionPrimitive box;
  box.type = agt_sensor_adapters::UrdfPrimitiveType::BOX;
  box.dimensions = {1.0, 0.6, 0.4};
  EXPECT_TRUE(box.contains_local({0.50, 0.30, 0.20}, 0.0));
  EXPECT_FALSE(box.contains_local({0.54, 0.0, 0.0}, 0.03));
  EXPECT_TRUE(box.contains_local({0.529, 0.0, 0.0}, 0.03));

  agt_sensor_adapters::UrdfCollisionPrimitive sphere;
  sphere.type = agt_sensor_adapters::UrdfPrimitiveType::SPHERE;
  sphere.dimensions = {0.20, 0.0, 0.0};
  EXPECT_TRUE(sphere.contains_local({0.22, 0.0, 0.0}, 0.03));
  EXPECT_FALSE(sphere.contains_local({0.24, 0.0, 0.0}, 0.03));

  agt_sensor_adapters::UrdfCollisionPrimitive cylinder;
  cylinder.type = agt_sensor_adapters::UrdfPrimitiveType::CYLINDER;
  cylinder.dimensions = {0.10, 0.40, 0.0};
  EXPECT_TRUE(cylinder.contains_local({0.12, 0.0, 0.21}, 0.03));
  EXPECT_FALSE(cylinder.contains_local({0.14, 0.0, 0.0}, 0.03));
  EXPECT_FALSE(cylinder.contains_local({0.0, 0.0, 0.24}, 0.03));
}

TEST(UrdfSelfFilterGeometry, RejectsMeshCollisionInsteadOfSilentlyUnderFiltering)
{
  try {
    (void)agt_sensor_adapters::parse_urdf_self_filter_geometry(R"urdf(
<robot name="mesh_robot">
  <link name="base_link">
    <collision>
      <geometry>
        <mesh filename="package://dummy/robot.stl"/>
      </geometry>
    </collision>
  </link>
</robot>
)urdf");
    FAIL() << "mesh collision unexpectedly accepted";
  } catch (const std::runtime_error & error) {
    EXPECT_NE(std::string(error.what()).find("primitive collision proxy"), std::string::npos);
  }
}

TEST(UrdfSelfFilterGeometry, RejectsUrdfWithoutCollisionGeometry)
{
  EXPECT_THROW(
    (void)agt_sensor_adapters::parse_urdf_self_filter_geometry(R"urdf(
<robot name="empty_robot">
  <link name="base_link"/>
</robot>
)urdf"),
    std::runtime_error);
}
