# P1-04 Active Site -> Navigation Binding Implementation Plan

Date: 2026-08-29
Branch: `feat/runtime-navigation-convergence-p1`
Design authority: `docs/superpowers/specs/2026-08-29-runtime-navigation-convergence-p1-design.md`

## Goal

Add one thin, read-only `agt_site_navigation` component that turns the authoritative `/agt/maps/active` Site selection into a deterministic, hash-verified navigation asset binding without becoming a second Site owner, a Mission executor, a Nav2 lifecycle owner, or a `map -> odom` publisher.

## Frozen ownership

```text
agt_site_runtime
  owns active Site discovery / validation / activation

agt_site_navigation   # P1-04
  consumes /agt/maps/active
  re-resolves the exact deployed Site revision
  verifies active identity + hashes + asset paths
  publishes one typed resolved binding

P1-05
  later owns NavigationRuntimeStatus / lifecycle readiness aggregation
```

## Task 1 — typed binding contract + pure resolver

TDD RED first.

Add `SiteNavigationBinding.msg` carrying only binding evidence:

- binding state: UNKNOWN / READY / BLOCKED / ERROR
- Site id/revision/hash
- manifest hash
- navigation YAML path/hash
- navigation image path/hash
- localization PCD path/hash
- processing record path
- blocker codes/messages

Add pure `agt_site_navigation.resolver` logic that:

1. rejects no active Site;
2. rejects non-READY / invalid / inactive summaries;
3. resolves the exact Site through `SiteRegistry`;
4. re-runs `SiteValidator` using the same Runtime Contract implementation;
5. rebuilds canonical Site summary and compares identity, hashes and paths against `/agt/maps/active`;
6. resolves the navigation image path deterministically from the validated Site manifest/YAML;
7. returns an immutable binding value.

No file mutation is allowed.

## Task 2 — ROS binding node

Create package `agt_site_navigation` and node `site_navigation_binding_node.py`.

Behavior:

```text
/agt/maps/active (TRANSIENT_LOCAL)
  -> resolver
  -> /agt/navigation/site_binding (TRANSIENT_LOCAL)
```

On tombstone/no-active/invalid/corrupt/mismatch input, publish BLOCKED/ERROR binding with empty asset paths and stable blocker code. Never retain the previous READY binding after authority is revoked.

The node must not:

- publish TF;
- start/stop a Mission;
- command Nav2;
- mutate Site assets;
- infer Nav2 lifecycle READY.

## Task 3 — launch/install/source contracts

Add an installable launch entry point for the binding node with explicit:

- `sites_root`
- `site_vehicle_profile`

Runtime Contract CI gains a dedicated P1-04 binding test step or extends the canonical Site/navigation test group without deleting any earlier gate.

Source contracts must prove the package does not import TF broadcasters, Mission execution APIs, or filesystem write helpers.

## Task 4 — acceptance and handoff

Acceptance requires:

- no Active Site -> fail-closed;
- missing Site -> fail-closed;
- corrupted/mismatched asset hash -> fail-closed;
- exact Active Site -> deterministic READY binding;
- authority tombstone clears READY binding;
- canonical Runtime Contracts green.

Evidence states:

```text
Code   -> may be COMPLETE after source/unit implementation
STATIC -> PASS only after canonical CI
HUMBLE -> remain PENDING until local ROS 2 Humble build/runtime smoke
FIELD  -> remain PENDING; P1-04 does not claim vehicle acceptance
```

Do not begin P1-05 until this slice has its acceptance record and convergence status update.
