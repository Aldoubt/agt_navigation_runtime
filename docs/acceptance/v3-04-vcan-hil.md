# V3-04 MK-mini Virtual-CAN Software-HIL Acceptance

## Status

```text
Cloud source / pure tests: PASS
Local ROS 2 Humble build: PENDING
Local vcan0 five-scenario HIL: PENDING
```

Cloud CI proves source contracts, independent protocol packing, deterministic VCU-model tests, launch/source structure, and existing V3 regressions. It does **not** prove Linux PF_CAN/vcan behavior or ROS runtime integration on the target workstation.

V3-04 virtual-CAN HIL is Acceptance PASS only after all five local scenarios below report `[PASS]` on a real `vcan0` interface.

## 1. Checkout and build

```bash
cd ~/agt_navigation_runtime

git fetch origin
git switch v3-04/vcan-sim
git pull --ff-only origin v3-04/vcan-sim

git log -1 --oneline

rm -rf build install log
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

Run source regressions:

```bash
python3 -m pytest -q \
  tests/contracts \
  tests/odometry \
  tests/execution \
  src/agt_chassis_mk_mini_sim/test
```

Run ROS package tests:

```bash
colcon test \
  --packages-select agt_chassis_mk_mini agt_chassis_mk_mini_sim \
  --event-handlers console_direct+

colcon test-result --verbose
```

Validate launch installation:

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py --show-args
```

Expected safe defaults include:

```text
can_interface: vcan0
operation_mode: monitor
steering_calibration_confirmed: false
allow_uncalibrated_control: false
drop_feedback: false
corrupt_bcc: false
```

## 2. Create host vcan0

The ROS package intentionally does not perform privileged network configuration.

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan 2>/dev/null || true
sudo ip link set up vcan0
ip -details link show vcan0
```

Optional raw observation:

```bash
candump vcan0
```

## 3. Scenario 1 — monitor_only

Terminal A:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=monitor
```

Terminal B:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario monitor_only
```

Pass criteria:

```text
/agt/chassis/connected becomes true
simulated ctrl_fb is decoded
zero ctrl_cmd frames are observed during the assertion window
[PASS] monitor_only
```

Stop Terminal A before the next scenario.

## 4. Scenario 2 — forward

The steering-calibration flag below is valid only for the virtual VCU's exact simulated mapping. It is not a physical-chassis calibration claim.

Terminal A:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=control \
  steering_calibration_confirmed:=true
```

Terminal B:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario forward
```

Pass criteria:

```text
D + 0 m/s is observed before D + nonzero speed
positive /agt/chassis/backend/ackermann_feedback is observed
positive /agt/chassis/wheel_twist is observed
[PASS] forward
```

Stop Terminal A before the next scenario.

## 5. Scenario 3 — reverse_interlock

Terminal A:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=control \
  steering_calibration_confirmed:=true
```

Terminal B:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario reverse_interlock
```

Pass criteria:

```text
vehicle first reaches forward motion
raw CAN ordering includes D + 0 -> R + 0 -> R + nonzero
negative Ackermann feedback is observed only after the interlock
[PASS] reverse_interlock
```

Stop Terminal A before the next scenario.

## 6. Scenario 4 — command_timeout

Terminal A:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=control \
  steering_calibration_confirmed:=true
```

Terminal B:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario command_timeout
```

Pass criteria:

```text
vehicle first reaches forward motion
runner stops refreshing Twist
real adapter becomes silent after its upstream freshness timeout
real CAN backend continues ctrl_cmd heartbeat
backend requests zero/deceleration before PARK
P command and P feedback are observed after standstill hold
[PASS] command_timeout
```

Stop Terminal A before the next scenario.

## 7. Scenario 5 — feedback_fault

Use one fault mechanism at a time. BCC corruption exercises the real protocol rejection path directly.

Terminal A:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=monitor \
  corrupt_bcc:=true
```

Terminal B:

```bash
source ~/agt_navigation_runtime/install/setup.bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario feedback_fault
```

Pass criteria:

```text
invalid simulated ctrl_fb is rejected
/agt/chassis/connected becomes false
/agt/chassis/status reports DiagnosticStatus.ERROR
[PASS] feedback_fault
```

The alternate transport-loss-style check is:

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=monitor \
  drop_feedback:=true
```

## 8. Acceptance record

Record the exact outputs for:

```text
colcon build Summary
pytest summary
colcon test-result --verbose
mk_mini_vcan_hil.launch.py --show-args
[PASS] monitor_only
[PASS] forward
[PASS] reverse_interlock
[PASS] command_timeout
[PASS] feedback_fault
```

Only after all five scenario results are present should this document's local HIL status be changed to PASS.
