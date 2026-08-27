# Runtime Bringup P0 Implementation Report

Date: 2026-08-27
Branch: `feat/bunker-rtabmap-slope-nav`
Plan: `docs/superpowers/plans/2026-08-27-runtime-bringup-p0.md`
Spec: `docs/superpowers/specs/2026-08-27-bunker-rtabmap-slope-nav-design.md`

## Status

**P0 USER-ACCEPTED / LOCAL GATES REPORTED PASSING**

P0 production code, contract tests, and operator documentation are on the feature branch. The Runtime machine completed a full 24-package build during verification round two, the focused `agt_bringup` pytest suite passed 13/13, and the user reports that the corrected package tests plus the safe-default launch gate also passed in verification round three. The final fail-closed gate output was provided directly and rejected `start_navigation:=true` with `start_localization:=false` using the expected error `navigation requires start_localization:=true`.

Evidence boundary: these ROS 2/colcon commands were executed on the user's Runtime machine, not inside the assistant execution environment. This report records local acceptance evidence without claiming independent assistant-side execution.

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

- Forbidden path strings are assembled at runtime so the scanner can validate the source tree without containing its own forbidden literal.
- The launch contract checks the actual required-file registration and generic fail-closed error path rather than a compile-time string that does not exist in the implementation.

## Verification round 2 findings

### Initial Runtime build blocker

The first failing build package was `agt_bt_executor` because the ROS 2 Humble BehaviorTree.CPP package was missing or not resolvable. The package manifest already declares `<depend>behaviortree_cpp</depend>`.

The Runtime machine later installed `ros-humble-behaviortree-cpp`. Its shared library is installed at:

```text
/opt/ros/humble/lib/x86_64-linux-gnu/libbehaviortree_cpp.so
```

A local compatibility link was used so the exported Humble CMake metadata could resolve the library. Verification round two then completed the full workspace build.

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

The Runtime `agt_bringup` package was installed and `ros2 pkg executables agt_bringup` exposed `localization_navigation_gate.py`. `ros2 launch agt_bringup system.launch.py --show-args` parsed successfully and showed the intended motion-safe defaults.

### Remaining package-test failure

`agt_localization` initially reported one failed CTest because `test_processing_record_is_ready_and_hash_bound` tried to read a machine-local file under gitignored `runtime/localization_validation/...`.

Correction:

- Replaced the machine-local asset assertion with a contract assertion that the real-bag validation preflight enforces `state == ready`, matching `map_id`, exact PCD SHA-256 binding, and candidate map identity.
- Added a guard asserting this package contract does not re-introduce a dependency on `runtime/localization_validation`.
- Real handheld PCD/processing-record validation remains a real-data acceptance responsibility, not a source package unit-test prerequisite.

## Verification round 3 findings

The user reports that the corrected package tests and hardware-free safe-default launch completed successfully. The final illegal composition was provided directly:

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

Observed fail-closed result:

```text
[ERROR] [launch]: Caught exception in launch (see debug for traceback): navigation requires start_localization:=true
```

This is the expected P0 lifecycle-authority rejection.

## Review rulings

### Gate ownership

`agt_bringup/system.launch.py` is the owner of the localization-to-Nav2 lifecycle gate. `agt_navigation` does not depend back on `agt_bringup`.

### Nav2 lifecycle authority

The Runtime system entry passes `autostart=false` to `agt_navigation/navigation.launch.py`; the localization gate issues STARTUP/PAUSE/RESUME/RESET. The standalone offline navigation launch remains allowed to use Nav2 autostart for its simulator-only path.

### Runtime versus asset production

`agt_bringup/system.launch.py` forces FAST-LIVO2 `save_pcd=false`. Direct FAST-LIVO2 PCD saving is a commissioning/debug path only. Versioned READY map/semantic/task asset production remains outside Runtime.

### Source tests versus real-data acceptance

Package CTests must be reproducible from a clean repository plus declared dependencies. Files below gitignored `runtime/` are execution/validation artifacts and may be required by explicit real-data validation commands, but they cannot be unconditional package-test inputs.

## P0 exit decision

P0 is accepted from the user's Runtime-machine verification evidence. Subsequent work may proceed to the P1/P2 hardware-interface and calibration-capture scope while preserving all P0 safety and ownership constraints.
