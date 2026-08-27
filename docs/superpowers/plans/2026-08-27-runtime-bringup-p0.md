# Runtime Bringup P0 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `agt_navigation_runtime` independently buildable and runnable with a minimal BUNKER-oriented `agt_bringup` package, removing the current broken runtime reference to a bringup package that only exists in V2.

**Architecture:** Add a small Runtime-owned `agt_bringup` package that owns composition and lifecycle gating only. Reuse existing package launch files for BUNKER description, MID360, sensor health, FAST-LIVO2, local perception, NDT/ICP localization, Nav2, safety, and chassis; do not copy V2 Qt/semantic/coverage orchestration. Keep all motion fail-closed by default: chassis driver and Nav2 are opt-in, Nav2 lifecycle remains localization-gated, and BUNKER driver TF remains disabled.

**Tech Stack:** ROS 2 Humble, Python launch, `ament_cmake`, `rclpy`, `nav2_msgs`, pytest/ament_cmake_pytest, existing AGT runtime packages.

**Spec:** `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Global Constraints

- Runtime must build and run without sourcing `agt_navigation_v2/install/setup.bash` or referencing the V2 source tree.
- FAST-LIVO2 adapter remains the only publisher of `odom -> base_footprint`.
- GlobalCorrectionManager remains the only publisher of `map -> odom`.
- BUNKER driver must keep `publish_driver_odom_tf:=false`.
- `agt_safety` and chassis command guard remain mandatory for control mode; no launch in this plan may publish navigation velocity directly to the BUNKER driver.
- RTAB-Map, GNSS fusion, slope-aware perception, semantic/Keepout production, Qt, and coverage are outside P0.
- Existing validated FAST-LIVO2, Nav2, safety, chassis, and localization parameter files are not changed in P0.
- The default unified bringup is motion-safe: `start_navigation:=false`, `start_localization:=false`, `start_chassis:=false`; sensor, odometry, health, local perception, and safety-capable runtime composition are enabled independently.
- No hard-coded usernames, absolute workspace paths, or V2 relative paths.

---

## File Structure

P0 creates one package and changes only the runtime files required to make the package authoritative:

```text
src/agt_bringup/
├── CMakeLists.txt                     # installs launch/scripts and registers P0 tests
├── package.xml                        # runtime-only dependencies
├── README.md                          # operator contract and safe launch examples
├── launch/
│   └── system.launch.py               # single Runtime composition entry point
├── scripts/
│   └── localization_navigation_gate.py # Nav2 lifecycle gate migrated into Runtime
└── test/
    ├── test_localization_navigation_gate.py
    └── test_runtime_bringup_contract.py

README.md                               # list agt_bringup and document P0 entry point
src/agt_mapping/README.md               # remove stale V2.5 ownership wording where it describes Runtime behavior
src/agt_navigation/launch/navigation.launch.py # keep gate invocation, now resolved by Runtime package
```

`system.launch.py` composes existing launch files; it does not reimplement their nodes:

```text
agt_description/bunker_description.launch.py
agt_sensor_adapters/mid360.launch.py
agt_sensor_monitor/sensor_monitor.launch.py
agt_mapping/fast_livo2_mapping.launch.py
agt_perception/local_obstacles.launch.py
agt_localization/relocalization.launch.py
agt_navigation/navigation.launch.py
agt_chassis/bunker.launch.py
```

---

### Task 1: Add the Runtime-owned `agt_bringup` package and freeze its dependency boundary

**Files:**
- Create: `src/agt_bringup/package.xml`
- Create: `src/agt_bringup/CMakeLists.txt`
- Create: `src/agt_bringup/README.md`
- Create: `src/agt_bringup/test/test_runtime_bringup_contract.py`

**Interfaces:**
- Consumes: existing ROS package names `agt_description`, `agt_sensor_adapters`, `agt_sensor_monitor`, `agt_mapping`, `agt_localization`, `agt_perception`, `agt_navigation`, `agt_safety`, `agt_chassis`.
- Produces: installable package `agt_bringup`; later tasks install `localization_navigation_gate.py` and `system.launch.py` into it.

- [ ] **Step 1: Write the failing package-boundary test**

Create `src/agt_bringup/test/test_runtime_bringup_contract.py` with:

```python
from pathlib import Path
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[3]
PACKAGE = ROOT / "src" / "agt_bringup"


def test_runtime_bringup_package_exists_and_is_runtime_only():
    package_xml = PACKAGE / "package.xml"
    assert package_xml.is_file()
    root = ET.parse(package_xml).getroot()
    assert root.findtext("name") == "agt_bringup"

    dependencies = {
        element.text
        for element in root
        if element.tag in {"depend", "exec_depend", "buildtool_depend"}
    }
    required = {
        "ament_cmake",
        "agt_chassis",
        "agt_description",
        "agt_interfaces",
        "agt_localization",
        "agt_mapping",
        "agt_navigation",
        "agt_perception",
        "agt_safety",
        "agt_sensor_adapters",
        "agt_sensor_monitor",
        "launch",
        "launch_ros",
        "nav2_msgs",
        "rclpy",
    }
    assert required <= dependencies
    forbidden = {
        "agt_coverage_planning",
        "agt_map_processing",
        "agt_teach_repeat",
        "agt_ui_bridge",
    }
    assert not (dependencies & forbidden)


def test_runtime_bringup_sources_do_not_reference_v2_workspace():
    forbidden_tokens = (
        "agt_navigation_v2/install",
        "agt_navigation_v2/src",
        "/home/yangxuan",
    )
    for path in PACKAGE.rglob("*"):
        if not path.is_file() or path.suffix not in {".py", ".xml", ".txt", ".md"}:
            continue
        text = path.read_text(encoding="utf-8")
        for token in forbidden_tokens:
            assert token not in text, f"{path}: forbidden runtime dependency {token}"
```

- [ ] **Step 2: Run the test to verify it fails before the package exists**

Run:

```bash
source /opt/ros/humble/setup.bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: FAIL because `src/agt_bringup/package.xml` does not exist yet.

- [ ] **Step 3: Create the minimal runtime-only package manifest**

Create `src/agt_bringup/package.xml` exactly with the runtime dependencies needed by this P0 package:

```xml
<?xml version="1.0"?>
<package format="3">
  <name>agt_bringup</name>
  <version>0.1.0</version>
  <description>Runtime-only system composition and Nav2 localization gating.</description>
  <maintainer email="yangxuan@example.com">yangxuan</maintainer>
  <license>Apache-2.0</license>
  <buildtool_depend>ament_cmake</buildtool_depend>
  <exec_depend>launch</exec_depend>
  <exec_depend>launch_ros</exec_depend>
  <exec_depend>agt_chassis</exec_depend>
  <exec_depend>agt_description</exec_depend>
  <exec_depend>agt_interfaces</exec_depend>
  <exec_depend>agt_localization</exec_depend>
  <exec_depend>agt_mapping</exec_depend>
  <exec_depend>agt_navigation</exec_depend>
  <exec_depend>agt_perception</exec_depend>
  <exec_depend>agt_safety</exec_depend>
  <exec_depend>agt_sensor_adapters</exec_depend>
  <exec_depend>agt_sensor_monitor</exec_depend>
  <exec_depend>nav2_msgs</exec_depend>
  <exec_depend>rclpy</exec_depend>
  <test_depend>ament_cmake_pytest</test_depend>
  <test_depend>python3-pytest</test_depend>
  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```

- [ ] **Step 4: Add CMake installation and test registration**

Create `src/agt_bringup/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.8)
project(agt_bringup)

find_package(ament_cmake REQUIRED)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/localization_navigation_gate.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_localization_navigation_gate
    test/test_localization_navigation_gate.py
  )
  ament_add_pytest_test(
    test_runtime_bringup_contract
    test/test_runtime_bringup_contract.py
  )
endif()

ament_package()
```

Create `src/agt_bringup/README.md` with these ownership rules and safe command surface:

```markdown
# agt_bringup

Runtime-only composition for `agt_navigation_runtime`.

It may compose robot description, sensors, sensor monitoring, continuous odometry,
localization, local perception, Nav2, safety, and chassis. It must not contain Qt,
semantic-map generation, coverage planning, offline map production, or dependencies on
`agt_navigation_v2` source/install trees.

The default `system.launch.py` startup is motion-safe: localization, Nav2, and the BUNKER
CAN driver remain opt-in until their required map/calibration inputs are supplied.
```

- [ ] **Step 5: Run the package-boundary test**

Run:

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: PASS.

- [ ] **Step 6: Commit Task 1**

```bash
git add src/agt_bringup/package.xml src/agt_bringup/CMakeLists.txt \
  src/agt_bringup/README.md src/agt_bringup/test/test_runtime_bringup_contract.py
git commit -m "feat(bringup): add runtime-owned package boundary"
```

---

### Task 2: Migrate the localization-to-Nav2 lifecycle gate into Runtime

**Files:**
- Create: `src/agt_bringup/scripts/localization_navigation_gate.py`
- Create: `src/agt_bringup/test/test_localization_navigation_gate.py`
- Verify unchanged consumer: `src/agt_navigation/launch/navigation.launch.py`

**Interfaces:**
- Consumes: `/agt/localization/status` (`agt_interfaces/msg/LocalizationStatus`) and `/lifecycle_manager_navigation/manage_nodes` (`nav2_msgs/srv/ManageLifecycleNodes`).
- Produces: lifecycle commands STARTUP/PAUSE/RESUME/RESET only; publishes no TF and no velocity.

- [ ] **Step 1: Write the Runtime gate tests before adding the script**

Create `src/agt_bringup/test/test_localization_navigation_gate.py`:

```python
import importlib.util
from pathlib import Path

from agt_interfaces.msg import LocalizationStatus
from nav2_msgs.srv import ManageLifecycleNodes


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "localization_navigation_gate.py"
SPEC = importlib.util.spec_from_file_location("localization_navigation_gate", SCRIPT)
GATE = importlib.util.module_from_spec(SPEC)


def _load_gate():
    SPEC.loader.exec_module(GATE)
    return GATE


def test_gate_requires_fresh_accepted_tracking_status():
    gate = _load_gate()
    status = LocalizationStatus()
    assert not gate.localization_status_is_ready(status)
    status.state = LocalizationStatus.STATE_TRACKING
    status.pose_valid = True
    status.localization_accepted = True
    status.error_code = LocalizationStatus.ERROR_NONE
    assert gate.localization_status_is_ready(status)
    status.status_stale = True
    assert not gate.localization_status_is_ready(status)


def test_gate_keeps_ten_second_default_freshness_window():
    source = SCRIPT.read_text(encoding="utf-8")
    assert 'declare_parameter("localization_status_timeout", 10.0)' in source


class _Logger:
    def error(self, *_args): pass
    def info(self, *_args): pass
    def warn(self, *_args): pass


class _GateState:
    def __init__(self, command):
        self._in_flight = True
        self._pending_command = command
        self._nav_started = False
        self._nav_paused = False
        self._recovery_reset_required = False
        self._logger = _Logger()

    def get_logger(self):
        return self._logger


class _Future:
    def __init__(self, *, success=None, error=None):
        self._success = success
        self._error = error

    def result(self):
        if self._error is not None:
            raise self._error
        response = ManageLifecycleNodes.Response()
        response.success = self._success
        return response


def test_rejected_startup_is_fail_closed_and_requires_reset():
    gate_module = _load_gate()
    state = _GateState(ManageLifecycleNodes.Request.STARTUP)
    gate_module.LocalizationNavigationGate._command_done(state, _Future(success=False))
    assert not state._nav_started
    assert state._recovery_reset_required


def test_lifecycle_service_exception_is_fail_closed():
    gate_module = _load_gate()
    state = _GateState(ManageLifecycleNodes.Request.RESUME)
    gate_module.LocalizationNavigationGate._command_done(
        state, _Future(error=RuntimeError("service unavailable"))
    )
    assert not state._nav_started
    assert state._recovery_reset_required
```

- [ ] **Step 2: Run the gate test and verify failure**

Run:

```bash
source /opt/ros/humble/setup.bash
python3 -m pytest src/agt_bringup/test/test_localization_navigation_gate.py -q
```

Expected: FAIL because `scripts/localization_navigation_gate.py` is absent.

- [ ] **Step 3: Add the Runtime gate implementation**

Create `src/agt_bringup/scripts/localization_navigation_gate.py` by migrating the validated Runtime-compatible logic already used by the V2 gate. Preserve these exact public behaviors:

```python
def localization_status_is_ready(message: LocalizationStatus) -> bool:
    return (
        message.state == LocalizationStatus.STATE_TRACKING
        and message.pose_valid
        and message.localization_accepted
        and message.error_code == LocalizationStatus.ERROR_NONE
        and not message.status_stale
    )
```

The node constructor must keep:

```python
self._manager_service = self.declare_parameter(
    "manager_service", "/lifecycle_manager_navigation/manage_nodes"
).value
self._status_timeout = float(
    self.declare_parameter("localization_status_timeout", 10.0).value
)
self._retry_period = float(
    self.declare_parameter("lifecycle_retry_period", 1.0).value
)
self._invalid_grace_period = float(
    self.declare_parameter("localization_invalid_grace_period", 1.0).value
)
self._pause_on_invalid = bool(
    self.declare_parameter("pause_on_invalid", True).value
)
```

The state machine must retain these transitions:

```text
fresh accepted TRACKING -> STARTUP when never started
fresh accepted TRACKING after PAUSE -> RESUME
stale/rejected status after grace -> PAUSE
failed STARTUP/RESUME -> fail closed, require RESET before retry
failed RESET -> clear reset-required flag so retry cannot lock into RESET forever
```

Do not add TF broadcasters, publishers to `cmd_vel`, or direct chassis dependencies.

- [ ] **Step 4: Run the gate tests**

Run:

```bash
python3 -m pytest src/agt_bringup/test/test_localization_navigation_gate.py -q
```

Expected: PASS.

- [ ] **Step 5: Verify the existing Nav2 launch resolves to Runtime-owned gate**

Run after a package build:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-select agt_interfaces agt_bringup agt_navigation
source install/setup.bash
ros2 pkg executables agt_bringup | grep localization_navigation_gate.py
```

Expected output includes:

```text
agt_bringup localization_navigation_gate.py
```

Also verify `src/agt_navigation/launch/navigation.launch.py` still contains:

```python
Node(
    package="agt_bringup",
    executable="localization_navigation_gate.py",
    ...
)
```

No change to Nav2 lifecycle semantics is required in this task.

- [ ] **Step 6: Commit Task 2**

```bash
git add src/agt_bringup/scripts/localization_navigation_gate.py \
  src/agt_bringup/test/test_localization_navigation_gate.py
git commit -m "feat(bringup): own localization navigation gate"
```

---

### Task 3: Add the minimal unified BUNKER Runtime composition launch

**Files:**
- Create: `src/agt_bringup/launch/system.launch.py`
- Modify: `src/agt_bringup/test/test_runtime_bringup_contract.py`

**Interfaces:**
- Consumes existing package launch files listed in the File Structure section.
- Produces one safe entry point: `ros2 launch agt_bringup system.launch.py platform:=bunker`.
- The P0 launch does not create new topic or TF contracts; it only composes existing ones.

- [ ] **Step 1: Extend the contract test with launch ownership and safety defaults**

Append to `src/agt_bringup/test/test_runtime_bringup_contract.py`:

```python
def test_system_launch_composes_only_runtime_packages_and_is_motion_safe_by_default():
    launch_path = PACKAGE / "launch" / "system.launch.py"
    source = launch_path.read_text(encoding="utf-8")

    for package in (
        "agt_description",
        "agt_sensor_adapters",
        "agt_sensor_monitor",
        "agt_mapping",
        "agt_perception",
        "agt_localization",
        "agt_navigation",
        "agt_chassis",
    ):
        assert f'get_package_share_directory("{package}")' in source

    assert 'DeclareLaunchArgument("platform", default_value="bunker")' in source
    assert 'DeclareLaunchArgument("start_localization", default_value="false")' in source
    assert 'DeclareLaunchArgument("start_navigation", default_value="false")' in source
    assert 'DeclareLaunchArgument("start_chassis", default_value="false")' in source
    assert '"publish_driver_odom_tf": "false"' in source
    assert "agt_navigation_v2" not in source


def test_navigation_requires_localization_in_p0_launch_contract():
    source = (PACKAGE / "launch" / "system.launch.py").read_text(encoding="utf-8")
    assert "navigation requires start_localization:=true" in source
    assert "navigation_map must be a file" in source
    assert "global_map_pcd must be a file" in source
    assert "global_map_processing_record must be a file" in source
```

- [ ] **Step 2: Run the contract test and verify failure**

Run:

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: FAIL because `launch/system.launch.py` does not exist.

- [ ] **Step 3: Implement validation helpers in `system.launch.py`**

Create `src/agt_bringup/launch/system.launch.py` with these imports and validation semantics:

```python
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def _enabled(context, name: str) -> bool:
    return LaunchConfiguration(name).perform(context).strip().lower() in {
        "true", "1", "yes", "on"
    }


def _validate(context):
    platform = LaunchConfiguration("platform").perform(context)
    if platform != "bunker":
        raise RuntimeError(f"P0 supports only platform:=bunker, got {platform!r}")

    start_localization = _enabled(context, "start_localization")
    start_navigation = _enabled(context, "start_navigation")
    if start_navigation and not start_localization:
        raise RuntimeError("navigation requires start_localization:=true")

    required_files = []
    if start_localization:
        required_files.extend(
            ["global_map_pcd", "global_map_processing_record"]
        )
    if start_navigation:
        required_files.append("navigation_map")

    for name in required_files:
        path = Path(LaunchConfiguration(name).perform(context)).expanduser()
        if not path.is_file():
            raise RuntimeError(f"{name} must be a file: {path}")
    return []
```

Declare these arguments exactly:

```python
DeclareLaunchArgument("platform", default_value="bunker")
DeclareLaunchArgument("use_sim_time", default_value="false")
DeclareLaunchArgument("start_sensor", default_value="true")
DeclareLaunchArgument("start_sensor_monitor", default_value="true")
DeclareLaunchArgument("start_odometry", default_value="true")
DeclareLaunchArgument("start_perception", default_value="true")
DeclareLaunchArgument("start_localization", default_value="false")
DeclareLaunchArgument("start_navigation", default_value="false")
DeclareLaunchArgument("start_chassis", default_value="false")
DeclareLaunchArgument("chassis_operation_mode", default_value="control")
DeclareLaunchArgument("can_interface", default_value="can0")
DeclareLaunchArgument("navigation_map", default_value="")
DeclareLaunchArgument("global_map_pcd", default_value="")
DeclareLaunchArgument("global_map_processing_record", default_value="")
DeclareLaunchArgument("map_id", default_value="")
DeclareLaunchArgument("map_hash", default_value="")
DeclareLaunchArgument("localization_backend", default_value="ndt")
DeclareLaunchArgument("navigation_autostart", default_value="false")
```

- [ ] **Step 4: Compose the existing Runtime launch files without duplicating safety**

In `generate_launch_description()`, resolve package share directories:

```python
description_share = Path(get_package_share_directory("agt_description"))
sensor_share = Path(get_package_share_directory("agt_sensor_adapters"))
monitor_share = Path(get_package_share_directory("agt_sensor_monitor"))
mapping_share = Path(get_package_share_directory("agt_mapping"))
perception_share = Path(get_package_share_directory("agt_perception"))
localization_share = Path(get_package_share_directory("agt_localization"))
navigation_share = Path(get_package_share_directory("agt_navigation"))
chassis_share = Path(get_package_share_directory("agt_chassis"))
```

Always include the BUNKER description:

```python
IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(description_share / "launch" / "bunker_description.launch.py")
    ),
    launch_arguments={"use_sim_time": LaunchConfiguration("use_sim_time")}.items(),
)
```

Conditionally include sensor, monitor, odometry and perception:

```python
IncludeLaunchDescription(
    PythonLaunchDescriptionSource(str(sensor_share / "launch" / "mid360.launch.py")),
    launch_arguments={"use_sim_time": LaunchConfiguration("use_sim_time")}.items(),
    condition=IfCondition(LaunchConfiguration("start_sensor")),
)

IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(monitor_share / "launch" / "sensor_monitor.launch.py")
    ),
    launch_arguments={"use_sim_time": LaunchConfiguration("use_sim_time")}.items(),
    condition=IfCondition(LaunchConfiguration("start_sensor_monitor")),
)

IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(mapping_share / "launch" / "fast_livo2_mapping.launch.py")
    ),
    launch_arguments={
        "use_sim_time": LaunchConfiguration("use_sim_time"),
        "save_pcd": "false",
    }.items(),
    condition=IfCondition(LaunchConfiguration("start_odometry")),
)

IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(perception_share / "launch" / "local_obstacles.launch.py")
    ),
    launch_arguments={"use_sim_time": LaunchConfiguration("use_sim_time")}.items(),
    condition=IfCondition(LaunchConfiguration("start_perception")),
)
```

Conditionally include localization:

```python
IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(localization_share / "launch" / "relocalization.launch.py")
    ),
    launch_arguments={
        "global_map_pcd": LaunchConfiguration("global_map_pcd"),
        "global_map_processing_record": LaunchConfiguration(
            "global_map_processing_record"
        ),
        "map_id": LaunchConfiguration("map_id"),
        "map_hash": LaunchConfiguration("map_hash"),
        "backend": LaunchConfiguration("localization_backend"),
        "use_sim_time": LaunchConfiguration("use_sim_time"),
    }.items(),
    condition=IfCondition(LaunchConfiguration("start_localization")),
)
```

Conditionally include Nav2 and preserve localization gating:

```python
IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        str(navigation_share / "launch" / "navigation.launch.py")
    ),
    launch_arguments={
        "map": LaunchConfiguration("navigation_map"),
        "map_id": LaunchConfiguration("map_id"),
        "current_localization_pcd_sha256": LaunchConfiguration("map_hash"),
        "use_sim_time": LaunchConfiguration("use_sim_time"),
        "autostart": LaunchConfiguration("navigation_autostart"),
        "enable_localization_gate": "true",
    }.items(),
    condition=IfCondition(LaunchConfiguration("start_navigation")),
)
```

Conditionally include the chassis. Let `agt_chassis/bunker.launch.py` own the safety-controller inclusion so the unified launch cannot create two safety nodes:

```python
IncludeLaunchDescription(
    PythonLaunchDescriptionSource(str(chassis_share / "launch" / "bunker.launch.py")),
    launch_arguments={
        "use_sim_time": LaunchConfiguration("use_sim_time"),
        "operation_mode": LaunchConfiguration("chassis_operation_mode"),
        "can_interface": LaunchConfiguration("can_interface"),
        "start_driver": "true",
        "start_safety": "true",
        "publish_driver_odom_tf": "false",
    }.items(),
    condition=IfCondition(LaunchConfiguration("start_chassis")),
)
```

The default launch must not include a second standalone `agt_safety` launch. Safety is started by the BUNKER chassis launch when control mode is explicitly enabled.

- [ ] **Step 5: Run the P0 contract tests**

Run:

```bash
python3 -m pytest \
  src/agt_bringup/test/test_runtime_bringup_contract.py \
  src/agt_bringup/test/test_localization_navigation_gate.py -q
```

Expected: PASS.

- [ ] **Step 6: Perform launch argument smoke checks after build**

Run:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-up-to agt_bringup agt_navigation
source install/setup.bash
ros2 launch agt_bringup system.launch.py --show-args
```

Expected: output lists all P0 arguments and the command exits without requiring V2.

Then verify a hardware-free composition parse:

```bash
ros2 launch agt_bringup system.launch.py \
  start_sensor:=false \
  start_sensor_monitor:=false \
  start_odometry:=false \
  start_perception:=false \
  start_localization:=false \
  start_navigation:=false \
  start_chassis:=false
```

Expected: robot description starts; no BUNKER driver, Nav2, localization, or motion node is enabled.

- [ ] **Step 7: Commit Task 3**

```bash
git add src/agt_bringup/launch/system.launch.py \
  src/agt_bringup/test/test_runtime_bringup_contract.py
git commit -m "feat(bringup): add safe unified bunker runtime launch"
```

---

### Task 4: Document Runtime ownership and remove stale extraction wording from the operator path

**Files:**
- Modify: `README.md`
- Modify: `src/agt_mapping/README.md`
- Modify: `src/agt_bringup/README.md`
- Modify: `src/agt_bringup/test/test_runtime_bringup_contract.py`

**Interfaces:**
- Produces the operator-facing P0 command and repository boundary used by all later plans.

- [ ] **Step 1: Add documentation assertions before editing docs**

Append to `test_runtime_bringup_contract.py`:

```python
def test_root_readme_declares_runtime_bringup_and_no_v2_overlay_requirement():
    root_readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert "agt_bringup" in root_readme
    assert "ros2 launch agt_bringup system.launch.py" in root_readme
    assert "must build without sourcing `agt_navigation_v2/install/setup.bash`" in root_readme


def test_mapping_readme_uses_runtime_bringup_as_runtime_owner():
    mapping_readme = (ROOT / "src" / "agt_mapping" / "README.md").read_text(
        encoding="utf-8"
    )
    assert "ros2 launch agt_bringup system.launch.py" in mapping_readme
    assert "V2.5 默认" not in mapping_readme
```

- [ ] **Step 2: Run the documentation tests and verify they fail**

Run:

```bash
python3 -m pytest src/agt_bringup/test/test_runtime_bringup_contract.py -q
```

Expected: FAIL on missing Runtime bringup documentation and/or stale `V2.5 默认` wording.

- [ ] **Step 3: Update the root README**

Add `agt_bringup` to the current package tree and add this P0 operator section:

```markdown
## Unified Runtime Bringup

P0 introduces a Runtime-owned system entry point. The safe default starts no Nav2,
localization, or chassis driver:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_bringup system.launch.py platform:=bunker
```

For real navigation, provide the READY map/PCD inputs explicitly and enable each layer:

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_localization:=true \
  start_navigation:=true \
  navigation_map:=/absolute/path/to/site.yaml \
  global_map_pcd:=/absolute/path/to/localization_map.pcd \
  global_map_processing_record:=/absolute/path/to/localization_map.processing.yaml
```

`start_chassis:=true` is a separate explicit action and does not bypass `agt_safety`.
```

Keep the existing statement that Runtime must build without sourcing `agt_navigation_v2/install/setup.bash`.

- [ ] **Step 4: Correct `agt_mapping/README.md` terminology**

Replace Runtime-facing text that says `V2.5 默认` with Runtime ownership language. Keep the technical self-filter, FAST-LIVO2, PCD, ABI and TF details unchanged. The recommended runtime command becomes:

```bash
ros2 launch agt_bringup system.launch.py \
  platform:=bunker \
  start_navigation:=false \
  start_localization:=false \
  start_chassis:=false
```

Do not introduce any V2 workspace path.

- [ ] **Step 5: Expand `agt_bringup/README.md` with P0 mode table**

Document at minimum:

```text
start_sensor=true          MID360 driver
start_sensor_monitor=true  stream health
start_odometry=true        FAST-LIVO2 runtime odometry, PCD saving forced off
start_perception=true      local obstacle baseline
start_localization=false   NDT/ICP + GlobalCorrectionManager, requires PCD assets
start_navigation=false     Nav2, requires localization and navigation map
start_chassis=false        BUNKER CAN driver + safety/guard, explicit opt-in
```

Also state that `publish_driver_odom_tf=false` is fixed by the outer Runtime composition.

- [ ] **Step 6: Run documentation and gate tests**

Run:

```bash
python3 -m pytest src/agt_bringup/test -q
```

Expected: PASS.

- [ ] **Step 7: Commit Task 4**

```bash
git add README.md src/agt_mapping/README.md src/agt_bringup/README.md \
  src/agt_bringup/test/test_runtime_bringup_contract.py
git commit -m "docs(runtime): document unified bunker bringup boundary"
```

---

### Task 5: Prove P0 independent build and regression safety

**Files:**
- No new production file required unless a failing build exposes a P0-owned defect.
- Test/verification scope: whole Runtime workspace plus focused launch/package tests.

**Interfaces:**
- Produces the P0 acceptance evidence required before starting the calibration/RTAB-Map plan.

- [ ] **Step 1: Verify no Runtime source references V2 install/source paths**

Run from repository root:

```bash
grep -RInE 'agt_navigation_v2/(install|src)|/home/yangxuan/.*/agt_navigation_v2' \
  --exclude-dir=.git --exclude-dir=build --exclude-dir=install --exclude-dir=log .
```

Expected: no runtime dependency match. Documentation may mention the repository boundary, but must not prescribe sourcing or resolving files from V2.

- [ ] **Step 2: Run focused P0 tests**

```bash
source /opt/ros/humble/setup.bash
python3 -m pytest src/agt_bringup/test -q
```

Expected: PASS.

- [ ] **Step 3: Build Runtime without a V2 overlay**

Start from a shell that has sourced only ROS Humble. Do not source any V2 workspace:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
```

Expected: all Runtime packages, including `agt_bringup`, finish successfully. If the repository's existing third-party bootstrap requires a documented source step, use only Runtime-local dependencies under `third_party/`; never source V2.

- [ ] **Step 4: Run package tests**

```bash
source install/setup.bash
colcon test --packages-select agt_bringup agt_navigation agt_mapping agt_localization agt_safety agt_chassis
colcon test-result --verbose
```

Expected: zero failed tests.

- [ ] **Step 5: Verify safe launch defaults**

```bash
ros2 launch agt_bringup system.launch.py \
  start_sensor:=false \
  start_sensor_monitor:=false \
  start_odometry:=false \
  start_perception:=false \
  start_localization:=false \
  start_navigation:=false \
  start_chassis:=false
```

In another shell:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 node list
```

Expected: description-side nodes may exist; the list must not contain `agt_bunker_base`, `controller_server`, `bt_navigator`, `agt_relocalization`, or `agt_global_correction_manager`.

- [ ] **Step 6: Verify illegal navigation composition fails before motion**

```bash
ros2 launch agt_bringup system.launch.py \
  start_navigation:=true \
  start_localization:=false
```

Expected: launch exits with `navigation requires start_localization:=true` before Nav2 starts.

- [ ] **Step 7: Final P0 commit if verification required no fixes**

If Tasks 1-4 already contain all changes, do not create an empty commit. Record the successful commands and exact commit SHAs in the next implementation report. If verification reveals a P0-owned defect, add a failing regression test first, fix only that defect, rerun Steps 2-6, and commit with a narrowly scoped `fix(bringup): ...` message.

---

## P0 Exit Gate

P0 is complete only when all of the following are true:

```text
[ ] agt_bringup exists inside agt_navigation_runtime
[ ] localization_navigation_gate.py is Runtime-owned and tested
[ ] navigation.launch.py no longer resolves a package that exists only in V2
[ ] system.launch.py composes BUNKER description/sensor/odom/perception and optional localization/Nav2/chassis
[ ] default system launch cannot command BUNKER motion
[ ] navigation cannot start without localization
[ ] BUNKER driver odom TF is disabled
[ ] Runtime source/install paths do not depend on agt_navigation_v2
[ ] focused tests pass
[ ] full Runtime colcon build succeeds from ROS Humble without V2 overlay
```

Only after this gate passes should the next plan start P1/P2: BUNKER + MID360 + IMU + wheel odom + GNSS bringup and calibration rosbag acquisition.