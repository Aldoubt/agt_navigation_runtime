# P1-08 ROS 2 Humble Convergence Regression Plan

Date: 2026-08-29
Branch: `feat/runtime-navigation-convergence-p1`
Design authority: `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

## Goal

Produce fresh, repeatable ROS 2 Humble evidence for the canonical convergence branch. Existing Runtime Contracts on Ubuntu 24.04 remain STATIC evidence only.

P1-08 closes the software/runtime regression gate before any BUNKER + MID360 motion acceptance in P1-09.

## Scope

### A. Clean Humble build/test lane

Run on Ubuntu 22.04 with ROS 2 Humble and build/test the convergence core that is independent of physical BUNKER/MID360 availability:

```text
agt_interfaces
agt_runtime_contracts
agt_site_runtime
agt_site_navigation
agt_system_manager
agt_navigation
agt_safety
agt_operator_gateway
```

Include repository-internal dependencies required by those packages. Install ROS dependencies with rosdep from only the selected core package manifests so external vendor hardware SDKs do not become an accidental CI prerequisite.

### B. Humble interface/runtime smoke

After build, source the workspace and verify:

- generated P1 interfaces import on Humble;
- Site Runtime can validate/list a fixture or generated valid Site Package without physical hardware;
- `agt_site_navigation` launch/runtime assets resolve from the install tree;
- `navigation.launch.py` exposes the production direct-goal bridge as disabled by default;
- no-upstream readiness remains fail-closed rather than READY.

Where a smoke can be expressed as an existing package test, run it through `colcon test`. Do not create a fake Nav2 READY state merely to pass CI.

### C. Separate physical/vendor boundary

Do not require FAST-LIVO2 binaries, Livox hardware, CAN, BUNKER or vendor SDK processes for the P1-08 core Humble lane. Their real integration/motion evidence is P1-09.

`agt_hardware_bringup` remains covered by its source/no-ROS contract in P1-08 unless a clean Humble dependency-only build can be added without pulling non-reproducible vendor runtime assets. This limitation must be explicit in the acceptance record.

## TDD / execution order

1. Add a no-ROS source contract for the required Humble workflow and observe RED while the workflow is absent.
2. Add `.github/workflows/runtime-humble.yml` using an actual Humble/Jammy environment.
3. Run dependency installation, `colcon build`, `colcon test`, and `colcon test-result --verbose` in that workflow.
4. Inspect the first real Humble failure. Fix repository defects; do not weaken the gate to hide them.
5. Add bounded no-hardware smoke checks only after the build/test lane is green.
6. Record exact run IDs, package/test results, skipped vendor/hardware boundary, and remaining field gate.
7. Update convergence status only after a fresh final-head Humble run and Runtime Contracts run both pass.

## Initial Humble package set

```text
agt_interfaces
agt_runtime_contracts
agt_site_runtime
agt_site_navigation
agt_system_manager
agt_navigation
agt_safety
agt_operator_gateway
```

The package set may expand when an internal dependency is required. It may not shrink merely to avoid a genuine regression in one of these packages.

## Acceptance

P1-08 passes only when all are true:

```text
[x] workflow runs in a real ROS 2 Humble / Ubuntu 22.04 environment
[x] rosdep installs selected-core dependencies from clean runner state
[x] selected core colcon build succeeds
[x] selected core colcon tests succeed
[x] generated P1 interfaces import after sourcing install/setup.bash
[x] fail-closed/no-upstream smoke succeeds without physical hardware
[x] production RViz direct-goal default remains guarded
[x] acceptance record captures exact run/head and vendor/hardware exclusions
```

P1-08 does not mark FIELD complete. P1-09 remains the BUNKER + MID360 hardware acceptance gate.
