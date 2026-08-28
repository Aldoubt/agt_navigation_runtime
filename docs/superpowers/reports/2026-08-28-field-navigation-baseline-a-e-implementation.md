# Field Navigation Baseline A-E Implementation Report

Date: 2026-08-28
Branch: `feat/field-navigation-baseline`
Implementation head accepted: `7d4421345b54c8bed9446174e3b1fd5462b59c5f`
Plan: `docs/superpowers/plans/2026-08-28-field-navigation-baseline-a-e.md`
Spec: `docs/superpowers/specs/2026-08-28-field-navigation-baseline-design.md`
Runbook: `docs/runbooks/field_navigation_baseline.md`

## Status

**FIELD NAVIGATION BASELINE A-E — SOFTWARE BASELINE ACCEPTED / USER-MACHINE VERIFICATION REPORTED PASSING**

The A-E commissioning baseline implementation, contract tests, map-freeze helper, explicit rosbag profiles, commissioning RViz layout, and operator runbook are present on `feat/field-navigation-baseline`. The user reports that the final integrated pytest selection passed with zero failures, the selected `agt_bringup`, `agt_navigation`, and `agt_experiment_manager` packages built successfully, and the final selected package tests completed with zero errors / zero failures.

Evidence boundary: the ROS 2, pytest, colcon build, and colcon test commands were executed on the user's Runtime machine. The assistant did not independently execute ROS 2 or colcon in its environment. This report records user-machine software acceptance evidence and does not claim real-vehicle acceptance.

## Accepted implementation boundary

- Added safe mapping-save passthrough to `agt_bringup/system.launch.py` while keeping normal production PCD saving disabled by default.
- Added `field_mapping.launch.py` for Phase A FAST-LIVO2 LIO-only commissioning capture with localization/navigation forced off, PCD saving on, optional GNSS, and BUNKER monitor mode.
- Kept the Phase A mapping output under `runtime/commissioning/<map_id>/<run_id>/mapping` and rejected reuse of a populated mapping directory.
- Made the existing RViz `/goal_pose -> NavigateToPose` bridge explicit opt-in in normal navigation; default remains off.
- Added `field_navigation.launch.py` for Phase C frozen-map navigation using existing relocalization, GlobalCorrectionManager, Nav2, perception, and safety ownership.
- Kept Phase C `start_chassis=false` by default so motion requires explicit operator opt-in after preflight.
- Added `field_navigation.rviz` with `map` fixed frame, frozen map, registered point cloud, plan, global/local costmaps, TF, RobotModel, SetInitialPose, and SetGoal.
- Added explicit `field_mapping_baseline` and `field_navigation_baseline` rosbag profiles under the sole recorder ownership of `agt_experiment_manager`; neither uses record-all.
- Added `/agt/perception/obstacle_cloud` to navigation baseline evidence alongside localization, plan, raw/filtered command, safety, costmap, chassis, TF, and optional GNSS evidence.
- Added `freeze_map_assets.py` for deterministic PCD/navigation YAML/navigation image SHA256 identity, atomic `map_manifest.json` writing, `FAST_LIVO2_LIO_ONLY` mapping source, and initial `UNVERIFIED` calibration status.
- Added fail-closed tests for empty identity, missing files, unresolved navigation image, and manifest overwrite.
- Added the field operator runbook covering Phase A/B/C, ExperimentManager recording flow, pre-motion gates, calibration trajectory, frozen asset preparation, TRACKING gate, RViz commissioning goals, N0-N6 progression, and stop conditions.

## Ownership preserved

- FAST-LIVO2 adapter remains the unique `odom -> base_footprint` authority.
- GlobalCorrectionManager remains the unique `map -> odom` authority.
- Relocalization remains evidence/correction generation and does not take TF authority.
- Nav2 lifecycle remains localization-gated.
- RViz direct goals are commissioning-only and do not become the formal Mission/Task authority.
- Collision Monitor, `agt_safety`, and the chassis command chain remain in place.
- The first baseline does not introduce RTAB-Map into Phase C and does not use GNSS as an online global-correction owner.
- Runtime remains independent of the V2 source/install/workspace; V2 remains the offline Site Asset production boundary.

## TDD / verification history

Implementation was performed with focused RED -> minimal GREEN cycles. Notable RED findings included:

1. Missing Phase A mapping wrapper.
2. Unconditional RViz direct-goal bridge.
3. Missing Phase C frozen-map wrapper and RViz layout.
4. Missing field baseline bag profiles.
5. Missing map-freeze helper and runbook.
6. Static tests that initially overfit source formatting rather than behavior; these were corrected without changing valid production behavior.
7. Final requirements review found and corrected three plan-alignment gaps before acceptance: Phase C chassis default had to be `false`, navigation recording needed `/agt/perception/obstacle_cloud`, and ExperimentManager README needed explicit field-baseline recorder ownership guidance.

The final user-machine verification included the integrated contract/helper/runbook pytest suite plus fresh builds and CTests for:

```text
agt_bringup
agt_navigation
agt_experiment_manager
```

Reported final result:

```text
integrated pytest:             PASS / 0 failed
selected colcon build:         PASS
selected colcon test-result:   0 errors / 0 failures
```

## Software acceptance decision

The implementation at `7d4421345b54c8bed9446174e3b1fd5462b59c5f` is accepted as the software baseline for the first field commissioning session.

This means the repository now has a reproducible software path for:

```text
Phase A: field mapping + calibration evidence
        ->
Phase B: offline 2D navigation asset preparation + map identity freeze
        ->
Phase C: frozen-map relocalization + gated Nav2 + commissioning RViz goals
```

## Hardware acceptance remains OPEN

The following are explicitly not proven by software tests and must remain open until a real vehicle session supplies evidence:

- Real MID360/IMU timestamp continuity and sensor health.
- Real FAST-LIVO2 odometry and registered-point-cloud quality.
- Real unique TF authority for `odom -> base_footprint` and `map -> odom`.
- Real BUNKER CAN connectivity, monitor-mode command inertness, and control-mode safety chain.
- Real GNSS status/covariance and later RTK-LIO calibration observability.
- Real Phase A commissioning bag and saved PCD.
- Real Phase B generated PGM/YAML and frozen `map_manifest.json` bound to the actual map assets.
- Real localization transition to `TRACKING` with `pose_valid=true`, `localization_accepted=true`, and fresh status.
- Real `/agt/perception/obstacle_cloud`, Collision Monitor, and `agt_safety` behavior.
- N0-N6 physical navigation sequence and corresponding per-run bags/metrics.

Do not label the baseline hardware-green until those real-vehicle gates and N0-N6 evidence are collected.

## Next operational step

The next step is not another architecture expansion. Use `docs/runbooks/field_navigation_baseline.md` on the real BUNKER and execute the frozen sequence in order:

```text
Phase A preflight -> mapping/calibration capture -> bag validation
Phase B map preparation -> freeze_map_assets.py -> inspect manifest/hash
Phase C start_chassis=false -> TRACKING/safety gate -> explicit motion opt-in
N0 -> N1 -> N2 -> N3 -> N4 -> N5 -> N6
```

One `run_id` and one managed bag should be preserved per navigation experiment so later RTK-LIO calibration and controller/localization analysis remain traceable.
