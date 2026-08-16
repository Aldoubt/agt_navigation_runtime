# V3-04 MK-mini Virtual-CAN Software HIL Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a ROS 2 Humble `vcan0` software-HIL loop that exercises the real MK-mini adapter, CAN backend, fail-safe state machine, protocol decoder, SocketCAN transport, and ROS feedback topics against an independent simulated MK-mini VCU.

**Architecture:** Create a separate development-only package `agt_chassis_mk_mini_sim`. The simulator reads the real backend's `0x18C4D2D0` frames from `vcan0`, independently validates command bytes, evolves a minimal longitudinal/gear state, and independently packs `ctrl_fb`, rear-wheel, and BMS frames back onto `vcan0`. A HIL launch composes the existing real adapter/backend with the simulator but never creates or configures host CAN interfaces.

**Tech Stack:** ROS 2 Humble, Python 3.10, Linux SocketCAN/vcan, ament_cmake_python, pytest, launch/launch_ros.

## Global Constraints

- Real package `agt_chassis_mk_mini` must not depend on `agt_chassis_mk_mini_sim`.
- Default simulated CAN interface is `vcan0`; no HIL launch or node may execute `sudo`, `ip link`, or mutate host networking.
- Real backend defaults stay `operation_mode=monitor`, `steering_calibration_confirmed=false`, `allow_uncalibrated_control=false`.
- Simulator feedback packing must be independent from real backend feedback decoder implementation.
- Simulator may reuse public CAN IDs/enums and Linux SocketCAN transport primitives from `agt_chassis_mk_mini`.
- This plan does not add Gazebo, Nav2 tuning, tire dynamics, or real steering calibration.
- Existing V3-01/V3-02/V3-03/V3-04 tests must remain green.

---

### Task 1: Freeze the simulator package and protocol boundary

**Files:**
- Create: `src/agt_chassis_mk_mini_sim/package.xml`
- Create: `src/agt_chassis_mk_mini_sim/CMakeLists.txt`
- Create: `src/agt_chassis_mk_mini_sim/agt_chassis_mk_mini_sim/__init__.py`
- Create: `src/agt_chassis_mk_mini_sim/agt_chassis_mk_mini_sim/vcu_protocol.py`
- Create: `src/agt_chassis_mk_mini_sim/test/test_vcu_protocol.py`
- Create: `tests/execution/test_v3_04_vcan_hil_contract.py`
- Modify: `.github/workflows/runtime-contracts.yml`

**Interfaces:**
- Consumes: public logical IDs and `Gear` values from `agt_chassis_mk_mini.mk_mini_protocol`.
- Produces: `decode_ctrl_command(payload: bytes) -> CtrlCommand`, `encode_ctrl_feedback(...) -> bytes`, `encode_wheel_feedback(...) -> bytes`, `encode_bms_info(...) -> bytes`.

- [ ] **Step 1: Write RED source-contract and pure protocol tests**

Require the new package to exist, prohibit shell/network configuration strings, verify the simulator package is absent from the real backend's manifest, and use real-backend decoders only in tests to verify independently packed simulator feedback bytes.

- [ ] **Step 2: Run RED tests**

Run:
```bash
python3 -m pytest -q tests/execution/test_v3_04_vcan_hil_contract.py
```
Expected: FAIL because `agt_chassis_mk_mini_sim` and `vcu_protocol.py` do not exist.

- [ ] **Step 3: Implement independent protocol packing**

`CtrlCommand` contains `gear`, `speed_mps`, `steering_deg`, `alive_counter`. Command decode validates DLC/BCC and extracts manufacturer fields without calling `decode_ctrl_feedback`. Feedback encoders manually pack byte/nibble fields and compute XOR BCC locally in the simulator module.

- [ ] **Step 4: Run GREEN protocol tests**

Run:
```bash
python3 -m pytest -q src/agt_chassis_mk_mini_sim/test/test_vcu_protocol.py tests/execution/test_v3_04_vcan_hil_contract.py
```
Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_chassis_mk_mini_sim tests/execution .github/workflows/runtime-contracts.yml
git commit -m "feat(v3-04): add independent MK-mini VCU protocol simulator"
```

---

### Task 2: Add deterministic minimal VCU dynamics and fault model

**Files:**
- Create: `src/agt_chassis_mk_mini_sim/agt_chassis_mk_mini_sim/vcu_model.py`
- Create: `src/agt_chassis_mk_mini_sim/test/test_vcu_model.py`

**Interfaces:**
- Consumes: decoded `CtrlCommand` from Task 1.
- Produces: `VcuModel.step(command, dt) -> VcuState` with confirmed gear, signed speed, steering, wheel speeds, pulse counts, battery values, and VCU mode.

- [ ] **Step 1: Write RED model tests**

Tests require bounded acceleration/deceleration, D/R confirmation only while stationary, no instantaneous reversal, deterministic pulse accumulation, and explicit fault configuration for `drop_feedback` and `corrupt_bcc`.

- [ ] **Step 2: Run RED model tests**

Run:
```bash
python3 -m pytest -q src/agt_chassis_mk_mini_sim/test/test_vcu_model.py
```
Expected: FAIL because `vcu_model.py` is absent.

- [ ] **Step 3: Implement minimal model**

Use configurable `max_accel_mps2`, `max_decel_mps2`, `stationary_threshold_mps`, `wheel_diameter_m`, and `encoder_pulses_per_rev`. Gear requests are acknowledged only when the current speed magnitude is below the stationary threshold. Signed vehicle speed follows confirmed D/R gear and a nonnegative VCU speed target.

- [ ] **Step 4: Run GREEN model tests**

Run the same pytest command; expected PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_chassis_mk_mini_sim/agt_chassis_mk_mini_sim/vcu_model.py src/agt_chassis_mk_mini_sim/test/test_vcu_model.py
git commit -m "feat(v3-04): add deterministic MK-mini VCU state model"
```

---

### Task 3: Add SocketCAN simulator node and ROS observability

**Files:**
- Create: `src/agt_chassis_mk_mini_sim/scripts/mk_mini_vcu_sim.py`
- Create: `src/agt_chassis_mk_mini_sim/config/vcu_sim.yaml`
- Create: `src/agt_chassis_mk_mini_sim/test/test_vcu_sim_source.py`
- Modify: `src/agt_chassis_mk_mini_sim/CMakeLists.txt`
- Modify: `src/agt_chassis_mk_mini_sim/package.xml`

**Interfaces:**
- Consumes: SocketCAN frames from configurable interface `vcan0`, command ID `0x18C4D2D0`.
- Produces: `0x18C4D2EF`, `0x18C4D7EF`, `0x18C4D8EF`, `0x18C4E1EF`, plus `/agt/sim/mk_mini/status` diagnostics.

- [ ] **Step 1: Write RED source/package tests**

Require a nonblocking SocketCAN receive loop, command checksum/AliveCounter counters, feedback timers, fault parameters, and diagnostics. Assert no `sudo`, `ip link`, `subprocess`, or physical `can0` default.

- [ ] **Step 2: Run RED tests**

Expected FAIL because the node does not exist.

- [ ] **Step 3: Implement node**

The node opens `SocketCanTransport(vcan0)`, consumes only `CTRL_CMD_ID`, validates command progression, advances the model, and sends feedback at configured periods. `corrupt_bcc` flips feedback checksum after independent packing; `drop_feedback` suppresses selected feedback transmission.

- [ ] **Step 4: Run GREEN package tests**

Run:
```bash
python3 -m pytest -q src/agt_chassis_mk_mini_sim/test
```
Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_chassis_mk_mini_sim
git commit -m "feat(v3-04): add MK-mini SocketCAN VCU simulator node"
```

---

### Task 4: Compose the real backend and simulator in a safe HIL launch

**Files:**
- Create: `src/agt_chassis_mk_mini_sim/launch/mk_mini_vcan_hil.launch.py`
- Create: `src/agt_chassis_mk_mini_sim/test/test_vcan_hil_launch.py`
- Modify: `src/agt_chassis_mk_mini_sim/CMakeLists.txt`

**Interfaces:**
- Produces launch arguments: `can_interface:=vcan0`, `operation_mode:=monitor`, `steering_calibration_confirmed:=false`, `allow_uncalibrated_control:=false`, `start_adapter:=true`, `start_backend:=true`, `start_simulator:=true`, and simulator fault arguments.

- [ ] **Step 1: Write RED launch contract**

Assert launch includes the existing real adapter/backend launch behavior and simulator node, exposes safe arguments, defaults to `vcan0`, and contains no host-network mutation.

- [ ] **Step 2: Run RED test**

Expected FAIL because launch file is absent.

- [ ] **Step 3: Implement launch**

Launch the real `agt_chassis_mk_mini` adapter/backend with explicit substitutions and launch the simulator on the same `vcan0`. Do not execute external commands.

- [ ] **Step 4: Run GREEN launch-source tests**

Expected PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_chassis_mk_mini_sim/launch src/agt_chassis_mk_mini_sim/test src/agt_chassis_mk_mini_sim/CMakeLists.txt
git commit -m "feat(v3-04): compose MK-mini vcan software HIL launch"
```

---

### Task 5: Add local five-scenario HIL acceptance runner

**Files:**
- Create: `src/agt_chassis_mk_mini_sim/scripts/vcan_hil_acceptance.py`
- Create: `src/agt_chassis_mk_mini_sim/test/test_vcan_hil_acceptance_source.py`
- Modify: `src/agt_chassis_mk_mini_sim/CMakeLists.txt`
- Create: `docs/acceptance/v3-04-vcan-hil.md`

**Interfaces:**
- Consumes real backend ROS topics and publishes `/agt/chassis/cmd_vel`.
- Produces deterministic PASS/FAIL evidence for monitor-only, forward, reverse interlock, command-timeout-to-P, and feedback-fault scenarios.

- [ ] **Step 1: Write RED acceptance-source contract**

Require all five named scenarios, explicit timeouts, assertions on `/agt/chassis/connected`, `/agt/chassis/status`, `/agt/chassis/backend/ackermann_feedback`, `/agt/chassis/wheel_twist`, and absence of control commands in monitor mode.

- [ ] **Step 2: Run RED test**

Expected FAIL because acceptance runner is absent.

- [ ] **Step 3: Implement acceptance runner**

Use rclpy and bounded waits. Every scenario exits nonzero on timeout or contract violation and prints a concise per-scenario PASS/FAIL line. No scenario creates `vcan0`.

- [ ] **Step 4: Run source tests**

Expected PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_chassis_mk_mini_sim/scripts/vcan_hil_acceptance.py src/agt_chassis_mk_mini_sim/test docs/acceptance/v3-04-vcan-hil.md src/agt_chassis_mk_mini_sim/CMakeLists.txt
git commit -m "test(v3-04): add five-scenario MK-mini vcan HIL acceptance"
```

---

### Task 6: Regression, CI, and local ROS acceptance instructions

**Files:**
- Modify: `README.md`
- Modify: `src/agt_chassis_mk_mini/README.md`
- Modify: `.github/workflows/runtime-contracts.yml`

**Interfaces:**
- CI runs pure/source tests only; local ROS Humble runs package tests and actual `vcan0` scenarios.

- [ ] **Step 1: Run complete cloud-safe regression**

```bash
python3 -m pytest -q tests/contracts tests/odometry tests/execution
```
Expected: all PASS.

- [ ] **Step 2: Run simulator pure tests**

```bash
python3 -m pytest -q src/agt_chassis_mk_mini_sim/test
```
Expected: all PASS where ROS-runtime-only tests are represented as source contracts rather than requiring PF_CAN privileges in GitHub-hosted CI.

- [ ] **Step 3: Document local setup and acceptance**

Document exactly:
```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan 2>/dev/null || true
sudo ip link set up vcan0
ip -details link show vcan0
```
then build, `ros2 launch ... --show-args`, monitor-only run, and five-scenario acceptance run.

- [ ] **Step 4: Verify no physical CAN default leaked**

Search new simulator package for `can0`, `sudo`, and `ip link`; only documentation may contain host setup commands, and runtime defaults must remain `vcan0`.

- [ ] **Step 5: Commit**

```bash
git add README.md src/agt_chassis_mk_mini/README.md .github/workflows/runtime-contracts.yml docs/acceptance/v3-04-vcan-hil.md
git commit -m "docs(v3-04): document MK-mini virtual-CAN HIL acceptance"
```

## Local acceptance after implementation

```bash
cd ~/agt_navigation_runtime
git fetch origin
git switch v3-04/vcan-sim
git pull --ff-only origin v3-04/vcan-sim

rm -rf build install log
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash

python3 -m pytest -q tests/contracts tests/odometry tests/execution
colcon test --packages-select agt_chassis_mk_mini agt_chassis_mk_mini_sim --event-handlers console_direct+
colcon test-result --verbose

ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py --show-args

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan 2>/dev/null || true
sudo ip link set up vcan0
ip -details link show vcan0

ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py operation_mode:=monitor
```

The physical backend is not V3-04 HIL Acceptance PASS until the five local scenarios execute successfully on `vcan0`; cloud/source CI alone is insufficient.
