# V3-04 MK-mini Virtual-CAN Software-HIL Acceptance

## Status

```text
Cloud source / pure tests: PASS
Local affected-package ROS 2 Humble build: PASS
Local full-workspace clean build after simulator integration: PASS
Known build-warning cleanup: PASS
Local vcan0 five-scenario HIL: PASS
Virtual-CAN Software-HIL Acceptance: PASS
Physical CAN / vehicle acceptance: PENDING
```

Cloud CI proves source contracts, independent protocol packing, deterministic VCU-model tests, launch/source structure, ROS Python entrypoint execute-bit regression coverage, build-warning hygiene contracts, and existing V3 regressions. It does **not** prove Linux PF_CAN/vcan behavior or ROS runtime integration on the target workstation.

The local five-scenario run on 2026-08-16 proves the package-level virtual-CAN backend HIL path. The local clean build on 2026-08-16 additionally proves that the integrated 26-package ROS 2 Humble workspace builds from a clean `build/install/log` state without known CMake/colcon warning regressions. Neither result constitutes full runtime safety-chain acceptance, physical MK-mini steering calibration, physical CAN acceptance, or permission for autonomous ground operation.

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

## 8. Local acceptance record — 2026-08-16

Branch: `v3-04/vcan-sim`

Executable-install regression discovered during local HIL bringup:

```text
symptom: ros2 launch could not find mk_mini_adapter.py in libexec
cause: ROS Python scripts were tracked as 100644 while --symlink-install preserved source permissions
fix: 0d75258049c2bb4e028c67b4c0f4dbc4a1c45aeb
regression contract: d42de0860125465695ee61ca9bab1da2e23de566
```

Affected-package rebuild after the execute-bit fix:

```text
agt_chassis_mk_mini: finished
agt_chassis_mk_mini_sim: finished
Summary: 2 packages finished [5.99s]
```

ROS executable discovery and installed execute-bit checks passed for:

```text
agt_chassis_mk_mini/mk_mini_adapter.py
agt_chassis_mk_mini/mk_mini_can_backend.py
agt_chassis_mk_mini_sim/mk_mini_vcu_sim.py
agt_chassis_mk_mini_sim/vcan_hil_acceptance.py
```

Five-scenario result:

```text
[PASS] monitor_only
[PASS] forward
[PASS] reverse_interlock
[PASS] command_timeout
[PASS] feedback_fault
```

Additional operator evidence:

```text
monitor_only:
  backend connected=true
  backend rx_frames > 0
  backend tx_frames=0
  protocol_errors=0
  transport_errors=0

forward:
  real backend ctrl_cmd (0x18C4D2D0) observed on vcan0
  virtual VCU ctrl/wheel feedback observed
  runner verified D-zero before D-moving and positive feedback

reverse_interlock:
  runner verified D-zero < R-zero < R-moving
  reverse motion completed before post-test fail-safe PARK

command_timeout:
  upstream Twist refresh stopped
  backend CAN heartbeat continued
  zero/stationary transition completed before PARK
  PARK heartbeat continued with AliveCounter progression

feedback_fault:
  executed with drop_feedback=true
  /agt/chassis/connected=false
  /agt/chassis/status=ERROR, message="CAN/VCU feedback unavailable"
  state_reason=command_stale+feedback_stale
  rx_frames=0 while tx_frames continued
  protocol_errors=0 and transport_errors=0
```

For the control-mode virtual scenarios, the local run used `allow_uncalibrated_control:=true` as a **simulation-only override**. This is not steering calibration evidence and must not be carried into physical autonomous ground operation.

The first `monitor_only` runner attempt timed out waiting for ROS connected discovery even though raw CAN and backend diagnostics subsequently showed a healthy monitor path. A final 20-second rerun returned `[PASS] monitor_only`; the final five-scenario acceptance record therefore contains five explicit runner PASS results.

Full-workspace warning-hygiene verification after the cleanup branch was integrated:

```text
fresh shell sourced only /opt/ros/humble/setup.bash before clean build
build/install/log removed before build
Summary: 26 packages finished [2min 44s]
no package reported stderr output in the summary
no CMake Warning / WARNING / CMP0074 / disabled pcap/png backend warning remained
warning grep matched only the normal CMake STATUS line:
  -- Found PNG: /usr/lib/x86_64-linux-gnu/libpng.so (found version "1.6.37")
```

The warning cleanup addresses root causes rather than globally suppressing developer warnings: FAST-LIVO selects CMP0074 NEW behavior, NDT-OMP requests only needed PCL components, Livox/vikit informational messages use STATUS severity, and relocalization_core keeps required PCL IO while quietly ignoring unused optional IO backends.

## 9. Remaining scope

The following are intentionally outside this virtual-CAN acceptance:

```text
physical can0 monitor-only validation
physical VCU feedback validation
physical steering calibration
wheels-lifted physical control validation
autonomous ground operation
full V3 runtime safety-chain acceptance
```

No physical autonomous ground control is authorized by this Software-HIL result.
