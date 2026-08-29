# Hardware Bringup P0 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make first BUNKER + MID360 vehicle tests a parameter-validation and acceptance exercise rather than an on-vehicle software-integration exercise.

**Architecture:** Add an orchestration-only `agt_hardware_bringup` package that composes the existing BUNKER, MID360, sensor-monitor, and safety owners. Add read-only SocketCAN and ROS preflight tools, and split sensor monitoring into hardware-check versus navigation profiles. Camera/gimbal remain optional external launch hooks until the visual team delivers the real drivers.

**Tech Stack:** ROS2 Humble launch/rclpy command-line tooling, Python 3, YAML, pytest/ament static tests.

**Spec:** `docs/superpowers/specs/2026-08-29-hardware-bringup-p0-design.md`

## Global Constraints

- Do not modify Nav2, localization, mission-manager, BUNKER driver internals, or safety policy ownership.
- Do not guess real CAN bitrate, NIC/device names, MID360 installation TF, camera USB path, gimbal serial path, limits, or settle time.
- SocketCAN and vehicle preflight tools are read-only and must never execute motion, mission, gimbal, or network-mutating commands.
- Unified launch defaults to `operation_mode=monitor`.
- Missing required health evidence fails closed.
- Current phase must remain verifiable without a ROS2 installation.

---

### Task 1: SocketCAN preflight

**Files:**
- Create: `src/agt_hardware_bringup/agt_hardware_bringup/socketcan_preflight.py`
- Create: `src/agt_hardware_bringup/scripts/socketcan_preflight.py`
- Create: `src/agt_hardware_bringup/test/test_socketcan_preflight.py`

**Interfaces:**
- Produces: `parse_ip_link_details(text: str) -> dict[str, object]`
- Produces: `evaluate_can_link(details: dict[str, object], expected_bitrate: int = 0) -> tuple[bool, list[str]]`
- CLI arguments: `--interface`, `--expected-bitrate`, `--json-output`

- [ ] **Step 1: Write failing pure-Python tests**

Cover parsing of a healthy CAN link, bitrate mismatch, non-CAN interface, BUS-OFF, missing interface evidence, and extraction of RX/TX error counters.

- [ ] **Step 2: Run the test and confirm RED**

Run: `python -m pytest -q src/agt_hardware_bringup/test/test_socketcan_preflight.py`
Expected: import/file failure because the implementation does not exist.

- [ ] **Step 3: Implement the pure evaluator and read-only CLI**

Use only `Path('/sys/class/net')` reads and `subprocess.run(['ip','-details','-statistics','link','show', interface], ...)`. Do not call `ip link set`.

- [ ] **Step 4: Run the tests and confirm GREEN**

Run the same pytest command and `python -m compileall -q src/agt_hardware_bringup`.

- [ ] **Step 5: Commit**

Commit message: `feat(hardware): add read-only socketcan preflight`

### Task 2: Sensor-monitor profiles

**Files:**
- Create: `src/agt_hardware_bringup/config/sensor_monitor.hardware_check.yaml`
- Create: `src/agt_hardware_bringup/config/sensor_monitor.navigation.yaml`
- Create: `src/agt_hardware_bringup/test/test_sensor_profiles.py`

**Interfaces:**
- `hardware_check`: raw lidar + IMU required; filtered lidar/camera/camera_info/GNSS disabled.
- `navigation`: raw lidar + filtered lidar + IMU required; camera/camera_info/GNSS optional and disabled by default.

- [ ] **Step 1: Write failing config-semantic tests**

Tests must parse YAML and assert exact `enabled`, `required`, topic, min-rate, and timeout policy for the two profiles.

- [ ] **Step 2: Run RED**

Run: `python -m pytest -q src/agt_hardware_bringup/test/test_sensor_profiles.py`
Expected: missing YAML files.

- [ ] **Step 3: Add the two profiles**

Reuse current production MID360 thresholds: lidar `8 Hz / 0.5 s`, IMU `150 Hz / 0.2 s`.

- [ ] **Step 4: Run GREEN**

Run the profile tests plus Task 1 tests.

- [ ] **Step 5: Commit**

Commit message: `feat(hardware): split sensor health profiles`

### Task 3: Unified BUNKER + MID360 launch

**Files:**
- Create: `src/agt_hardware_bringup/launch/bunker_mid360.launch.py`
- Create: `src/agt_hardware_bringup/test/test_bringup_launch_contract.py`

**Interfaces:**
- Launch args: `use_sim_time`, `operation_mode`, `can_interface`, `expected_can_bitrate`, `run_can_preflight`, `mid360_user_config_path`, `sensor_profile`, `start_camera`, `camera_launch_file`, `start_gimbal`, `gimbal_launch_file`.
- Includes existing `agt_chassis_bunker/bunker.launch.py`, `agt_sensor_adapters/mid360.launch.py`, and `agt_sensor_monitor/sensor_monitor.launch.py`.

- [ ] **Step 1: Write static RED tests**

Assert monitor-mode default, all required include paths, exact profile choices, and absence of `/cmd_vel` publishing code in the new package.

- [ ] **Step 2: Run RED**

Expected: launch file missing.

- [ ] **Step 3: Implement launch composition**

Run the SocketCAN preflight via a `ExecuteProcess`/Python entry point before/alongside driver startup as observational evidence only. Include camera/gimbal launch files only when explicitly enabled and non-empty.

- [ ] **Step 4: Run GREEN + compileall**

- [ ] **Step 5: Commit**

Commit message: `feat(hardware): add unified bunker mid360 bringup`

### Task 4: Vehicle preflight evidence tool

**Files:**
- Create: `src/agt_hardware_bringup/agt_hardware_bringup/vehicle_preflight.py`
- Create: `src/agt_hardware_bringup/scripts/vehicle_preflight.py`
- Create: `src/agt_hardware_bringup/test/test_vehicle_preflight.py`

**Interfaces:**
- CLI: `--require-camera`, `--require-gimbal`, `--json-output`, `--topic-timeout`.
- Checks via `ros2 topic type`, `ros2 topic echo --once`, and `ros2 topic list`; no rclpy dependency is required for the diagnostic shell tool.
- JSON output includes check name, status, evidence, and overall `ready` boolean.

- [ ] **Step 1: Write RED unit tests for command-result classification and JSON summary**

Include cases for missing ROS2 CLI, missing required topic, unhealthy `/agt/chassis/connected`, optional camera absent, and required camera absent.

- [ ] **Step 2: Run RED**

- [ ] **Step 3: Implement minimal observational preflight**

Never publish to ROS topics and never call mission/gimbal/chassis command services/actions.

- [ ] **Step 4: Run GREEN + compileall**

- [ ] **Step 5: Commit**

Commit message: `feat(hardware): add vehicle preflight evidence tool`

### Task 5: ROS package integration and no-ROS CI gate

**Files:**
- Create: `src/agt_hardware_bringup/CMakeLists.txt`
- Create: `src/agt_hardware_bringup/package.xml`
- Create: `src/agt_hardware_bringup/README.md`
- Modify: `.github/workflows/operator-gateway-no-ros.yml` or add a narrowly scoped hardware no-ROS workflow if separation is cleaner.
- Create: `src/agt_hardware_bringup/test/test_package_contract.py`

**Interfaces:**
- Install launch/config/scripts/Python package.
- Runtime dependencies only on the existing AGT packages and launch machinery needed by composition.

- [ ] **Step 1: Write RED package/static tests**

Assert installed assets, dependency declarations, executable scripts, monitor-mode default, and no network mutation or motion command strings.

- [ ] **Step 2: Run RED**

- [ ] **Step 3: Add package metadata/install rules and README**

README must show monitor-first command and list all vehicle-only values that remain unverified.

- [ ] **Step 4: Run full no-ROS suite and compileall**

Run all `agt_hardware_bringup/test` tests plus existing gateway no-ROS tests. Expected: all pass.

- [ ] **Step 5: Commit**

Commit message: `test(hardware): gate bringup without ros environment`

### Task 6: Freeze and branch-isolation verification

**Files:**
- Create: `docs/acceptance/hardware-first-vehicle-checklist.md`

**Interfaces:**
- Checklist order: SocketCAN → BUNKER status → MID360 network/data → diagnostics → TF → low-speed motion only after monitor gates pass → navigation later.

- [ ] **Step 1: Add acceptance checklist**

Clearly mark vehicle-only values as `UNVERIFIED` rather than choosing defaults.

- [ ] **Step 2: Run final no-ROS CI and inspect workflow status**

Do not claim ROS2/colcon success.

- [ ] **Step 3: Compare branch against `feat/operator-gateway-p1-mission-control`**

Expected: changes limited to new hardware package, docs, and no-ROS CI wiring. Existing BUNKER/MID360/Safety/Nav2 code remains unchanged.

- [ ] **Step 4: Freeze current phase**

Report no-ROS evidence separately from deferred ROS2/vehicle acceptance.
