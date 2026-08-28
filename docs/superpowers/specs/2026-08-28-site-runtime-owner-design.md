# Read-Only Site Runtime Owner Design

## Status

Approved design for the next Runtime convergence slice after P0.

This document freezes the architecture and behavior of the read-only Site Runtime owner before implementation.

## Goal

Add an authoritative Runtime owner for already-deployed Site Packages so the runtime can discover, validate,
explicitly activate, persist the selected site revision, restore it after reboot through full revalidation, and
publish exactly one authoritative `/agt/maps/active` state.

The implementation must close the current `ACTIVE_MAP_UNKNOWN` provider gap without turning Runtime into an
asset-production or map-lifecycle database.

## Selected Approach

Create a new package named `agt_site_runtime`.

`agt_site_runtime` is a read-only deployment registry and activation owner. It is intentionally not named
`agt_map_manager`, because it does not import, delete, archive, purge, pin, mutate, or generate map assets.

The package consumes only deployed Site Packages under a configured `sites_root` and a configured Vehicle
Profile. It must not discover or depend on a V2/V2.5 source or install workspace.

## Existing Contract Reuse

The existing Site Package 1.0 contract remains the deployment boundary.

Reference layout:

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

The existing runtime contract validator remains the single validation truth for:

- Site schema 1.0;
- relative-path and path-escape rules;
- required assets;
- Nav2 navigation image dependency;
- SHA-256 integrity;
- Vehicle Profile compatibility;
- Ackermann geometry validity when applicable.

`agt_site_runtime` must wrap and reuse that validation behavior instead of reimplementing independent ROS-side
validation rules.

## Scope

### In Scope

- discover deployed `sites_root/<site_id>/<revision>/manifest.yaml` candidates;
- validate deployed candidates;
- list deployed candidates with READY/INVALID summaries;
- explicitly activate one valid candidate;
- publish authoritative `/agt/maps/active`;
- persist only the selected `<site_id, revision>`;
- restore the selected site after reboot only after full revalidation;
- expose narrow List / Validate / Activate ROS services;
- keep an existing healthy active site unchanged when a later activation request fails;
- integrate with existing `agt_system_manager` through `/agt/maps/active`.

### Explicitly Out of Scope

- Site Package import;
- V2 workspace discovery;
- automatic Site Package selection;
- fallback to another site or revision after restore validation failure;
- map deletion, purge, archive, pin or unpin;
- Site Package mutation;
- Nav2 map-server hot switching;
- localization backend hot switching;
- process/lifecycle orchestration;
- BUNKER unified bringup;
- HMI/Gateway command transport;
- map generation or map optimization.

## Core Safety Rules

### Explicit activation only

If no persistent active selection exists, the node may list all READY candidates but must publish no active
map, even when exactly one valid candidate exists.

### Persistent selection, non-persistent validity

Only activation intent survives reboot.

```text
Active selection is persistent.
Active validity is NOT persistent.
```

The persisted file records only the selected Site identity. It must not persist cached validation state, hashes,
resolved paths, or READY status.

### Startup restore requires full revalidation

On startup:

```text
load persisted selection
        |
        +-- absent --> start with no active map
        |
        +-- present
              |
              v
       resolve exact candidate
              |
              v
       full current validation
          /             \
       PASS             FAIL
        |                |
        v                v
 publish active       publish no active
                     do not fallback
```

A failed startup restore must leave `/agt/maps/active` unpublished. `agt_system_manager` therefore remains
fail-closed with `ACTIVE_MAP_UNKNOWN`.

### Failed switch preserves the existing active map

If a runtime already has a healthy active Site and a new activation request fails at any point, the existing
active state and persisted selection remain unchanged.

### Invalid Site Packages are never published as active

Invalid candidates remain visible through List/Validate as `STATE_INVALID`, but `/agt/maps/active` represents
only the currently accepted authoritative active Site.

## Package Boundary

Proposed package structure:

```text
src/agt_site_runtime/
├── agt_site_runtime/
│   ├── __init__.py
│   ├── models.py
│   ├── registry.py
│   ├── validator.py
│   ├── activation_store.py
│   └── summary_builder.py
├── scripts/
│   └── site_runtime_node.py
├── launch/
│   └── site_runtime.launch.py
├── config/
│   └── site_runtime.yaml
├── test/
│   ├── test_registry.py
│   ├── test_validator.py
│   ├── test_activation_store.py
│   ├── test_summary_builder.py
│   └── test_runtime_policy.py
├── CMakeLists.txt
├── package.xml
└── README.md
```

### `models.py`

Owns small ROS-independent data models used by the registry, validator, persistence and summary builder.

At minimum:

```python
@dataclass(frozen=True)
class SiteKey:
    site_id: str
    revision: str

@dataclass(frozen=True)
class SiteCandidate:
    key: SiteKey
    root: Path
    manifest_path: Path

@dataclass(frozen=True)
class ActiveSelection:
    site_id: str
    revision: str
```

Additional immutable validation/summary data structures may be added when required, but ROS messages must not
become the domain model.

### `registry.py`

Responsibilities:

- scan exactly `sites_root/<site_id>/<revision>/manifest.yaml`;
- create `SiteCandidate` objects;
- provide deterministic ordering by `(site_id, revision)`;
- resolve an exact candidate by `SiteKey`;
- ignore unrelated filesystem entries without treating them as Site Packages.

The registry does not:

- hash assets;
- perform contract validation;
- publish ROS messages;
- write persistent state;
- auto-select a candidate.

### `validator.py`

Responsibilities:

- reuse existing runtime contract validation against the selected Vehicle Profile;
- enforce directory/manifest identity consistency;
- normalize validation results into stable Site Runtime blocker codes;
- expose only deployed-candidate validation, never arbitrary external paths.

Directory identity must match manifest identity exactly:

```text
sites/greenhouse_a/2026-r01/
manifest.site.id       == greenhouse_a
manifest.site.revision == 2026-r01
```

Mismatch returns an invalid result with:

```text
SITE_IDENTITY_MISMATCH
```

### `activation_store.py`

Responsibilities:

- read the persisted active selection;
- validate persistence-file shape;
- atomically replace the active selection;
- never cache validation status.

Default state location is configured independently of the read-only Site Package root.

Example:

```text
~/.local/state/agt_navigation_runtime/active_site.yaml
```

File contents:

```yaml
schema_version: "1.0"
site_id: greenhouse_a
revision: 2026-08-16-r01
```

Atomic write sequence:

```text
write temporary file
flush
fsync temporary file
os.replace(temp, active_site.yaml)
```

The node must not publish a new active map before persistence succeeds.

### `summary_builder.py`

Responsibilities:

- build authoritative `MapVersionSummary` values from validated deployed Site data;
- resolve Runtime absolute asset paths only from paths already accepted by the Site validation rules;
- compute deterministic content identity fields.

It must not perform activation or persistence.

### `site_runtime_node.py`

The ROS node owns:

- `/agt/maps/active` publication;
- `/agt/maps/list`;
- `/agt/maps/validate`;
- `/agt/maps/activate`;
- startup restore;
- activation serialization and request idempotency;
- diagnostics/logging.

The node does not start map servers, localization backends, navigation nodes, or process managers.

## MapVersionSummary Semantics

Runtime must use one canonical interpretation for the existing `MapVersionSummary` fields.

### Identity

```text
map_id         = manifest.site.id
map_version_id = manifest.site.revision
```

`parent_map_version_id` may be populated only when the deployed contract contains an explicit parent revision;
otherwise it remains empty.

### State

P0.1 Site Runtime produces only:

```text
STATE_READY
STATE_INVALID
```

It does not produce DRAFT, PROCESSING, ARCHIVED or DELETED states.

For an accepted active candidate:

```text
state  = STATE_READY
active = true
valid  = true
```

For a valid inactive candidate:

```text
state  = STATE_READY
active = false
valid  = true
```

For an invalid candidate:

```text
state  = STATE_INVALID
active = false
valid  = false
```

`deleted` and `pinned` remain false in this read-only implementation.

### Resolved Runtime Paths

The Site Package manifest remains relocatable and continues to store relative paths.

The Runtime read model publishes normalized absolute paths for downstream consumers:

```text
navigation_yaml
localization_pcd
processing_record
tasks_directory
```

Absolute Runtime paths must only be produced from paths that remain within the validated Site Package root.

`tasks_directory` is not invented from `routes/`. For Site Package 1.0:

```text
if <site_root>/tasks/ exists:
    tasks_directory = absolute path to <site_root>/tasks/
else:
    tasks_directory = ""
```

A formal task-registry asset can be added by a future Site Package schema revision rather than hidden inside
P0.1 behavior.

### Hash Fields

```text
manifest_sha256
= SHA256(manifest.yaml bytes)

navigation_yaml_sha256
= validated digest for assets.navigation_map

navigation_image_sha256
= validated digest for the image referenced by the Nav2 map YAML

localization_pcd_sha256
= validated digest for assets.localization_map
```

`map_hash` is the deterministic Site content identity and is not equal to only the localization PCD digest.

Canonical algorithm:

1. compute `manifest_sha256` from the current manifest bytes;
2. load the validated hash mapping;
3. collect all integrity-protected effective Site assets, including the transitive Nav2 image;
4. sort entries by Site-root-relative path;
5. serialize each as `<relative-path>:<sha256>\n`;
6. hash the UTF-8 bytes of:

```text
<manifest_sha256>\n
<sorted asset lines>
```

The resulting lowercase SHA-256 digest is `map_hash`.

This gives three separate identities:

```text
map_id          logical site identity
map_version_id  human-readable deployment revision
map_hash        current deployment content identity
```

## ROS API

### `/agt/maps/active`

Type:

```text
agt_interfaces/MapVersionSummary
```

QoS:

```text
RELIABLE
TRANSIENT_LOCAL
depth = 1
```

This topic is the single authoritative active Site read model.

No separate GetActive service is added in P0.1.

### `/agt/maps/list`

Type:

```text
agt_interfaces/ListMapVersions
```

Behavior:

- scan deployed candidates;
- validate each candidate;
- return deterministic summaries;
- honor `map_id` filtering;
- honor `state == STATE_UNKNOWN` as no state filter;
- never return `deleted=true` in P0.1.

### `/agt/maps/validate`

Add a narrow new service:

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

This service validates only an exact candidate already deployed below `sites_root`.

It must not accept candidate paths, import paths, V2 workspace paths, external YAML paths, or arbitrary files.

### `/agt/maps/activate`

Reuse the existing `agt_interfaces/ActivateMapVersion` service.

Activation sequence:

```text
validate request identity
resolve exact candidate
full Site validation
build READY summary
atomically persist selection
replace in-memory active state
publish /agt/maps/active
return success
```

Failure at any step preserves the current active state.

## Error and Blocker Semantics

Service `error_code` remains coarse-grained. Stable blocker codes provide diagnostic detail.

P0.1 stable blocker vocabulary:

```text
INVALID_REQUEST
SITE_NOT_FOUND
SITE_IDENTITY_MISMATCH
SITE_SCHEMA_INVALID
SITE_PATH_UNSAFE
SITE_ASSET_MISSING
SITE_HASH_MISSING
SITE_HASH_MISMATCH
SITE_VEHICLE_INCOMPATIBLE
SITE_NAVIGATION_MAP_INVALID
SITE_VALIDATION_FAILED
ACTIVE_SELECTION_PERSIST_FAILED
```

The implementation may map multiple low-level validator issues to the same stable blocker code when that keeps
the public contract stable.

Operator-facing messages must be concise. Technical messages may include paths and expected/actual digests.
HMI/Gateway code must not be required to parse Python exception text.

## Concurrency and Idempotency

Activation state changes are serialized in-process with a re-entrant lock.

For `ActivateMapVersion.client_request_id`:

```text
same request_id + same target
    -> return the previous result without repeating persistence or publication

same request_id + different target
    -> ERROR_INVALID_REQUEST
```

A bounded recent-request cache is sufficient. No database or distributed lock is required.

Two different valid activation requests are serialized in lock acquisition order. If both succeed, the later
successful request becomes active.

## Startup Sequence

```text
load parameters
construct Registry / Validator / ActivationStore
scan registry
load persisted selection

if no selection:
    start normally
    publish no active map

if selection exists:
    resolve exact candidate
    full revalidation
    if PASS:
        restore in-memory active
        publish /agt/maps/active
    if FAIL:
        log/diagnose restore failure
        publish no active map
        do not modify the stored selection automatically
        do not fallback to any other revision
```

Leaving the invalid persisted selection in place is intentional: it preserves operator intent and makes the
restore failure inspectable. A later explicit successful activation replaces it atomically.

## SystemManager Integration

P0.1 does not change the existing SystemManager readiness policy.

Before a valid active Site exists:

```text
ACTIVE_MAP_UNKNOWN
ready = false
```

After Site Runtime publishes a valid active summary, that blocker may disappear, but the system must remain
blocked while other required evidence is absent, including localization, safety, chassis or sensor-health
evidence.

This proves that each Runtime provider clears only the blockers it owns.

## Localization and Navigation Boundary

P0.1 publishes Site identity, content identity and resolved validated asset paths.

It does not:

- restart or reconfigure Nav2 map_server;
- reload localization maps;
- change TF ownership;
- coordinate lifecycle transitions.

Those responsibilities belong to the later stable unified bringup/lifecycle convergence slice.

## Configuration

Reference parameters:

```yaml
agt_site_runtime:
  ros__parameters:
    sites_root: /opt/agt/sites
    state_root: ~/.local/state/agt_navigation_runtime
    vehicle_profile: /opt/agt/profiles/bunker.yaml
    site_schema: ""
    vehicle_schema: ""
    recent_request_limit: 128
```

Empty schema parameters mean the package resolves the repository-installed default Runtime schemas through its
installed share resources. Explicit paths are allowed for tests and deployment overrides.

The implementation must validate that required parameters resolve to readable files/directories before claiming
any Site READY.

## Testing Strategy

### Pure Python tests

Registry:

- empty sites root;
- multiple sites and revisions;
- deterministic ordering;
- unrelated hierarchy ignored;
- exact resolution;
- directory/manifest identity mismatch.

Validator:

- valid fixture passes;
- unsupported schema;
- absolute path rejection;
- path escape rejection;
- missing asset;
- hash mismatch;
- missing hash;
- incompatible vehicle;
- Nav2 image validation;
- stable blocker mapping.

ActivationStore:

- no existing state;
- valid state load;
- malformed state rejection;
- successful atomic replacement;
- simulated write/replace failure preserves old file;
- persisted contents contain only schema_version/site_id/revision.

SummaryBuilder:

- READY summary fields;
- INVALID summary fields;
- active flag behavior;
- normalized absolute paths;
- manifest digest;
- Nav2 YAML/image/PCD digest fields;
- deterministic `map_hash`;
- content mutation changes `map_hash`;
- optional tasks directory behavior.

Runtime policy:

- no auto-select with zero/one/many READY candidates;
- failed activation preserves previous active;
- successful activation persists before publishing;
- startup valid selection restores;
- startup invalid selection restores nothing;
- no startup fallback.

Existing contract fixtures should be reused where possible rather than copied into a second fixture family.

### Source/contract tests

Cloud-capable tests must assert:

- package files exist and Python sources parse;
- exact public topic/service names;
- active publisher uses transient-local reliable QoS;
- the node exposes no `ManageMapVersion` service;
- no import/delete/archive/purge/pin operation is implemented;
- package does not depend on V2/V2.5 workspace packages;
- new `ValidateMapVersion.srv` is registered in `agt_interfaces`;
- existing Runtime contracts remain green.

### Local ROS 2 integration tests

Required local acceptance scenarios:

1. start with no persisted selection -> no active map is published;
2. list a READY candidate and an INVALID candidate;
3. validate READY candidate -> success;
4. validate invalid candidate -> validation failure and blocker details;
5. activate READY candidate -> success and transient-local `/agt/maps/active` available;
6. restart node -> active candidate is revalidated and restored;
7. corrupt selected asset and restart -> active map is not restored;
8. restore asset, activate valid site, then attempt invalid switch -> original active map remains active;
9. duplicate request id with same target is idempotent;
10. duplicate request id with different target is rejected.

### SystemManager integration smoke

Sequence:

```text
start agt_system_manager only
-> ACTIVE_MAP_UNKNOWN present

start agt_site_runtime with no active selection
-> ACTIVE_MAP_UNKNOWN remains

activate valid Site
-> ACTIVE_MAP_UNKNOWN disappears
-> map_id/map_version_id propagate into TaskReadiness/RobotState
-> readiness remains false while localization/safety/chassis evidence is missing
```

## Acceptance Criteria

P0.1 is PASS only when all of the following are demonstrated:

```text
Site discovery                         PASS
Full contract validation               PASS
Directory/manifest identity binding    PASS
Explicit activation only               PASS
No auto-select                         PASS
Persistent selection                   PASS
Startup full revalidation              PASS
No fallback on failed restore          PASS
Atomic persistence                     PASS
Failed switch preserves active         PASS
/agt/maps/active transient-local       PASS
List / Validate / Activate             PASS
Invalid Site never active              PASS
Activation request idempotency         PASS
SystemManager integration              PASS
No import/delete/archive/purge/pin     PASS
Cloud contract suite                   PASS
Local ROS integration                  PASS
```

A clean-source-tree reproduction remains a separate repository hygiene gate if the developer workstation still
contains unrelated local modifications.

## Deferred Follow-Up

After P0.1 passes, the recommended next convergence slice is stable BUNKER unified bringup using the already
accepted `agt_odometry` boundary. That slice can consume the authoritative active Site paths and coordinate
Nav2/localization lifecycle without changing Site Runtime ownership.
