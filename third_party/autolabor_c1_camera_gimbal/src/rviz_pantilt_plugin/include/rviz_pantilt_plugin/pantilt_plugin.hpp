#ifndef RVIZ_PANTILT_PLUGIN__PANTILT_PLUGIN_HPP_
#define RVIZ_PANTILT_PLUGIN__PANTILT_PLUGIN_HPP_

#include <memory>
#include <string>

#include <QComboBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <rviz_common/panel.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction_iface.hpp>

#include "pantilt_camera_serial/action/move_pantilt.hpp"
#include "pantilt_camera_serial/msg/pantilt_angle_info.hpp"
#include "pantilt_camera_serial/msg/pantilt_status.hpp"
#include "pantilt_camera_serial/srv/pantilt_command.hpp"

namespace autolabor_plugin
{

class PantiltRvizPanel : public rviz_common::Panel
{
  Q_OBJECT

public:
  explicit PantiltRvizPanel(QWidget * parent = nullptr);
  void onInitialize() override;

public Q_SLOTS:
  void setLockMode();
  void setHeadingFollow();
  void setHeadingPitchFollow();
  void setFullFollowMode();
  void backToCenter();
  void sendAngles();
  void updateSelectedNode(int index);
  void populateNodeSelector();
  void sendVel();

protected:
  bool eventFilter(QObject * watched, QEvent * event) override;

private:
  using MovePantilt = pantilt_camera_serial::action::MovePantilt;

  void angleCallback(const pantilt_camera_serial::msg::PantiltAngleInfo::SharedPtr msg);
  void statusCallback(const pantilt_camera_serial::msg::PantiltStatus::SharedPtr msg);
  void handleKeyPressEvent(QKeyEvent * event);
  void handleKeyReleaseEvent(QKeyEvent * event);
  void callService(const std::string & command_name);
  void sendMoveGoal(double heading, double roll, double pitch, const QString & label);
  void setPanelLog(const QString & text);
  static std::string normalizeNamespace(const QString & text);

  bool pitch_up_{false};
  bool pitch_down_{false};
  bool head_left_{false};
  bool head_right_{false};

  std::shared_ptr<rviz_common::ros_integration::RosNodeAbstractionIface> node_ptr_;
  rclcpp::Node::SharedPtr node_;
  rclcpp::Client<pantilt_camera_serial::srv::PantiltCommand>::SharedPtr service_client_;
  rclcpp_action::Client<MovePantilt>::SharedPtr action_client_;
  rclcpp::Subscription<pantilt_camera_serial::msg::PantiltAngleInfo>::SharedPtr angle_sub_;
  rclcpp::Subscription<pantilt_camera_serial::msg::PantiltStatus>::SharedPtr status_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;

  QComboBox * node_selector_{nullptr};
  QLabel * angle_label_{nullptr};
  QLabel * status_label_{nullptr};
  QLabel * log_label_{nullptr};
  QLineEdit * head_input_{nullptr};
  QLineEdit * roll_input_{nullptr};
  QLineEdit * pitch_input_{nullptr};
  QTimer * vel_timer_{nullptr};
};

}  // namespace autolabor_plugin

#endif  // RVIZ_PANTILT_PLUGIN__PANTILT_PLUGIN_HPP_
