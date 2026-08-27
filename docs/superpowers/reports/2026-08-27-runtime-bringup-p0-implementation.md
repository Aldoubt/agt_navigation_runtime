# Runtime Bringup P0 Implementation Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-runtime-bringup-p0.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

**CODE_LANDED / LOCAL_VERIFICATION_ROUND_2_REQUIRED**

P0 production code, contract tests, and operator documentation are on the feature branch. A first real ROS 2 Humble verification run was executed on the Runtime machine and exposed two independent blockers: three P0 contract-test defects and a missing external BehaviorTree.CPP dependency. The P0 test defects have been corrected in the branch; the build dependency must be installed/resolved locally before the clean build can be repeated.

P0 is not DONE until the round-two commands below complete successfully.

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

### Full Runtime build

The first failing build package was `agt_bt_executor`:

```text
find_package(behaviortree_cpp REQUIRED)
```

could not resolve `behaviortree_cppConfig.cmake`. The package manifest already declares `<depend>behaviortree_cpp</depend>`, so this is an environment/bootstrap dependency rather than a P0 bringup-code dependency. On ROS 2 Humble the matching binary dependency is `ros-humble-behaviortree-cpp` (BehaviorTree.CPP v4 package).

Because `agt_bt_executor` failed first, downstream packages were aborted and `agt_bringup` was never installed. The later `Package 'agt_bringup' not found` and `Has this package been built before?` errors are therefore secondary evidence, not separate root causes.

## Review rulings

### Gate ownership

An initial implementation left `navigation.launch.py` starting a node from `agt_bringup`, while `agt_bringup` depends on `agt_navigation`. This created a hidden runtime package dependency cycle. The final design starts the localization gate only from `agt_bringup/system.launch.py`.

### Nav2 lifecycle authority

The Runtime system entry does not expose an autostart override. It passes `autostart=false` to `agt_navigation/navigation.launch.py`; the localization gate issues STARTUP/PAUSE/RESUME/RESET. The standalone offline navigation launch remains allowed to use Nav2 autostart for its simulator-only path.

### Script executable permissions

GitHub content writes may store Python sources as mode `0644`. `agt_bringup/CMakeLists.txt` therefore follows the existing Runtime `agt_navigation` pattern: it copies the gate into the build tree with explicit executable permissions before installing it, including under `colcon --symlink-install`.

### Runtime versus asset production

`agt_bringup/system.launch.py` forces FAST-LIVO2 `save_pcd=false`. Direct FAST-LIVO2 PCD saving is a commissioning/debug path only. Versioned READY map/semantic/task asset production remains outside Runtime.

## Local verification round 2

Run from a clean shell in `agt_navigation_runtime` on ROS 2 Humble. Do **not** source V2 first.

```bash
cd ~/agt_navigation_runtime
git checkout feat/bunker-rtabmap-slope-nav
git pull

source /opt/ros/humble/setup.bash
rosdep update
rosdep install --from-paths src third_party --ignore-src -r -y

# If rosdep still reports behaviortree_cpp unresolved:
sudo apt update
sudo apt install ros-humble-behaviortree-cpp

rm -rf build install log
colcon build --symlink-install
source install/setup.bash

python3 -m pytest src/agt_bringup/test -q

colcon test --packages-select \
  agt_bringup agt_navigation agt_mapping \
  agt_localization agt_safety agt_chassis
colcon test-result --verbose

ros2 pkg executables agt_bringup | grep localization_navigation_gate.py
ros2 launch agt_bringup system.launch.py --show-args
```

Then perform the hardware-free safe-default parse:

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

The following nodes must not be present in that mode:

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
  start_navigation:=true \
  start_localization:=false
```

Expected launch error:

```text
navigation requires start_localization:=true
```

## P0 exit condition

Do not mark P0 DONE until the clean Runtime build, focused tests, package tests, safe-default launch, and illegal-navigation rejection above all have fresh passing evidence.
