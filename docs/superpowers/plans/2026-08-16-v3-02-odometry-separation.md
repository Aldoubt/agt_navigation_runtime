# V3-02 Odometry / Localization Separation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the V2.5-derived `agt_mapping` runtime package with `agt_odometry`, migrate all runtime consumers to `/agt/odometry/*`, and remove all V3 PCD-map production controls without changing FAST-LIVO2 adapter math.

**Architecture:** Build a new runtime-only `agt_odometry` package beside the legacy package first, prove adapter parity, then migrate consumers and delete `agt_mapping`. `agt_odometry` remains the sole owner of `odom -> base_footprint`; localization retains `map -> odom` authority.

**Tech Stack:** ROS 2 Humble, ament_cmake, rclpy, nav_msgs, sensor_msgs, tf2_ros, Python/pytest, FAST-LIVO2 vendor backend.

## Global Constraints

- Final public odometry topic: `/agt/odometry/odometry`.
- Final public registered-cloud topic: `/agt/odometry/registered_points`.
- Final backend-private registered-cloud topic: `/agt/odometry/backend/registered_points`.
- `agt_odometry` must not expose `save_pcd`, `pcd_save_interval`, or `pcd_output_dir`.
- FAST-LIVO2 PCD saving is forced off in runtime launch.
- Adapter pose/twist equations remain unchanged.
- `agt_odometry` owns `odom -> base_footprint`; localization owns `map -> odom`.
- Final source tree contains `agt_odometry` and does not contain `agt_mapping`.
- Final independent ROS 2 Humble build must still finish 23 packages.

---

### Task 1: Add migration contract tests

**Files:**
- Create: `tests/odometry/test_v3_02_odometry_contract.py`

**Interfaces:**
- Consumes: repository source tree.
- Produces: executable source-level acceptance gates for package name, topic namespace, launch PCD rules, consumer migration, and final package replacement.

- [ ] **Step 1: Write failing tests**

Create tests that assert:

```python
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def text(path):
    return (ROOT / path).read_text(encoding="utf-8")


def test_odometry_package_exists():
    assert (ROOT / "src/agt_odometry/package.xml").is_file()


def test_odometry_package_declares_runtime_name():
    assert "<name>agt_odometry</name>" in text("src/agt_odometry/package.xml")


def test_runtime_launch_has_no_pcd_save_arguments():
    launch = text("src/agt_odometry/launch/fast_livo2_odometry.launch.py")
    assert 'DeclareLaunchArgument("save_pcd"' not in launch
    assert 'DeclareLaunchArgument("pcd_save_interval"' not in launch
    assert 'DeclareLaunchArgument("pcd_output_dir"' not in launch
    assert '"pcd_save.pcd_save_en": False' in launch


def test_canonical_topics_are_odometry_scoped():
    config = text("src/agt_odometry/config/fast_livo2_adapter.yaml")
    assert "/agt/odometry/odometry" in config
    assert "/agt/odometry/backend/registered_points" in config
    assert "/agt/odometry/registered_points" in config
    assert "/agt/mapping/" not in config


def test_runtime_consumers_do_not_use_mapping_topic_namespace():
    checked = [
        "src/agt_localization",
        "src/agt_perception",
        "src/agt_navigation",
        "src/agt_experiment_manager",
    ]
    violations = []
    for relative in checked:
        for path in (ROOT / relative).rglob("*"):
            if path.is_file() and path.suffix in {".py", ".cpp", ".hpp", ".yaml", ".yml", ".md", ".rviz"}:
                if "/agt/mapping/" in path.read_text(encoding="utf-8", errors="ignore"):
                    violations.append(str(path.relative_to(ROOT)))
    assert violations == []


def test_legacy_mapping_package_is_removed():
    assert not (ROOT / "src/agt_mapping").exists()
```

- [ ] **Step 2: Run the new suite and record RED**

Run:

```bash
python3 -m pytest -q tests/odometry/test_v3_02_odometry_contract.py
```

Expected: failures because `src/agt_odometry` does not exist and existing consumers still reference `/agt/mapping/*`.

- [ ] **Step 3: Commit RED tests**

```bash
git add tests/odometry/test_v3_02_odometry_contract.py
git commit -m "test(v3-02): define odometry separation contract"
```

---

### Task 2: Create `agt_odometry` with adapter behavior parity

**Files:**
- Create: `src/agt_odometry/package.xml`
- Create: `src/agt_odometry/CMakeLists.txt`
- Create: `src/agt_odometry/scripts/fast_livo2_adapter.py`
- Create: `src/agt_odometry/test/test_fast_livo2_adapter.py`
- Create: `src/agt_odometry/config/fast_livo2_adapter.yaml`
- Create: `src/agt_odometry/config/fast_livo2_adapter_handheld.yaml`
- Copy runtime backend YAMLs required by launch from `src/agt_mapping/config/`.

**Interfaces:**
- Consumes: FAST-LIVO2 `/aft_mapped_to_init` and backend registered cloud.
- Produces: `/agt/odometry/odometry`, `/agt/odometry/registered_points`, and optional `odom -> base_footprint` TF.

- [ ] **Step 1: Copy adapter math tests first**

Copy the five existing adapter tests unchanged except the module path points to `src/agt_odometry/scripts/fast_livo2_adapter.py`.

- [ ] **Step 2: Run adapter tests and record RED**

Run:

```bash
python3 -m pytest -q src/agt_odometry/test/test_fast_livo2_adapter.py
```

Expected: fail because the new adapter file does not yet exist.

- [ ] **Step 3: Copy adapter implementation without changing equations**

Copy the existing adapter functions and node logic, changing only:

```python
super().__init__("agt_odometry_fast_livo2_adapter")
```

and defaults:

```python
"output_odometry": "/agt/odometry/odometry",
"input_registered_points": "/agt/odometry/backend/registered_points",
"output_registered_points": "/agt/odometry/registered_points",
```

- [ ] **Step 4: Create package metadata and install rules**

`package.xml` uses:

```xml
<name>agt_odometry</name>
<description>Runtime continuous odometry backend adapters and canonical state-estimation outputs.</description>
```

Keep only dependencies required by the adapter and runtime launch.

`CMakeLists.txt` installs adapter, launch/config directories, and registers the migrated pytest adapter test.

- [ ] **Step 5: Run adapter tests GREEN**

```bash
python3 -m pytest -q src/agt_odometry/test/test_fast_livo2_adapter.py
```

Expected: 5 passed.

- [ ] **Step 6: Commit package skeleton and adapter**

```bash
git add src/agt_odometry
git commit -m "feat(v3-02): add runtime odometry adapter package"
```

---

### Task 3: Add runtime-only FAST-LIVO2 launch

**Files:**
- Create: `src/agt_odometry/launch/fast_livo2_odometry.launch.py`
- Modify: `src/agt_odometry/config/fast_livo2_adapter.yaml`
- Modify: `src/agt_odometry/README.md`

**Interfaces:**
- Consumes: `/agt/sensors/lidar/custom_filtered`, FAST-LIVO2 configs, optional self-filter.
- Produces: canonical odometry/cloud topics through the adapter.

- [ ] **Step 1: Run migration contract and observe launch-related RED**

```bash
python3 -m pytest -q tests/odometry/test_v3_02_odometry_contract.py
```

- [ ] **Step 2: Implement launch without map-production arguments**

Base it on the existing FAST-LIVO2 launch but remove:

```text
validate_pcd_output
save_pcd
pcd_save_interval
pcd_output_dir
```

Set runtime backend parameters explicitly:

```python
"pcd_save.pcd_save_en": False,
"pcd_save.interval": -1,
```

Do not pass an output directory parameter.

Remap:

```python
("/cloud_registered", "/agt/odometry/backend/registered_points")
```

Launch adapter as:

```python
Node(
    package="agt_odometry",
    executable="fast_livo2_adapter.py",
    name="agt_odometry_fast_livo2_adapter",
    ...
)
```

- [ ] **Step 3: Document final ownership and non-goals**

README explicitly says this package does not create maps or Site Package assets and owns only continuous local odometry.

- [ ] **Step 4: Run package tests**

```bash
python3 -m pytest -q src/agt_odometry/test/test_fast_livo2_adapter.py tests/odometry/test_v3_02_odometry_contract.py
```

Expected: adapter tests pass; consumer/removal assertions may still fail until later tasks.

- [ ] **Step 5: Commit runtime launch**

```bash
git add src/agt_odometry
git commit -m "feat(v3-02): add runtime-only FAST-LIVO2 odometry launch"
```

---

### Task 4: Migrate localization and perception consumers

**Files:**
- Modify: `src/agt_localization/config/relocalization.yaml`
- Modify: `src/agt_localization/config/relocalization_handheld_validation.yaml`
- Modify: `src/agt_localization/src/relocalization_node.cpp` only if a default topic is hard-coded there.
- Modify: `src/agt_localization/launch/v25_10_realbag_validation.launch.py`
- Modify: `src/agt_localization/scripts/v25_10_realbag_validation.py`
- Modify: `src/agt_localization/test/test_v25_10_validation_contract.py`
- Modify: `src/agt_localization/rviz/v25_10_realbag_validation.rviz`
- Modify: `src/agt_localization/README.md`
- Modify: `src/agt_perception/config/local_obstacle_filter.yaml`
- Modify: `src/agt_perception/src/local_obstacle_filter.cpp` only if a default topic is hard-coded there.
- Modify: `src/agt_perception/README.md`

**Interfaces:**
- Consumes: `/agt/odometry/registered_points`.
- Produces: unchanged localization/perception outputs.

- [ ] **Step 1: Replace runtime cloud-input topic references**

Change every executable/config runtime reference:

```text
/agt/mapping/registered_points
```

to:

```text
/agt/odometry/registered_points
```

Change launch package references from `agt_mapping` to `agt_odometry` and launch filename to `fast_livo2_odometry.launch.py`.

- [ ] **Step 2: Run localization/perception tests plus migration contract**

```bash
python3 -m pytest -q src/agt_localization/test tests/odometry/test_v3_02_odometry_contract.py
```

Expected: no localization/perception mapping-topic violations; final legacy-package assertion may remain RED.

- [ ] **Step 3: Commit consumer migration**

```bash
git add src/agt_localization src/agt_perception
git commit -m "refactor(v3-02): migrate localization and perception to odometry topics"
```

---

### Task 5: Migrate experiment and navigation utility references

**Files:**
- Modify: `src/agt_experiment_manager/config/bag_profiles.yaml`
- Modify: `src/agt_experiment_manager/agt_experiment_manager/manager.py`
- Modify: `src/agt_experiment_manager/test/test_experiment_manager.py`
- Modify: runtime smoke/scripts under `src/agt_navigation/scripts/` that use `/agt/mapping/odometry`.
- Modify: any corresponding navigation tests/docs.

**Interfaces:**
- Consumes/records: `/agt/odometry/odometry` and `/agt/odometry/registered_points`.
- Produces: unchanged experiment session/navigation smoke semantics.

- [ ] **Step 1: Replace runtime odometry/cloud references**

Use:

```text
/agt/odometry/odometry
/agt/odometry/registered_points
```

- [ ] **Step 2: Run affected tests and migration contract**

```bash
python3 -m pytest -q src/agt_experiment_manager/test tests/odometry/test_v3_02_odometry_contract.py
```

- [ ] **Step 3: Commit utility migration**

```bash
git add src/agt_experiment_manager src/agt_navigation
git commit -m "refactor(v3-02): migrate runtime recording and smoke topics"
```

---

### Task 6: Remove `agt_mapping` and clean repository references

**Files:**
- Delete: `src/agt_mapping/`
- Modify: root `README.md`
- Modify: V3 architecture docs that identify `agt_mapping` as transitional.

**Interfaces:**
- Produces: final one-owner source tree with `agt_odometry` only.

- [ ] **Step 1: Search before deletion**

Run:

```bash
grep -RIn --exclude-dir=.git \
  -e '/agt/mapping/' \
  -e 'package="agt_mapping"' \
  -e '<depend>agt_mapping</depend>' \
  -e '<exec_depend>agt_mapping</exec_depend>' \
  src README.md docs || true
```

Classify remaining hits. Runtime executable/config dependencies must be zero before deletion.

- [ ] **Step 2: Delete legacy package**

```bash
rm -rf src/agt_mapping
```

- [ ] **Step 3: Update root docs**

Replace transitional package references with `agt_odometry`. Keep historical V2.5 provenance only where explicitly historical.

- [ ] **Step 4: Run migration and V3-01 contract suites**

```bash
python3 -m pytest -q tests/odometry tests/contracts
```

Expected: all pass.

- [ ] **Step 5: Commit legacy removal**

```bash
git add -A src/agt_mapping src/agt_odometry README.md docs tests
git commit -m "refactor(v3-02): retire runtime mapping package"
```

---

### Task 7: Final source/build verification

**Files:**
- Modify only if verification exposes a concrete defect.

**Interfaces:**
- Produces: V3-02 acceptance evidence.

- [ ] **Step 1: Run pure-Python suites**

```bash
python3 -m pytest -q tests/contracts tests/odometry src/agt_odometry/test
```

Expected: all pass.

- [ ] **Step 2: Repository-wide runtime namespace scan**

```bash
grep -RIn --exclude-dir=.git '/agt/mapping/' src || true
```

Expected: no executable/config runtime references. Historical documentation must be reviewed individually rather than blindly accepted.

- [ ] **Step 3: Verify package replacement**

```bash
test -d src/agt_odometry
test ! -e src/agt_mapping
```

- [ ] **Step 4: Independent ROS build on the robot-development workstation**

```bash
env | grep -E 'AMENT_PREFIX_PATH|CMAKE_PREFIX_PATH|COLCON_PREFIX_PATH'
source /opt/ros/humble/setup.bash
rm -rf build install log
colcon build --symlink-install
```

Expected environment prefix contains ROS Humble only and build summary reports:

```text
23 packages finished
```

- [ ] **Step 5: Optional runtime/bag smoke when input is available**

```bash
ros2 topic hz /agt/odometry/odometry
ros2 topic hz /agt/odometry/registered_points
ros2 topic echo /agt/odometry/odometry --once
```

Verify `header.frame_id == odom`, `child_frame_id == base_footprint`, registered cloud frame is `odom`, and only one node publishes `odom -> base_footprint`.

- [ ] **Step 6: Final code review**

Review diff against the V3-02 spec. Fix Critical/Important findings before integration.
