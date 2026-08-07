#include <gtest/gtest.h>
#include "agt_bt_executor/bt_factory.hpp"
#include <rclcpp/rclcpp.hpp>

TEST(V2506WaypointMission, AllowlistedTreeUsesOnlyProjectNodes) {
  rclcpp::init(0, nullptr);
  auto node = std::make_shared<rclcpp::Node>("v25_06_waypoint_mission_test");
  BT::BehaviorTreeFactory factory;
  agt_bt_executor::registerAgtBtNodes(factory, node);
  auto tree = agt_bt_executor::createAllowlistedTree(factory, "v25_06_waypoint_mission");
  ASSERT_NE(tree.rootNode(), nullptr);
  EXPECT_EQ(tree.rootNode()->name(), "Sequence");
  rclcpp::shutdown();
}
