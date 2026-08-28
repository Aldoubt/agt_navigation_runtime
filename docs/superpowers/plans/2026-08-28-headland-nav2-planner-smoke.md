# Headland Nav2 Planner Smoke Harness Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Consume the frozen greenhouse `planner_pairs.yaml` and gap diagnostics, execute all strict-connected pair directions as positive Nav2 planner smoke tests plus all relaxed-connectable mixed/clearance-only pair directions as negative controls, and write reproducible machine-readable results without starting a controller or chassis.

**Architecture:** Keep manifest construction, expectation semantics, metrics, GeoJSON, and static-map overlay rendering in a ROS-independent Python module. A thin ROS 2 runner sequentially calls `nav2_msgs/action/ComputePathToPose`. A dedicated launch starts only map_server, planner_server, lifecycle management, and the smoke runner, reusing the same conservative static-map contract and `allow_unknown: false` policy.

**Tech Stack:** Python 3, ROS 2 Humble, rclpy, Nav2 SmacPlanner2D, PyYAML, stdlib JSON/CSV/PNG support.

**Spec:** This plan implements the approved P1 handoff: 11 strict-connected pair-side cases -> 22 positive directional requests; A02-A03 exit, A11-A12 exit, A13-A14 exit relaxed-connectable cases -> 6 negative directional requests for the current frozen dataset.

## Global Constraints

- Do not edit or regenerate the source navigation PGM.
- Unknown remains non-traversable in Nav2 (`allow_unknown: false`).
- Phase 1 planner smoke uses a frozen 0.20 m robot-radius proxy matching the topology experiment; it is not MK-mini vehicle acceptance.
- Do not start controller_server, bt_navigator, waypoint_follower, safety enable, or chassis.
- Positive and negative case selection must be derived from the supplied artifacts, not hard-coded aisle IDs.
- Negative controls are only `mixed_bridge` or `clearance_only_bridge` strict failures; `hard_or_finite_headland_blocked` remains diagnostic but is not promoted to a planner expectation.
- A successful negative-control plan is a smoke-test mismatch, not permission to edit the map.

---

### Task 1: Freeze artifact-to-request semantics

**Files:**
- Create: `src/agt_navigation/test/test_headland_planner_smoke.py`
- Create later: `src/agt_navigation/agt_navigation/headland_planner_smoke.py`

**Interfaces:**
- Consumes: planner-pair payload with `radius_m` and `tests`; gap-diagnostic payload with `radius_m` and `records`.
- Produces: `build_smoke_manifest(planner_pairs, gap_diagnostics) -> dict`.

- [ ] **Step 1: Write the failing tests**

Cover: 11 enabled pair-side tests become 22 positive directional requests; three relaxed-connectable negative pair-side records become 6 negative requests; hard/finite blocked records are ignored as negatives; mismatched radii raise `ValueError`; every request keeps the exact forward/reverse start and goal poses.

- [ ] **Step 2: Run test to verify RED**

Run:

```bash
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_navigation/test/test_headland_planner_smoke.py
```

Expected: FAIL because `agt_navigation.headland_planner_smoke` does not exist yet.

- [ ] **Step 3: Implement minimal manifest core**

Create pure helpers for finite pose validation, pair-id matching, positive/negative selection, deterministic request IDs, and radius validation.

- [ ] **Step 4: Run test to verify GREEN**

Expected: all Task 1 tests pass.

- [ ] **Step 5: Commit**

```bash
git add src/agt_navigation/test/test_headland_planner_smoke.py \
        src/agt_navigation/agt_navigation/headland_planner_smoke.py
git commit -m "feat: build headland planner smoke manifest"
```

### Task 2: Freeze planner outcome metrics and bundle outputs

**Files:**
- Modify: `src/agt_navigation/test/test_headland_planner_smoke.py`
- Modify: `src/agt_navigation/agt_navigation/headland_planner_smoke.py`

**Interfaces:**
- Consumes: request manifest plus per-request Nav2 outcomes.
- Produces: `finalize_smoke_results(...)`, `write_smoke_bundle(...)` and files `planner_smoke_results.json`, `summary.csv`, `planner_paths.geojson`, `planner_overlay.png`.

- [ ] **Step 1: Write failing tests**

Assert path length, expectation classification, positive failure / negative unexpected-success mismatch counts, GeoJSON line output, and a valid PNG signature from a synthetic PGM/YAML map.

- [ ] **Step 2: Run to verify RED**

Expected: FAIL because result/bundle helpers do not exist.

- [ ] **Step 3: Implement minimal result and renderer code**

Use standard-library CSV/JSON/zlib/struct. Read P2/P5 PGM, convert map coordinates with YAML resolution/origin, draw successful paths, and emit an RGB PNG without adding OpenCV/matplotlib runtime dependencies.

- [ ] **Step 4: Run to verify GREEN**

Expected: all pure smoke tests pass.

- [ ] **Step 5: Commit**

```bash
git add src/agt_navigation/test/test_headland_planner_smoke.py \
        src/agt_navigation/agt_navigation/headland_planner_smoke.py
git commit -m "feat: write headland planner smoke result bundle"
```

### Task 3: Add the ROS 2 ComputePathToPose runner

**Files:**
- Create: `src/agt_navigation/scripts/headland_planner_smoke.py`
- Modify: `src/agt_navigation/CMakeLists.txt`

**Interfaces:**
- Consumes CLI args `--planner-pairs`, `--gap-diagnostics`, `--map-yaml`, `--output`, `--planner-id`, `--server-timeout`, `--request-timeout`.
- Produces sequential `ComputePathToPose` calls with `use_start=true` and the Task 2 output bundle.

- [ ] **Step 1: Add static/unit coverage for argument and helper behavior where ROS transport is not required.**
- [ ] **Step 2: Verify the new tests fail before runner integration.**
- [ ] **Step 3: Implement the thin ROS action runner.**

For every request: send exact map-frame start/goal, record action acceptance/status/error code, returned path, wall-clock elapsed time, Nav2 planning duration when present, path pose count, and failure reason. Exit non-zero when any expectation is violated.

- [ ] **Step 4: Run Python syntax check and package tests.**

```bash
python -m py_compile src/agt_navigation/scripts/headland_planner_smoke.py
PYTEST_DISABLE_PLUGIN_AUTOLOAD=1 python -m pytest -q \
  src/agt_navigation/test/test_headland_planner_smoke.py
```

- [ ] **Step 5: Commit.**

### Task 4: Add planner-only launch and frozen Phase-1 Nav2 parameters

**Files:**
- Create: `src/agt_navigation/config/headland_planner_smoke_nav2.yaml`
- Create: `src/agt_navigation/launch/headland_planner_smoke.launch.py`
- Create: `src/agt_navigation/test/test_headland_planner_smoke_launch.py`
- Modify: `src/agt_navigation/CMakeLists.txt`

**Interfaces:**
- Launch args: `map`, `planner_pairs`, `gap_diagnostics`, `output`, optional timeout/planner parameters.
- Nodes: map_server, planner_server, lifecycle manager(s), headland smoke runner only.

- [ ] **Step 1: Write failing launch-contract test** checking that motion-stack executables are absent and required planner/map/runner nodes and artifact arguments are present.
- [ ] **Step 2: Verify RED.**
- [ ] **Step 3: Implement launch/config** with SmacPlanner2D `GridBased`, `allow_unknown: false`, `robot_radius: 0.20`, static + inflation layers, and no motion stack.
- [ ] **Step 4: Run launch-contract tests and `colcon build --packages-select agt_navigation`.**
- [ ] **Step 5: Commit.**

### Task 5: Document P1 runtime handoff and real replay commands

**Files:**
- Modify: `src/agt_navigation/README.md`
- Modify: root `README.md`

**Interfaces:**
- Documents map-reconstruction producer inputs and runtime smoke output contract.

- [ ] **Step 1:** Document the Phase-1 purpose and the distinction between 0.20 m topology proxy and MK-mini Ackermann acceptance.
- [ ] **Step 2:** Add the exact `ros2 launch agt_navigation headland_planner_smoke.launch.py ...` replay command.
- [ ] **Step 3:** Document expected current-frozen manifest counts `22 positive + 6 negative`, but require the generated manifest to remain the authority.
- [ ] **Step 4:** Re-run tests/build before claiming completion.
- [ ] **Step 5:** Commit documentation.

## Self-review

- Spec coverage: producer artifacts, 22/6 current replay, positive/negative semantics, no motion stack, result JSON/CSV/GeoJSON/PNG, and Nav2 planner-only launch are all assigned to tasks.
- Placeholder scan: no TBD/TODO placeholders are used.
- Type consistency: all phases consume the same manifest request shape and the runner emits outcomes consumed by `finalize_smoke_results`.
