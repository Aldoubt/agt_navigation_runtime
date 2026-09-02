#pragma once
#include <QObject>
#include <QString>
#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_srvs/srv/trigger.hpp>

class AgtRosInterface : public QObject {
  Q_OBJECT
 public:
  explicit AgtRosInterface(QObject *parent=nullptr); ~AgtRosInterface();
  void startTask(const QString &taskFile); void pauseTask(); void cancelTask(); void goPoint(double x,double y,double yaw);
 signals:
  void mapReceived(const nav_msgs::msg::OccupancyGrid::SharedPtr);
  void poseReceived(double x,double y,double yaw); void batteryReceived(double percent);
  void laserReceived(const sensor_msgs::msg::LaserScan::SharedPtr); void imageReceived(const sensor_msgs::msg::Image::SharedPtr);
  void taskStatusReceived(const QString&); void visionResultReceived(const QString&,const QString&,double,const QString&);
 private: void spin(); rclcpp::Node::SharedPtr node_; rclcpp::executors::SingleThreadedExecutor executor_; std::thread thread_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr task_request_; rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr task_start_,task_pause_,task_cancel_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr navigation_goal_;
};
