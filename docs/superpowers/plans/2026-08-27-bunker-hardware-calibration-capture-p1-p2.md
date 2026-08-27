# BUNKER Hardware + Calibration Capture P1/P2 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `agt_navigation_runtime` expose a standalone, motion-safe BUNKER hardware bringup with canonical MID360/IMU/wheel-odometry/GNSS interfaces and produce auditable rosbag2 calibration datasets for the later wheel/LIO extrinsic and time-offset solver.

**Architecture:** Keep hardware acquisition and canonical topic normalization inside Runtime, while leaving calibration estimation itself offline. BUNKER remains the wheel-odometry source, FAST-LIVO2 remains the continuous LiDAR-inertial odometry source, and GNSS is an optional `sensor_msgs/NavSatFix` prior carried on a canonical topic without introducing `robot_localization`, `navsat_transform`, or a second TF authority. Calibration recording reuses the existing `agt_experiment_manager` ownership model and an explicit topic profile; a separate metadata validator rejects incomplete bags before they are used by later calibration tools.

**Tech Stack:** ROS 2 Humble, Python launch, C++17/rclcpp, `sensor_msgs/NavSatFix`, `nav_msgs/Odometry`, rosbag2 sqlite3, pytest/gtest, YAML.

**Spec:** `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Global Constraints

- Runtime must build and launch without sourcing `agt_navigation_v2` source/install/workspace overlays or relative paths into V2.
- `/agt/mapping/odometry` remains the canonical continuous LIO odometry topic.
- `/agt/mapping/registered_points` remains the canonical registered cloud topic.
- `/agt/chassis/odometry` remains the canonical BUNKER wheel-odometry topic.
- `/agt/sensors/lidar/custom` and `/agt/sensors/imu/data` remain the canonical MID360 raw interfaces.
- GNSS canonical output is `/agt/sensors/gnss/fix`; the upstream driver topic must be configurable and must not be hard-coded to a specific receiver vendor.
- FAST-LIVO2 remains the unique runtime `odom -> base_footprint` authority; BUNKER driver odom TF remains disabled.
- `map -> odom` remains owned only by GlobalCorrectionManager; this P1/P2 plan must not publish it.
- GNSS is optional/recommended. Loss of GNSS must not stop the pure LIO runtime path.
- Do not add `robot_localization`, `navsat_transform_node`, RTAB-Map, wheel/LIO online fusion, or a 3D planner in this plan.
- New GNSS and calibration-capture behavior is explicit opt-in and fail-closed on malformed configuration.
- BUNKER wheel odometry is calibration evidence, not ground truth; spin-in-place/high-slip segments are not promoted to truth by this plan.
- Runtime map production remains disabled (`save_pcd=false`) in the robot execution entry.
- Calibration datasets must explicitly contain wheel odometry, LIO odometry, LiDAR, IMU, TF, and chassis status; GNSS is optional unless the operator requests a GNSS-required capture.

---

## File Structure Locked by This Plan

- `src/agt_description/urdf/agt_base.urdf.xacro` — static robot frame tree, including `gps_link`.
- `src/agt_description/config/bunker_mid360.yaml` — BUNKER/MID360/GNSS provisional extrinsic parameters; unverified values remain explicitly marked unverified.
- `src/agt_description/test/test_tf_contract.py` — static TF contract.
- `profiles/platforms/bunker.yaml` — platform-level calibration status and canonical sensor bindings.
- `src/agt_sensor_adapters/include/agt_sensor_adapters/navsat_fix_adapter_core.hpp` — pure `NavSatFix` normalization helper.
- `src/agt_sensor_adapters/src/navsat_fix_adapter.cpp` — configurable raw-GNSS-to-canonical-topic ROS node.
- `src/agt_sensor_adapters/launch/gnss_navsat.launch.py` — GNSS adapter launch boundary.
- `src/agt_sensor_adapters/test/test_navsat_fix_adapter_core.cpp` — message-preservation and frame-normalization tests.
- `src/agt_sensor_monitor/launch/sensor_monitor.launch.py` — runtime overrides for optional GNSS monitoring.
- `src/agt_chassis/launch/bunker.launch.py` — monitor-mode command sink and canonical wheel odometry.
- `src/agt_bringup/launch/system.launch.py` — unified Runtime opt-in GNSS wiring.
- `src/agt_bringup/launch/calibration_capture.launch.py` — motion-safe acquisition composition for calibration runs.
- `src/agt_bringup/test/test_runtime_bringup_contract.py` — system/monitor-mode/calibration-capture contracts.
- `src/agt_experiment_manager/config/bag_profiles.yaml` — explicit `calibration` rosbag profile.
- `src/agt_experiment_manager/test/test_experiment_manager.py` — calibration profile ownership/record-command tests.
- `tools/calibration/validate_calibration_bag.py` — offline metadata gate for a completed calibration bag.
- `tools/calibration/test_validate_calibration_bag.py` — metadata validator tests.
- `src/agt_experiment_manager/README.md` and `src/agt_bringup/README.md` — operator workflow and acceptance commands.

---

### Task 1: Freeze `gps_link` and BUNKER sensor/extrinsic contract

**Files:**
- Modify: `src/agt_description/urdf/agt_base.urdf.xacro`
- Modify: `src/agt_description/config/bunker_mid360.yaml`
- Modify: `src/agt_description/test/test_tf_contract.py`
- Modify: `profiles/platforms/bunker.yaml`

**Interfaces:**
- Consumes: existing `base_footprint -> base_link -> lidar_link -> {livox_frame, imu_link}` tree.
- Produces: fixed `base_link -> gps_link` edge and launch-overridable `gps_x`, `gps_y`, `gps_z`, `gps_roll`, `gps_pitch`, `gps_yaw` arguments.
- The initial GNSS extrinsic values are `0.0` placeholders and must remain explicitly unverified until physically measured; no fabricated antenna position is allowed.

- [ ] **Step 1: Extend the TF contract test first**

Add assertions to `test_tf_contract.py` requiring exactly one `gps_link`, exactly one fixed parent from `base_link`, and the six GNSS xacro arguments. The test must also assert that `bunker_mid360.yaml` retains `calibration_verified: false` while GNSS values are still provisional.

```python
assert 'name="gps_link"' in xacro
assert 'name="base_link_to_gps_link" type="fixed"' in xacro
for name in ("gps_x", "gps_y", "gps_z", "gps_roll", "gps_pitch", "gps_yaw"):
    assert f'name="{name}"' in xacro
assert params["calibration_verified"] is False
```

- [ ] **Step 2: Run the focused test and verify RED**

Run:

```bash
python3 -m pytest src/agt_description/test/test_tf_contract.py -q
```

Expected: FAIL because `gps_link` and GNSS xacro arguments do not exist yet.

- [ ] **Step 3: Add the minimal `gps_link` implementation**

Add these xacro arguments near the LiDAR arguments:

```xml
<xacro:arg name="gps_x" default="0.0"/>
<xacro:arg name="gps_y" default="0.0"/>
<xacro:arg name="gps_z" default="0.0"/>
<xacro:arg name="gps_roll" default="0.0"/>
<xacro:arg name="gps_pitch" default="0.0"/>
<xacro:arg name="gps_yaw" default="0.0"/>
```

Add one static antenna frame only:

```xml
<link name="gps_link"/>
<joint name="base_link_to_gps_link" type="fixed">
  <parent link="base_link"/>
  <child link="gps_link"/>
  <origin
    xyz="$(arg gps_x) $(arg gps_y) $(arg gps_z)"
    rpy="$(arg gps_roll) $(arg gps_pitch) $(arg gps_yaw)"/>
</joint>
```

Add the six parameters to `bunker_mid360.yaml` with zero values and a comment stating that they are placeholders pending physical antenna measurement. Do not change `calibration_verified` to true.

Extend `profiles/platforms/bunker.yaml` with a `sensors` mapping that freezes the canonical interfaces without inventing a driver:

```yaml
  sensors:
    lidar:
      frame: lidar_link
      topic: /agt/sensors/lidar/custom
    imu:
      frame: imu_link
      topic: /agt/sensors/imu/data
    gnss:
      frame: gps_link
      topic: /agt/sensors/gnss/fix
      extrinsic_verified: false
      driver_topic: configurable
    wheel_odometry:
      frame: bunker_odom
      child_frame: base_footprint
      topic: /agt/chassis/odometry
      publish_tf: false
```

- [ ] **Step 4: Run the description test and verify GREEN**

```bash
python3 -m pytest src/agt_description/test/test_tf_contract.py -q
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_description/urdf/agt_base.urdf.xacro \
  src/agt_description/config/bunker_mid360.yaml \
  src/agt_description/test/test_tf_contract.py \
  profiles/platforms/bunker.yaml
git commit -m "feat(description): add provisional BUNKER GNSS frame contract"
```

---

### Task 2: Add vendor-neutral `NavSatFix` canonical adapter

**Files:**
- Create: `src/agt_sensor_adapters/include/agt_sensor_adapters/navsat_fix_adapter_core.hpp`
- Create: `src/agt_sensor_adapters/src/navsat_fix_adapter.cpp`
- Create: `src/agt_sensor_adapters/launch/gnss_navsat.launch.py`
- Create: `src/agt_sensor_adapters/test/test_navsat_fix_adapter_core.cpp`
- Modify: `src/agt_sensor_adapters/CMakeLists.txt`
- Modify: `src/agt_sensor_adapters/package.xml`
- Modify: `src/agt_sensor_adapters/README.md`

**Interfaces:**
- Consumes: configurable `sensor_msgs/msg/NavSatFix` upstream topic `input_topic`.
- Produces: `/agt/sensors/gnss/fix` by default, frame-normalized to `gps_link`.
- Preserves: original timestamp, status, latitude/longitude/altitude, covariance values, and covariance type exactly.
- Rejects: empty/non-absolute input topic and input/output self-loop.

- [ ] **Step 1: Write the pure message-normalization gtest**

Test a helper with this signature:

```cpp
sensor_msgs::msg::NavSatFix normalizeNavSatFix(
  const sensor_msgs::msg::NavSatFix & input,
  const std::string & frame_id);
```

The test must construct a fix with non-default status, coordinates, covariance, covariance type, and timestamp, then assert every field is unchanged except `header.frame_id == "gps_link"`.

- [ ] **Step 2: Run the new gtest and verify RED**

```bash
colcon test --packages-select agt_sensor_adapters \
  --ctest-args -R test_navsat_fix_adapter_core --output-on-failure
```

Expected: FAIL because the helper and test target do not exist.

- [ ] **Step 3: Implement the core helper and ROS node**

`navsat_fix_adapter_core.hpp` contains only the normalization helper and no ROS node state. The implementation copies the complete message then changes only the frame:

```cpp
inline sensor_msgs::msg::NavSatFix normalizeNavSatFix(
  const sensor_msgs::msg::NavSatFix & input,
  const std::string & frame_id)
{
  auto output = input;
  output.header.frame_id = frame_id;
  return output;
}
```

`navsat_fix_adapter.cpp` must declare:

```text
input_topic      required absolute topic, no vendor default
output_topic     /agt/sensors/gnss/fix
frame_id         gps_link
```

Fail construction when `input_topic` is empty, does not start with `/`, or equals `output_topic`. Use `rclcpp::SensorDataQoS()` for input and output. The callback performs no coordinate conversion, filtering, covariance rewriting, or timestamp replacement.

- [ ] **Step 4: Add the launch boundary**

`gnss_navsat.launch.py` declares `input_topic`, `output_topic`, `frame_id`, and `use_sim_time`, starts only `agt_sensor_adapters/navsat_fix_adapter`, and defaults the output/frame to the canonical values.

- [ ] **Step 5: Wire build/test metadata and run GREEN**

Add executable/test targets to CMake and ensure `sensor_msgs` remains declared in `package.xml`.

```bash
colcon build --packages-select agt_sensor_adapters --symlink-install
source install/setup.bash
colcon test --packages-select agt_sensor_adapters
colcon test-result --verbose
```

Expected: all `agt_sensor_adapters` tests pass.

- [ ] **Step 6: Commit**

```bash
git add src/agt_sensor_adapters
git commit -m "feat(sensors): add canonical NavSatFix adapter"
```

---

### Task 3: Integrate optional GNSS monitoring and make BUNKER monitor mode command-inert

**Files:**
- Modify: `src/agt_sensor_monitor/launch/sensor_monitor.launch.py`
- Modify: `src/agt_chassis/launch/bunker.launch.py`
- Modify: `src/agt_bringup/launch/system.launch.py`
- Modify: `src/agt_bringup/test/test_runtime_bringup_contract.py`

**Interfaces:**
- Produces new Runtime launch args: `start_gnss:=false`, `gnss_input_topic:=""`.
- When GNSS is enabled, sensor monitor watches `/agt/sensors/gnss/fix` but keeps it `required=false`.
- When `chassis_operation_mode:=monitor`, the BUNKER driver must not subscribe to the normal `/agt/chassis/cmd_vel` command path.

- [ ] **Step 1: Add failing bringup contract assertions**

Require in `system.launch.py`:

```python
assert 'DeclareLaunchArgument("start_gnss", default_value="false")' in source
assert 'DeclareLaunchArgument("gnss_input_topic", default_value="")' in source
assert 'gnss_navsat.launch.py' in source
```

Require monitor mode in `bunker.launch.py` to use a command sink such as:

```text
/agt/chassis/monitor_only_cmd_vel_disabled
```

and verify control mode still uses `LaunchConfiguration("command_topic")`.

- [ ] **Step 2: Run P0/P1 contract tests and verify RED**

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: FAIL on missing GNSS arguments and monitor-only command sink.

- [ ] **Step 3: Extend sensor monitor launch with an override**

Add launch argument:

```python
DeclareLaunchArgument("gnss_enabled", default_value="false")
```

and pass a parameter override after the YAML file:

```python
{
    "use_sim_time": LaunchConfiguration("use_sim_time"),
    "gnss.enabled": ParameterValue(
        LaunchConfiguration("gnss_enabled"), value_type=bool
    ),
    "gnss.required": False,
}
```

Do not change the base YAML default: GNSS remains disabled when the system does not request it.

- [ ] **Step 4: Make BUNKER monitor mode command-inert**

Keep the driver running so `/agt/chassis/odometry` and status are available, but map its `/cmd_vel` subscription to an unpublished sink when `operation_mode == "monitor"`. Control mode must continue to use `/agt/chassis/cmd_vel` through the existing safety chain.

Use a launch substitution equivalent to:

```python
PythonExpression([
    "'", LaunchConfiguration("operation_mode"),
    "' == 'control' and '", LaunchConfiguration("command_topic"),
    "' or '/agt/chassis/monitor_only_cmd_vel_disabled'",
])
```

- [ ] **Step 5: Add GNSS system validation/wiring**

In `_validate`, if `start_gnss` is true:

```python
input_topic = LaunchConfiguration("gnss_input_topic").perform(context).strip()
if not input_topic.startswith("/"):
    raise RuntimeError("start_gnss requires an absolute gnss_input_topic")
if input_topic == "/agt/sensors/gnss/fix":
    raise RuntimeError("gnss_input_topic must not equal canonical GNSS output")
```

Conditionally include `gnss_navsat.launch.py`, and pass `start_gnss` to `sensor_monitor.launch.py` as `gnss_enabled`.

- [ ] **Step 6: Run focused tests and verify GREEN**

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
colcon test --packages-select agt_sensor_monitor agt_chassis agt_bringup
colcon test-result --verbose
```

Expected: zero failures.

- [ ] **Step 7: Commit**

```bash
git add src/agt_sensor_monitor/launch/sensor_monitor.launch.py \
  src/agt_chassis/launch/bunker.launch.py \
  src/agt_bringup/launch/system.launch.py \
  src/agt_bringup/test/test_runtime_bringup_contract.py
git commit -m "feat(bringup): wire optional GNSS and inert chassis monitor mode"
```

---

### Task 4: Add explicit calibration rosbag profile and offline metadata gate

**Files:**
- Modify: `src/agt_experiment_manager/config/bag_profiles.yaml`
- Modify: `src/agt_experiment_manager/test/test_experiment_manager.py`
- Create: `tools/calibration/validate_calibration_bag.py`
- Create: `tools/calibration/test_validate_calibration_bag.py`

**Interfaces:**
- Produces bag profile id: `calibration`.
- Required captured topics:
  - `/tf`
  - `/tf_static`
  - `/agt/sensors/lidar/custom`
  - `/agt/sensors/imu/data`
  - `/agt/chassis/odometry`
  - `/agt/chassis/status`
  - `/agt/mapping/odometry`
  - `/agt/mapping/registered_points`
  - `/agt/navigation/cmd_vel`
  - `/diagnostics`
- Optional captured topic: `/agt/sensors/gnss/fix`.
- Validator exit code `0` means structural bag contract accepted; non-zero means missing/empty required evidence.

- [ ] **Step 1: Write failing profile tests**

Add a test that loads `bag_profiles.yaml`, requires `profiles["calibration"]`, checks the exact required topics above are present, checks `/agt/sensors/gnss/fix` is included for captures where GNSS exists, and checks the profile never contains `-a`.

Also assert the existing `ExperimentManager.start_bag()` command remains explicit:

```python
assert command[:6] == ["ros2", "bag", "record", "--storage", "sqlite3", "--output"]
assert "-a" not in command
```

- [ ] **Step 2: Run the experiment-manager test and verify RED**

```bash
python3 -m pytest src/agt_experiment_manager/test/test_experiment_manager.py -q
```

Expected: FAIL because the `calibration` profile does not exist.

- [ ] **Step 3: Add the `calibration` profile**

Add the explicit topic list to `bag_profiles.yaml`. Include `/agt/sensors/gnss/fix` in the recording profile even though the validator may treat it as optional; rosbag may record zero GNSS messages when no GNSS adapter is active, while all non-GNSS evidence remains usable.

- [ ] **Step 4: Write validator tests before the validator**

`test_validate_calibration_bag.py` creates temporary rosbag `metadata.yaml` fixtures with ROS2 `topics_with_message_count`. Cover:

1. complete required topics -> accepted;
2. missing wheel odometry -> rejected;
3. required topic with zero message count -> rejected;
4. missing GNSS accepted normally;
5. missing GNSS rejected with `--require-gnss`.

- [ ] **Step 5: Run validator tests and verify RED**

```bash
python3 -m pytest tools/calibration/test_validate_calibration_bag.py -q
```

Expected: FAIL because the validator script does not exist.

- [ ] **Step 6: Implement the metadata validator**

Expose pure function:

```python
def validate_metadata(metadata: dict, require_gnss: bool = False) -> dict:
    ...
```

Return a JSON-serializable object with:

```text
accepted
missing_topics
empty_topics
message_counts
duration_nanoseconds
gnss_present
```

CLI:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  /absolute/path/to/bag \
  [--require-gnss]
```

Read `<bag>/metadata.yaml`, reject missing/invalid metadata, and never inspect the large `.db3` directly in this P2 gate.

- [ ] **Step 7: Run both test groups and verify GREEN**

```bash
python3 -m pytest src/agt_experiment_manager/test/test_experiment_manager.py -q
python3 -m pytest tools/calibration/test_validate_calibration_bag.py -q
```

Expected: both pass.

- [ ] **Step 8: Commit**

```bash
git add src/agt_experiment_manager/config/bag_profiles.yaml \
  src/agt_experiment_manager/test/test_experiment_manager.py \
  tools/calibration/validate_calibration_bag.py \
  tools/calibration/test_validate_calibration_bag.py
git commit -m "feat(calibration): add explicit calibration rosbag contract"
```

---

### Task 5: Add motion-safe calibration capture launch and experiment ownership

**Files:**
- Create: `src/agt_bringup/launch/calibration_capture.launch.py`
- Modify: `src/agt_bringup/package.xml`
- Modify: `src/agt_bringup/test/test_runtime_bringup_contract.py`
- Modify: `src/agt_experiment_manager/README.md`
- Modify: `src/agt_bringup/README.md`

**Interfaces:**
- Launch command: `ros2 launch agt_bringup calibration_capture.launch.py`.
- Default composition: MID360 on, sensor monitor on, FAST-LIVO2 on, BUNKER driver on in `monitor` mode, perception/localization/navigation off, GNSS off unless explicitly configured.
- Starts `agt_experiment_manager` so the existing `/agt/data/bags/manage` service owns rosbag recording.
- No command path from controller/safety is started by the capture launch.

- [ ] **Step 1: Write failing launch-contract assertions**

Require the new launch to include `system.launch.py` with:

```text
start_sensor=true
start_sensor_monitor=true
start_odometry=true
start_perception=false
start_localization=false
start_navigation=false
start_chassis=true
chassis_operation_mode=monitor
```

Require it to include `agt_experiment_manager/launch/experiment_manager.launch.py` and to forward `start_gnss`/`gnss_input_topic`.

- [ ] **Step 2: Run bringup contract tests and verify RED**

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: FAIL because `calibration_capture.launch.py` does not exist.

- [ ] **Step 3: Implement `calibration_capture.launch.py`**

Declare only acquisition-specific knobs:

```text
use_sim_time=false
can_interface=can0
start_gnss=false
gnss_input_topic=""
runtime_dir=runtime
```

Include the Runtime system with fixed safety values above and include `experiment_manager.launch.py` with the same `runtime_dir`. Do not expose an override that can enable Nav2 or `chassis_operation_mode=control` from this launch.

- [ ] **Step 4: Add `agt_experiment_manager` Runtime dependency**

Add `<exec_depend>agt_experiment_manager</exec_depend>` to `agt_bringup/package.xml`. Keep all dependencies Runtime-local; do not introduce V2 packages.

- [ ] **Step 5: Document exact recording service sequence**

The operator workflow in `agt_bringup/README.md` must use the existing `ManageBagSession` service, not a second recorder process.

Create and immediately start an experiment:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 5,
  experiment_title: 'bunker-wheel-lio-calibration',
  objective: 'collect synchronized BUNKER wheel odom and FAST-LIVO2 evidence',
  profile_id: '',
  platform_profile: 'profiles/platforms/bunker.yaml',
  calibration_profile: 'bunker-wheel-lio-p1',
  start_experiment: true
}"
```

Copy the returned `experiment_id`, then start the explicit calibration profile:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 1,
  experiment_id: '<returned_experiment_id>',
  profile_id: 'calibration'
}"
```

The documentation must state that the placeholder in the second command is replaced by the actual returned id; this is documentation text, not code checked into an executable script.

Stop recording:

```bash
ros2 service call /agt/data/bags/manage agt_interfaces/srv/ManageBagSession "{
  operation: 2,
  experiment_id: '<returned_experiment_id>'
}"
```

Then complete the experiment with operation `6` and `result_status: 'COMPLETED'`.

- [ ] **Step 6: Correct stale experiment-manager documentation**

The current README mentions a legacy `bag_record.launch.py` that is not present in the Runtime launch directory. Replace that statement with the actual ownership model: `experiment_manager_node.py` plus `/agt/data/bags/manage` and explicit profiles.

- [ ] **Step 7: Run tests and launch parse**

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
colcon build --packages-select agt_bringup agt_experiment_manager --symlink-install
source install/setup.bash
ros2 launch agt_bringup calibration_capture.launch.py --show-args
```

Expected: all tests pass and the launch arguments contain no navigation/control-mode override.

- [ ] **Step 8: Commit**

```bash
git add src/agt_bringup src/agt_experiment_manager/README.md
git commit -m "feat(calibration): add motion-safe BUNKER capture bringup"
```

---

### Task 6: Hardware acceptance gate and calibration-dataset runbook

**Files:**
- Modify: `src/agt_bringup/README.md`
- Create: `docs/superpowers/reports/2026-08-27-bunker-hardware-calibration-p1-p2.md`

**Interfaces:**
- Produces a reproducible acceptance record for the first real BUNKER calibration bag.
- Does not estimate extrinsics or wheel scales yet; that belongs to P3.

- [ ] **Step 1: Add the hardware preflight commands**

Document a clean-shell sequence:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime/install/setup.bash
ip -details link show can0
ros2 launch agt_bringup calibration_capture.launch.py \
  can_interface:=can0 \
  start_gnss:=false
```

For a GNSS-equipped run, require the upstream driver's actual absolute `NavSatFix` topic:

```bash
ros2 launch agt_bringup calibration_capture.launch.py \
  can_interface:=can0 \
  start_gnss:=true \
  gnss_input_topic:=/receiver_specific/navsat_fix
```

The runbook must explicitly say `/receiver_specific/navsat_fix` is an example shape and must be replaced by the real driver topic discovered with `ros2 topic list`/`ros2 topic type`.

- [ ] **Step 2: Define topic/TF preflight checks**

Require:

```bash
ros2 topic hz /agt/sensors/lidar/custom
ros2 topic hz /agt/sensors/imu/data
ros2 topic hz /agt/chassis/odometry
ros2 topic hz /agt/mapping/odometry
ros2 topic hz /agt/mapping/registered_points
ros2 run tf2_ros tf2_echo base_link lidar_link
ros2 run tf2_ros tf2_echo base_link gps_link
```

For GNSS-enabled runs also require:

```bash
ros2 topic type /agt/sensors/gnss/fix
ros2 topic echo /agt/sensors/gnss/fix --once
```

Expected type: `sensor_msgs/msg/NavSatFix`.

- [ ] **Step 3: Define the calibration motion sequence**

Record one continuous bag spanning:

```text
1. static at start
2. straight forward
3. straight backward
4. large-radius left turn
5. large-radius right turn
6. figure eight
7. approximately +90/-90 degree turns
8. approximately +180/-180 degree turns
9. gentle slope up/down when available
10. static at end
```

State that spin-in-place and visibly slipping segments are collected for diagnosis but will be down-weighted/excluded by the later P3 solver.

- [ ] **Step 4: Validate the completed bag**

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory>
```

For GNSS-required capture:

```bash
python3 tools/calibration/validate_calibration_bag.py \
  runtime/experiments/<experiment_id>/rosbag/<calibration_bag_directory> \
  --require-gnss
```

The runbook must say to use the actual experiment/bag directory returned by the manager; the angle-bracket values are documentation placeholders only.

- [ ] **Step 5: Record acceptance evidence**

Create `docs/superpowers/reports/2026-08-27-bunker-hardware-calibration-p1-p2.md` with these initial states:

```text
CODE_LANDED: pending
LOCAL_BUILD: pending
HARDWARE_TOPICS: pending
TF_CONTRACT: pending
CALIBRATION_BAG: pending
BAG_METADATA_GATE: pending
```

Only change a state to PASS after the corresponding fresh local evidence is supplied.

- [ ] **Step 6: Run full affected regression set**

```bash
colcon build --symlink-install
source install/setup.bash
python3 -m pytest src/agt_bringup/test -q
python3 -m pytest tools/calibration/test_validate_calibration_bag.py -q
colcon test --packages-select \
  agt_description agt_sensor_adapters agt_sensor_monitor \
  agt_chassis agt_bringup agt_experiment_manager
colcon test-result --verbose
```

Expected before hardware acceptance: zero build/test failures.

- [ ] **Step 7: Commit docs/report scaffold**

```bash
git add src/agt_bringup/README.md \
  docs/superpowers/reports/2026-08-27-bunker-hardware-calibration-p1-p2.md
git commit -m "docs(calibration): add BUNKER P1 P2 acceptance runbook"
```

---

## P1/P2 Exit Gate

P1/P2 may be marked accepted only when all of the following have fresh evidence on the Runtime machine:

1. Clean Runtime build completes without a V2 overlay.
2. `gps_link` exists as one static `base_link` child and remains explicitly unverified until measured.
3. MID360 and IMU canonical topics are healthy.
4. BUNKER wheel odometry publishes `/agt/chassis/odometry` with driver odom TF disabled.
5. Calibration capture runs BUNKER in command-inert `monitor` mode.
6. FAST-LIVO2 publishes `/agt/mapping/odometry` and `/agt/mapping/registered_points` continuously.
7. GNSS adapter, when enabled, publishes `sensor_msgs/msg/NavSatFix` on `/agt/sensors/gnss/fix` without changing measurement values/covariance/timestamp.
8. Loss/absence of GNSS does not prevent the LIO/wheel calibration capture path.
9. The explicit `calibration` bag profile records the required topic set.
10. `validate_calibration_bag.py` accepts the first usable bag and rejects intentionally incomplete fixtures.
11. The captured bag includes the planned straight/turn/figure-eight/static excitation needed by the later P3 solver.
12. No new TF publisher owns `map -> odom` or duplicates `odom -> base_footprint`.

## Self-Review

- Spec coverage: this plan covers original design P1 hardware baseline and P2 rosbag calibration assets only. P3 wheel/LIO extrinsic/time/scale estimation, RTAB-Map, GNSS global correction, slope perception, and Nav2 field acceptance are intentionally excluded and remain later plans.
- Placeholder scan: executable/test code steps contain no `TBD`, `TODO`, or unspecified implementation behavior. Angle-bracket experiment ids appear only in operator documentation examples and are explicitly required to be replaced with values returned by the manager.
- Type consistency: GNSS is `sensor_msgs/msg/NavSatFix` end-to-end; canonical output is `/agt/sensors/gnss/fix`; wheel odometry remains `/agt/chassis/odometry`; LIO odometry remains `/agt/mapping/odometry`; the calibration profile and validator use the same required topic names.
- Safety review: calibration capture fixes chassis mode to `monitor`, monitor mode routes driver command subscription to an inert topic, navigation/localization/perception remain off, BUNKER driver TF remains off, and no new global-correction authority is introduced.
