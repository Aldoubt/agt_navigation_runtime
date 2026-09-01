# Branch Cleanup Plan

## Purpose

This document defines the branch consolidation plan for `agt_navigation_runtime` after the runtime architecture, hardware bringup, operator gateway, and field integration work have entered the stabilization phase.

The goal is to reduce long-lived feature branches and keep the repository aligned with a product-style development workflow.

---

# Target Branch Model

```text
main
 |
 +-- feat/runtime-navigation-v3
 |
 +-- feat/hardware-bringup
 |
 +-- feat/operator-gateway
 |
 +-- feat/field-integration
 |
 +-- feat/inspection
 |
 +-- feat/mk-mini-can
 |
 +-- experiment/*
```

---

# Keep Branches

## Runtime Core

| Branch | Action | Reason |
|---|---|---|
| feat/runtime-navigation-convergence-p1 | rename/merge candidate | Current runtime architecture evolution line |
| feat/v3-01-runtime-contracts | keep temporarily | Runtime contract foundation |

## Hardware

| Branch | Action | Reason |
|---|---|---|
| feat/hardware-bringup-p0 | keep until vehicle acceptance | BUNKER + MID360 bringup |
| v3-04/mk-mini-can | keep temporarily | Chassis integration |

## Field Delivery

| Branch | Action | Reason |
|---|---|---|
| feat/field-real-vehicle-integration | keep until acceptance complete | Physical robot integration |
| feat/field-navigation-baseline | keep | Navigation baseline |

## Application

| Branch | Action | Reason |
|---|---|---|
| feat/operator-gateway-p1-mission-control | keep if not fully merged | HMI/control capability |
| feat/camera-gimbal-driver-import | keep | Inspection hardware capability |
| feat/inspection-multiview-evidence | keep | Inspection product direction |

---

# Merge Completed Branches

The following branches contain work that has already entered other branches and should be merged historically only if needed, otherwise removed:

- feat/runtime-site-owner-p01
- feat/operator-gateway-control-lease

---

# Archive/Delete Candidates

## Duplicate Contract Branches

- v3-01/contracts-work
- v3-01/contracts-work-spec
- feat/v3-01-runtime-contracts-spec

Reason:

Duplicated specification and implementation tracking branches.

---

## Acceptance Freeze Branches

Convert to tags/releases instead of long-lived branches:

- v3-02/acceptance-freeze
- v3-03/acceptance-freeze

Suggested tags:

```
v3.2-runtime-acceptance
v3.3-runtime-acceptance
```

---

## Experimental Navigation Branches

Move to experiment namespace or archive:

- feat/nav2-planner-smoke-harness
- feat/headland-planner-smoke
- feat/bunker-rtabmap-slope-nav

Reason:

Useful for research, but should not remain in production runtime branch list.

---

## Vision Algorithm Branch

Candidate:

- feat/vision-camera-algorithms

Recommendation:

Move vision algorithm development into a dedicated repository such as `agt_vision_runtime`.

Reason:

Runtime should consume vision capabilities through interfaces instead of owning algorithm implementation.

---

# Recommended Cleanup Order

1. Verify merged PR branches.
2. Create release tags for acceptance freeze branches.
3. Merge hardware acceptance branch after real vehicle validation.
4. Merge field integration branch after system acceptance.
5. Freeze main as a runtime delivery baseline.
6. Remove obsolete feature branches.

---

# Future Policy

- Feature branches should have a clear owner and merge target.
- Acceptance branches should become tags after validation.
- Hardware drivers, vision algorithms, and navigation algorithms should remain separated by capability boundaries.
- `main` should represent deployable robot runtime state.
