#include "agt_bt_executor/bt_factory.hpp"
#include "agt_bt_executor/is_task_ready.hpp"
#include "agt_bt_executor/relocalize_action.hpp"
#include "agt_bt_executor/execute_waypoint_task_action.hpp"
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <stdexcept>
namespace agt_bt_executor {
void registerAgtBtNodes(BT::BehaviorTreeFactory & factory, rclcpp::Node::SharedPtr node) {
  factory.registerBuilder<IsTaskReady>("IsTaskReady", [node](const std::string & name, const BT::NodeConfiguration & c) { return std::make_unique<IsTaskReady>(name, c, node); });
  factory.registerBuilder<Relocalize>("Relocalize", [node](const std::string & name, const BT::NodeConfiguration & c) { return std::make_unique<Relocalize>(name, c, node); });
  factory.registerBuilder<ExecuteWaypointTask>("ExecuteWaypointTask", [node](const std::string & name, const BT::NodeConfiguration & c) { return std::make_unique<ExecuteWaypointTask>(name, c, node); });
}

BT::Tree createAllowlistedTree(BT::BehaviorTreeFactory & factory, const std::string & tree_id) {
  std::string filename;
  if (tree_id == "v25_05_smoke") filename = "v25_05_smoke.xml";
  else if (tree_id == "v25_06_waypoint_mission") filename = "v25_06_waypoint_mission.xml";
  else throw std::invalid_argument("unknown BT tree id: " + tree_id);
  const auto path = ament_index_cpp::get_package_share_directory("agt_bt_executor") + "/behavior_trees/" + filename;
  return factory.createTreeFromFile(path);
}
}
