# P1-03 Task Registry Decoupling Acceptance — 2026-08-29

## Decision

```text
IMPLEMENTED:       PASS
STATIC / CI:       PASS
ROS 2 HUMBLE:      NOT RUN ON CANONICAL P1 BRANCH
REAL VEHICLE:      NOT RUN / NOT REQUIRED FOR P1-03
```

P1-03 is complete at the source, unit and cloud-contract level. Mutable task authority is no longer stored below immutable Site/map version assets. Formal task execution is also bound to the authoritative active Site identity. This record does **not** claim ROS 2 Humble runtime or field acceptance.

## Source

- Canonical branch: `feat/runtime-navigation-convergence-p1`
- P1-03 baseline: accepted P1-02 canonical branch state
- P1-03 static acceptance head: `e6f62810088912b4b9b27c2ae1dc1c83f50b0df2`
- Final canonical Runtime Contracts evidence: run `#281` (`33237868775`)

P1-03 was implemented directly on the canonical branch. No new parallel navigation feature line was created.

## Implemented

### 1. Immutable Site assets and mutable Task Library are separated

Canonical ownership is now:

```text
Site / map assets — immutable deployment authority

<sites_root>/<site_id>/<revision>/...

legacy/runtime map asset tree where applicable:
runtime/maps/<site_id>/versions/<revision>/
  manifest.yaml
  navigation/
  localization/
  routes/

Task Library — mutable operator/runtime authority

runtime/tasks/<site_id>/<revision>/
  site_binding.json
  task_index.json
  <task_group_id>.json
  <task_group_id>.route.yaml      # optional mutable Task -> Route binding
  archive/
```

The immutable Route Asset itself remains below the map/Site version `routes/` tree. Only the mutable binding that opts one exact task revision into that Route Asset lives beside the mutable task.

### 2. Task storage is bound to validated Site content

Each mutable task revision directory is guarded by:

```text
site_binding.json
```

The persisted binding records:

```text
map_id / site_id
map_version_id / site_revision
map_hash
manifest_sha256
navigation_yaml_sha256
navigation_image_sha256
localization_pcd_sha256
```

`TaskRegistry` resolves the deployed Site before list/get/put/archive operations. If persisted Site identity differs from the currently validated deployed Site content, the store fails closed with `TASK_SITE_BINDING_MISMATCH` rather than silently reusing tasks against changed assets.

The public task/service schema keeps `map_id` and `map_version_id` for compatibility. In this P1 architecture they identify the Site id/revision bound to the task.

### 3. All production mutable task writers use one `tasks_root`

Both task persistence implementations now use:

```text
runtime/tasks/<site>/<revision>
```

This includes:

- `TaskRegistry` used by ROS task services;
- `TaskRepository` used by Qt/offline task tooling;
- `WaypointTaskServer` / `NavigationCapabilityServer` formal execution lookup;
- optional Task -> Route binding sidecars.

`navigation.launch.py` declares one `tasks_root` launch argument and forwards the same value to both the execution capability and the ROS Task Registry node.

### 4. Editing and execution use different, intentional Site authority gates

Task editing/storage requires the requested Site revision to be a deployed, validated Site revision through `FilesystemSiteBindingResolver`.

Formal task execution is stricter. `WaypointTaskServer` resolves the Task Registry against the current transient-local `/agt/maps/active` summary using:

```text
binding_from_map_version_summary(..., require_active=True)
```

Therefore a formal task cannot resolve for execution unless the requested Site revision:

```text
exists
AND state == READY
AND valid == true
AND active == true
AND requested Site id/revision == /agt/maps/active id/revision
AND persisted task-store Site content hashes still match
```

This is in addition to the existing OccupancyGrid geometry/content, localization, TaskReadiness, safety and Nav2 gates.

### 5. ROUTE task sidecars no longer create a second task authority

Before P1-03, optional ROUTE bindings were looked up below:

```text
runtime/maps/<site>/versions/<revision>/tasks/<task>.route.yaml
```

P1-03 changes the mutable binding path to:

```text
runtime/tasks/<site>/<revision>/<task>.route.yaml
```

while preserving the immutable Route Asset lookup below:

```text
runtime/maps/<site>/versions/<revision>/routes/<route_id>/<route_revision>/
```

`RouteTaskResolver` now receives both `maps_root` and `tasks_root` explicitly. A legacy `.route.yaml` left in `maps/.../tasks` is deliberately ignored; there is no implicit fallback.

### 6. Legacy task migration is explicit and one-way

Runtime nodes never fall back to the old map-local task directory. Existing deployments may be migrated only through the installed operator utility:

```text
migrate_legacy_task_store.py
```

The utility is dry-run by default. A typical preflight is:

```bash
ros2 run agt_navigation migrate_legacy_task_store.py \
  --map-id orchard_a \
  --map-version-id r01 \
  --legacy-maps-root runtime/maps \
  --tasks-root runtime/tasks
```

Only after reviewing the report is persistence enabled explicitly:

```bash
ros2 run agt_navigation migrate_legacy_task_store.py \
  --map-id orchard_a \
  --map-version-id r01 \
  --legacy-maps-root runtime/maps \
  --tasks-root runtime/tasks \
  --apply
```

Migration behavior:

- validates the destination Site before any write;
- validates every legacy task JSON and Site asset hash binding;
- preserves the exact existing task `revision` and `content_sha256` when the destination does not exist;
- validates matching ROUTE sidecar task identity before copying it;
- performs complete preflight before the first write;
- is rerunnable: an identical destination is skipped;
- rejects a non-identical destination before migrating other tasks;
- rejects orphan ROUTE sidecars;
- rejects symlink/path-escape sources and destinations;
- does not delete the legacy source automatically.

Legacy source cleanup is an explicit operator action after migration verification, not part of Runtime startup.

## Intentionally not implemented

P1-03 does **not** implement:

- Active Site -> concrete localization/Nav2 asset lifecycle binding; that is P1-04;
- `NavigationRuntimeStatus` aggregation; that is P1-05;
- field mapping/commissioning selective port; that is P1-06;
- production RViz direct-goal hardening beyond the existing default-disabled formal path; P1-07 owns that acceptance;
- full ROS 2 Humble convergence regression; that is P1-08;
- BUNKER/MID360 field acceptance; that is P1-09;
- inspection capability integration; that is P1-10;
- HMI MissionDraft publication/persistence API; that remains a later HMI/Gateway integration concern.

P1-03 also does not mutate Site packages when task points change.

## Interface changes

No public TaskGroup, service or `ExecuteWaypointTask` schema migration was required.

New/updated runtime parameters:

```text
tasks_root
sites_root
site_vehicle_profile
```

The ROS Task Registry edit node uses deployed Site validation. The execution node uses active-Site validation.

New installed operator utility:

```text
ros2 run agt_navigation migrate_legacy_task_store.py ...
```

## Test evidence

### TDD evidence

P1-03 intentionally introduced RED gates before the corresponding implementation slices. Observed failures included:

- missing Site-task binding module;
- old `TaskRegistry` constructor/storage authority;
- old `TaskRepository` map-local path;
- ROS edit node/launch not forwarding `tasks_root` and Site validation inputs;
- execution server still instantiating `TaskRegistry(self.maps_root)`;
- ROUTE sidecar still resolving from `maps/.../tasks`;
- explicit migration module not yet existing.

Each RED was isolated to the new P1 task-storage step while the earlier Runtime/SystemManager/Site suites stayed green, then returned to GREEN after implementation.

### Final static / cloud CI

Canonical head:

```text
e6f62810088912b4b9b27c2ae1dc1c83f50b0df2
```

Runtime Contracts run `#281` (`33237868775`): **PASS**.

Exact successful test groups from that run:

```text
V3-01 contract tests:              19 passed
V3-02 odometry source contracts:    9 passed
V3-03 execution source contracts:  18 passed
runtime system-manager contracts:  28 passed
runtime site-owner contracts:      45 passed
P1 task-storage contracts:         52 passed
```

The P1 task-storage group includes:

```text
site task binding tests
TaskRegistry tests
TaskRepository/task-group tests
RouteTaskResolver split-authority tests
legacy task migration tests
production source-contract tests
```

Relevant enforced cases include:

- task writes use `tasks_root`, not map `versions/.../tasks`;
- Site content identity changes invalidate the task store;
- formal execution requires the READY/valid/active Site authority;
- ROUTE sidecars use `tasks_root`;
- legacy map-local ROUTE sidecars are ignored rather than used as fallback;
- route/task identity and route manifest changes fail closed;
- migration dry-run writes nothing;
- migration preserves task revision/hash;
- identical migration reruns are idempotent;
- destination conflicts fail before later tasks are written;
- orphan/symlink legacy inputs are rejected;
- migration CLI is explicit, installed, and dry-run unless `--apply` is supplied.

### ROS 2 Humble

`NOT RUN` for P1-03 on a ROS 2 Humble workstation in this implementation session.

Recommended narrow local gate:

```bash
source /opt/ros/humble/setup.bash

colcon build --symlink-install --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_navigation

source install/setup.bash

colcon test --packages-select \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_navigation \
  --event-handlers console_direct+

colcon test-result --verbose
```

Additional runtime smoke should verify that `navigation.launch.py` starts with one explicit `tasks_root`, that task services can put/get a task for a deployed Site, and that formal execution rejects the same task when another Site revision is active.

Hard gate: zero build/test failures and expected fail-closed behavior for wrong Active Site.

### Real vehicle

`NOT RUN` and not required for P1-03.

## Known blockers / follow-up

1. P1-03 still needs the consolidated ROS 2 Humble verification recorded later in P1-08 or earlier local testing.
2. Site activation currently publishes the correct authority, but P1-04 must bind that authority to the exact localization and Nav2 runtime assets/lifecycle.
3. Existing old task files remain on disk until an operator explicitly migrates and later removes them; Runtime does not consume them automatically.
4. HMI task authoring still needs a Gateway publication/persistence bridge to create these versioned Runtime tasks remotely.

## Handoff

P1-03 is accepted for continuation as:

```text
CODE:   COMPLETE
STATIC: PASS
HUMBLE: PENDING
FIELD:  N/A
```

The next and only development slice is:

```text
P1-04 — Active Site -> navigation binding
```
