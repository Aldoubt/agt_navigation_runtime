# P1-03 Task Registry Decoupling Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Move all mutable Task/Task-route binding authority out of immutable Site/map assets into one canonical `runtime/tasks` tree while preserving existing TaskGroup, ROS service and ExecuteWaypointTask public schemas.

**Architecture:** Keep existing `map_id` / `map_version_id` field names as compatibility aliases for Site `id` / `revision`, so HMI, Gateway and Mission callers do not need a schema migration in P1-03. `TaskRegistry` receives one validated Site-binding resolver, persists tasks under `tasks_root/<site>/<revision>/`, writes an immutable-Site binding sidecar containing the active Site content identity, and rejects any operation whose Site identity/hashes no longer match. Editing resolves deployed Site packages from `sites_root`; execution resolves the same task store against the authoritative `/agt/maps/active` snapshot. Legacy map-tree tasks are never read implicitly and require an explicit import tool.

**Tech Stack:** ROS 2 Humble, Python 3.10, rclpy, ament/pytest, Site Runtime/Runtime Contracts, JSON/YAML, SHA256.

**Spec:** `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

## Global Constraints

- Work only on `feat/runtime-navigation-convergence-p1`.
- P1-03 must not change TaskGroup schema version 1 or public ROS Task service / ExecuteWaypointTask request fields.
- `map_id` and `map_version_id` remain public compatibility field names but semantically bind to Site `site.id` and `site.revision`.
- Mutable task files must live only below an explicit `tasks_root`, defaulting to `runtime/tasks`.
- Site Package files below `sites_root` remain read-only and must never be mutated by Task Registry operations.
- Existing revision monotonicity, `content_sha256`, idempotent client request IDs, atomic write/rollback, path traversal and symlink protections remain fail-closed.
- A validated Site identity/content mismatch must block task read/write/execution.
- No implicit fallback to the legacy `runtime/maps/<map>/versions/<version>/tasks` tree is allowed.
- ROUTE task binding YAML is mutable task metadata and therefore moves with the task store; immutable Route Assets are not redesigned in P1-03.
- P1-04 Site-to-Navigation bootstrap and P1-05 Nav2 runtime readiness are out of scope.

---

## File Structure Locked by This Plan

### New files

- `src/agt_navigation/agt_navigation/site_task_binding.py` — pure Site binding model + deployed-Site resolver adapter.
- `src/agt_navigation/scripts/import_legacy_tasks.py` — explicit one-way legacy task import tool.
- `src/agt_navigation/test/test_site_task_binding.py` — binding/resolver contract tests.
- `src/agt_navigation/test/test_legacy_task_import.py` — explicit migration behavior tests.
- `tests/navigation/test_task_storage_source_contract.py` — no-ROS source guard against old production task-write paths.
- `docs/acceptance/2026-08-29-runtime-navigation-p1-03-task-registry-decoupling.md` — slice evidence.

### Modified files

- `src/agt_navigation/agt_navigation/task_registry.py` — canonical mutable store rooted at `tasks_root`.
- `src/agt_navigation/agt_navigation/task_group.py` — `TaskRepository` points to the same mutable task root instead of immutable map version assets.
- `src/agt_navigation/agt_navigation/route_task_binding.py` — separate mutable task-binding root from immutable route-asset root.
- `src/agt_navigation/scripts/task_registry_node.py` — deployed Site resolver + `tasks_root` parameters.
- `src/agt_navigation/scripts/waypoint_task_server.py` — execution registry uses `tasks_root` and active-Site binding resolver.
- `src/agt_navigation/scripts/navigation_capability_server.py` — ROUTE binding lookup uses `tasks_root`.
- `src/agt_navigation/launch/navigation.launch.py` — forwards `tasks_root` / `sites_root` / Site validation configuration without changing existing public navigation actions.
- `src/agt_navigation/CMakeLists.txt` — installs import tool and registers new tests.
- `src/agt_navigation/package.xml` — declares runtime dependency needed by deployed-Site resolver.
- `src/agt_navigation/test/test_task_registry.py` — tests new store and binding invariants.
- `src/agt_navigation/test/test_route_task_binding.py` — tests mutable binding root separation.
- `.github/workflows/runtime-contracts.yml` — add focused no-ROS P1 navigation storage contract gate.
- `docs/convergence/runtime-navigation-convergence-p1.md` — advance status after evidence passes.

---

### Task 1: Add validated Site binding model and resolver

**Files:**
- Create: `src/agt_navigation/agt_navigation/site_task_binding.py`
- Create: `src/agt_navigation/test/test_site_task_binding.py`

**Interfaces:**
- Produces immutable dataclass `ValidatedSiteBinding`.
- Produces callable protocol-compatible resolver `FilesystemSiteBindingResolver.__call__(map_id: str, map_version_id: str) -> ValidatedSiteBinding`.
- Consumes accepted `agt_site_runtime.SiteRegistry`, `SiteValidator`, `build_site_summary` and installed `agt_runtime_contracts` schemas lazily.

- [ ] **Step 1: Write RED tests for normalized binding identity**

Require a binding with exactly these persisted fields:

```python
ValidatedSiteBinding(
    map_id="orchard_a",
    map_version_id="r01",
    map_hash="sha256:<64hex>",
    manifest_sha256="sha256:<64hex>",
    navigation_yaml_sha256="sha256:<64hex>",
    navigation_image_sha256="sha256:<64hex>",
    localization_pcd_sha256="sha256:<64hex>",
)
```

Tests must reject empty identities and malformed digests.

- [ ] **Step 2: Write RED tests for deployed Site resolution**

Use a stub Site Runtime adapter or injected resolver seam to prove:

```text
missing Site -> MAP_NOT_READY
invalid Site -> MAP_NOT_READY with stable blocker detail
identity mismatch -> MAP_VERSION_MISMATCH
valid Site -> exact ValidatedSiteBinding
```

The pure test must not require a ROS graph.

- [ ] **Step 3: Implement minimal binding model and filesystem resolver**

Hash normalization rule:

```python
def normalize_sha256(value: str) -> str:
    # accept canonical source values with or without `sha256:`
    # return exactly `sha256:<64 lowercase hex>`
```

The resolver must never mutate Site files.

- [ ] **Step 4: Run focused tests**

```bash
PYTHONPATH=src/agt_navigation:src/agt_site_runtime:src/agt_runtime_contracts \
python -m pytest -q \
  src/agt_navigation/test/test_site_task_binding.py
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git commit -m "feat(navigation): add validated site task binding"
```

---

### Task 2: Move TaskRegistry storage to `tasks_root`

**Files:**
- Modify: `src/agt_navigation/agt_navigation/task_registry.py`
- Modify: `src/agt_navigation/test/test_task_registry.py`

**Interfaces:**
- Constructor becomes:

```python
TaskRegistry(
    tasks_root: str | Path,
    *,
    site_binding_resolver: Callable[[str, str], ValidatedSiteBinding],
    maximum_task_bytes: int = 1024 * 1024,
    backup_count: int = 5,
    recent_request_limit: int = 256,
)
```

- Canonical directory:

```text
<tasks_root>/<map_id>/<map_version_id>/
  site_binding.json
  task_index.json
  <task_group_id>.json
  <task_group_id>.route.yaml
  archive/
```

- [ ] **Step 1: Rewrite tests to require separate immutable Site and mutable task roots**

Test fixture must have different paths:

```text
sites_root/orchard_a/r01/...   # read-only fixture identity only
tasks_root/orchard_a/r01/...   # mutable output
```

Core unit tests may use a fake `site_binding_resolver` so no ROS/Site Runtime import is required.

- [ ] **Step 2: Add RED test proving no Site mutation**

Snapshot every file below the fake Site root before `put_task`, update and archive, then assert byte-for-byte equality afterward.

Also assert no directory named `tasks` is created below the Site root.

- [ ] **Step 3: Add RED binding-sidecar tests**

First successful operation writes canonical `site_binding.json` atomically.

A later resolver result with a different `map_hash`, manifest hash, nav/image/PCD hash or identity must fail closed with `TASK_SITE_BINDING_MISMATCH` and must not modify task files.

- [ ] **Step 4: Implement new path helpers**

Replace old `_version_root()` / `_manifest()` ownership with:

```python
_task_version_root(map_id, map_version_id)
_resolve_site_binding(map_id, map_version_id)
_validate_or_write_binding(map_id, map_version_id, binding)
_tasks_root boundary checks
```

No runtime read of legacy map manifests is permitted.

- [ ] **Step 5: Preserve all existing transaction behavior**

Keep:

```text
revision conflict
content hash validation
duplicate request handling
backup rotation
atomic writes
index rollback
archive rollback
symlink/path escape rejection
```

Archive relative paths are relative to the new task-version root.

- [ ] **Step 6: Run task registry suite**

```bash
PYTHONPATH=src/agt_navigation \
python -m pytest -q src/agt_navigation/test/test_task_registry.py
```

Expected: PASS.

- [ ] **Step 7: Commit**

```bash
git commit -m "refactor(navigation): decouple task registry from site assets"
```

---

### Task 3: Make every task writer use the same mutable root

**Files:**
- Modify: `src/agt_navigation/agt_navigation/task_group.py`
- Modify: `src/agt_navigation/test/test_task_group.py`
- Create: `tests/navigation/test_task_storage_source_contract.py`

**Interfaces:**
- `TaskRepository` constructor first argument semantically becomes `tasks_root`.
- Directory is exactly `<tasks_root>/<map_id>/<map_version_id>`.

- [ ] **Step 1: Add RED source guard**

Fail when production Task persistence code contains any active write path equivalent to:

```text
/maps/<id>/versions/<version>/tasks
```

The test must cover at least `task_registry.py` and `task_group.py` and must not flag documentation/examples.

- [ ] **Step 2: Update TaskRepository tests**

Require save/load/index behavior below the mutable root and verify map/Site assets remain untouched.

- [ ] **Step 3: Change TaskRepository only as necessary**

Do not redesign TaskGroup schema or its map-binding validation.

- [ ] **Step 4: Run tests**

```bash
PYTHONPATH=src/agt_navigation python -m pytest -q \
  src/agt_navigation/test/test_task_group.py \
  tests/navigation/test_task_storage_source_contract.py
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git commit -m "refactor(navigation): unify mutable task repository root"
```

---

### Task 4: Wire edit services to deployed Site validation

**Files:**
- Modify: `src/agt_navigation/scripts/task_registry_node.py`
- Modify: `src/agt_navigation/launch/navigation.launch.py`
- Modify: `src/agt_navigation/package.xml`
- Modify: `src/agt_navigation/CMakeLists.txt`

**Interfaces:**
- New node parameters:

```text
tasks_root              default "" -> <runtime_dir>/tasks
sites_root              default "/opt/agt/sites"
site_vehicle_profile    default "/opt/agt/profiles/bunker.yaml"
```

- Schema paths resolve from installed `agt_runtime_contracts/share/.../schemas`.
- Existing Task service names and request/response definitions remain unchanged.

- [ ] **Step 1: Add source/launch RED assertions**

Assert `task_registry_node.py` no longer constructs `TaskRegistry(maps_root)` and `navigation.launch.py` declares/forwards `tasks_root` and Site resolver inputs.

- [ ] **Step 2: Instantiate FilesystemSiteBindingResolver lazily**

Node startup may create the resolver object when files are absent; absence must fail a task operation with a stable TaskRegistry error rather than crash unrelated offline navigation startup.

- [ ] **Step 3: Keep public services unchanged**

Do not modify:

```text
/agt/navigation/tasks/list
/agt/navigation/tasks/get
/agt/navigation/tasks/put
/agt/navigation/tasks/archive
```

- [ ] **Step 4: Register package dependency and tests**

Declare `agt_runtime_contracts` and `agt_site_runtime` runtime dependencies needed by the edit-service resolver, without adding a dependency from Site Runtime back to Navigation.

- [ ] **Step 5: Run source tests / compile guard**

Expected: no import cycle, no old Registry constructor remains in edit node.

- [ ] **Step 6: Commit**

```bash
git commit -m "feat(navigation): validate task edits against deployed sites"
```

---

### Task 5: Wire execution to the authoritative active Site

**Files:**
- Modify: `src/agt_navigation/scripts/waypoint_task_server.py`
- Modify: `src/agt_navigation/test/test_waypoint_task_server.py`
- Modify: `src/agt_navigation/test/test_navigation_capability_runtime_gates.py`

**Interfaces:**
- New `tasks_root` parameter defaults to `<runtime_dir>/tasks`.
- `TaskRegistry` execution resolver derives `ValidatedSiteBinding` from the current authoritative `MapVersionSummary` already received on `/agt/maps/active`.

- [ ] **Step 1: Add RED tests for active-Site-only task resolution**

Require:

```text
no active Site -> MAP_NOT_READY
inactive/invalid/non-READY Site -> MAP_NOT_READY
requested id/revision != active Site -> MAP_VERSION_MISMATCH
active Site exact match -> registry may resolve task
changed active Site map_hash -> stored task binding rejected
```

- [ ] **Step 2: Implement `_resolve_active_site_binding()`**

Build `ValidatedSiteBinding` from:

```text
MapVersionSummary.map_id
map_version_id
map_hash
manifest_sha256
navigation_yaml_sha256
navigation_image_sha256
localization_pcd_sha256
```

Do not make execution call `/agt/maps/validate`; `/agt/maps/active` is already the authoritative snapshot.

- [ ] **Step 3: Instantiate execution TaskRegistry on `tasks_root`**

No execution fallback to legacy map-tree tasks is allowed.

- [ ] **Step 4: Run focused execution tests**

```bash
PYTHONPATH=src/agt_navigation python -m pytest -q \
  src/agt_navigation/test/test_waypoint_task_server.py \
  src/agt_navigation/test/test_navigation_capability_runtime_gates.py
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git commit -m "fix(navigation): bind task execution to active site"
```

---

### Task 6: Move mutable ROUTE task bindings without redesigning Route Assets

**Files:**
- Modify: `src/agt_navigation/agt_navigation/route_task_binding.py`
- Modify: `src/agt_navigation/scripts/navigation_capability_server.py`
- Modify: `src/agt_navigation/test/test_route_task_binding.py`
- Modify: `src/agt_navigation/test/test_navigation_capability_server.py`

**Interfaces:**
- Resolver constructor becomes conceptually:

```python
RouteTaskResolver(route_assets_root, tasks_root)
```

- Mutable binding path:

```text
<tasks_root>/<map_id>/<map_version_id>/<task_group_id>.route.yaml
```

- Immutable route asset resolution remains on the existing route-assets/map root for P1-03.

- [ ] **Step 1: Add RED path-separation test**

Put the `.route.yaml` only under `tasks_root`; put route manifest/data only under route-assets root. Resolver must succeed only with both present and hash-bound.

- [ ] **Step 2: Reject old mutable binding location**

A binding that exists only under legacy `<maps_root>/.../tasks/` must not opt a task into ROUTE execution.

- [ ] **Step 3: Update capability server binding lookup**

Use `self.tasks_root` for `_route_binding_path()` and construct `RouteTaskResolver(self.maps_root, self.tasks_root)`.

- [ ] **Step 4: Run ROUTE suites**

```bash
PYTHONPATH=src/agt_navigation python -m pytest -q \
  src/agt_navigation/test/test_route_task_binding.py \
  src/agt_navigation/test/test_navigation_capability_server.py \
  src/agt_navigation/test/test_v25_10_route_correction_generation.py
```

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git commit -m "refactor(navigation): move route task bindings to task store"
```

---

### Task 7: Add explicit legacy task import and forbid implicit dual authority

**Files:**
- Create: `src/agt_navigation/scripts/import_legacy_tasks.py`
- Create: `src/agt_navigation/test/test_legacy_task_import.py`
- Modify: `src/agt_navigation/CMakeLists.txt`
- Modify: `tests/navigation/test_task_storage_source_contract.py`

**Interfaces:**
- Tool accepts explicit legacy source root + destination tasks root + exact Site id/revision.
- It imports through `TaskRegistry.put_task()` so schema/hash/Site checks remain authoritative.
- It never deletes source files.

- [ ] **Step 1: Add RED migration tests**

Require:

```text
explicit old task JSON import -> new tasks_root
source unchanged
existing destination with conflicting revision -> reject
symlink source -> reject
missing/invalid Site binding -> reject
legacy path is never read by TaskRegistry without calling import tool
```

- [ ] **Step 2: Implement import utility**

Import task JSONs in deterministic lexical order. Copy optional matching `.route.yaml` only when the destination does not exist and the source is a regular non-symlink file; do not claim Route Asset validity during import.

- [ ] **Step 3: Install the tool**

Add it to the generated executable list using the existing executable-permission pattern.

- [ ] **Step 4: Run migration/source guard tests**

Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git commit -m "feat(navigation): add explicit legacy task import"
```

---

### Task 8: Add canonical cloud gate for P1-03 and record acceptance

**Files:**
- Modify: `.github/workflows/runtime-contracts.yml`
- Create: `docs/acceptance/2026-08-29-runtime-navigation-p1-03-task-registry-decoupling.md`
- Modify: `docs/convergence/runtime-navigation-convergence-p1.md`

**Interfaces:**
- Produces repeatable no-ROS P1-03 CI evidence on the canonical branch.

- [ ] **Step 1: Add navigation task-storage CI step**

Run the no-ROS subset that does not import rclpy/Nav2:

```bash
PYTHONPATH=src/agt_navigation:src/agt_site_runtime:src/agt_runtime_contracts \
python -m pytest -q \
  src/agt_navigation/test/test_site_task_binding.py \
  src/agt_navigation/test/test_task_registry.py \
  src/agt_navigation/test/test_task_group.py \
  src/agt_navigation/test/test_route_task_binding.py \
  src/agt_navigation/test/test_legacy_task_import.py \
  tests/navigation/test_task_storage_source_contract.py
```

Do not add ROS-only tests to a cloud job that does not install ROS.

- [ ] **Step 2: Let canonical branch CI run and inspect every step**

Hard gate: Runtime Contracts including the new P1 navigation storage step concludes `success`.

- [ ] **Step 3: Write acceptance report**

Record exact commits, changed interfaces, CI run ID, what is and is not ROS2 Humble verified, and prove Site files were not mutated by unit tests.

- [ ] **Step 4: Advance convergence table**

Mark:

```text
P1-03 Code   [x]
P1-03 STATIC [x]
P1-03 HUMBLE [ ] unless separately run
```

Set the only next development slice to P1-04.

- [ ] **Step 5: Stop**

Do not begin P1-04 in the same implementation slice before P1-03 acceptance is recorded.

---

## Plan self-review

- Spec coverage: mutable tasks are outside Site assets; exact Site identity/content is bound; no implicit old-tree authority; public Task/Action schemas remain stable; ROUTE mutable binding is included; explicit migration exists.
- Scope check: no Site-to-Nav lifecycle work, no Nav2 readiness work, no HMI schema migration, no Route Asset redesign.
- Placeholder scan: no TBD/TODO or unspecified implementation actions remain.
- Type consistency: all task writers/readers use `tasks_root/<map_id>/<map_version_id>`; external compatibility names stay `map_id` / `map_version_id`; persisted Site binding uses the exact content identity fields already present in `MapVersionSummary`.
