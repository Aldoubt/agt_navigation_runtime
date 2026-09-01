# Branch Cleanup Execution Guide

## Target

Consolidate `agt_navigation_runtime` branches after runtime architecture convergence.

## Delete after verification

```bash
git push origin --delete \
  feat/runtime-site-owner-p01 \
  feat/operator-gateway-control-lease
```

## Remove duplicated v3 specification branches

```bash
git push origin --delete \
  v3-01/contracts-work \
  v3-01/contracts-work-spec \
  feat/v3-01-runtime-contracts-spec
```

## Archive experimental branches

Review before deletion:

```bash
git push origin --delete \
  feat/nav2-planner-smoke-harness \
  feat/headland-planner-smoke \
  feat/bunker-rtabmap-slope-nav \
  feat/vision-camera-algorithms
```

## Protected branches

Do not delete before physical robot acceptance:

- feat/hardware-bringup-p0
- feat/field-real-vehicle-integration
- feat/field-navigation-baseline

## Recommended release point

After field acceptance:

```
main -> v0.3.0-field-ready
```
