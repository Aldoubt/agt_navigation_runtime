# Runtime Site Owner P0.1 Acceptance

## Status

- Branch: `feat/runtime-site-owner-p01`
- Cloud/source-contract gate: PASS at Runtime Contracts run #244 before this acceptance-document-only commit.
- ROS 2 Humble build/test gate: PENDING LOCAL EVIDENCE.
- ROS graph/runtime smoke gate: PENDING LOCAL EVIDENCE.
- Merge/PR: NOT REQUESTED.

This acceptance is intentionally no-motion. It validates only deployed Site ownership, selection persistence, authoritative `/agt/maps/active`, and SystemManager fail-closed interpretation.

## 0. Protect any existing dirty workspace

Do not reset unrelated local changes. If the main Runtime checkout has modified/deleted files, use a detached worktree for this acceptance:

```bash
cd ~/agt_navigation_runtime
git fetch origin feat/runtime-site-owner-p01

git worktree add --detach \
  ../agt_navigation_runtime_site_p01 \
  origin/feat/runtime-site-owner-p01

cd ../agt_navigation_runtime_site_p01
git rev-parse HEAD
git status --short
```

Expected: the acceptance worktree is at the remote feature head and `git status --short` is empty. The original working tree remains untouched.

## 1. Build the narrow ROS package set

```bash
cd ~/agt_navigation_runtime_site_p01
source /opt/ros/humble/setup.bash

colcon build --symlink-install --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_system_manager
```

Expected: zero build failures.

Then run the package tests from fresh build products:

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash

colcon test --packages-select \
  agt_interfaces \
  agt_runtime_contracts \
  agt_site_runtime \
  agt_system_manager \
  --event-handlers console_direct+

colcon test-result --verbose
```

Hard gate: zero test failures. Do not continue runtime smoke if build or package tests fail.

## 2. Prepare deterministic deployed-site fixtures

The smoke test uses repository contract fixtures so it does not depend on a production map or a real vehicle.

```bash
cd ~/agt_navigation_runtime_site_p01

ACCEPT=/tmp/agt_site_runtime_p01_acceptance
SITES=$ACCEPT/sites
STATE=$ACCEPT/state
rm -rf "$ACCEPT"
mkdir -p "$SITES/greenhouse_test"
cp -a tests/contracts/fixtures/site_valid "$SITES/greenhouse_test/r01"

# Create a second, correctly identified but integrity-invalid deployed revision.
mkdir -p "$SITES/orchard_invalid"
cp -a tests/contracts/fixtures/site_valid "$SITES/orchard_invalid/r99"
python3 - "$SITES/orchard_invalid/r99/manifest.yaml" <<'PY'
from pathlib import Path
import sys
import yaml

path = Path(sys.argv[1])
doc = yaml.safe_load(path.read_text(encoding="utf-8"))
doc["site"]["id"] = "orchard_invalid"
doc["site"]["revision"] = "r99"
path.write_text(yaml.safe_dump(doc, sort_keys=False), encoding="utf-8")
PY
printf '\nacceptance-corruption\n' >> \
  "$SITES/orchard_invalid/r99/map/localization_map.pcd"

cat > "$ACCEPT/site_runtime.params.yaml" <<EOF
agt_site_runtime:
  ros__parameters:
    sites_root: $SITES
    state_root: $STATE
    vehicle_profile: $(pwd)/profiles/platforms/mk_mini.yaml
    recent_request_limit: 32
EOF

cat "$ACCEPT/site_runtime.params.yaml"
find "$SITES" -maxdepth 3 -name manifest.yaml -print | sort
```

Expected deployed identities:

```text
.../sites/greenhouse_test/r01/manifest.yaml
.../sites/orchard_invalid/r99/manifest.yaml
```

`greenhouse_test/r01` is valid; `orchard_invalid/r99` must fail integrity validation.

## 3. Start SystemManager and Site Runtime

Terminal A:

```bash
cd ~/agt_navigation_runtime_site_p01
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 launch agt_system_manager system_manager.launch.py
```

Terminal B:

```bash
cd ~/agt_navigation_runtime_site_p01
source /opt/ros/humble/setup.bash
source install/setup.bash
ros2 run agt_site_runtime site_runtime_node.py --ros-args \
  --params-file /tmp/agt_site_runtime_p01_acceptance/site_runtime.params.yaml
```

On the first start there is no persisted selection. The Site owner must not auto-select `greenhouse_test/r01`. It publishes an explicit no-active tombstone to revoke any stale transient-local authority.

## 4. No-selection fail-closed smoke

Terminal C:

```bash
source /opt/ros/humble/setup.bash
source ~/agt_navigation_runtime_site_p01/install/setup.bash

ros2 service call /agt/maps/list \
  agt_interfaces/srv/ListMapVersions \
  "{map_id: '', state: 0, include_deleted: false}"

ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable \
  --qos-durability transient_local

ros2 topic echo /agt/system/task_readiness --once
```

Required observations:

- list contains `greenhouse_test/r01` as `STATE_READY`, `valid=true`, `active=false`;
- list contains `orchard_invalid/r99` as `STATE_INVALID`, `valid=false`, `active=false`;
- `/agt/maps/active` is the tombstone: `STATE_UNKNOWN`, empty identity, `active=false`, `valid=false`;
- SystemManager readiness contains `ACTIVE_MAP_UNKNOWN` and `ready=false`;
- no candidate is selected automatically.

## 5. Exact validation and explicit activation

First validate both exact deployed identities:

```bash
ros2 service call /agt/maps/validate \
  agt_interfaces/srv/ValidateMapVersion \
  "{map_id: 'greenhouse_test', map_version_id: 'r01'}"

ros2 service call /agt/maps/validate \
  agt_interfaces/srv/ValidateMapVersion \
  "{map_id: 'orchard_invalid', map_version_id: 'r99'}"
```

Required: valid candidate succeeds; invalid candidate returns `ERROR_VALIDATION_FAILED` with a stable integrity blocker such as `SITE_HASH_MISMATCH`.

Activate only the valid revision:

```bash
ros2 service call /agt/maps/activate \
  agt_interfaces/srv/ActivateMapVersion \
  "{map_id: 'greenhouse_test', map_version_id: 'r01', client_request_id: 'acceptance-activate-1'}"

ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable \
  --qos-durability transient_local

ros2 topic echo /agt/system/task_readiness --once

cat /tmp/agt_site_runtime_p01_acceptance/state/active_site.yaml
```

Required observations:

- activation succeeds with `STATE_READY`;
- a late subscriber receives `map_id=greenhouse_test`, `map_version_id=r01`, `active=true`, `valid=true` immediately;
- `ACTIVE_MAP_UNKNOWN` disappears from SystemManager blockers;
- SystemManager remains `ready=false` because unrelated sensor/localization/safety/chassis evidence is intentionally absent;
- persisted YAML contains only `schema_version`, `site_id`, and `revision` and selects `greenhouse_test/r01`.

## 6. Restart restore smoke

Stop only Terminal B with Ctrl-C, leave SystemManager running, then start the identical Site Runtime command again:

```bash
ros2 run agt_site_runtime site_runtime_node.py --ros-args \
  --params-file /tmp/agt_site_runtime_p01_acceptance/site_runtime.params.yaml
```

From Terminal C:

```bash
ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable \
  --qos-durability transient_local
```

Required: the exact persisted `greenhouse_test/r01` is fully revalidated and republished READY/active. The selection file is not rewritten merely to restore it.

## 7. Corrupt-then-restart tombstone smoke

Stop only Site Runtime. Preserve the valid bytes, corrupt one integrity-protected active asset, then restart Site Runtime while SystemManager remains alive:

```bash
ACCEPT=/tmp/agt_site_runtime_p01_acceptance
ACTIVE_PCD=$ACCEPT/sites/greenhouse_test/r01/map/localization_map.pcd
cp "$ACTIVE_PCD" "$ACCEPT/localization_map.pcd.valid.bak"
printf '\nrestart-corruption\n' >> "$ACTIVE_PCD"
```

Restart Terminal B with the same command. Then Terminal C:

```bash
ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable \
  --qos-durability transient_local

ros2 topic echo /agt/system/task_readiness --once

cat /tmp/agt_site_runtime_p01_acceptance/state/active_site.yaml
```

Required observations:

- Site Runtime does not fallback to `orchard_invalid/r99` or any other revision;
- `/agt/maps/active` becomes the UNKNOWN tombstone (`active=false`, `valid=false`);
- the long-running SystemManager returns to `ACTIVE_MAP_UNKNOWN` and `ready=false`;
- persisted operator intent remains `greenhouse_test/r01`; restore failure does not silently rewrite it.

Restore the valid bytes, restart Site Runtime once more, and verify READY restoration:

```bash
cp "$ACCEPT/localization_map.pcd.valid.bak" "$ACTIVE_PCD"
```

## 8. Failed-switch preservation smoke

With restored `greenhouse_test/r01` active, request the known-invalid second revision:

```bash
ros2 service call /agt/maps/activate \
  agt_interfaces/srv/ActivateMapVersion \
  "{map_id: 'orchard_invalid', map_version_id: 'r99', client_request_id: 'acceptance-invalid-switch-1'}"

ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable \
  --qos-durability transient_local

cat /tmp/agt_site_runtime_p01_acceptance/state/active_site.yaml
```

Hard gate:

- activation fails with validation error;
- current authoritative active summary remains `greenhouse_test/r01`, READY/active/valid;
- persisted selection remains `greenhouse_test/r01`;
- no tombstone is published for a failed runtime switch while a healthy active Site already exists.

## 9. Evidence to return for acceptance

Return the following output, without deleting unrelated local source changes:

```bash
git rev-parse HEAD
git status --short
colcon test-result --verbose

ros2 service call /agt/maps/list agt_interfaces/srv/ListMapVersions \
  "{map_id: '', state: 0, include_deleted: false}"
ros2 topic echo /agt/maps/active --once \
  --qos-reliability reliable --qos-durability transient_local
ros2 topic echo /agt/system/task_readiness --once
cat /tmp/agt_site_runtime_p01_acceptance/state/active_site.yaml
```

Also report whether all five runtime scenarios passed: no-selection, explicit activation, restart restore, corrupt-restart tombstone, and failed-switch preservation.

## Acceptance decision

P0.1 is PASS only when all of the following are true:

1. feature-head cloud contracts are green;
2. Humble narrow build succeeds;
3. selected package tests report zero failures;
4. no-selection remains fail-closed;
5. explicit valid activation produces the single authoritative READY active Site;
6. restart restore revalidates the exact persisted selection;
7. invalid restart revokes stale authority through the tombstone and SystemManager reports `ACTIVE_MAP_UNKNOWN`;
8. failed runtime switching preserves the previous valid active Site and persisted selection.

Until those local ROS observations are supplied, P0.1 remains **IMPLEMENTED / LOCAL ACCEPTANCE PENDING**, not fully accepted.
