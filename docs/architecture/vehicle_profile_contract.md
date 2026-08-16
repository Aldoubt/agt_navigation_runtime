# Vehicle Profile Contract 1.0

## Purpose

Vehicle Profiles describe the physical and runtime constraints required to execute navigation safely on a specific chassis

The canonical directory remains

```text
profiles/platforms/
```

No parallel `vehicles/` tree is introduced in V3-01

## Versioning

Every V3 Vehicle Profile must declare

```yaml
schema_version: "1.0"
```

The existing `platform:` object remains the profile root for compatibility with current runtime consumers

## Required Common Fields

```yaml
schema_version: "1.0"
platform:
  name: <vehicle-id>
  kinematics: <model>
  footprint_frame: base_footprint
  base_frame: base_link
  geometry:
    length: <meters>
    width: <meters>
    footprint: [[x, y], ...]
  limits:
    max_forward_velocity: <m/s>
    max_reverse_velocity: <m/s>
```

## Ackermann Requirements

For `platform.kinematics: ackermann`, runtime validation additionally requires

- wheelbase, using canonical `wheel_base` or accepted legacy `wheelbase`
- `min_turning_radius`
- a footprint containing at least three 2D points

The validator does not derive missing geometry from unrelated steering fields

## Truth and Policy Separation

A profile may contain three distinct classes of information

### Manufacturer Truth

Examples include overall dimensions, rated maximum speed, manual-specified turning radius, CAN protocol facts, and published vehicle limits

### Measured / Calibrated Truth

Examples include measured reference-point offsets, effective steering response, stopping distance, latency, and calibrated footprint

### Navigation Operating Limits

Examples include conservative runtime maximum velocity, reverse velocity, acceleration limits, and controller policy

Navigation operating limits must not overwrite manufacturer or measured truth. Runtime policy may be more conservative than the physical platform capability

## Validation Semantics

Structural validation is performed with `schemas/vehicle_profile.schema.json`

Semantic Ackermann checks are repeated in the runtime validator so invalid geometry fails closed even if a future schema becomes more permissive

A Vehicle Profile with an unsupported version or missing required geometry is NOT READY
