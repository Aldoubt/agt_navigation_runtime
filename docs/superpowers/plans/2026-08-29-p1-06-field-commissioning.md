# P1-06 Field Commissioning Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Selectively port the accepted field commissioning flow into the canonical P1 branch without making normal Runtime odometry persist maps or allowing navigation against a changing commissioning map.

**Architecture:** Add a dedicated `agt_field_commissioning` package. Phase A launches BUNKER/MID360 + FAST-LIVO2 LIO-only with PCD persistence enabled only in commissioning and writes to a unique `runtime/commissioning/<site_id>/<run_id>` run directory. A pure-Python finalizer verifies the FAST-LIVO2 shutdown artifacts and records hashes. Phase C remains a frozen-Site workflow and composes the current Site/Navigation contracts; the old monolithic `agt_bringup/system.launch.py` is not restored.

**Tech Stack:** ROS 2 Humble launch/ament_cmake_python, Python 3, pytest/no-ROS contract tests, FAST-LIVO2 vendor package already pinned in this repository.

**Spec:** `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

## Global Constraints

- Work only on `feat/runtime-navigation-convergence-p1`.
- Do not modify normal `agt_odometry/launch/fast_livo2_odometry.launch.py` map-persistence defaults.
- Commissioning mapping uses `pcd_save.pcd_save_en=true`, `pcd_save.interval=-1`, and an explicit commissioning output directory.
- Mapping runs refuse silent reuse/overwrite of populated output directories.
- FAST-LIVO2 must be allowed to exit normally before PCD acceptance; `SIGKILL` is not an accepted save path.
- Phase A starts with localization and Nav2 disabled.
- Phase C consumes frozen Site Package assets only.
- Do not restore the divergent old `agt_bringup` architecture.
- Do not mark ROS 2 Humble or real-vehicle acceptance from static/no-ROS evidence.

---

## File Structure

Create:

```text
src/agt_field_commissioning/
  CMakeLists.txt
  package.xml
  README.md
  agt_field_commissioning/
    __init__.py
    mapping_artifacts.py
  launch/
    field_mapping.launch.py
    field_navigation.launch.py
  scripts/
    finalize_mapping_run.py
  rviz/
    field_commissioning.rviz

tests/commissioning/
  test_mapping_artifacts.py
  test_field_mapping_contract.py
  test_field_navigation_contract.py
  test_field_commissioning_runbook.py

docs/runbooks/field-navigation-commissioning.md
docs/acceptance/2026-08-29-runtime-navigation-p1-06-field-commissioning.md
```

Responsibilities:

- `mapping_artifacts.py`: deterministic run paths, identity validation, non-overwrite guard, shutdown artifact validation, SHA256 evidence.
- `field_mapping.launch.py`: commissioning-only hardware + FAST-LIVO2 mapping composition; no localization/Nav2.
- `field_navigation.launch.py`: frozen-Site field navigation composition and commissioning RViz entry point; no map generation.
- `finalize_mapping_run.py`: operator CLI for post-shutdown verification/evidence writing.
- runbook: exact Phase A -> offline reconstruction -> Site Package -> contract validation -> explicit activation -> Phase C sequence.

### Task 1: Mapping artifact contract and finalizer

**Files:**
- Create: `tests/commissioning/test_mapping_artifacts.py`
- Create: `src/agt_field_commissioning/agt_field_commissioning/__init__.py`
- Create: `src/agt_field_commissioning/agt_field_commissioning/mapping_artifacts.py`
- Create: `src/agt_field_commissioning/scripts/finalize_mapping_run.py`

**Interfaces:**
- Produces: `CommissioningRunPaths`, `prepare_mapping_run(runtime_dir, site_id, run_id)`, `finalize_mapping_run(runtime_dir, site_id, run_id)`.
- `finalize_mapping_run` returns a JSON-serializable dict and writes `evidence/mapping_metadata.json` atomically.

- [ ] **Step 1: Write the failing tests**

Test that `prepare_mapping_run` creates the exact unique run path, rejects unsafe identity tokens, and rejects a populated mapping directory. Test that `finalize_mapping_run` rejects missing/empty PCD, rejects leftover `*.tmp`, requires `localization_map.processing.yaml`, computes SHA256, and writes READY evidence.

- [ ] **Step 2: Verify RED**

Run:

```bash
PYTHONPATH=src/agt_field_commissioning pytest -q tests/commissioning/test_mapping_artifacts.py
```

Expected: FAIL because `agt_field_commissioning.mapping_artifacts` does not exist.

- [ ] **Step 3: Implement minimal production code**

Use `pathlib.Path`, `hashlib.sha256`, `json`, `dataclasses.dataclass`, an identity regex `^[A-Za-z0-9][A-Za-z0-9._-]{0,63}$`, and atomic `*.tmp -> replace()` evidence writes. Require both:

```text
mapping/localization_map.pcd
mapping/localization_map.processing.yaml
```

- [ ] **Step 4: Verify GREEN**

Run the same pytest command; expected PASS.

- [ ] **Step 5: Commit**

Commit message: `feat(commissioning): add mapping artifact finalizer`.

### Task 2: Dedicated Phase A mapping launch

**Files:**
- Create: `tests/commissioning/test_field_mapping_contract.py`
- Create: `src/agt_field_commissioning/launch/field_mapping.launch.py`
- Create: `src/agt_field_commissioning/CMakeLists.txt`
- Create: `src/agt_field_commissioning/package.xml`
- Create: `src/agt_field_commissioning/README.md`

**Interfaces:**
- Consumes: `prepare_mapping_run(...)`.
- Produces ROS launch arguments: `runtime_dir`, `site_id`, `run_id`, `use_sim_time`, `start_hardware`, BUNKER/MID360 hardware arguments, FAST-LIVO2 parameter file and self-filter arguments.

- [ ] **Step 1: Write failing static contract tests**

Assert the launch source:

```text
includes agt_hardware_bringup/bunker_mid360.launch.py
starts fast_livo/fastlivo_mapping directly
sets pcd_save.pcd_save_en True
sets pcd_save.interval -1
sets pcd_save.output_directory from the unique mapping directory
uses sigterm_timeout >= 30
never includes localization or agt_navigation launch files
remaps cloud_registered to /agt/commissioning/mapping/registered_points
```

Also assert normal `agt_odometry/launch/fast_livo2_odometry.launch.py` still contains `pcd_save.pcd_save_en: False`.

- [ ] **Step 2: Verify RED**

Run:

```bash
pytest -q tests/commissioning/test_field_mapping_contract.py
```

Expected: FAIL because the commissioning launch/package does not exist.

- [ ] **Step 3: Implement minimal launch/package**

The launch must use the existing odometry YAML as the baseline config but override only commissioning persistence and output topic/path. It must not alter normal Runtime odometry.

- [ ] **Step 4: Verify GREEN**

Run the contract test plus Task 1 tests; expected PASS.

- [ ] **Step 5: Commit**

Commit message: `feat(commissioning): add FAST-LIVO2 field mapping entrypoint`.

### Task 3: Frozen-Site Phase C field navigation entry point

**Files:**
- Create: `tests/commissioning/test_field_navigation_contract.py`
- Create: `src/agt_field_commissioning/launch/field_navigation.launch.py`
- Create: `src/agt_field_commissioning/rviz/field_commissioning.rviz`

**Interfaces:**
- Consumes deployed `sites_root`, explicit `site_id/site_revision` activation performed before launch, current `agt_navigation`, `agt_site_navigation`, localization and hardware packages.
- Produces an operator commissioning entry point only; it does not generate or mutate Site assets.

- [ ] **Step 1: Write failing static contract tests**

Assert that Phase C launch has no FAST-LIVO2 PCD-save enable, no map-writing tool, and no fallback to commissioning map paths. Assert it references Site binding/runtime-status and current navigation packages rather than old `agt_bringup/system.launch.py`.

- [ ] **Step 2: Verify RED**

Run:

```bash
pytest -q tests/commissioning/test_field_navigation_contract.py
```

Expected: FAIL because the new Phase C launch does not exist.

- [ ] **Step 3: Implement minimal frozen-Site wrapper**

Keep map generation absent. Use current Site/Navigation authorities and expose commissioning RViz. Direct RViz goal opt-in remains explicitly identified as P1-07 work if the underlying standard navigation launch cannot yet gate it.

- [ ] **Step 4: Verify GREEN**

Run Task 3 and prior commissioning tests; expected PASS.

- [ ] **Step 5: Commit**

Commit message: `feat(commissioning): add frozen-site field navigation entrypoint`.

### Task 4: Runbook and source-branch traceability

**Files:**
- Create: `tests/commissioning/test_field_commissioning_runbook.py`
- Create: `docs/runbooks/field-navigation-commissioning.md`

**Interfaces:**
- Documents source branch `feat/field-navigation-baseline` and selective-port decisions.

- [ ] **Step 1: Write failing documentation contract test**

Require the runbook to contain the ordered gates:

```text
Phase A mapping
normal Ctrl+C / ROS shutdown
finalize_mapping_run.py
offline reconstruction/export
Site Package 1.0
runtime-contract validation
deploy under sites_root
explicit Site activation
Phase C navigation
```

Require explicit statements that commissioning output is mutable, Site Package is immutable, and changing tasks never rebuilds the Site Package.

- [ ] **Step 2: Verify RED**

Run the runbook test; expected FAIL because the document does not exist.

- [ ] **Step 3: Write the runbook**

Include exact example commands and acceptance checks. Do not claim hardware PASS.

- [ ] **Step 4: Verify GREEN**

Run all `tests/commissioning`; expected PASS.

- [ ] **Step 5: Commit**

Commit message: `docs(commissioning): add field navigation runbook`.

### Task 5: P1-06 acceptance record and convergence status

**Files:**
- Create: `docs/acceptance/2026-08-29-runtime-navigation-p1-06-field-commissioning.md`
- Modify: `docs/convergence/runtime-navigation-convergence-p1.md`

**Interfaces:**
- Records source head and exact test evidence; separates STATIC/HUMBLE/FIELD.

- [ ] **Step 1: Run final static regression**

Run:

```bash
pytest -q tests/commissioning
```

and the relevant existing odometry contract test(s). Record actual results only.

- [ ] **Step 2: Review changed source against P1-06 acceptance invariants**

Confirm Phase A has no localization/Nav2, Phase C has no map generation, normal odometry persistence remains disabled, and populated outputs are not overwritten.

- [ ] **Step 3: Write acceptance note and update convergence table**

Mark P1-06 `Code [x] / STATIC [x]` only if evidence passes. Leave `HUMBLE [ ] / FIELD [ ]` until independently executed.

- [ ] **Step 4: Commit**

Commit message: `docs(convergence): accept P1-06 static field commissioning`.
