# P1-04 Active Site -> Navigation Binding Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN
```

P1-04 is complete at source/unit/cloud-contract level. It adds one read-only navigation-asset binding authority downstream of `agt_site_runtime`; it does not claim Nav2 lifecycle readiness, localization startup, `map -> odom` ownership, Mission execution, ROS 2 Humble runtime acceptance, or field acceptance.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- P1-04 implementation plan: `docs/superpowers/plans/2026-08-29-runtime-navigation-p1-04-active-site-binding.md`
- P1-04 static acceptance code head: `52ca77e785c8e5c90684fbed4c0b58feb5f2484b`
- Runtime Contracts: run `#298` (`33238275311`), PASS

No new parallel runtime/navigation branch was created.

## Implemented

### 1. New read-only `agt_site_navigation` package

P1-04 introduces:

```text
src/agt_site_navigation/
├── agt_site_navigation/
│   ├── __init__.py
│   └── resolver.py
├── scripts/
│   └── site_navigation_binding_node.py
├── launch/
│   └── site_navigation_binding.launch.py
├── test/
│   ├── test_resolver.py
│   └── test_source_contract.py
├── CMakeLists.txt
└── package.xml
```

Its ownership is intentionally narrow:

```text
/agt/maps/active
    -> re-resolve exact deployed Site revision
    -> re-run canonical Site Runtime validation
    -> compare exact identity/hash/path evidence
    -> /agt/navigation/site_binding
```

It does not mutate Site assets.

### 2. Resolver reuses Site Runtime / Runtime Contract authority

`ActiveSiteNavigationResolver` does not invent a second Site hash or path policy. It reuses:

```text
SiteRegistry
SiteValidator
build_site_summary
load_yaml
navigation_image_asset
```

Resolution succeeds only if the input Active Site is:

```text
active == true
state == READY
valid == true
exact Site id/revision is still deployed
canonical Site validation still passes
canonical identity/hashes/paths still match /agt/maps/active
required resolved navigation/localization assets still exist
```

A successful immutable `ResolvedNavigationBinding` carries:

```text
site_id
site_revision
site_hash
manifest_sha256
navigation_yaml + navigation_yaml_sha256
navigation_image + navigation_image_sha256
localization_pcd + localization_pcd_sha256
processing_record (optional)
```

### 3. Stable fail-closed resolver errors

Expected binding failures use stable codes:

```text
NO_ACTIVE_SITE
ACTIVE_SITE_NOT_READY
ACTIVE_SITE_NOT_DEPLOYED
ACTIVE_SITE_IDENTITY_MISMATCH
SITE_ASSET_INVALID
```

Examples:

- no Active Site or inactive tombstone -> `NO_ACTIVE_SITE`;
- invalid/non-READY authority -> `ACTIVE_SITE_NOT_READY`;
- selected revision removed from deployment -> `ACTIVE_SITE_NOT_DEPLOYED`;
- Active Site summary no longer matches canonical deployed hashes/paths -> `ACTIVE_SITE_IDENTITY_MISMATCH`;
- an asset is corrupted after activation -> `SITE_ASSET_INVALID`.

No prior valid binding is silently reused.

### 4. Typed `SiteNavigationBinding` interface

New ROS interface:

```text
agt_interfaces/msg/SiteNavigationBinding.msg
```

States:

```text
STATE_UNKNOWN
STATE_READY
STATE_BLOCKED
STATE_ERROR
```

The message carries Site identity, exact resolved asset paths/hashes, and blocker evidence. It deliberately contains no Nav2 lifecycle READY fields; those belong to P1-05 `NavigationRuntimeStatus`.

A Humble serialization/default-state smoke test is registered in `agt_interfaces`, but has not been run in this cloud-only implementation session.

### 5. ROS binding node

`site_navigation_binding_node.py`:

- subscribes `/agt/maps/active`;
- publishes `/agt/navigation/site_binding`;
- uses reliable + transient-local QoS for both authority input and binding output;
- publishes an initial UNKNOWN binding;
- publishes READY only after successful canonical re-resolution;
- publishes a **fresh** BLOCKED/ERROR message when authority is revoked, invalid, changed or corrupted.

Because each callback builds a new message, an inactive/tombstone Active Site cannot leave previous YAML/image/PCD paths latched as READY evidence.

### 6. Explicit authority boundaries

Source contracts prohibit the P1-04 node from importing/owning:

```text
TF broadcasters
Mission execution actions
ROS ActionServer / ActionClient control authority
cmd_vel
FollowPath / FollowWaypoints
filesystem write helpers
```

Therefore P1-04 does not create a second `map -> odom` authority and does not bypass Mission/Nav2/safety ownership.

## Intentionally not implemented

P1-04 does **not**:

- start or stop localization;
- load Nav2 map servers itself;
- activate/deactivate Nav2 lifecycle nodes;
- publish `map -> odom`;
- publish `NavigationRuntimeStatus`;
- set `SystemManager.navigation_ready`;
- hot-switch an active running Mission;
- mutate or generate Site Packages;
- change Task Registry storage;
- add a new SLAM/localization/planner/controller algorithm.

Those lifecycle/readiness concerns belong to P1-05 and later convergence slices.

## Interface / launch additions

New topic contract:

```text
/agt/navigation/site_binding
  type: agt_interfaces/msg/SiteNavigationBinding
  QoS: RELIABLE + TRANSIENT_LOCAL
```

New launch entry point:

```bash
ros2 launch agt_site_navigation site_navigation_binding.launch.py \
  sites_root:=/opt/agt/sites \
  site_vehicle_profile:=/opt/agt/profiles/bunker.yaml
```

## Test evidence

### TDD RED

The first P1-04 resolver CI gate failed only because `agt_site_navigation.resolver` did not exist; all earlier Runtime suites remained green.

After the resolver was implemented, its six functional cases became GREEN.

A second source-contract RED was then introduced. Resolver tests remained GREEN, while only these missing ROS/package surfaces failed:

```text
SiteNavigationBinding.msg missing
agt_site_navigation/CMakeLists.txt missing
site_navigation_binding_node.py missing
```

This confirmed the test was checking the intended new surface rather than breaking previous Runtime behavior.

### Final static/cloud evidence

Runtime Contracts run `#298` (`33238275311`): **PASS** at code head:

```text
52ca77e785c8e5c90684fbed4c0b58feb5f2484b
```

Successful groups:

```text
V3-01 contract tests:                    19 passed
V3-02 odometry source contracts:          9 passed
V3-03 execution source contracts:        18 passed
runtime system-manager contracts:        28 passed
runtime site-owner contracts:            45 passed
P1 task-storage contracts:               52 passed
P1 active-site navigation binding:       10 passed
```

P1-04's ten cloud tests cover:

```text
exact Active Site -> deterministic resolved binding
no Active Site -> fail closed
inactive/invalid Active Site -> fail closed
Active Site hash mismatch -> fail closed
asset corruption after activation -> fail closed
missing deployed revision -> fail closed
typed message source registration
package/install/launch source contract
transient-local fail-closed ROS node source contract
resolver read-only / Site Runtime authority contract
```

### ROS 2 Humble

`NOT RUN` in this implementation session.

Recommended narrow Humble gate:

```bash
source /opt/ros/humble/setup.bash

colcon build --symlink-install --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_site_navigation

source install/setup.bash

colcon test --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_site_navigation \
  --event-handlers console_direct+

colcon test-result --verbose
```

Runtime smoke should additionally verify:

1. node initially publishes UNKNOWN;
2. activating an exact valid Site publishes READY with the expected absolute asset paths;
3. publishing/activating a tombstone or invalid Site overwrites the latched READY with BLOCKED and empty asset paths;
4. no TF authority is added by `agt_site_navigation`.

Hard gate: zero build/test failures and fail-closed tombstone behavior.

### Real vehicle

`NOT RUN`.

P1-04 does not require vehicle motion to prove its software contract, but field release remains pending until later P1 hardware acceptance.

## Known follow-up

1. P1-04 Humble build/runtime evidence remains pending.
2. `SiteNavigationBinding` is asset binding evidence only. P1-05 must aggregate it with localization/Nav2 lifecycle/safety-related evidence into navigation readiness.
3. The component does not yet own automatic lifecycle transition sequencing; that must be designed in P1-05 without taking Site ownership away from `agt_site_runtime`.
4. Full integration with the field commissioning launch path is deferred to P1-06.

## Handoff

```text
P1-04 Code:   COMPLETE
P1-04 STATIC: PASS
P1-04 HUMBLE: PENDING
P1-04 FIELD:  PENDING
```

The next and only development slice is:

```text
P1-05 — NavigationRuntimeStatus + SystemManager gate
```
