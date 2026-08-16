# V3-01 Runtime Contracts Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add versioned Vehicle Profile and deployable Site Package contracts plus a fail-closed, ROS-independent validator and CI while preserving the current runtime package behavior

**Architecture:** Keep existing `profiles/platforms/*.yaml` as the canonical vehicle source, add JSON Schema Draft 2020-12 files for structural validation, and implement cross-file/path/hash/compatibility rules in a small Python module. Use pure-Python fixtures and GitHub Actions so the contract layer can be validated without ROS

**Tech Stack:** Python 3, PyYAML, jsonschema, pytest, JSON Schema Draft 2020-12, GitHub Actions

## Global Constraints

- `schema_version` for Vehicle Profiles is exactly `"1.0"`
- `site_schema_version` for Site Packages is exactly `"1.0"`
- Existing `profiles/platforms/` remains canonical; no parallel vehicle tree
- `agt_mapping` is not renamed or behaviorally refactored in V3-01
- Site asset paths must be relative, must not contain traversal outside the package root, and must not depend on V2.5 source/install paths
- Validation is fail-closed and returns non-zero on contract failure
- Validator code has no ROS dependency
- Existing algorithm, Nav2, localization, BT, safety, and chassis behavior is unchanged

---

## File Structure

- Create `docs/architecture/runtime_boundary.md` — runtime package ownership and V2.5/V3 boundary
- Create `docs/architecture/vehicle_profile_contract.md` — Vehicle Profile 1.0 semantics
- Create `docs/architecture/site_package_contract.md` — Site Package 1.0 semantics
- Create `schemas/vehicle_profile.schema.json` — structural Vehicle Profile schema
- Create `schemas/site_package.schema.json` — structural Site Package manifest schema
- Create `tools/runtime_contracts/__init__.py` — public validator exports
- Create `tools/runtime_contracts/validator.py` — YAML loading, schema, path, integrity, compatibility checks
- Create `tools/validate_runtime_contracts.py` — CLI only
- Create `tests/contracts/test_runtime_contracts.py` — behavior tests
- Create `tests/contracts/fixtures/site_valid/**` — positive fixture
- Create `tests/contracts/fixtures/site_absolute_path/**` — invalid path fixture
- Create `tests/contracts/fixtures/site_hash_mismatch/**` — invalid integrity fixture
- Create `tests/contracts/fixtures/site_incompatible_vehicle/**` — incompatible vehicle fixture
- Create `requirements-contracts.txt` — pinned minimum Python validation dependencies
- Create `.github/workflows/runtime-contracts.yml` — lightweight contract CI
- Modify `profiles/platforms/mk_mini.yaml` — add `schema_version: "1.0"` only
- Modify `README.md` — document contract validation entry point

---

### Task 1: Freeze contract documentation and schemas

**Files:**
- Create: `docs/architecture/runtime_boundary.md`
- Create: `docs/architecture/vehicle_profile_contract.md`
- Create: `docs/architecture/site_package_contract.md`
- Create: `schemas/vehicle_profile.schema.json`
- Create: `schemas/site_package.schema.json`
- Modify: `profiles/platforms/mk_mini.yaml`

**Interfaces:**
- Consumes: approved V3-01 design
- Produces: exact schema field names consumed by `validator.py` and tests

- [ ] **Step 1: Add schema-version assertion test for the real MK-mini profile**

```python
def test_real_mk_mini_profile_declares_v1_schema(repo_root):
    profile = load_yaml(repo_root / "profiles/platforms/mk_mini.yaml")
    assert profile["schema_version"] == "1.0"
```

- [ ] **Step 2: Run the test and verify it fails because `schema_version` is absent**

Run: `pytest -q tests/contracts/test_runtime_contracts.py::test_real_mk_mini_profile_declares_v1_schema`
Expected: FAIL with missing `schema_version`

- [ ] **Step 3: Add `schema_version: "1.0"` and the two JSON schemas**

Vehicle schema must require common identity/frame/geometry/limits fields and conditionally require Ackermann wheelbase + minimum turning radius

Site schema must require site identity, global frame, asset paths, compatibility vehicle ids, and hashes file path

- [ ] **Step 4: Run the schema-version test and verify it passes**

Run: `pytest -q tests/contracts/test_runtime_contracts.py::test_real_mk_mini_profile_declares_v1_schema`
Expected: PASS

- [ ] **Step 5: Commit**

```bash
git add docs/architecture schemas profiles/platforms/mk_mini.yaml tests/contracts/test_runtime_contracts.py
git commit -m "feat(v3-01): freeze runtime contract schemas"
```

### Task 2: Implement structural Vehicle Profile validation

**Files:**
- Create: `tools/runtime_contracts/__init__.py`
- Create: `tools/runtime_contracts/validator.py`
- Test: `tests/contracts/test_runtime_contracts.py`
- Create: `requirements-contracts.txt`

**Interfaces:**
- Produces: `load_yaml(path: Path) -> dict`
- Produces: `validate_vehicle_profile(path: Path, schema_path: Path) -> ValidationReport`
- Produces: `ValidationIssue(code: str, message: str)`
- Produces: `ValidationReport(ok: bool, checks: tuple[str, ...], issues: tuple[ValidationIssue, ...])`

- [ ] **Step 1: Write failing test validating the real MK-mini profile**

```python
def test_real_mk_mini_profile_passes_vehicle_schema(repo_root):
    report = validate_vehicle_profile(
        repo_root / "profiles/platforms/mk_mini.yaml",
        repo_root / "schemas/vehicle_profile.schema.json",
    )
    assert report.ok, report.issues
```

- [ ] **Step 2: Run and verify RED because `validate_vehicle_profile` does not exist**

Run: `pytest -q tests/contracts/test_runtime_contracts.py::test_real_mk_mini_profile_passes_vehicle_schema`
Expected: FAIL on missing import/function

- [ ] **Step 3: Implement minimal loader, report types, and jsonschema validation**

`load_yaml` must reject non-mapping YAML roots. `validate_vehicle_profile` must surface stable `VEHICLE_SCHEMA` issues rather than uncaught exceptions

- [ ] **Step 4: Run and verify GREEN**

Run: `pytest -q tests/contracts/test_runtime_contracts.py::test_real_mk_mini_profile_passes_vehicle_schema`
Expected: PASS

- [ ] **Step 5: Commit**

```bash
git add tools/runtime_contracts requirements-contracts.txt tests/contracts/test_runtime_contracts.py
git commit -m "feat(v3-01): validate vehicle profiles"
```

### Task 3: Implement Site Package structure and path containment validation

**Files:**
- Modify: `tools/runtime_contracts/validator.py`
- Test: `tests/contracts/test_runtime_contracts.py`
- Create: `tests/contracts/fixtures/site_valid/manifest.yaml`
- Create: `tests/contracts/fixtures/site_absolute_path/manifest.yaml`
- Add fixture asset placeholder files under each fixture

**Interfaces:**
- Produces: `validate_site_package(site_root: Path, schema_path: Path) -> ValidationReport`
- Internal: `_resolve_relative_path(site_root: Path, raw: str) -> Path`

- [ ] **Step 1: Write failing tests for a valid relative path package and an absolute path package**

```python
def test_site_relative_paths_pass(repo_root):
    report = validate_site_package(
        repo_root / "tests/contracts/fixtures/site_valid",
        repo_root / "schemas/site_package.schema.json",
    )
    assert report.ok, report.issues


def test_site_absolute_asset_path_fails_closed(repo_root):
    report = validate_site_package(
        repo_root / "tests/contracts/fixtures/site_absolute_path",
        repo_root / "schemas/site_package.schema.json",
    )
    assert not report.ok
    assert any(issue.code == "ABSOLUTE_PATH" for issue in report.issues)
```

- [ ] **Step 2: Run and verify RED**

Run: `pytest -q tests/contracts/test_runtime_contracts.py -k 'site_relative_paths or absolute_asset_path'`
Expected: FAIL because site validation is missing

- [ ] **Step 3: Implement schema validation, required asset existence, absolute-path rejection, and package-root containment**

Reject `Path(raw).is_absolute()` and reject resolved paths not under `site_root.resolve()`

- [ ] **Step 4: Run and verify GREEN**

Run: `pytest -q tests/contracts/test_runtime_contracts.py -k 'site_relative_paths or absolute_asset_path'`
Expected: PASS

- [ ] **Step 5: Commit**

```bash
git add tools/runtime_contracts/validator.py tests/contracts
git commit -m "feat(v3-01): validate site package paths"
```

### Task 4: Implement SHA-256 integrity and vehicle compatibility

**Files:**
- Modify: `tools/runtime_contracts/validator.py`
- Test: `tests/contracts/test_runtime_contracts.py`
- Create: `tests/contracts/fixtures/site_hash_mismatch/**`
- Create: `tests/contracts/fixtures/site_incompatible_vehicle/**`

**Interfaces:**
- Produces: `validate_runtime_contracts(vehicle_path: Path, site_root: Path, vehicle_schema_path: Path, site_schema_path: Path) -> ValidationReport`
- Internal: `_sha256(path: Path) -> str`

- [ ] **Step 1: Write failing tests for hash mismatch and incompatible vehicle**

```python
def test_hash_mismatch_fails_closed(repo_root):
    report = validate_runtime_contracts(...site_hash_mismatch...)
    assert not report.ok
    assert any(issue.code == "HASH_MISMATCH" for issue in report.issues)


def test_incompatible_vehicle_fails_closed(repo_root):
    report = validate_runtime_contracts(...site_incompatible_vehicle...)
    assert not report.ok
    assert any(issue.code == "INCOMPATIBLE_VEHICLE" for issue in report.issues)
```

- [ ] **Step 2: Run and verify RED**

Run: `pytest -q tests/contracts/test_runtime_contracts.py -k 'hash_mismatch or incompatible_vehicle'`
Expected: FAIL because combined validation/integrity checks are missing

- [ ] **Step 3: Implement hash verification and compatibility**

Read `hashes.yaml`, require lowercase 64-character SHA-256 values, hash every manifest-declared asset, and compare selected `platform.name` with `compatibility.vehicle_profiles`

- [ ] **Step 4: Add Ackermann semantic guard**

For `platform.kinematics == "ackermann"`, require wheelbase (`wheel_base` or legacy `wheelbase`), `min_turning_radius`, and a non-empty footprint. Return `ACKERMANN_GEOMETRY` on failure

- [ ] **Step 5: Run all contract tests**

Run: `pytest -q tests/contracts`
Expected: PASS

- [ ] **Step 6: Commit**

```bash
git add tools/runtime_contracts/validator.py tests/contracts
git commit -m "feat(v3-01): enforce runtime integrity and compatibility"
```

### Task 5: Add CLI and contract CI

**Files:**
- Create: `tools/validate_runtime_contracts.py`
- Create: `.github/workflows/runtime-contracts.yml`
- Modify: `README.md`
- Test: `tests/contracts/test_runtime_contracts.py`

**Interfaces:**
- CLI inputs: `--vehicle PATH`, `--site PATH`, optional schema path overrides
- CLI exit: `0` READY, `2` contract validation failure, `1` unexpected execution/configuration error

- [ ] **Step 1: Write failing CLI success/failure tests using subprocess**

```python
def test_cli_returns_zero_for_ready_contract(repo_root): ...
def test_cli_returns_two_for_contract_failure(repo_root): ...
```

- [ ] **Step 2: Run and verify RED because CLI does not exist**

Run: `pytest -q tests/contracts/test_runtime_contracts.py -k 'cli_returns'`
Expected: FAIL

- [ ] **Step 3: Implement CLI output**

Successful output must include

```text
[PASS] vehicle schema
[PASS] site schema
[PASS] relative paths
[PASS] required assets
[PASS] SHA256 integrity
[PASS] vehicle compatibility
[PASS] Ackermann geometry
Runtime contract validation: READY
```

Failure output must include issue codes/messages and `Runtime contract validation: NOT READY`

- [ ] **Step 4: Add GitHub Actions workflow**

Workflow uses Python 3.10, installs `requirements-contracts.txt`, and runs `pytest -q tests/contracts`

- [ ] **Step 5: Run full pure-Python suite**

Run: `pytest -q tests/contracts`
Expected: PASS

- [ ] **Step 6: Commit**

```bash
git add tools/validate_runtime_contracts.py .github/workflows/runtime-contracts.yml README.md tests/contracts
git commit -m "ci(v3-01): gate runtime contracts"
```

### Task 6: Final verification and V3-01 handoff

**Files:**
- Review all files in this plan

**Interfaces:**
- Produces: branch ready for local ROS regression and PR review

- [ ] **Step 1: Run contract suite**

Run: `python3 -m pytest -q tests/contracts`
Expected: PASS

- [ ] **Step 2: Run CLI against the real MK-mini profile and valid fixture**

Run:

```bash
python3 tools/validate_runtime_contracts.py \
  --vehicle profiles/platforms/mk_mini.yaml \
  --site tests/contracts/fixtures/site_valid
```

Expected: READY and exit 0

- [ ] **Step 3: Run local ROS regression after pulling branch**

Run:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
```

Expected: current 23-package independent build remains successful; existing vendor warnings are allowed but no build failures are accepted

- [ ] **Step 4: Confirm no V2.5 dependency strings were introduced**

Run:

```bash
grep -RIn --exclude-dir=.git --exclude='*.md' 'agt_navigation_v2\|/home/.*/agt_navigation_v2' .
```

Expected: no runtime/config/code matches

- [ ] **Step 5: Open PR with V3-01 acceptance checklist**

PR must explicitly distinguish GitHub pure-Python CI evidence from the user-machine 23-package ROS/colcon regression evidence
