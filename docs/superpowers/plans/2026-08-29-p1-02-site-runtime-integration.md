# P1-02 Site Runtime Integration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Integrate the accepted Site Runtime owner into `feat/runtime-navigation-convergence-p1` without regressing Gateway, hardware bringup, SystemManager fail-closed readiness, or existing Runtime contracts.

**Architecture:** Because `feat/runtime-site-owner-p01` and the canonical P1 branch are not directly mergeable, P1-02 performs a responsibility-preserving selective integration. Pure Site Runtime additions are imported unchanged where compatible; overlapping interfaces, Runtime Contracts, SystemManager, workflows, and tests are merged manually so both the newer hardware/Gateway baseline and Site owner behavior remain authoritative in their own domains.

**Tech Stack:** ROS 2 Humble, CMake/ament, Python, pytest, GitHub Actions, YAML/JSON runtime contracts.

**Spec:** `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

## Global Constraints

- Canonical implementation branch is `feat/runtime-navigation-convergence-p1`.
- Keep `agt_operator_gateway` and `agt_hardware_bringup` behavior inherited from `feat/hardware-bringup-p0`.
- Keep `agt_system_manager` as read-model aggregation only; it must not activate maps, start algorithms, publish velocity, or own Gateway transport.
- `agt_site_runtime` owns deployed Site discovery, validation and explicit activation only; it does not generate map assets or own Nav2/map-server process lifecycle.
- Site selection remains fail-closed: no automatic fallback to another revision.
- Preserve one authoritative `/agt/maps/active` source.
- Do not start P1-03 Task Registry changes in this plan.
- Software/static evidence must not be reported as real-vehicle evidence.

---

### Task 1: Freeze the integration conflict surface

**Files:**
- Read: branch comparison `feat/runtime-navigation-convergence-p1...feat/runtime-site-owner-p01`
- Update later: `docs/convergence/runtime-navigation-convergence-p1.md`

**Interfaces:**
- Consumes: P1 branch at the current P1-01 documentation head and Site owner branch `3969b152157e20dddd479fb08f95a694aeb08681`.
- Produces: an explicit file disposition used by Tasks 2-5.

- [ ] **Step 1: Confirm direct merge is not allowed**

Use the preview PR or branch comparison and record the result. Expected: branches diverged and direct PR is not mergeable.

- [ ] **Step 2: Classify changed files**

Classify every Site-owner changed file into one of:

```text
IMPORT_UNCHANGED
MERGE_INTERFACES
MERGE_RUNTIME_CONTRACTS
MERGE_SYSTEM_MANAGER
DOCS_TESTS_WORKFLOW
```

Expected pure imports include the new `agt_runtime_contracts` and `agt_site_runtime` package trees. Overlapping files must not be replaced wholesale.

- [ ] **Step 3: Record source identity**

Record source branch and source commit in the P1-02 acceptance report:

```text
source_branch: feat/runtime-site-owner-p01
source_commit: 3969b152157e20dddd479fb08f95a694aeb08681
```

---

### Task 2: Import Site Runtime packages and interface additions

**Files:**
- Create/import: `src/agt_runtime_contracts/**`
- Create/import: `src/agt_site_runtime/**`
- Create/import: `src/agt_interfaces/srv/ValidateMapVersion.srv`
- Modify: `src/agt_interfaces/CMakeLists.txt`
- Modify: `src/agt_interfaces/test/test_system_interfaces.py`

**Interfaces:**
- Consumes: existing `agt_interfaces` package on P1.
- Produces: installed `agt_runtime_contracts`, `agt_site_runtime`, `ValidateMapVersion.srv`, and `/agt/maps/list|validate|activate` plus `/agt/maps/active` contracts.

- [ ] **Step 1: Preserve the interface test delta before implementation**

Ensure the interface test requires `ValidateMapVersion.srv` to be registered and generated while retaining every service/action/message already present on the P1 branch.

- [ ] **Step 2: Import the new packages**

Import the complete `src/agt_runtime_contracts/` and `src/agt_site_runtime/` trees from the accepted Site-owner source commit.

- [ ] **Step 3: Merge `agt_interfaces` registration additively**

Add only the Site-owner service registration and associated test assertions. Do not remove Gateway, Mission, navigation, or hardware-related interfaces that exist on the P1 base.

- [ ] **Step 4: Static verification**

Verify all package manifests/CMake files reference only files that exist in the integrated tree and that `ValidateMapVersion.srv` is included exactly once.

Expected: no duplicate service registration and no lost pre-existing interface.

---

### Task 3: Merge Runtime Contract validation without losing the newer baseline

**Files:**
- Modify: `tools/runtime_contracts/__init__.py`
- Modify: `tools/runtime_contracts/validator.py`
- Create/import: `tests/contracts/test_runtime_contract_library.py`
- Create/import: `tests/contracts/test_site_runtime_interfaces_contract.py`
- Create/import: `tests/site_runtime/test_site_runtime_source_contract.py`
- Modify: `.github/workflows/runtime-contracts.yml`

**Interfaces:**
- Consumes: existing P1 runtime-contract schemas/tools and the installed `agt_runtime_contracts` library.
- Produces: one compatible validator path usable from both repository tools and the installable ROS package.

- [ ] **Step 1: Retain all existing P1 validation behavior**

Before applying the Site-owner delta, enumerate the public functions/imports used by current P1 contract tests. The final validator must preserve these names and behaviors.

- [ ] **Step 2: Add the installable contract library path**

Integrate the Site-owner delegation/refactoring so repository-level validation and installed `agt_runtime_contracts` validation agree on Site Package results.

- [ ] **Step 3: Add cross-package source tests**

Import the Site Runtime interface/contract tests and ensure they reference the integrated package paths rather than the old source branch.

- [ ] **Step 4: Merge CI additively**

Extend `runtime-contracts.yml` with the Site/runtime checks while keeping current Gateway/hardware/runtime stages present on P1.

- [ ] **Step 5: Static regression gate**

Expected test groups to remain represented:

```text
runtime contracts
site runtime source/contracts
system manager contracts
operator gateway contracts
hardware bringup no-ROS checks
```

No prior P1 CI stage may disappear as a side effect of this integration.

---

### Task 4: Merge Site readiness into authoritative SystemManager

**Files:**
- Modify: `src/agt_system_manager/agt_system_manager/readiness.py`
- Modify: `src/agt_system_manager/scripts/system_manager_node.py`
- Modify: `tests/system_manager/test_readiness.py`
- Modify: `tests/system_manager/test_system_manager_source_contract.py`

**Interfaces:**
- Consumes: authoritative `/agt/maps/active` summary from `agt_site_runtime` plus existing system/localization/safety/chassis/mission evidence.
- Produces: fail-closed TaskReadiness/RobotState that understands active Site readiness without taking Site activation ownership.

- [ ] **Step 1: Freeze expected fail-closed cases in tests**

Keep existing blockers and add Site-owner cases so these conditions remain blocking:

```text
ACTIVE_MAP_UNKNOWN
ACTIVE_MAP_NOT_READY
LOCALIZATION_MAP_MISMATCH
```

The tests must also prove previously accepted safety/chassis/system blockers still work.

- [ ] **Step 2: Merge readiness logic additively**

Integrate Site identity/readiness fields from the Site-owner branch into the current P1 readiness evaluator. Do not replace the whole file with the older branch version if the P1 base has newer checks.

- [ ] **Step 3: Merge node subscriptions/read model additively**

Subscribe to the authoritative active-map topic and feed it into readiness aggregation while preserving all current P1 inputs and read services.

- [ ] **Step 4: Source-contract verification**

Ensure `agt_system_manager` still does not call Site activation services, shell commands, Nav2 commands, or velocity publishers.

Expected ownership:

```text
agt_site_runtime -> publishes active Site authority
agt_system_manager -> reads authority and evaluates readiness
```

---

### Task 5: Add P1-02 acceptance evidence and update convergence state

**Files:**
- Create: `docs/acceptance/2026-08-29-runtime-navigation-p1-02-site-runtime-integration.md`
- Modify: `docs/convergence/runtime-navigation-convergence-p1.md`

**Interfaces:**
- Consumes: integrated P1-02 source and available CI/static evidence.
- Produces: an auditable handoff into P1-03.

- [ ] **Step 1: Record exact imported source**

Acceptance report must include:

```text
source branch: feat/runtime-site-owner-p01
source commit: 3969b152157e20dddd479fb08f95a694aeb08681
canonical branch: feat/runtime-navigation-convergence-p1
```

- [ ] **Step 2: Record what was intentionally not imported**

Explicitly state that P1-03 Task Registry changes, P1-04 navigation binding, P1-05 Nav2 runtime readiness, field commissioning changes, and inspection changes are not part of P1-02.

- [ ] **Step 3: Record test evidence by level**

Use separate sections for:

```text
STATIC/unit
ROS 2 Humble
real vehicle
```

If ROS 2 or field tests have not run, mark them `NOT RUN`; never infer PASS.

- [ ] **Step 4: Update convergence table**

Mark P1-02 `Code [x]` only after the integrated source is committed. Mark `STATIC [x]` only when static/unit/CI evidence actually passes. Leave HUMBLE/FIELD unchecked unless separately verified.

- [ ] **Step 5: Commit boundary**

Create one integration commit (or a minimal small series) whose message clearly identifies P1-02, then stop before P1-03.

Suggested message:

```text
feat(runtime): integrate site runtime owner for p1
```

---

## Plan self-review

- Spec coverage: P1-02 preserves Site owner, Runtime Contracts, interfaces, SystemManager readiness, Gateway and hardware boundaries.
- Scope: Task Registry, Site-to-Navigation binding, Nav2 lifecycle readiness and field commissioning are intentionally excluded.
- Placeholder scan: no TBD/TODO or unspecified implementation steps remain.
- Type/interface consistency: this plan reuses the existing `MapVersionSummary`, `ValidateMapVersion.srv`, `/agt/maps/active`, and SystemManager readiness interfaces from the accepted source branches; no new P1-03/P1-05 types are introduced here.
