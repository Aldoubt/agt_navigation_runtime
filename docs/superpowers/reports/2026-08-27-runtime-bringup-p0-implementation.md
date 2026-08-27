# Runtime Bringup P0 Implementation Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-runtime-bringup-p0.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

**CODE_LANDED / ROS_BUILD_PENDING**

P0 production code, contract tests, and operator documentation have been written to the feature branch. This environment cannot execute the ROS 2 Humble/colcon acceptance commands because `/opt/ros` and `colcon` are unavailable, and its local container cannot clone GitHub due DNS/network restrictions. Therefore this report does not claim that the Runtime workspace builds or that ROS launch tests pass.

The P0 exit gate remains open until the commands in `Local verification required` complete successfully on the Runtime machine.

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
- Added source-tree contract coverage preventing `agt_navigation_v2/install` and `agt_navigation_v2/src` hints from re-entering Runtime source.

## Review rulings

### Gate ownership

An initial implementation left `navigation.launch.py` starting a node from `agt_bringup`, while `agt_bringup` depends on `agt_navigation`. This created a hidden runtime package dependency cycle. The final design starts the localization gate only from `agt_bringup/system.launch.py`.

### Nav2 lifecycle authority

The Runtime system entry does not expose an autostart override. It passes `autostart=false` to `agt_navigation/navigation.launch.py`; the localization gate issues STARTUP/PAUSE/RESUME/RESET. The standalone offline navigation launch remains allowed to use Nav2 autostart for its simulator-only path.

### Script executable permissions

GitHub content writes may store Python sources as mode `0644`. `agt_bringup/CMakeLists.txt` therefore follows the existing Runtime `agt_navigation` pattern: it copies the gate into the build tree with explicit executable permissions before installing it, including under `colcon --symlink-install`.

### Runtime versus asset production

`agt_bringup/system.launch.py` forces FAST-LIVO2 `save_pcd=false`. Direct FAST-LIVO2 PCD saving is a commissioning/debug path only. Versioned READY map/semantic/task asset production remains outside Runtime.

## Static evidence available in this environment

The feature branch diff from the P0 plan baseline contains the new `agt_bringup` package plus the narrowly scoped Runtime integration changes. GitHub branch inspection also confirms the real-bag validation hint now points to `source install/setup.bash`, not a V2 install space.

These checks are not substitutes for ROS build/test evidence.

## Local verification required

Run from a clean shell in `agt_navigation_runtime` on ROS 2 Humble. Do **not** source V2 first.

```bash
source /opt/ros/humble/setup.bash

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
