# Field Commissioning + HMI Map Workflow Design

Date: 2026-08-30

Status: APPROVED PRODUCT DIRECTION / DESIGN FREEZE CANDIDATE

## 1. Goal

Define the first delivery-grade operator workflow for the litchi inspection vehicle on sloped terrain without requiring the operator to switch repositories, run offline map scripts manually, open RViz for normal operation, or understand ROS graph details.

The product workflow is:

```text
robot boot
  -> automatic hardware bringup and health checks
  -> Mapping
  -> review generated 2D occupancy map
  -> lightweight map cleanup
  -> save a new immutable Site revision
  -> author inspection waypoints and capture settings
  -> planner-only route preview
  -> save Task / Mission definition
  -> Run page
  -> relocalization
  -> navigation readiness
  -> physical remote AUTO permit
  -> START
  -> navigate -> stop -> capture -> next point
  -> optional RETURN_HOME
  -> report/evidence
```

The operator experiences this as one HMI. Repository boundaries remain an engineering concern only.

## 2. Product Baseline

The first field baseline is frozen as:

```text
3D mapping / local odometry        FAST-LIVO2
2D map projection                  RTAB-Map-style grid projection backend
map review/edit                    HMI commissioning workspace
map version authority              immutable Site revision
route preview                      Nav2 ComputePathToPose, planner-only
production waypoint execution      ExecuteWaypointTask -> Nav2 FollowWaypoints
production global planner          SmacPlanner2D
smoothing                          SimpleSmoother
controller                         MPPI DiffDrive
initial/global correction          bounded multi-candidate NDT relocalization
inspection                         frozen agt_inspection AcquireView flow
online flower inference            DEFERRED for first field acceptance
physical autonomous permission     remote-controller AUTO permit gate
software task command              HMI -> Operator Gateway -> Mission Manager
```

This design does not change the frozen inspection evidence or AcquireView behavior.

## 3. Repository and Responsibility Boundary

### 3.1 Runtime execution plane

The normal execution plane keeps its existing ownership:

```text
Site activation
Localization / map->odom authority
Nav2 planning and control
Mission Manager
Inspection
Safety
Chassis
```

Normal runtime execution must never start map production or mutate the active Site.

### 3.2 Commissioning plane inside the Runtime repository

`agt_field_commissioning` becomes the single robot-side field commissioning owner for the operator workflow:

```text
hardware preflight
mapping session orchestration
mapping artifact finalization
2D projection request
map review draft management
Site candidate creation
Site revision validation/promotion request
```

This changes the old repository boundary only at the field-product workflow level. The normal Runtime execution plane remains map-consumer-only.

### 3.3 Algorithm R&D repository

`Aldoubt/Aldoubt-agt_map_reconstruction` remains an independent algorithm and benchmark repository.

Its role is:

```text
compare reconstruction methods
run PMF/CSF/semantic experiments
validate agricultural corridor recovery
produce paper/benchmark evidence
prove candidate algorithms before migration
```

It is not part of the normal operator path and must not be a required runtime dependency for first-vehicle delivery.

## 4. Hardware Startup and Health Model

Hardware processes start independently from the browser, preferably under robot-local service/orchestration ownership. Closing the browser must not stop sensors or drivers.

The HMI consumes health truth only.

### 4.1 MID360 readiness

MID360 is READY only when all required layers pass:

```text
network/NIC configuration valid
  + lidar host reachable or driver network initialized successfully
  + Livox driver alive
  + lidar stream fresh
  + IMU stream fresh
  + timestamps valid/fresh
```

A successful ping alone is not sufficient.

The vehicle installation freezes the robot NIC and sensor addresses as deployment configuration. The HMI displays the configured identity and health; it does not edit the LiDAR IP during normal use.

### 4.2 BUNKER readiness

BUNKER readiness is based on the existing SocketCAN/hardware bringup evidence and runtime chassis health. Monitor-mode checks remain non-commanding.

### 4.3 Camera/gimbal readiness

The frozen `/camera_gimbal/health` contract remains authoritative. New inspection goals require fresh READY health with camera alive, serial connected, feedback alive, move action ready, and not busy.

## 5. Mapping Workflow

### 5.1 Operator sequence

The Mapping page exposes only:

```text
sensor readiness
mapping state
elapsed time
basic trajectory/distance feedback where available
START MAPPING
FINISH MAPPING
ABORT
```

`START MAPPING` uses the commissioning-specific mapping entry point. Normal odometry mode continues to keep map persistence disabled.

### 5.2 Mapping artifacts

A mapping session writes only into a run-scoped mutable commissioning directory:

```text
runtime/commissioning/<site_id>/<run_id>/
  mapping/
    localization_map.pcd
    localization_map.processing.yaml
  projection/
  map_review/
  evidence/
```

The session is not a Site until finalization and validation complete.

### 5.3 Finish behavior

`FINISH MAPPING` performs an orderly mapping shutdown so FAST-LIVO2 can complete its save path, then finalizes the PCD and verifies:

```text
PCD exists
PCD is non-empty
processing record exists
no temporary files remain
content hashes are recorded
```

Crash/SIGKILL output does not count as a successful mapping result.

## 6. 3D -> 2D Projection

### 6.1 Architectural rule

The first sloped-terrain delivery uses a dedicated `MapProjectionBackend` abstraction. The initial production backend is `rtabmap_grid`.

```text
localization_map.pcd
      |
      v
MapProjectionBackend
      |
      +-- rtabmap_grid       [first field default]
      |
      `-- future backends    [only after independent validation]
      |
      v
OccupancyGrid + PGM/YAML + projection evidence
```

The backend name is diagnostic metadata. The HMI presents only `Generating 2D map` and the result/status.

### 6.2 What is migrated from RTAB-Map

Only the proven grid projection behavior is reused. RTAB-Map does not become the primary SLAM, odometry, localization or loop-closure owner for this baseline.

The projection implementation must use RTAB-Map's maintained grid/occupancy capabilities or an equivalent thin wrapper around them, with slope-aware ground/obstacle segmentation. The interface is PCD-to-2D-map; the implementation must not introduce a second live `map->odom` authority.

### 6.3 Slope requirement

The backend must not rely on one global world-Z threshold as the sole ground classifier. The field baseline must support local ground orientation / surface-normal-aware segmentation so a legitimate slope is not painted as a wall simply because its absolute Z rises.

### 6.4 Required outputs

Every successful projection produces:

```text
raw_map.pgm
raw_map.yaml
projection_record.yaml
projection_preview.png (optional convenience artifact; not authoritative)
```

The record includes at minimum:

```text
source PCD hash
projection backend identity/version
projection parameter identity/hash
map resolution
map dimensions/origin
occupied/free/unknown cell counts
output PGM hash
output YAML hash
created_at
```

The PGM/YAML are the authoritative 2D navigation-map draft.

## 7. HMI Map Review and Lightweight Editing

### 7.1 Product scope

The first map editor is deliberately small. Required tools:

```text
erase erroneous obstacle -> free
paint obstacle -> occupied
undo
redo
reset to raw projection
```

Optional polygon convenience may be added only if it does not delay the core brush workflow.

### 7.2 Data semantics

The editor preserves occupancy semantics:

```text
occupied
free
unknown
```

Unknown is not silently converted to free by generic erase/reset logic unless the operator explicitly applies a free-space edit.

### 7.3 Non-destructive editing

`raw_map.pgm` is immutable commissioning evidence.

Edits are recorded as a draft operation log and materialized into a reviewed map:

```text
raw_map
  + edit operations
  -> reviewed_map.pgm
  -> reviewed_map.yaml
```

The draft may be changed repeatedly. The active Site is never modified in place.

### 7.4 Save map behavior

`SAVE MAP` performs:

```text
materialize reviewed PGM/YAML
validate occupancy image/YAML consistency
compute hashes
create candidate Site revision
validate Site contract
present validation result
promote/activate only through explicit operator action
```

Saving a review creates a new Site revision; it never mutates the currently active revision.

## 8. Site Revision Policy

The Site package remains immutable after promotion.

Example:

```text
site orchard_slope
  r01  raw/first reviewed map
  r02  operator cleaned map
  r03  later corrected map
```

Each revision records its parent/reason and asset hashes. A failed new revision leaves the previous active Site untouched.

Normal navigation consumes only an explicitly active validated Site.

## 9. HMI Task Authoring

### 9.1 Waypoint editing

The Task page supports:

```text
add waypoint on map
move waypoint
rotate heading
delete waypoint
reorder waypoint
```

Waypoint coordinates are stored in the active Site's `map` frame and bound to exact `site_id + site_revision`.

### 9.2 Inspection configuration

Each inspection waypoint may define:

```text
point_id
x/y/yaw
stationary requirement
dwell/stability time
one or more view definitions
```

For first field acceptance, the default authoring template is one center view per point. Additional left/right views are opt-in after the center-only route and capture path pass physical acceptance.

The frozen inspection task schema remains authoritative for execution. HMI authoring must serialize into that contract rather than creating a parallel mission format.

### 9.3 Persistence

Task edits remain drafts until `SAVE TASK` succeeds through the Gateway/Task Registry boundary.

The browser is never the authoritative task database.

## 10. Planner-Only Route Preview

Before saving or running a task, the operator can request route preview.

```text
HMI waypoints
  -> Gateway preview request
  -> Runtime planner-only adapter
  -> Nav2 ComputePathToPose for each segment
  -> merged preview path + per-segment result
  -> HMI overlay
```

The preview launch/adapter must not start controller, BT Navigator, Waypoint Follower, safety enable or chassis motion.

The preview is advisory validation, not execution. A successful preview does not itself authorize motion.

If any segment fails, the HMI identifies the failing `Pi -> Pj` segment and does not report the task as route-validated.

## 11. Run Page and Relocalization

### 11.1 Run readiness

The Run page presents Runtime-owned readiness, not browser-inferred readiness:

```text
Site               READY / blocker
Localization       TRACKING / blocker
Navigation         READY / blocker
MID360             READY / blocker
Camera/Gimbal      READY / blocker
Autonomous Permit  ENABLED / WAITING
Mission            READY / RUNNING / ...
```

### 11.2 First-field initial relocalization policy

For the first sloped-terrain acceptance, the vehicle is placed near the known mapping start area before autonomous operation.

The startup localization policy is bounded and verified, not a blind identity transform:

```text
known start seed (approximately map origin / surveyed commissioning start)
  + bounded XY search
  + bounded yaw search
  -> NDT candidates against localization_map.pcd
  -> quality/ambiguity gate
  -> accepted global pose
  -> GlobalCorrectionManager owns map->odom
  -> TRACKING
```

The exact position/yaw radii are deployment parameters validated on the vehicle. The operator workflow does not claim arbitrary-position, no-prior global localization.

### 11.3 Future global coarse retrieval

Scan Context/place-recognition or other no-prior coarse localization is explicitly deferred. It may later provide candidate seeds to the existing Relocalize Action but is not required for the first acceptance.

## 12. Physical Remote AUTO Permit

The remote controller is a physical autonomous-permission gate, not a second simultaneous velocity commander.

Required semantic states:

```text
MANUAL       manual control owns motion; autonomous command path blocked
AUTO ENABLE  Nav2 autonomous command path may pass; sticks do not compete with Nav2
STOP         autonomous motion blocked and vehicle commanded/stays stopped
```

The exact RC channel mapping is vehicle-specific and must be recorded during physical acceptance.

### 12.1 Two-key authorization

Autonomous mission motion requires both:

```text
software permission: Mission START from authorized HMI controller
physical permission: remote AUTO ENABLE
```

If START is requested while physical permit is absent, the mission remains non-moving in a visible `WAITING_FOR_AUTO_PERMIT`/equivalent state rather than silently issuing motion.

Loss of AUTO permit during autonomous motion must block the autonomous velocity path fail-closed. The detailed Mission pause/cancel state transition is part of implementation acceptance; safety behavior must not depend on browser connectivity.

## 13. Production Mission Execution

Production motion keeps the frozen ownership chain:

```text
HMI
  -> Operator Gateway
  -> Mission Manager
  -> Inspection Task
  -> ExecuteWaypointTask
  -> Nav2 FollowWaypoints
  -> SmacPlanner2D / SimpleSmoother / MPPI
  -> Collision Monitor
  -> agt_safety
  -> autonomous-permit gate
  -> BUNKER
```

At each inspection point:

```text
navigation arrival
  -> stationary gate
  -> camera/gimbal health gate
  -> atomic AcquireView
  -> post-settle image
  -> bind image timestamp to accepted TRACKING localization
  -> persist evidence
  -> next point
```

Online litchi-flower inference remains `DEFERRED` for the first field baseline.

## 14. HMI Information Architecture

The first delivery UI uses five primary workspaces:

```text
Status | Mapping | Map | Task | Run
```

### Status

Robot-level hardware/runtime health and blockers.

### Mapping

Mapping start/finish/abort and progress. No algorithm tuning panel in normal mode.

### Map

2D map review, lightweight cleanup, revision validation/promotion.

### Task

Waypoint/view authoring, route preview, task save.

### Run

Readiness, AUTO permit, mission controls, point-by-point progress, evidence/report links.

Engineering diagnostics may expose backend names and raw status but remain secondary.

## 15. Gateway Boundary

The browser remains ROS-independent.

The Gateway is responsible for translating stable web contracts to Runtime operations. The implementation will require separate read/write APIs for:

```text
commissioning state and commands
map image/metadata retrieval
map-edit draft persistence/materialization
Site revision validation/promotion
Task Registry CRUD
planner preview
mission control
readiness/health streaming
```

Existing Control Lease and command-token protection remain applicable to state-changing operations. Read-only monitoring can remain multi-client.

## 16. Failure Semantics

The workflow is fail-closed at every promotion/execution boundary.

### Mapping failure

No valid finalized PCD -> no projection -> no Site candidate.

### Projection failure

Keep PCD/evidence; HMI reports projection failure. Do not fabricate an empty free map.

### Map edit validation failure

Keep draft and previous active Site. Do not activate invalid output.

### Planner preview failure

Mark failing segment; do not claim task route-valid.

### Relocalization failure

Navigation remains not-ready; mission cannot move.

### Camera/gimbal failure

Inspection task admission/capture fails closed using the frozen health contract.

### AUTO permit absent/lost

Autonomous velocity path blocked independent of HMI connectivity.

### Browser/network loss

Runtime remains authoritative. Reconnect rehydrates current truth; browser state is not used to reconstruct mission truth.

## 17. Acceptance Scope

The first integrated acceptance is intentionally small:

```text
1. boot robot
2. all required hardware health becomes READY
3. start mapping
4. remote-control one representative sloped route
5. finish mapping cleanly
6. generate RTAB-Map-style 2D occupancy map
7. HMI displays real map
8. erase one known false obstacle and optionally paint one obstacle
9. save/validate new Site revision
10. activate the revision
11. author P01/P02/P03, one center capture each
12. planner-only preview passes all segments
13. save task
14. place robot near commissioning start area
15. bounded NDT relocalization reaches TRACKING
16. Runtime navigation READY
17. remote AUTO ENABLE active
18. HMI START
19. P01/P02/P03 each navigate -> stop -> capture evidence
20. RETURN_HOME if enabled
21. report/evidence available in HMI
```

## 18. Explicit Non-Goals for This Slice

Do not add these before the above acceptance passes:

```text
arbitrary-position no-prior global localization
Scan Context/place recognition
online flower inference as a motion gate
multi-view flower identity deduplication
automatic semantic corridor generation in the field UI
full Photoshop-like map editor
live 3D point-cloud editing in the browser
browser direct ROS/Nav2/cmd_vel access
RTAB-Map as the primary runtime SLAM/localization owner
automatic Site activation without operator review
map mutation in-place
```

## 19. Compatibility with the Inspection MVP Freeze

The Inspection MVP behavior freeze remains intact. This design changes the commissioning/user-facing preparation path and HMI integration around it.

The following frozen inspection behaviors remain unchanged:

```text
camera/gimbal atomic AcquireView
post-settle image requirement
actual gimbal feedback evidence
accepted TRACKING localization association
DEFERRED vision default
Mission/inspection authority boundaries
```

If implementation requires changing frozen inspection behavior, it is treated as a separate acceptance-discovered defect/change with RED reproducer, minimal fix, GREEN verification and a new freeze SHA.

## 20. Implementation Decomposition

After this design is reviewed, implementation should be split into two sequential phases rather than one large branch.

### Phase A — Commissioning + Map Review Vertical Slice

```text
hardware/readiness exposure
mapping command boundary
PCD finalization
rtabmap_grid projection backend
map asset API
HMI real map display
lightweight edits
Site revision save/validate/promote
```

Acceptance ends when a real sloped-terrain mapping run can become an HMI-reviewed active Site without manual repository switching.

### Phase B — Task Authoring + Run Vertical Slice

```text
Task Registry web boundary
inspection waypoint/view authoring
planner-only preview
startup relocalization orchestration
AUTO permit readiness/gate
Run page readiness + mission start/progress
P01/P02/P03 capture acceptance
```

Phase B must reuse the frozen Mission/Inspection Runtime behavior rather than create a parallel execution path.

## 21. Final Architecture

```text
                    ROBOT BOOT
                        |
                        v
                 Hardware Bringup
                        |
             health/readiness truth
                        |
                        v
                       HMI
                        |
        +---------------+----------------+
        |                                |
        v                                v
  COMMISSIONING                      OPERATION
        |                                |
  FAST-LIVO2 mapping                 Active Site
        |                                |
  finalized 3D PCD                  Relocalize/NDT
        |                                |
  rtabmap_grid projection            TRACKING
        |                                |
  raw occupancy map                 Nav2 READY
        |
  HMI lightweight edit
        |
  immutable Site revision
        |
  HMI waypoint/view authoring
        |
  planner-only preview
        |
  Task Registry ------------------------+
                                         |
                                  Remote AUTO permit
                                         |
                                     HMI START
                                         |
                                      Mission
                                         |
                         navigate -> stop -> capture
                                         |
                                      Evidence
                                         |
                                       Report
```

This is the delivery architecture for the next field-integration slice.