# Read-Only Site Runtime Owner P0.1 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add an installable Runtime contract library and a read-only `agt_site_runtime` owner that discovers deployed Site Packages, validates them, explicitly activates one version, persists only the selection, revalidates on restore, and owns `/agt/maps/active` fail-closed.

**Architecture:** Extract the existing repository contract validator into the installable, ROS-node-free `agt_runtime_contracts` package and leave `tools/runtime_contracts` as a compatibility wrapper. Build `agt_site_runtime` as pure domain components plus a thin ROS node. All state-changing activation operations are serialized and persist before publication. A no-active `STATE_UNKNOWN` tombstone is published when the owner must revoke previously cached authoritative state, so long-running consumers cannot retain a stale active map after an isolated owner restart.

**Tech Stack:** ROS 2 Humble, Python 3.10, ament_cmake/ament_cmake_python, rclpy, PyYAML, jsonschema, pytest, GitHub Actions source-contract CI.

**Spec:** `docs/superpowers/specs/2026-08-28-site-runtime-owner-design.md`

## Global Constraints

- Runtime consumes only deployed Site Packages; it never discovers V2/V2.5 workspaces.
- Site Package 1.0 remains read-only; no import/delete/archive/purge/pin/unpin capability is exposed.
- No automatic map selection and no fallback to another revision.
- Persist only `site_id` and `revision`; validity is always recomputed.
- Validation is fail-closed and has one canonical implementation.
- `/agt/maps/active` uses RELIABLE + TRANSIENT_LOCAL + depth 1.
- Failed runtime switching preserves the previous healthy active selection and publication.
- Startup restore failure must revoke stale authoritative state and leave SystemManager blocked.
- No Nav2/localization hot switching or process lifecycle orchestration in P0.1.
- Preserve the frozen P0 readiness semantics except for interpreting an explicit no-active tombstone as `ACTIVE_MAP_UNKNOWN`.
- No production code is added before its corresponding failing test/source contract has been observed.

---

### Task 1: Add the narrow ValidateMapVersion interface

**Files:**
- Create: `src/agt_interfaces/srv/ValidateMapVersion.srv`
- Modify: `src/agt_interfaces/CMakeLists.txt`
- Modify: `src/agt_interfaces/test/test_system_interfaces.py`

**Interfaces:**
- Produces: `agt_interfaces/srv/ValidateMapVersion`
- Request: `map_id: string`, `map_version_id: string`
- Response: `success`, `error_code`, `version`, `blocker_codes`, `blocker_messages`, `message`

- [ ] **Step 1: Write the failing interface contract**

Add assertions to `test_system_interfaces.py` that `ValidateMapVersion.srv` exists in the generated interface list and declares exactly the approved error constants and fields.

- [ ] **Step 2: Verify RED**

Run in cloud/source contract context:

```bash
python -m pytest -q tests/contracts src/agt_interfaces/test/test_system_interfaces.py
```

Expected: FAIL because `ValidateMapVersion.srv` is absent.

- [ ] **Step 3: Add the service definition and generator entry**

Create:

```text
string map_id
string map_version_id
---
uint16 ERROR_NONE=0
uint16 ERROR_INVALID_REQUEST=1
uint16 ERROR_NOT_FOUND=2
uint16 ERROR_VALIDATION_FAILED=3
uint16 ERROR_INTERNAL=255

bool success
uint16 error_code
agt_interfaces/MapVersionSummary version
string[] blocker_codes
string[] blocker_messages
string message
```

Add `"srv/ValidateMapVersion.srv"` to `rosidl_generate_interfaces`.

- [ ] **Step 4: Verify GREEN**

Run the interface/source tests available without ROS generation and later include `agt_interfaces` in the local ROS build gate.

- [ ] **Step 5: Commit**

```bash
git add src/agt_interfaces
git commit -m "feat(interfaces): add map validation service"
```

---

### Task 2: Extract the canonical validator into agt_runtime_contracts

**Files:**
- Create: `src/agt_runtime_contracts/agt_runtime_contracts/__init__.py`
- Create: `src/agt_runtime_contracts/agt_runtime_contracts/validator.py`
- Create: `src/agt_runtime_contracts/CMakeLists.txt`
- Create: `src/agt_runtime_contracts/package.xml`
- Create: `src/agt_runtime_contracts/README.md`
- Create: `src/agt_runtime_contracts/test/test_validator.py`
- Modify: `tools/runtime_contracts/validator.py`
- Modify: `tools/runtime_contracts/__init__.py`
- Modify: `.github/workflows/runtime-contracts.yml`
- Test: `tests/contracts/test_runtime_contracts.py`

**Interfaces:**
- Produces canonical Python API:

```python
@dataclass(frozen=True)
class ValidationIssue:
    code: str
    message: str

@dataclass(frozen=True)
class ValidationReport:
    ok: bool
    checks: tuple[str, ...] = ()
    issues: tuple[ValidationIssue, ...] = ()

def load_yaml(path: Path) -> dict[str, Any]: ...
def validate_vehicle_profile(path: Path, schema_path: Path) -> ValidationReport: ...
def validate_site_package(site_root: Path, schema_path: Path) -> ValidationReport: ...
def validate_runtime_contracts(vehicle_path: Path, site_root: Path,
                               vehicle_schema_path: Path,
                               site_schema_path: Path) -> ValidationReport: ...
def resolve_relative_path(site_root: Path, raw: str) -> Path: ...
def navigation_image_asset(site_root: Path, manifest: Mapping[str, Any]) -> tuple[str, Path]: ...
def load_hashes(site_root: Path, manifest: Mapping[str, Any]) -> dict[str, str]: ...
def sha256_file(path: Path) -> str: ...
```

- [ ] **Step 1: Write a failing canonical-import contract**

Add cloud tests that import `agt_runtime_contracts.validator` with `PYTHONPATH=src/agt_runtime_contracts`, run the existing valid and invalid Site fixtures, and assert the compatibility wrapper exports the same function objects/results.

- [ ] **Step 2: Verify RED**

Run:

```bash
PYTHONPATH=src/agt_runtime_contracts python -m pytest -q tests/contracts
```

Expected: FAIL because `agt_runtime_contracts` does not exist.

- [ ] **Step 3: Move the validator implementation into the installable package**

Copy behavior, not a second implementation. Publicize the safe path/hash helpers required by Site Runtime. Keep all existing blocker codes and existing contract-test behavior unchanged.

- [ ] **Step 4: Convert repository tooling to a compatibility wrapper**

`tools/runtime_contracts/validator.py` imports and re-exports the canonical package symbols. `tools/runtime_contracts/__init__.py` remains backward compatible.

- [ ] **Step 5: Install schema resources with the package**

Use `install(FILES ...)` so `site_package.schema.json` and `vehicle_profile.schema.json` are available under `share/agt_runtime_contracts/schemas`. Add a test/source assertion that installed schema content is sourced from the repository canonical schema files rather than an independent definition.

- [ ] **Step 6: Verify GREEN**

Run all existing contract tests with `PYTHONPATH=src/agt_runtime_contracts` and ensure the old CLI import path still works.

- [ ] **Step 7: Commit**

```bash
git add src/agt_runtime_contracts tools/runtime_contracts .github/workflows/runtime-contracts.yml tests/contracts
git commit -m "refactor(runtime): install canonical contract validator"
```

---

### Task 3: Implement Site Registry and identity validation

**Files:**
- Create: `src/agt_site_runtime/agt_site_runtime/__init__.py`
- Create: `src/agt_site_runtime/agt_site_runtime/models.py`
- Create: `src/agt_site_runtime/agt_site_runtime/registry.py`
- Create: `src/agt_site_runtime/agt_site_runtime/validator.py`
- Create: `src/agt_site_runtime/test/test_registry.py`
- Create: `src/agt_site_runtime/test/test_validator.py`

**Interfaces:**

```python
@dataclass(frozen=True, order=True)
class SiteKey:
    site_id: str
    revision: str

@dataclass(frozen=True)
class SiteCandidate:
    key: SiteKey
    root: Path
    manifest_path: Path

@dataclass(frozen=True)
class SiteValidation:
    candidate: SiteCandidate
    valid: bool
    blocker_codes: tuple[str, ...]
    blocker_messages: tuple[str, ...]

class SiteRegistry:
    def __init__(self, sites_root: Path): ...
    def scan(self) -> tuple[SiteCandidate, ...]: ...
    def resolve(self, key: SiteKey) -> SiteCandidate | None: ...

class SiteValidator:
    def __init__(self, vehicle_profile: Path,
                 vehicle_schema: Path,
                 site_schema: Path): ...
    def validate(self, candidate: SiteCandidate) -> SiteValidation: ...
```

- [ ] **Step 1: Write failing Registry tests**

Cover empty root, multiple deterministic `(site_id, revision)` ordering, unrelated hierarchy ignored, and exact resolution.

- [ ] **Step 2: Verify RED**

```bash
PYTHONPATH=src/agt_site_runtime:src/agt_runtime_contracts python -m pytest -q src/agt_site_runtime/test/test_registry.py
```

Expected: import/module failure.

- [ ] **Step 3: Implement minimal models and Registry**

Only discover `sites_root/<site_id>/<revision>/manifest.yaml`; do not validate content or auto-select.

- [ ] **Step 4: Verify Registry GREEN**

Run `test_registry.py`.

- [ ] **Step 5: Write failing SiteValidator tests**

Cover a valid fixture, directory/manifest `site.id` mismatch, revision mismatch, and stable mapping of low-level contract issues to:

```text
SITE_SCHEMA_INVALID
SITE_PATH_UNSAFE
SITE_ASSET_MISSING
SITE_HASH_MISSING
SITE_HASH_MISMATCH
SITE_VEHICLE_INCOMPATIBLE
SITE_NAVIGATION_MAP_INVALID
SITE_VALIDATION_FAILED
```

- [ ] **Step 6: Verify validator RED, implement, then GREEN**

`SiteValidator` must call `agt_runtime_contracts.validate_runtime_contracts` and separately enforce directory identity equality.

- [ ] **Step 7: Commit**

```bash
git add src/agt_site_runtime/agt_site_runtime src/agt_site_runtime/test
git commit -m "feat(site-runtime): add deployed site registry validation"
```

---

### Task 4: Implement immutable summary data and deterministic content identity

**Files:**
- Modify: `src/agt_site_runtime/agt_site_runtime/models.py`
- Create: `src/agt_site_runtime/agt_site_runtime/summary_builder.py`
- Create: `src/agt_site_runtime/test/test_summary_builder.py`

**Interfaces:**

```python
@dataclass(frozen=True)
class SiteSummary:
    map_id: str
    map_version_id: str
    state: int
    active: bool
    valid: bool
    map_hash: str
    manifest_sha256: str
    navigation_yaml_sha256: str
    navigation_image_sha256: str
    localization_pcd_sha256: str
    navigation_yaml: str
    localization_pcd: str
    processing_record: str
    tasks_directory: str
    validation_errors: tuple[str, ...]
    validation_warnings: tuple[str, ...]

def build_site_summary(candidate: SiteCandidate,
                       validation: SiteValidation,
                       *, active: bool) -> SiteSummary: ...
```

The ROS node later converts `SiteSummary` into `MapVersionSummary`, keeping ROS types out of the pure domain model.

- [ ] **Step 1: Write failing summary tests**

Assert READY/INVALID semantics, validated absolute paths, exact individual digest fields, `tasks_directory == ""`, and deterministic `map_hash` from manifest SHA plus sorted effective asset digest lines.

- [ ] **Step 2: Verify RED**

Run `test_summary_builder.py`; expected module/function absence.

- [ ] **Step 3: Implement minimal summary builder**

Reuse canonical safe path/hash helpers. Never publish a path that has not passed containment validation.

- [ ] **Step 4: Verify GREEN and determinism**

Run the test twice and assert a fixture copy with one protected byte changed produces a different `map_hash` and fails validation before it can become READY.

- [ ] **Step 5: Commit**

```bash
git add src/agt_site_runtime/agt_site_runtime/models.py src/agt_site_runtime/agt_site_runtime/summary_builder.py src/agt_site_runtime/test/test_summary_builder.py
git commit -m "feat(site-runtime): build validated site summaries"
```

---

### Task 5: Implement atomic active-selection persistence

**Files:**
- Create: `src/agt_site_runtime/agt_site_runtime/activation_store.py`
- Create: `src/agt_site_runtime/test/test_activation_store.py`

**Interfaces:**

```python
@dataclass(frozen=True)
class ActiveSelection:
    site_id: str
    revision: str

class ActivationStore:
    def __init__(self, state_root: Path): ...
    @property
    def path(self) -> Path: ...
    def load(self) -> ActiveSelection | None: ...
    def save(self, selection: ActiveSelection) -> None: ...
```

- [ ] **Step 1: Write failing persistence tests**

Cover no file, valid load, malformed YAML/shape treated as a typed `ActivationStoreError`, exact persisted keys only, and atomic replacement failure preserving the old file.

- [ ] **Step 2: Verify RED**

Run `test_activation_store.py`; expected import/module failure.

- [ ] **Step 3: Implement atomic save**

Write YAML to a sibling temporary file, flush, `os.fsync`, then `os.replace`. Clean up an uncommitted temp file on error and never delete the old active file before successful replacement.

- [ ] **Step 4: Verify GREEN**

Run the persistence tests.

- [ ] **Step 5: Commit**

```bash
git add src/agt_site_runtime/agt_site_runtime/activation_store.py src/agt_site_runtime/test/test_activation_store.py
git commit -m "feat(site-runtime): persist active site selection atomically"
```

---

### Task 6: Implement pure activation/restore policy and no-active tombstone semantics

**Files:**
- Create: `src/agt_site_runtime/agt_site_runtime/runtime_policy.py`
- Create: `src/agt_site_runtime/test/test_runtime_policy.py`
- Modify: `src/agt_system_manager/agt_system_manager/readiness.py` only if needed by message-level semantics
- Modify: `src/agt_system_manager/scripts/system_manager_node.py`
- Modify: `src/agt_system_manager/test/test_readiness_core.py`

**Interfaces:**

```python
@dataclass(frozen=True)
class ActivationResult:
    success: bool
    error_code: int
    summary: SiteSummary | None
    blocker_codes: tuple[str, ...]
    blocker_messages: tuple[str, ...]
    message: str

class SiteRuntimePolicy:
    def list_versions(self, map_id: str = "", state: int = 0) -> tuple[SiteSummary, ...]: ...
    def validate(self, key: SiteKey) -> ActivationResult: ...
    def activate(self, key: SiteKey, client_request_id: str) -> ActivationResult: ...
    def restore(self) -> ActivationResult: ...
    @property
    def active_summary(self) -> SiteSummary | None: ...
```

- [ ] **Step 1: Write failing policy tests**

Cover explicit activation only; valid activate persists then becomes active; failed switch preserves previous active; startup restore revalidates; invalid restore does not fallback; same request id/same target is idempotent; same request id/different target is rejected; bounded request cache.

- [ ] **Step 2: Add the stale-cache revocation test**

Model the owner restarting while a consumer still has a previous active snapshot. The policy must surface `active_summary=None` on failed restore and instruct the ROS adapter to publish a no-active tombstone (`STATE_UNKNOWN`, `active=false`, `valid=false`) to revoke the previous authority.

- [ ] **Step 3: Verify RED**

Run `test_runtime_policy.py`; expected module/function failure.

- [ ] **Step 4: Implement minimal policy**

Activation order is validate -> build summary -> persist -> replace in-memory active. Serialization is handled by one `RLock`; no database or distributed lock.

- [ ] **Step 5: Update SystemManager tombstone interpretation test-first**

Add a ROS-independent/source-level assertion that an explicit `MapVersionSummary.STATE_UNKNOWN` / `active=false` snapshot is treated as no authoritative active map, yielding `ACTIVE_MAP_UNKNOWN`, not READY.

- [ ] **Step 6: Verify GREEN**

Run Site Runtime pure tests plus SystemManager core/source tests.

- [ ] **Step 7: Commit**

```bash
git add src/agt_site_runtime src/agt_system_manager
git commit -m "feat(site-runtime): add fail-closed activation policy"
```

---

### Task 7: Add the ROS package/node, QoS, services, and source contracts

**Files:**
- Create: `src/agt_site_runtime/CMakeLists.txt`
- Create: `src/agt_site_runtime/package.xml`
- Create: `src/agt_site_runtime/scripts/site_runtime_node.py`
- Create: `src/agt_site_runtime/launch/site_runtime.launch.py`
- Create: `src/agt_site_runtime/config/site_runtime.yaml`
- Create: `src/agt_site_runtime/README.md`
- Create: `tests/site_runtime/test_site_runtime_source_contract.py`
- Modify: `.github/workflows/runtime-contracts.yml`

**Interfaces:**
- Publishes: `/agt/maps/active` (`MapVersionSummary`, RELIABLE, TRANSIENT_LOCAL, depth 1)
- Services: `/agt/maps/list`, `/agt/maps/validate`, `/agt/maps/activate`
- Does not create a `ManageMapVersion` service.

- [ ] **Step 1: Write failing source contract**

AST/text assertions require exact topic/service names, transient-local QoS, generated executable-copy install pattern for symlink-install safety, and absence of import/delete/archive/purge endpoints.

- [ ] **Step 2: Verify RED in GitHub Actions**

Add a `Run runtime site-owner contracts` workflow step and observe failure before the package/node exists.

- [ ] **Step 3: Implement the ROS adapter**

The node converts pure `SiteSummary` to `MapVersionSummary`, restores at startup, publishes a no-active tombstone when restore state must revoke stale authority, implements List/Validate/Activate response mapping, and logs concise operator-safe messages.

- [ ] **Step 4: Add package/config/launch/install behavior**

Use the already-proven generated executable-copy pattern so `ros2 run/launch` works under `--symlink-install` even when repository API-created scripts arrive mode 0644.

- [ ] **Step 5: Verify GREEN in cloud source contracts**

Require all Runtime Contracts stages to pass.

- [ ] **Step 6: Commit**

```bash
git add src/agt_site_runtime tests/site_runtime .github/workflows/runtime-contracts.yml
git commit -m "feat(site-runtime): expose read-only site owner"
```

---

### Task 8: Local ROS integration and P0.1 acceptance

**Files:**
- Create: `docs/acceptance/2026-08-28-runtime-site-owner-p01.md`

**Interfaces:** End-to-end deployment behavior.

- [ ] **Step 1: Local build gate**

On Ubuntu 22.04 / ROS 2 Humble:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-select \
  agt_interfaces agt_runtime_contracts agt_site_runtime agt_system_manager
```

Expected: zero build failures.

- [ ] **Step 2: Local package tests**

```bash
source install/setup.bash
colcon test --packages-select \
  agt_interfaces agt_runtime_contracts agt_site_runtime agt_system_manager \
  --event-handlers console_direct+
colcon test-result --verbose
```

Expected: zero test failures.

- [ ] **Step 3: No-selection smoke**

Start Site Runtime against a temporary deployed sites root with no `active_site.yaml`. `list` shows READY candidates, but SystemManager remains `ACTIVE_MAP_UNKNOWN` and no READY active map is published.

- [ ] **Step 4: Explicit activation smoke**

Call `/agt/maps/activate` for a valid Site. Verify `/agt/maps/active` immediately returns the READY active summary to a late subscriber and SystemManager clears only `ACTIVE_MAP_UNKNOWN` while remaining blocked on missing localization/safety/chassis/sensor evidence.

- [ ] **Step 5: Restart restore smoke**

Restart Site Runtime without touching persisted selection. Verify full revalidation and active restoration.

- [ ] **Step 6: Corrupt-then-restart smoke**

Corrupt one integrity-protected asset, restart only Site Runtime while SystemManager remains running, and verify the no-active tombstone removes stale authority and SystemManager returns to `ACTIVE_MAP_UNKNOWN` / `ready=false` with no fallback.

- [ ] **Step 7: Failed-switch preservation smoke**

Restore a valid active Site, request activation of an invalid Site, and verify the existing valid active summary and persisted selection remain unchanged.

- [ ] **Step 8: Final cloud verification**

Require the branch-head Runtime Contracts workflow to be green after the acceptance record commit.

- [ ] **Step 9: Freeze acceptance**

Record exact commits, cloud run IDs, local build/test counts, service outputs, and any remaining non-blocking limitations. Do not merge or open a PR unless explicitly requested.
