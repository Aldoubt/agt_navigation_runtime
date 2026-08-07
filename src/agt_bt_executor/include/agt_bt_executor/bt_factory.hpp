#pragma once
#include <behaviortree_cpp/bt_factory.h>
#include <rclcpp/rclcpp.hpp>
namespace agt_bt_executor {
void registerAgtBtNodes(BT::BehaviorTreeFactory &, rclcpp::Node::SharedPtr);
BT::Tree createAllowlistedTree(BT::BehaviorTreeFactory &, const std::string & tree_id);
}
