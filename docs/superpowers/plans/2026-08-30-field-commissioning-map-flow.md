# Field Commissioning Map Flow Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the robot-side Runtime expose a delivery-grade commissioning path from finalized FAST-LIVO2 PCD through slope-aware RTAB-Map grid projection, non-destructive map review, Site candidate materialization, task persistence/route preview contracts, and bounded startup relocalization requests.

**Architecture:** Keep normal Runtime execution map-consumer-only. Add pure commissioning domain modules under `agt_field_commissioning`, an optional C++ `rtabmap_grid_projector` linked to RTAB-Map core when installed, and a filesystem-backed `CommissioningPort` consumed by `agt_operator_gateway`. The browser receives stable HTTP contracts and never owns ROS topics, filesystem paths, or subprocesses.

**Tech Stack:** ROS 2 Humble, Python 3, aiohttp, PGM/YAML, PCL, RTAB-Map core (`rtabmap::core`), Nav2 existing planner preview, pytest.

**Spec:** `docs/superpowers/specs/2026-08-30-field-commissioning-hmi-map-workflow-design.md`

## Global Constraints

- Do not modify frozen `agt_inspection` AcquireView/evidence behavior.
- RTAB-Map is a projection backend only; FAST-LIVO2 remains mapping/odometry owner and GlobalCorrectionManager remains sole `map->odom` authority.
- Raw projected map is immutable; edits materialize a reviewed draft and promotion creates a new Site revision.
- Browser command writes remain guarded by the existing Gateway write/token boundary.
- Planner preview never starts controller, BT Navigator, Waypoint Follower, safety enable, or chassis motion.
- First field localization is bounded around configured/last/external candidate seeds; no arbitrary-position place recognition is claimed.

---

### Task 1: Commissioning map review domain

**Files:**
- Create: `src/agt_field_commissioning/agt_field_commissioning/map_review.py`
- Test: `tests/commissioning/test_map_review.py`

**Interfaces:**
- Produces: `PgmMap.load(path)`, `PgmMap.write(path)`, `MapEdit(kind, cells)`, `MapReviewDraft.create(raw_pgm, raw_yaml, draft_dir)`, `MapReviewDraft.apply(edit)`, `undo()`, `redo()`, `reset()`, `materialize()`.

- [ ] Write failing tests proving P5/P2 parsing, occupied/free edits, obstacle-overrides-free semantics, undo/redo/reset, and raw-map immutability.
- [ ] Run `PYTHONPATH=src/agt_field_commissioning python -m pytest -q tests/commissioning/test_map_review.py` and verify RED because `map_review` does not exist.
- [ ] Implement the minimal parser/editor and atomic reviewed-map materialization.
- [ ] Re-run the focused tests and all `tests/commissioning`; expect GREEN.
- [ ] Commit as `feat: add non-destructive commissioning map review`.

### Task 2: Slope-aware RTAB-Map projection backend

**Files:**
- Create: `src/agt_field_commissioning/agt_field_commissioning/projection.py`
- Create: `src/agt_field_commissioning/src/rtabmap_grid_projector.cpp`
- Create: `src/agt_field_commissioning/config/rtabmap_grid_slope.yaml`
- Modify: `src/agt_field_commissioning/CMakeLists.txt`
- Modify: `src/agt_field_commissioning/package.xml`
- Test: `tests/commissioning/test_projection_contract.py`

**Interfaces:**
- Produces: `ProjectionRequest`, `ProjectionResult`, `RtabmapGridBackend.project(request)`, `load_projection_record(path)`.
- The C++ executable accepts `--input`, `--output-pgm`, `--output-yaml`, `--cell-size`, `--max-ground-angle-deg`, `--normal-k`, `--min-ground-height`, `--max-ground-height`, `--max-obstacle-height`.

- [ ] Write failing Python contract tests for command construction, fail-closed missing executable/output, hashing, and projection record schema.
- [ ] Run focused tests and verify RED.
- [ ] Implement the Python backend with injectable runner and atomic record creation.
- [ ] Add an optional CMake target gated by `find_package(RTABMap QUIET)` and `find_package(PCL QUIET)` so standard Runtime CI does not fail when RTAB-Map is absent.
- [ ] Implement the C++ projector: load PCD, use `rtabmap::LocalGridMaker::segmentCloud()` with `Grid/NormalsSegmentation=true`, rasterize ground as free and obstacles as occupied, write Nav2 PGM/YAML, and never publish TF.
- [ ] Run Python tests/compile checks; on target Humble additionally require a build with RTAB-Map installed before field acceptance.
- [ ] Commit as `feat: add rtabmap slope grid projection backend`.

### Task 3: Commissioning filesystem service and Site candidate bundle

**Files:**
- Create: `src/agt_field_commissioning/agt_field_commissioning/service.py`
- Test: `tests/commissioning/test_commissioning_service.py`

**Interfaces:**
- Produces: `CommissioningService.status(site_id, run_id)`, `project(site_id, run_id)`, `map_descriptor(site_id, run_id)`, `apply_map_edit(...)`, `undo_map_edit(...)`, `redo_map_edit(...)`, `reset_map_edit(...)`, `save_review(site_id, run_id, revision)`.
- `save_review()` writes a candidate Site directory containing reviewed navigation PGM/YAML plus the finalized `localization_map.pcd` and processing record with hashes; it never activates the Site.

- [ ] Write failing tests using temporary commissioning runs and deterministic fake projection backend.
- [ ] Verify RED.
- [ ] Implement service orchestration, state JSON, atomic writes, revision identity validation, and candidate bundle materialization.
- [ ] Run focused + commissioning tests; expect GREEN.
- [ ] Commit as `feat: add commissioning map service`.

### Task 4: Operator Gateway commissioning HTTP contract

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/commissioning_port.py`
- Modify: `src/agt_operator_gateway/agt_operator_gateway/server.py`
- Modify: `src/agt_operator_gateway/scripts/operator_gateway_node.py`
- Modify: `src/agt_operator_gateway/CMakeLists.txt`
- Modify: `src/agt_operator_gateway/package.xml`
- Test: `src/agt_operator_gateway/test/test_commissioning_http.py`

**Interfaces:**
- Read: `GET /api/v1/commissioning/status`, `GET /api/v1/commissioning/map`, `GET /api/v1/commissioning/map/image`.
- Write: `POST /api/v1/commissioning/project`, `/map/edit`, `/map/undo`, `/map/redo`, `/map/reset`, `/map/save`.
- Writes require existing bearer-token guard when write mode is enabled.

- [ ] Write aiohttp failing tests with a fake `CommissioningPort` for route schema, validation, auth, and PGM binary response.
- [ ] Verify RED.
- [ ] Implement the port protocol/adapter and HTTP handlers without changing mission command semantics.
- [ ] Wire robot-local runtime directory parameters in `operator_gateway_node.py`.
- [ ] Run gateway focused tests plus existing operator gateway suite; expect GREEN.
- [ ] Commit as `feat: expose commissioning map gateway API`.

### Task 5: Task persistence and planner preview web contract

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/task_port.py`
- Modify: `src/agt_operator_gateway/agt_operator_gateway/server.py`
- Test: `src/agt_operator_gateway/test/test_task_http.py`

**Interfaces:**
- `GET /api/v1/tasks/{task_id}`
- `PUT /api/v1/tasks/{task_id}` persists an exact Site-bound task draft atomically under Runtime Task Registry storage.
- `POST /api/v1/tasks/preview` accepts ordered map-frame waypoints and delegates to an injected `TaskPreviewPort`; response is per-segment status plus merged path.

- [ ] Write failing HTTP tests for exact Site binding, invalid waypoint rejection, atomic task persistence, and preview failure reporting.
- [ ] Verify RED.
- [ ] Implement filesystem persistence adapter and preview port abstraction that can wrap the existing Nav2 planner-only adapter without adding a new planner.
- [ ] Run focused + gateway tests; expect GREEN.
- [ ] Commit as `feat: expose task registry and route preview API`.

### Task 6: Startup relocalization and AUTO permit contracts

**Files:**
- Create: `src/agt_operator_gateway/agt_operator_gateway/run_readiness.py`
- Modify: `src/agt_operator_gateway/agt_operator_gateway/server.py`
- Test: `src/agt_operator_gateway/test/test_run_readiness_http.py`

**Interfaces:**
- `GET /api/v1/run/readiness` returns Runtime-owned Site/localization/navigation/camera-gimbal/AUTO-permit readiness.
- `POST /api/v1/run/relocalize` delegates to an injected bounded `RelocalizePort`; it cannot fabricate TRACKING.
- AUTO permit is read-only at the web boundary; browser cannot spoof it.

- [ ] Write failing tests for absent permit, failed relocalization, and all-ready state.
- [ ] Verify RED.
- [ ] Implement the pure contract and injected port boundary; physical RC signal acquisition remains vehicle-adapter owned and must be validated on BUNKER.
- [ ] Run gateway suite; expect GREEN.
- [ ] Commit as `feat: expose run readiness and bounded relocalization`.

### Task 7: Regression and freeze evidence

**Files:**
- Create: `docs/acceptance/2026-08-30-field-commissioning-map-flow.md`
- Modify: `.github/workflows/inspection-mvp.yml` only if required to include new pure-Python tests; do not weaken existing inspection jobs.

- [ ] Run commissioning, gateway, navigation contract and frozen inspection static suites in CI.
- [ ] Run `python -m compileall` on changed Runtime Python packages.
- [ ] Confirm inspection freeze behavior files are unchanged by comparing against `73b0f2dfe02bb04c5940d8bebbcff2a95fd281d2` for the frozen inspection path.
- [ ] Record Code/STATIC results separately from ROS2 Humble/physical RTAB-Map/BUNKER gates.
- [ ] Commit as `docs: record commissioning map flow acceptance`.
