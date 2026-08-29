#include "rviz_pantilt_plugin/pantilt_plugin.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <functional>
#include <set>
#include <utility>

#include <QGridLayout>
#include <QGroupBox>
#include <QMetaObject>

#include <pluginlib/class_list_macros.hpp>
#include <rviz_common/display_context.hpp>

namespace autolabor_plugin
{

namespace
{
QString statusName(std::uint8_t state)
{
  using Status = pantilt_camera_serial::msg::PantiltStatus;
  switch (state) {
    case Status::STATE_DISCONNECTED: return "DISCONNECTED";
    case Status::STATE_WAITING_FEEDBACK: return "WAITING_FEEDBACK";
    case Status::STATE_IDLE: return "IDLE";
    case Status::STATE_MOVING: return "MOVING";
    case Status::STATE_STABILIZING: return "STABILIZING";
    case Status::STATE_REACHED: return "REACHED";
    case Status::STATE_UNVERIFIED: return "UNVERIFIED";
    case Status::STATE_ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}
}  // namespace

PantiltRvizPanel::PantiltRvizPanel(QWidget * parent)
: rviz_common::Panel(parent)
{
  auto * layout = new QGridLayout(this);

  auto * node_group = new QGroupBox("Gimbal Namespace");
  auto * node_layout = new QGridLayout(node_group);
  node_selector_ = new QComboBox();
  node_selector_->setEditable(true);
  node_selector_->addItem("/pantilt_camera_serial0");
  auto * refresh_button = new QPushButton("Refresh");
  node_layout->addWidget(node_selector_, 0, 0);
  node_layout->addWidget(refresh_button, 0, 1);
  layout->addWidget(node_group, 0, 0, 1, 2);

  auto * mode_group = new QGroupBox("Mode Settings");
  auto * mode_layout = new QGridLayout(mode_group);
  auto * lock_button = new QPushButton("LockMode");
  auto * heading_button = new QPushButton("HeadingFollow");
  auto * heading_pitch_button = new QPushButton("HeadPitchFollow");
  auto * full_button = new QPushButton("FullFollow");
  mode_layout->addWidget(lock_button, 0, 0);
  mode_layout->addWidget(heading_button, 0, 1);
  mode_layout->addWidget(heading_pitch_button, 1, 0);
  mode_layout->addWidget(full_button, 1, 1);
  layout->addWidget(mode_group, 1, 0, 1, 2);

  auto * angle_group = new QGroupBox("Angle Control (stable Action)");
  auto * angle_layout = new QGridLayout(angle_group);
  head_input_ = new QLineEdit("0");
  roll_input_ = new QLineEdit("0");
  pitch_input_ = new QLineEdit("0");
  auto * send_button = new QPushButton("Move & Wait Stable");
  auto * center_button = new QPushButton("Back to Center");
  angle_layout->addWidget(new QLabel("Heading:"), 0, 0);
  angle_layout->addWidget(head_input_, 0, 1);
  angle_layout->addWidget(new QLabel("Roll:"), 1, 0);
  angle_layout->addWidget(roll_input_, 1, 1);
  angle_layout->addWidget(new QLabel("Pitch:"), 2, 0);
  angle_layout->addWidget(pitch_input_, 2, 1);
  angle_layout->addWidget(send_button, 3, 0, 1, 2);
  angle_layout->addWidget(center_button, 4, 0, 1, 2);
  layout->addWidget(angle_group, 2, 0, 1, 2);

  angle_label_ = new QLabel("Encoder: --");
  status_label_ = new QLabel("Status: --");
  log_label_ = new QLabel("Ready");
  log_label_->setWordWrap(true);
  layout->addWidget(angle_label_, 3, 0, 1, 2);
  layout->addWidget(status_label_, 4, 0, 1, 2);
  layout->addWidget(log_label_, 5, 0, 1, 2);

  connect(refresh_button, &QPushButton::clicked, this, &PantiltRvizPanel::populateNodeSelector);
  connect(lock_button, &QPushButton::clicked, this, &PantiltRvizPanel::setLockMode);
  connect(heading_button, &QPushButton::clicked, this, &PantiltRvizPanel::setHeadingFollow);
  connect(heading_pitch_button, &QPushButton::clicked, this, &PantiltRvizPanel::setHeadingPitchFollow);
  connect(full_button, &QPushButton::clicked, this, &PantiltRvizPanel::setFullFollowMode);
  connect(send_button, &QPushButton::clicked, this, &PantiltRvizPanel::sendAngles);
  connect(center_button, &QPushButton::clicked, this, &PantiltRvizPanel::backToCenter);
  connect(
    node_selector_, QOverload<int>::of(&QComboBox::currentIndexChanged),
    this, &PantiltRvizPanel::updateSelectedNode);

  installEventFilter(this);
  setFocusPolicy(Qt::StrongFocus);
  node_selector_->installEventFilter(this);

  vel_timer_ = new QTimer(this);
  vel_timer_->setInterval(100);
  connect(vel_timer_, &QTimer::timeout, this, &PantiltRvizPanel::sendVel);
}

void PantiltRvizPanel::onInitialize()
{
  node_ptr_ = getDisplayContext()->getRosNodeAbstraction().lock();
  if (!node_ptr_) {
    setPanelLog("RViz ROS node unavailable");
    return;
  }
  node_ = node_ptr_->get_raw_node();
  populateNodeSelector();
  updateSelectedNode(node_selector_->currentIndex());
  vel_timer_->start();
}

std::string PantiltRvizPanel::normalizeNamespace(const QString & text)
{
  std::string ns = text.trimmed().toStdString();
  if (ns.empty()) {
    return "/pantilt_camera_serial0";
  }
  if (ns.front() != '/') {
    ns.insert(ns.begin(), '/');
  }
  while (ns.size() > 1U && ns.back() == '/') {
    ns.pop_back();
  }
  return ns;
}

void PantiltRvizPanel::populateNodeSelector()
{
  if (!node_) {
    return;
  }
  const QString current = node_selector_->currentText();
  std::set<std::string> namespaces;
  for (const auto & entry : node_->get_topic_names_and_types()) {
    const std::string suffix = "/pantilt_angle_info";
    if (entry.first.size() > suffix.size() &&
      entry.first.compare(entry.first.size() - suffix.size(), suffix.size(), suffix) == 0)
    {
      namespaces.insert(entry.first.substr(0, entry.first.size() - suffix.size()));
    }
  }

  node_selector_->blockSignals(true);
  node_selector_->clear();
  for (const auto & ns : namespaces) {
    node_selector_->addItem(QString::fromStdString(ns));
  }
  if (node_selector_->count() == 0) {
    node_selector_->addItem("/pantilt_camera_serial0");
  }
  const int found = node_selector_->findText(current);
  if (found >= 0) {
    node_selector_->setCurrentIndex(found);
  }
  node_selector_->blockSignals(false);
}

void PantiltRvizPanel::updateSelectedNode(int)
{
  if (!node_) {
    return;
  }
  const auto ns = normalizeNamespace(node_selector_->currentText());
  service_client_ = node_->create_client<pantilt_camera_serial::srv::PantiltCommand>(
    ns + "/send_command");
  action_client_ = rclcpp_action::create_client<MovePantilt>(node_, ns + "/move_pantilt");
  angle_sub_ = node_->create_subscription<pantilt_camera_serial::msg::PantiltAngleInfo>(
    ns + "/pantilt_angle_info", rclcpp::SensorDataQoS(),
    std::bind(&PantiltRvizPanel::angleCallback, this, std::placeholders::_1));
  status_sub_ = node_->create_subscription<pantilt_camera_serial::msg::PantiltStatus>(
    ns + "/pantilt_status", rclcpp::QoS(10),
    std::bind(&PantiltRvizPanel::statusCallback, this, std::placeholders::_1));
  vel_pub_ = node_->create_publisher<geometry_msgs::msg::Twist>(ns + "/pantilt_vel", 10);
  setPanelLog(QString("Connected UI to %1").arg(QString::fromStdString(ns)));
}

void PantiltRvizPanel::setLockMode() {callService("SetLockMode");}
void PantiltRvizPanel::setHeadingFollow() {callService("SetHeadingFollow");}
void PantiltRvizPanel::setHeadingPitchFollow() {callService("SetHeadingPitchFollow");}
void PantiltRvizPanel::setFullFollowMode() {callService("SetFullFollowMode");}

void PantiltRvizPanel::backToCenter()
{
  sendMoveGoal(0.0, 0.0, 0.0, "center");
}

void PantiltRvizPanel::sendAngles()
{
  sendMoveGoal(
    head_input_->text().toDouble(),
    roll_input_->text().toDouble(),
    pitch_input_->text().toDouble(),
    "target");
}

void PantiltRvizPanel::callService(const std::string & command_name)
{
  if (!service_client_) {
    setPanelLog("Service client is not initialized");
    return;
  }
  if (!service_client_->service_is_ready()) {
    setPanelLog("send_command service is not ready");
    return;
  }
  auto request = std::make_shared<pantilt_camera_serial::srv::PantiltCommand::Request>();
  request->command_name = command_name;
  service_client_->async_send_request(
    request,
    [this, command_name](rclcpp::Client<pantilt_camera_serial::srv::PantiltCommand>::SharedFuture future) {
      const auto response = future.get();
      const QString text = QString::fromStdString(command_name) +
        (response->success ? ": accepted - " : ": failed - ") +
        QString::fromStdString(response->message);
      setPanelLog(text);
    });
}

void PantiltRvizPanel::sendMoveGoal(
  double heading, double roll, double pitch, const QString & label)
{
  if (!action_client_) {
    setPanelLog("MovePantilt action client is not initialized");
    return;
  }
  if (!action_client_->action_server_is_ready()) {
    setPanelLog("MovePantilt action server is not ready");
    return;
  }

  MovePantilt::Goal goal;
  goal.heading = heading;
  goal.roll = roll;
  goal.pitch = pitch;
  goal.tolerance = 1.5;
  goal.timeout = 8.0;
  goal.stable_samples = 3U;

  rclcpp_action::Client<MovePantilt>::SendGoalOptions options;
  options.result_callback =
    [this, label](const rclcpp_action::ClientGoalHandle<MovePantilt>::WrappedResult & wrapped) {
      if (!wrapped.result) {
        setPanelLog(label + ": no action result");
        return;
      }
      const QString message = label +
        (wrapped.result->success ? ": REACHED - " : ": FAILED - ") +
        QString::fromStdString(wrapped.result->message);
      setPanelLog(message);
    };
  action_client_->async_send_goal(goal, options);
  setPanelLog(label + ": goal sent; waiting for stable encoder arrival");
}

void PantiltRvizPanel::angleCallback(
  const pantilt_camera_serial::msg::PantiltAngleInfo::SharedPtr msg)
{
  const QString text = QString("Encoder H=%1 R=%2 P=%3")
    .arg(msg->encoder_heading, 0, 'f', 2)
    .arg(msg->encoder_roll, 0, 'f', 2)
    .arg(msg->encoder_pitch, 0, 'f', 2);
  QMetaObject::invokeMethod(
    angle_label_, "setText", Qt::QueuedConnection, Q_ARG(QString, text));
}

void PantiltRvizPanel::statusCallback(
  const pantilt_camera_serial::msg::PantiltStatus::SharedPtr msg)
{
  const QString text = QString("State=%1 serial=%2 feedback=%3 stable=%4 error=%5")
    .arg(statusName(msg->state))
    .arg(msg->serial_connected ? "OK" : "DOWN")
    .arg(msg->feedback_alive ? "OK" : "STALE")
    .arg(static_cast<unsigned int>(msg->stable_count))
    .arg(QString::fromStdString(msg->last_error));
  QMetaObject::invokeMethod(
    status_label_, "setText", Qt::QueuedConnection, Q_ARG(QString, text));
}

void PantiltRvizPanel::setPanelLog(const QString & text)
{
  if (!log_label_) {
    return;
  }
  QMetaObject::invokeMethod(
    log_label_, "setText", Qt::QueuedConnection, Q_ARG(QString, text));
}

bool PantiltRvizPanel::eventFilter(QObject * watched, QEvent * event)
{
  if (watched == node_selector_ && event->type() == QEvent::MouseButtonPress) {
    populateNodeSelector();
  }
  if (event->type() == QEvent::KeyPress) {
    handleKeyPressEvent(static_cast<QKeyEvent *>(event));
  } else if (event->type() == QEvent::KeyRelease) {
    handleKeyReleaseEvent(static_cast<QKeyEvent *>(event));
  }
  return QWidget::eventFilter(watched, event);
}

void PantiltRvizPanel::handleKeyPressEvent(QKeyEvent * event)
{
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: pitch_up_ = true; break;
    case Qt::Key_Down:
    case Qt::Key_S: pitch_down_ = true; break;
    case Qt::Key_Left:
    case Qt::Key_A: head_left_ = true; break;
    case Qt::Key_Right:
    case Qt::Key_D: head_right_ = true; break;
    default: break;
  }
}

void PantiltRvizPanel::handleKeyReleaseEvent(QKeyEvent * event)
{
  switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: pitch_up_ = false; break;
    case Qt::Key_Down:
    case Qt::Key_S: pitch_down_ = false; break;
    case Qt::Key_Left:
    case Qt::Key_A: head_left_ = false; break;
    case Qt::Key_Right:
    case Qt::Key_D: head_right_ = false; break;
    default: break;
  }
}

void PantiltRvizPanel::sendVel()
{
  if (!vel_pub_) {
    return;
  }
  geometry_msgs::msg::Twist vel;
  vel.angular.z = head_left_ ? 0.5 : (head_right_ ? -0.5 : 0.0);
  vel.linear.x = pitch_up_ ? 0.5 : (pitch_down_ ? -0.5 : 0.0);
  vel_pub_->publish(vel);
}

}  // namespace autolabor_plugin

PLUGINLIB_EXPORT_CLASS(autolabor_plugin::PantiltRvizPanel, rviz_common::Panel)
