# V3-01 Runtime Contracts & Boundary Freeze Design

## Goal

Freeze the runtime-side contracts that separate `agt_navigation_runtime` from V2.5 asset production before algorithm or package refactors begin

The V3 runtime must consume versioned deployment artifacts and vehicle profiles without source-tree, install-space, ROS overlay, or relative-path dependencies on `agt_navigation_v2`

## Scope

V3-01 covers four deliverables

1. Runtime package ownership contract
2. Vehicle Profile schema and validation
3. Deployable Site Package schema and validation
4. Fail-closed contract validation with test fixtures and lightweight CI

V3-01 does not rename `agt_mapping`, change FAST-LIVO2/ICP/NDT/Nav2 behavior, tune controllers, implement Site Manager ROS nodes, implement the V2.5 exporter, or change chassis control behavior

## Runtime Package Ownership

The current migrated packages remain build-compatible during V3-01

### Foundation

- `agt_interfaces`
- `agt_description`
- `agt_sensor_adapters`
- `agt_sensor_monitor`

### State Estimation

- `agt_mapping` — transitional runtime estimator package
- `agt_localization`
- `agt_localization_fusion`

### Navigation Runtime

- `agt_perception`
- `agt_navigation`
- `agt_safety`
- `agt_chassis`

### Mission and Operations

- `agt_bt_executor`
- `agt_mission_manager`
- `agt_experiment_manager`

During V3-01, `agt_mapping` remains named as-is for compatibility but its V3 ownership is frozen to continuous runtime odometry / LIO estimation only. No new PCD production, map-version generation, offline processing, or Site Package production responsibilities may be added to it

## Vehicle Profile Contract

Existing files in `profiles/platforms/` remain canonical. V3-01 does not introduce a parallel `vehicles/` tree

The profile contract uses a top-level `schema_version: "1.0"` plus the existing `platform:` object to preserve compatibility with current consumers

Required common fields are

- `platform.name`
- `platform.kinematics`
- `platform.footprint_frame`
- `platform.base_frame`
- `platform.geometry.length`
- `platform.geometry.width`
- `platform.geometry.footprint`
- `platform.limits.max_forward_velocity`
- `platform.limits.max_reverse_velocity`

For Ackermann profiles, the validator additionally requires

- wheelbase using either canonical `wheel_base` or legacy `wheelbase`
- minimum turning radius
- a non-empty footprint

The contract explicitly separates three categories

1. Manufacturer/specification truth
2. Measured/calibrated truth
3. Navigation operating limits

Navigation policy must not overwrite manufacturer truth

## Deployable Site Package Contract

A V3 Site Package is a self-contained deployment directory produced by V2.5 and consumed read-only by V3

Reference layout

```text
sites/<site-id>/<revision>/
├── manifest.yaml
├── map/
│   ├── navigation.yaml
│   ├── navigation.pgm
│   └── localization_map.pcd
├── semantic/
│   └── semantic_map.yaml
├── routes/
│   └── route_graph.yaml
├── calibration/
│   └── sensors.yaml
└── hashes.yaml
```

The manifest uses `site_schema_version: "1.0"` and contains

- site identity and revision
- global frame
- relative asset paths
- compatible vehicle profile ids
- hashes file path

Every asset path must be relative to the Site Package root. Absolute paths, `..` traversal, and any path escaping the package root are invalid

V3 must never require paths such as `~/agt_navigation_v2/...`, `/home/.../agt_navigation_v2/...`, a sourced V2.5 install space, or a V2.5 ROS overlay

## Integrity Contract

`hashes.yaml` maps relative artifact paths to lowercase SHA-256 digests

The validator verifies

- hashes file exists
- every declared asset exists
- every declared asset has a hash entry
- every referenced hash matches the current file contents

The manifest itself is not required to hash itself

## Compatibility Contract

A selected vehicle profile must appear in `compatibility.vehicle_profiles`

For an Ackermann vehicle, the profile must provide the geometry required by runtime planning, including wheelbase, minimum turning radius, and footprint

A Site Package that is structurally valid but incompatible with the selected vehicle is not runtime READY

## Fail-Closed Rules

Validation returns failure and a non-zero CLI exit code for at least these conditions

- unsupported schema version
- missing required manifest field
- absolute asset path
- path traversal outside Site Package root
- missing asset
- missing hash entry
- SHA-256 mismatch
- incompatible vehicle
- Ackermann vehicle missing wheelbase, minimum turning radius, or footprint

No default geometry or guessed path may convert an invalid contract into READY

## Validator Architecture

V3-01 adds a pure-Python validator under `tools/runtime_contracts/`

The validator has no ROS dependency. It uses YAML parsing plus JSON Schema validation and explicit semantic/integrity checks that JSON Schema alone cannot express

Public command

```bash
python3 tools/validate_runtime_contracts.py \
  --vehicle profiles/platforms/mk_mini.yaml \
  --site tests/contracts/fixtures/site_valid
```

READY output is line-oriented and human-readable, including checks for vehicle schema, site schema, relative paths, required assets, SHA-256 integrity, compatibility, and Ackermann geometry

Failure output is deterministic and exits non-zero

## Schemas

V3-01 adds

- `schemas/vehicle_profile.schema.json`
- `schemas/site_package.schema.json`

Both use JSON Schema Draft 2020-12 and set their version fields to the exact constant `1.0`

The schemas validate shape and primitive constraints. Cross-file compatibility, path containment, existence, and SHA-256 are implemented by validator code

## Tests

Tests are pure Python and do not require ROS

Required fixtures include

- one valid Site Package
- absolute path failure
- hash mismatch failure
- incompatible vehicle failure

The existing `profiles/platforms/mk_mini.yaml` is upgraded minimally with `schema_version: "1.0"` and must validate without restructuring its existing truth and policy fields

At least one test validates the real MK-mini profile rather than a test-only copy

## CI

A lightweight GitHub Actions workflow runs only contract tests with Python dependencies installed explicitly

This CI is independent of the future ROS/colcon CI and does not claim that the full ROS workspace builds on GitHub-hosted runners

## Acceptance Criteria

V3-01 is complete when

- runtime package ownership is documented
- V2.5/V3 boundary is documented
- Vehicle Profile schema 1.0 exists
- Site Package schema 1.0 exists
- the real MK-mini profile passes Vehicle Profile validation
- one valid Site fixture passes full validation
- invalid absolute path, hash mismatch, and incompatible vehicle fixtures fail closed
- validator has no ROS dependency
- GitHub contract CI passes
- the existing local 23-package colcon build remains the baseline to re-run after pulling the branch
