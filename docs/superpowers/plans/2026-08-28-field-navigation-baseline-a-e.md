# BUNKER Field Navigation Baseline A-E Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a repeatable BUNKER field baseline that records a FAST-LIVO2 LIO-only commissioning map and calibration bag, freezes map assets, then runs existing relocalization + GlobalCorrectionManager + Nav2 with an explicitly opt-in RViz 2D Goal interface.

**Architecture:** Reuse the existing `agt_bringup/system.launch.py`, FAST-LIVO2 mapping launch, relocalization ownership, Nav2 stack, safety chain, and `agt_experiment_manager`. Add two thin commissioning launch wrappers instead of introducing another runtime stack. Mapping and navigation are separate runs; Runtime never navigates against a continuously changing commissioning map.

**Tech Stack:** ROS 2 Humble, Python launch, RViz2, FAST-LIVO2, Nav2, pytest, rosbag2, YAML/JSON/SHA256.

**Spec:** `docs/superpowers/specs/2026-08-28-field-navigation-baseline-design.md`

## Global Constraints

- Runtime remains independent of `agt_navigation_v2` source/install/workspace overlays.
- FAST-LIVO2 adapter remains the unique `odom -> base_footprint` authority.
- GlobalCorrectionManager remains the unique `map -> odom` authority.
- Relocalization produces correction evidence only; it does not publish `map -> odom`.
- Phase A and Phase C are separate processes. No online navigation against a map that is still being generated.
- `field_mapping.launch.py` must force localization/navigation off and PCD save on.
- `field_navigation.launch.py` must force PCD save off and use frozen PCD + processing record + navigation YAML.
- RViz direct goals are commissioning-only and default off in the normal `navigation.launch.py`.
- RViz goals do not bypass localization gating, Nav2 lifecycle, Collision Monitor, `agt_safety`, or chassis guard.
- First navigation baseline does not enable RTAB-Map or online GNSS global correction.
- Phase A must preserve canonical topics: `/agt/sensors/lidar/custom`, `/agt/sensors/imu/data`, `/agt/chassis/odometry`, `/agt/mapping/odometry`, `/agt/mapping/registered_points`, optional `/agt/sensors/gnss/fix`, `/tf`, `/tf_static`.
- Phase C must preserve canonical localization/navigation topics and record both raw and safety-filtered commands.
- Existing files and output directories must never be silently overwritten.

## File Structure Locked by This Plan

- `src/agt_bringup/launch/system.launch.py` — expose safe mapping-save arguments while keeping production defaults unchanged.
- `src/agt_bringup/launch/field_mapping.launch.py` — Phase A commissioning composition.
- `src/agt_bringup/launch/field_navigation.launch.py` — Phase C navigation composition.
- `src/agt_bringup/test/test_field_commissioning_contract.py` — static launch contract for Phase A/C.
- `src/agt_navigation/launch/navigation.launch.py` — make the existing RViz goal bridge explicit opt-in.
- `src/agt_navigation/config/field_navigation.rviz` — commissioning RViz layout and tools.
- `src/agt_navigation/test/test_rviz_goal_bridge_contract.py` — direct-goal ownership regression.
- `src/agt_experiment_manager/config/bag_profiles.yaml` — named baseline recording profiles.
- `src/agt_experiment_manager/test/test_experiment_manager.py` — profile/topic contract tests.
- `tools/commissioning/freeze_map_assets.py` — Phase B hash/manifest helper.
- `tools/commissioning/test_freeze_map_assets.py` — manifest and no-overwrite tests.
- `docs/runbooks/field_navigation_baseline.md` — copy/paste operator workflow, gates, stop conditions, and output layout.

---

### Task 1: Freeze commissioning launch contracts and expose mapping-save arguments

**Files:**
- Create: `src/agt_bringup/test/test_field_commissioning_contract.py`
- Modify: `src/agt_bringup/launch/system.launch.py`
- Modify: `src/agt_bringup/CMakeLists.txt`

**Interfaces:**
- Consumes: existing `agt_bringup/system.launch.py` and `agt_mapping/fast_livo2_mapping.launch.py`.
- Produces system args `mapping_save_pcd` (default `false`), `mapping_pcd_output_dir` (default `runtime/maps/fast_livo2`), and `mapping_pcd_save_interval` (default `-1`).

- [ ] **Step 1: Write the failing contract test**

Create `test_field_commissioning_contract.py` with assertions that the normal system launch exposes but does not enable mapping save by default:

```python
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SYSTEM = ROOT / "agt_bringup" / "launch" / "system.launch.py"


def test_system_exposes_safe_mapping_output_arguments():
    source = SYSTEM.read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("mapping_save_pcd", default_value="false")' in source
    assert 'DeclareLaunchArgument("mapping_pcd_save_interval", default_value="-1")' in source
    assert 'DeclareLaunchArgument("mapping_pcd_output_dir"' in source
    assert '"save_pcd": LaunchConfiguration("mapping_save_pcd")' in source
    assert '"pcd_save_interval": LaunchConfiguration("mapping_pcd_save_interval")' in source
    assert '"pcd_output_dir": LaunchConfiguration("mapping_pcd_output_dir")' in source
```

- [ ] **Step 2: Register and run RED**

Add an `ament_add_pytest_test(test_field_commissioning_contract ...)` entry in `src/agt_bringup/CMakeLists.txt`.

Run:

```bash
python3 -m pytest src/agt_bringup/test/test_field_commissioning_contract.py -q
```

Expected: FAIL because the three launch args do not exist and `system.launch.py` still hard-codes `save_pcd: false`.

- [ ] **Step 3: Add minimal safe passthrough to `system.launch.py`**

Declare:

```python
DeclareLaunchArgument("mapping_save_pcd", default_value="false"),
DeclareLaunchArgument("mapping_pcd_save_interval", default_value="-1"),
DeclareLaunchArgument(
    "mapping_pcd_output_dir",
    default_value="runtime/maps/fast_livo2",
),
```

Change only the FAST-LIVO2 include arguments to:

```python
launch_arguments={
    "use_sim_time": use_sim_time,
    "save_pcd": LaunchConfiguration("mapping_save_pcd"),
    "pcd_save_interval": LaunchConfiguration("mapping_pcd_save_interval"),
    "pcd_output_dir": LaunchConfiguration("mapping_pcd_output_dir"),
}.items(),
```

Do not change any normal default behavior.

- [ ] **Step 4: Run GREEN plus existing P0/P1 bringup regressions**

```bash
python3 -m pytest \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_bringup/test/test_runtime_bringup_contract.py \
  src/agt_bringup/test/test_localization_navigation_gate.py \
  -q
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_bringup/launch/system.launch.py \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_bringup/CMakeLists.txt
git commit -m "feat(bringup): expose safe commissioning mapping outputs"
```

---

### Task 2: Add Phase A `field_mapping.launch.py`

**Files:**
- Create: `src/agt_bringup/launch/field_mapping.launch.py`
- Modify: `src/agt_bringup/test/test_field_commissioning_contract.py`

**Interfaces:**
- Consumes: `agt_bringup/system.launch.py`.
- Produces: a field-mapping launch that forces localization/navigation off, PCD save on, and BUNKER default operation mode to `monitor`.
- Output root: `runtime/commissioning/<map_id>/<run_id>/mapping`.

- [ ] **Step 1: Extend the test first**

Add assertions requiring:

```python
def test_field_mapping_is_mapping_only_and_command_inert_by_default():
    source = (ROOT / "agt_bringup" / "launch" / "field_mapping.launch.py").read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("map_id")' in source
    assert 'DeclareLaunchArgument("run_id")' in source
    assert 'DeclareLaunchArgument("start_gnss", default_value="false")' in source
    assert 'DeclareLaunchArgument("chassis_operation_mode", default_value="monitor")' in source
    assert '"start_localization": "false"' in source
    assert '"start_navigation": "false"' in source
    assert '"mapping_save_pcd": "true"' in source
```

Also require an `OpaqueFunction` validator that rejects empty `map_id`, empty `run_id`, non-absolute GNSS input when GNSS is enabled, and an already-populated mapping output directory.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest src/agt_bringup/test/test_field_commissioning_contract.py -q
```

Expected: FAIL because `field_mapping.launch.py` does not exist.

- [ ] **Step 3: Implement the wrapper**

The launch must compute:

```text
runtime_dir/commissioning/<map_id>/<run_id>/mapping
```

from launch args `runtime_dir`, `map_id`, `run_id`. It then includes `system.launch.py` with these fixed values:

```python
{
    "platform": LaunchConfiguration("platform"),
    "start_sensor": "true",
    "start_sensor_monitor": "true",
    "start_gnss": LaunchConfiguration("start_gnss"),
    "gnss_input_topic": LaunchConfiguration("gnss_input_topic"),
    "start_odometry": "true",
    "start_perception": "false",
    "start_localization": "false",
    "start_navigation": "false",
    "start_chassis": LaunchConfiguration("start_chassis"),
    "chassis_operation_mode": LaunchConfiguration("chassis_operation_mode"),
    "can_interface": LaunchConfiguration("can_interface"),
    "mapping_save_pcd": "true",
    "mapping_pcd_save_interval": "-1",
    "mapping_pcd_output_dir": LaunchConfiguration("mapping_output_dir"),
}
```

Do not start Nav2, relocalization, RTAB-Map, or any direct-goal bridge.

- [ ] **Step 4: Run focused GREEN**

```bash
python3 -m pytest src/agt_bringup/test/test_field_commissioning_contract.py -q
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add src/agt_bringup/launch/field_mapping.launch.py \
  src/agt_bringup/test/test_field_commissioning_contract.py
git commit -m "feat(bringup): add field mapping commissioning launch"
```

---

### Task 3: Make RViz direct goals commissioning-only

**Files:**
- Modify: `src/agt_navigation/launch/navigation.launch.py`
- Create: `src/agt_navigation/test/test_rviz_goal_bridge_contract.py`
- Modify: `src/agt_navigation/CMakeLists.txt`

**Interfaces:**
- Consumes: existing `goal_pose_bridge.py` (`/goal_pose -> NavigateToPose`).
- Produces: `enable_rviz_goal_bridge:=false` as the normal default.

- [ ] **Step 1: Write the failing ownership test**

```python
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
NAV_LAUNCH = ROOT / "agt_navigation" / "launch" / "navigation.launch.py"


def test_rviz_goal_bridge_is_explicit_opt_in():
    source = NAV_LAUNCH.read_text(encoding="utf-8")
    assert 'DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false")' in source
    bridge = source[source.index('executable="goal_pose_bridge.py"'):]
    assert 'condition=IfCondition(LaunchConfiguration("enable_rviz_goal_bridge"))' in bridge
```

- [ ] **Step 2: Register and run RED**

Register with `ament_add_pytest_test` in `src/agt_navigation/CMakeLists.txt`.

```bash
python3 -m pytest src/agt_navigation/test/test_rviz_goal_bridge_contract.py -q
```

Expected: FAIL because the bridge currently starts unconditionally.

- [ ] **Step 3: Implement the opt-in boundary**

Declare:

```python
DeclareLaunchArgument("enable_rviz_goal_bridge", default_value="false"),
```

Add to the existing bridge node:

```python
condition=IfCondition(LaunchConfiguration("enable_rviz_goal_bridge")),
```

No changes to `goal_pose_bridge.py` behavior in this task.

- [ ] **Step 4: Run GREEN and navigation contract regression**

```bash
python3 -m pytest src/agt_navigation/test/test_rviz_goal_bridge_contract.py -q
colcon test --packages-select agt_navigation --event-handlers console_direct+
```

Expected: all `agt_navigation` tests pass.

- [ ] **Step 5: Commit**

```bash
git add src/agt_navigation/launch/navigation.launch.py \
  src/agt_navigation/test/test_rviz_goal_bridge_contract.py \
  src/agt_navigation/CMakeLists.txt
git commit -m "fix(navigation): make rviz direct goals commissioning only"
```

---

### Task 4: Add Phase C `field_navigation.launch.py` and commissioning RViz

**Files:**
- Create: `src/agt_bringup/launch/field_navigation.launch.py`
- Create: `src/agt_navigation/config/field_navigation.rviz`
- Modify: `src/agt_bringup/test/test_field_commissioning_contract.py`
- Modify: `src/agt_navigation/test/test_rviz_goal_bridge_contract.py`
- Modify: `src/agt_bringup/package.xml`

**Interfaces:**
- Consumes: frozen `global_map_pcd`, `global_map_processing_record`, `navigation_map`, `map_id`, `map_hash`.
- Produces: LIO-only odometry + existing relocalization + GlobalCorrectionManager + gated Nav2 + safety/chassis, with optional RViz and explicit direct-goal bridge.

- [ ] **Step 1: Add RED launch assertions**

Require `field_navigation.launch.py` to include `system.launch.py` with:

```python
{
    "start_sensor": "true",
    "start_sensor_monitor": "true",
    "start_odometry": "true",
    "mapping_save_pcd": "false",
    "start_perception": "true",
    "start_localization": "true",
    "start_navigation": "true",
    "start_chassis": LaunchConfiguration("start_chassis"),
    "chassis_operation_mode": LaunchConfiguration("chassis_operation_mode"),
    "global_map_pcd": LaunchConfiguration("global_map_pcd"),
    "global_map_processing_record": LaunchConfiguration("global_map_processing_record"),
    "navigation_map": LaunchConfiguration("navigation_map"),
    "map_id": LaunchConfiguration("map_id"),
    "map_hash": LaunchConfiguration("map_hash"),
}
```

Also require that the wrapper passes `enable_rviz_goal_bridge=true` to the navigation include path. If this cannot be passed through `system.launch.py` yet, extend `system.launch.py` with `enable_rviz_goal_bridge:=false` and forward it to `navigation.launch.py`; keep the default false.

Require asset validation to reject missing files, empty `map_id`, and non-canonical `map_hash` that does not match `sha256:<64 lowercase hex>`.

- [ ] **Step 2: Add RED RViz assertions**

Require `field_navigation.rviz` to contain:

```text
Fixed Frame: map
/agt/map/global_occupancy
/agt/mapping/registered_points
/plan
/global_costmap/costmap
/local_costmap/costmap
rviz_default_plugins/TF
rviz_default_plugins/RobotModel
rviz_default_plugins/SetInitialPose
rviz_default_plugins/SetGoal
/initialpose
/goal_pose
```

Run:

```bash
python3 -m pytest \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_navigation/test/test_rviz_goal_bridge_contract.py \
  -q
```

Expected: FAIL on missing wrapper/RViz config/passthrough.

- [ ] **Step 3: Implement `field_navigation.launch.py`**

The wrapper must default:

```text
start_chassis=false
chassis_operation_mode=control
start_rviz=true
start_gnss=false
```

`start_chassis=false` is deliberate: the operator must opt into motion after preflight. The launch must not enable RTAB-Map or GNSS global correction.

Start RViz only when requested:

```python
Node(
    package="rviz2",
    executable="rviz2",
    name="agt_field_navigation_rviz",
    arguments=["-d", str(navigation_share / "config" / "field_navigation.rviz")],
    condition=IfCondition(LaunchConfiguration("start_rviz")),
)
```

Add `<exec_depend>rviz2</exec_depend>` to `agt_bringup/package.xml` because this wrapper owns the optional RViz process.

- [ ] **Step 4: Create the RViz config**

Use the existing waypoint preview style as a starting point, but add live registered cloud, TF, RobotModel, global/local costmaps, path, SetInitialPose, and SetGoal. Keep `map` as fixed frame.

- [ ] **Step 5: Run GREEN and build smoke**

```bash
python3 -m pytest \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_navigation/test/test_rviz_goal_bridge_contract.py \
  -q

colcon build --packages-select agt_navigation agt_bringup --symlink-install
```

Expected: PASS/build success.

- [ ] **Step 6: Commit**

```bash
git add src/agt_bringup/launch/field_navigation.launch.py \
  src/agt_bringup/launch/system.launch.py \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_bringup/package.xml \
  src/agt_navigation/config/field_navigation.rviz \
  src/agt_navigation/test/test_rviz_goal_bridge_contract.py
git commit -m "feat(runtime): add gated field rviz navigation baseline"
```

---

### Task 5: Freeze Phase A/C rosbag profiles

**Files:**
- Modify: `src/agt_experiment_manager/config/bag_profiles.yaml`
- Modify: `src/agt_experiment_manager/test/test_experiment_manager.py`
- Modify: `src/agt_experiment_manager/README.md`

**Interfaces:**
- Produces profiles `field_mapping_baseline` and `field_navigation_baseline`.
- Reuses the sole recorder ownership in `agt_experiment_manager`; no `ros2 bag record` subprocess is launched by `agt_bringup`.

- [ ] **Step 1: Add failing profile assertions**

Add tests that load `bag_profiles.yaml` and require exact minimum subsets:

```python
mapping_required = {
    "/tf", "/tf_static",
    "/agt/sensors/lidar/custom",
    "/agt/sensors/imu/data",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/navigation/cmd_vel",
}

navigation_required = {
    "/tf", "/tf_static",
    "/agt/mapping/odometry",
    "/agt/mapping/registered_points",
    "/agt/localization/status",
    "/agt/navigation/cmd_vel_raw",
    "/agt/navigation/cmd_vel",
    "/plan",
    "/agt/chassis/odometry",
    "/agt/chassis/status",
    "/goal_pose",
    "/initialpose",
}
```

Both profiles should also include `/agt/sensors/gnss/fix`; absence of messages is allowed when GNSS is disabled.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest src/agt_experiment_manager/test/test_experiment_manager.py -q
```

Expected: FAIL because the named field baseline profiles do not exist.

- [ ] **Step 3: Add the two explicit profiles**

Do not alias or use wildcard recording. Add explicit lists to `bag_profiles.yaml`. The navigation profile should additionally include `/agt/perception/obstacle_cloud`, `/global_costmap/costmap`, `/local_costmap/costmap`, `/agt/safety/status`, and `/diagnostics` for diagnosis.

- [ ] **Step 4: Document recorder ownership and operator service flow**

Update README to state:

```text
field_mapping.launch.py / field_navigation.launch.py start runtime components only.
agt_experiment_manager remains the sole owner of rosbag recording.
Start the corresponding named profile before moving the robot.
```

- [ ] **Step 5: Run GREEN**

```bash
python3 -m pytest src/agt_experiment_manager/test/test_experiment_manager.py -q
```

Expected: PASS.

- [ ] **Step 6: Commit**

```bash
git add src/agt_experiment_manager/config/bag_profiles.yaml \
  src/agt_experiment_manager/test/test_experiment_manager.py \
  src/agt_experiment_manager/README.md
git commit -m "feat(experiments): freeze field commissioning bag profiles"
```

---

### Task 6: Add Phase B map-freeze helper and operator runbook

**Files:**
- Create: `tools/commissioning/freeze_map_assets.py`
- Create: `tools/commissioning/test_freeze_map_assets.py`
- Create: `docs/runbooks/field_navigation_baseline.md`

**Interfaces:**
- Consumes: one PCD, one navigation YAML, the image referenced by that YAML, `map_id`, `run_id`, and output manifest path.
- Produces: deterministic `map_manifest.json` with SHA256 identities and no silent overwrite.

- [ ] **Step 1: Write failing pure-Python tests**

Test helper behavior with temporary files:

```python
def test_manifest_hashes_pcd_yaml_and_image(tmp_path):
    ...
    manifest = freeze_assets(...)
    assert manifest["mapping_source"] == "FAST_LIVO2_LIO_ONLY"
    assert manifest["pcd_sha256"].startswith("sha256:")
    assert manifest["navigation_yaml_sha256"].startswith("sha256:")
    assert manifest["navigation_image_sha256"].startswith("sha256:")
    assert manifest["calibration_status"] == "UNVERIFIED"


def test_existing_manifest_is_not_overwritten(tmp_path):
    ...
    with pytest.raises(FileExistsError):
        freeze_assets(...)
```

Also test rejection for empty `map_id/run_id`, missing files, and a navigation YAML whose `image:` reference does not resolve.

- [ ] **Step 2: Run RED**

```bash
python3 -m pytest tools/commissioning/test_freeze_map_assets.py -q
```

Expected: FAIL because the helper does not exist.

- [ ] **Step 3: Implement deterministic hashing and manifest writing**

Use only Python stdlib + PyYAML already present in the repository environment. Hash files by streaming chunks, return canonical lowercase strings:

```text
sha256:<64 hex>
```

Write JSON atomically through `<manifest>.tmp` + `os.replace`, but reject when the final manifest path already exists.

Required manifest fields:

```json
{
  "schema_version": 1,
  "map_id": "...",
  "run_id": "...",
  "mapping_source": "FAST_LIVO2_LIO_ONLY",
  "pcd_path": "...",
  "pcd_sha256": "sha256:...",
  "navigation_yaml_path": "...",
  "navigation_yaml_sha256": "sha256:...",
  "navigation_image_path": "...",
  "navigation_image_sha256": "sha256:...",
  "calibration_status": "UNVERIFIED",
  "generated_at_utc": "..."
}
```

- [ ] **Step 4: Run GREEN**

```bash
python3 -m pytest tools/commissioning/test_freeze_map_assets.py -q
```

Expected: PASS.

- [ ] **Step 5: Write the field runbook with exact phases**

The runbook must include copy/paste sections for:

1. fresh shell + source ROS/Runtime;
2. BUNKER CAN setup;
3. Phase A `field_mapping.launch.py` with and without GNSS;
4. start `field_mapping_baseline` bag recording through `agt_experiment_manager`;
5. pre-motion topic/TF/monitor-sink checks;
6. frozen calibration trajectory: static 30 s, forward speed sweep, reverse, left/right large circle, S, figure-eight, ±90°, ±180°, optional slope, static 30 s;
7. stop recording and validate the bag;
8. build/freeze PCD + 2D map and run `freeze_map_assets.py`;
9. Phase C `field_navigation.launch.py` first with `start_chassis:=false`;
10. verify localization enters TRACKING and Nav2 lifecycle starts;
11. restart/enable motion only after safety checks;
12. RViz SetInitialPose and SetGoal usage;
13. N0–N6 sequence: 60 s stationary, 2 m, 5 m, two 90° targets, 5 m turning, 7 m, 10 m;
14. one run_id/bag per experiment;
15. stop conditions for localization invalid, collision stop, wrong point cloud, control oscillation, or TF authority conflict.

The runbook must explicitly say that GNSS in the first Phase C baseline is recorded as evaluation evidence only and does not own `map -> odom`.

- [ ] **Step 6: Run complete software baseline regression**

```bash
python3 -m pytest \
  src/agt_bringup/test/test_field_commissioning_contract.py \
  src/agt_bringup/test/test_runtime_bringup_contract.py \
  src/agt_bringup/test/test_localization_navigation_gate.py \
  src/agt_navigation/test/test_rviz_goal_bridge_contract.py \
  src/agt_experiment_manager/test/test_experiment_manager.py \
  tools/commissioning/test_freeze_map_assets.py \
  -q

colcon build --packages-select \
  agt_bringup agt_navigation agt_experiment_manager --symlink-install

colcon test --packages-select \
  agt_bringup agt_navigation agt_experiment_manager

colcon test-result --verbose
```

Expected: all selected tests pass / zero failures. This is a software gate only; it does not claim real hardware verification.

- [ ] **Step 7: Commit**

```bash
git add tools/commissioning \
  docs/runbooks/field_navigation_baseline.md
git commit -m "feat(runtime): freeze field navigation operator baseline"
```

---

## Final Acceptance Before First Vehicle Run

Software evidence required:

```text
field_mapping.launch.py contract                     PASS
field_navigation.launch.py contract                  PASS
normal navigation RViz direct-goal default OFF       PASS
commissioning direct-goal explicit opt-in            PASS
field_mapping_baseline bag profile                   PASS
field_navigation_baseline bag profile                PASS
map manifest no-overwrite/hash tests                 PASS
agt_bringup/agt_navigation/experiment_manager tests  PASS
selected colcon test-result                          0 failures
```

First real-vehicle session remains a separate hardware acceptance. Do not mark this plan hardware-green until MID360/IMU/LIO/GNSS/TF/chassis/safety and the N0–N6 run evidence are observed on the vehicle.
