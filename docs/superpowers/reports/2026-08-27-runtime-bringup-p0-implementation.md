# Runtime Bringup P0 Implementation Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-runtime-bringup-p0.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

**CODE_LANDED / LOCAL_VERIFICATION_ROUND_3_REQUIRED**

P0 production code, contract tests, and operator documentation are on the feature branch. Verification round two completed a full 24-package Runtime build and the focused `agt_bringup` pytest suite passed 13/13. The remaining package-test failure was traced to an `agt_localization` CTest that incorrectly required a machine-local file under the gitignored `runtime/` directory. That package-test defect has now been corrected in the branch.

P0 is not DONE until the round-three package tests and launch safety gates below have fresh passing evidence.

## Implemented boundary

- Added Runtime-owned `src/agt_bringup`.
- Added fail-closed `localization_navigation_gate.py` under Runtime ownership.
- Added `agt_bringup/system.launch.py` as the authoritative real-robot composition entry.
- Kept the safe defaults `start_localization=false`, `start_navigation=false`, `start_chassis=false`.
- Forced Nav2 `autostart=false` in the Runtime system entry so accepted localization owns lifecycle startup.
- Fixed BUNKER `publish_driver_odom_tf=false` in the outer composition.
- Kept FAST-LIVO2 runtime PCD saving disabled through `save_pcd=false`.
- Removed the reverse `agt_navigation -> agt_bringup` launch dependency; `agt_bringup` now owns the gate node while `agt_navigation` remains the Nav2 package.
- Removed the remaining V2 workspace source hint from the real-bag validation script.
- Added source-tree contract coverage preventing V2 install/source hints from re-entering Runtime source.
- Added dependency-bootstrap guidance to the root README.
- Removed package-test dependence on ignored `runtime/localization_validation/...` assets; real-data asset validation remains in the real-bag validation path.

## Verification round 1 findings

### P0 contract tests

Observed result: `3 failed, 10 passed`.

Root causes:

1. The source-tree guard test embedded the exact forbidden V2 path literals in its own Python source and therefore detected itself.
2. The same self-match occurred in the whole-`src/` guard.
3. The launch contract test searched for expanded messages such as `navigation_map must be a file`, while `system.launch.py` deliberately generates that message from `f"{name} must be a file: {path}"`.

Correction:

- Forbidden path strings are now assembled at runtime so the scanner can validate the source tree without containing its own forbidden literal.
- The launch contract now checks the actual required-file registration and generic fail-closed error path rather than a compile-time string that does not exist in the implementation.

### Initial Runtime build blocker

The first failing build package was `agt_bt_executor` because the ROS 2 Humble BehaviorTree.CPP package was missing or not resolvable. The package manifest already declares `<depend>behaviortree_cpp</depend>`.

The Runtime machine later installed `ros-humble-behaviortree-cpp`. Its shared library is installed at:

```text
/opt/ros/humble/lib/x86_64-linux-gnu/libbehaviortree_cpp.so
```

A local compatibility link was used so the exported Humble CMake metadata could resolve the library. Verification round two then completed the full workspace build.

## Verification round 2 findings

### Full Runtime build

Observed result:

```text
Summary: 24 packages finished
```

Only developer/warning stderr remained from existing third-party packages; there was no package build failure in this round.

### Focused P0 tests

Observed result:

```text
13 passed
```

The Runtime `agt_bringup` package was installed and `ros2 pkg executables agt_bringup` exposed `localization_navigation_gate.py`. `ros2 launch agt_bringup system.launch.py --show-args` also parsed successfully and showed the intended motion-safe defaults.

### Remaining package-test failure

`agt_localization` reported one failed CTest:

```text
test_processing_record_is_ready_and_hash_bound
```

The failing test tried to read:

```text
runtime/localization_validation/handheld_20260719/processing_record.yaml
```

but repository `.gitignore` intentionally excludes all of `runtime/`. Therefore a clean clone cannot guarantee this file exists, and a normal package CTest must not require it.

Correction:

- Replaced the machine-local asset assertion with a contract assertion that the real-bag validation preflight enforces `state == ready`, matching `map_id`, exact PCD SHA-256 binding, and candidate map identity.
- Added a guard asserting this package contract does not re-introduce a dependency on `runtime/localization_validation`.
- Real handheld PCD/processing-record validation remains a real-data acceptance responsibility, not a source package unit-test prerequisite.

## Review rulings

### Gate ownership

An initial implementation left `navigation.launch.py` starting a node from `agt_bringup`, while `agt_bringup` depends on `agt_navigation`. This created a hidden runtime package dependency cycle. The final design starts the localization gate only from `agt_bringup/system.launch.py`.

### Nav2 lifecycle authority

The Runtime system entry does not expose an autostart override. It passes `autostart=false` to `agt_navigation/navigation.launch.py`; the localization gate issues STARTUP/PAUSE/RESUME/RESET. The standalone offline navigation launch remains allowed to use Nav2 autostart for its simulator-only path.

### Script executable permissions

GitHub content writes may store Python sources as mode `0644`. `agt_bringup/CMakeLists.txt` therefore follows the existing Runtime `agt_navigation` pattern: it copies the gate into the build tree with explicit executable permissions before installing it, including under `colcon --symlink-install`.

### Runtime versus asset production

`agt_bringup/system.launch.py` forces FAST-LIVO2 `save_pcd=false`. Direct FAST-LIVO2 PCD saving is a commissioning/debug path only. Versioned READY map/semantic/task asset production remains outside Runtime.

### Source tests versus real-data acceptance

Package CTests must be reproducible from a clean repository plus declared dependencies. Files below gitignored `runtime/` are execution/validation artifacts and may be required by explicit real-data validation commands, but they cannot be unconditional package-test inputs.

## Local verification round 3

The full build already passed in round two. Pull the test correction and rerun only the affected package tests first:

```bash
cd ~/agt_navigation_runtime
git checkout feat/bunker-rtabmap-slope-nav
git pull

source /opt/ros/humble/setup.bash
source install/setup.bash

colcon test --packages-select \
  agt_bringup agt_navigation agt_mapping \
  agt_localization agt_safety agt_chassis
colcon test-result --verbose
```

If the previous `install/` was removed or the branch update changes build inputs in a way that invalidates the workspace, rebuild first:

```bash
rm -rf build install log
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

Then perform the hardware-free safe-default launch:

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

While it is running, these nodes must not appear:

```text
agt_bunker_base
controller_server
bt_navigator
agt_relocalization
agt_global_correction_manager
```

Finally verify fail-closed composition:

```bash
ros2 launch agt_bringup system.launch.py \
  start_sensor:=false \
  start_sensor_monitor:=false \
  start_odometry:=false \
  start_perception:=false \
  start_navigation:=true \
  start_localization:=false \
  start_chassis:=false
```

Expected launch error:

```text
navigation requires start_localization:=true
```

## P0 exit condition

Do not mark P0 DONE until the corrected package tests, safe-default launch, and illegal-navigation rejection above all have fresh passing evidence.