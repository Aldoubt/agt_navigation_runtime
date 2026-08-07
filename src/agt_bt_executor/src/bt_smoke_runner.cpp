#include "agt_bt_executor/bt_factory.hpp"
#include <behaviortree_cpp/loggers/bt_cout_logger.h>
#include <behaviortree_cpp/loggers/groot2_publisher.h>
#include <rclcpp/rclcpp.hpp>
int main(int argc, char ** argv) {
  rclcpp::init(argc, argv); auto node = std::make_shared<rclcpp::Node>("agt_bt_smoke_runner");
  BT::BehaviorTreeFactory factory; agt_bt_executor::registerAgtBtNodes(factory, node);
  try { auto tree = agt_bt_executor::createAllowlistedTree(factory, "v25_05_smoke"); BT::StdCoutLogger logger(tree);
    std::unique_ptr<BT::Groot2Publisher> groot;
    const bool enable_groot2 = node->declare_parameter<bool>("enable_groot2_monitoring", false);
    if (enable_groot2) { try { groot = std::make_unique<BT::Groot2Publisher>(tree); RCLCPP_INFO(node->get_logger(), "Groot2 monitoring enabled"); } catch (const std::exception & e) { RCLCPP_ERROR(node->get_logger(), "Groot2 initialization failed: %s", e.what()); } }
    auto status = tree.tickWhileRunning(); rclcpp::shutdown(); return status == BT::NodeStatus::SUCCESS ? 0 : 1; }
  catch (const std::exception & e) { RCLCPP_ERROR(node->get_logger(), "BT smoke failed: %s", e.what()); rclcpp::shutdown(); return 1; }
}
