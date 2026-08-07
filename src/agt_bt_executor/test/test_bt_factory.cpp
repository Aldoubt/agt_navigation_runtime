#include <gtest/gtest.h>
#include "agt_bt_executor/bt_factory.hpp"
#include <rclcpp/rclcpp.hpp>
#include <stdexcept>
TEST(BtFactory, RegistersProjectCapabilityNodes) {
  rclcpp::init(0, nullptr); auto node = std::make_shared<rclcpp::Node>("bt_factory_test"); BT::BehaviorTreeFactory factory; agt_bt_executor::registerAgtBtNodes(factory, node);
  EXPECT_TRUE(factory.manifests().count("IsTaskReady")); EXPECT_TRUE(factory.manifests().count("Relocalize")); EXPECT_TRUE(factory.manifests().count("ExecuteWaypointTask")); rclcpp::shutdown();
}
TEST(BtFactory, UnknownTreeIdIsRejected) {
  rclcpp::init(0, nullptr); auto node = std::make_shared<rclcpp::Node>("bt_factory_tree_test"); BT::BehaviorTreeFactory factory; agt_bt_executor::registerAgtBtNodes(factory, node);
  EXPECT_THROW(agt_bt_executor::createAllowlistedTree(factory, "arbitrary.xml"), std::invalid_argument); rclcpp::shutdown();
}
