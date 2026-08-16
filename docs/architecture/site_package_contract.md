# Site Package Contract 1.0

## Purpose

A Site Package is the only supported deployment boundary from V2.5 asset production into the V3 runtime

V3 consumes the package read-only and must not discover assets from a V2.5 workspace

## Reference Layout

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

## Manifest

```yaml
site_schema_version: "1.0"

site:
  id: greenhouse_a
  revision: 2026-08-16-r01

frames:
  global: map

assets:
  navigation_map: map/navigation.yaml
  localization_map: map/localization_map.pcd
  semantic_map: semantic/semantic_map.yaml
  route_graph: routes/route_graph.yaml

compatibility:
  vehicle_profiles:
    - mk_mini

integrity:
  hashes_file: hashes.yaml
```

## Path Rules

All paths in `assets` and `integrity.hashes_file` are relative to the Site Package root

The `image` field inside the Nav2 navigation-map YAML is resolved relative to that YAML file. It is also treated as a Site Package asset and must remain inside the Site Package root

The validator rejects

- absolute paths
- `..` traversal that escapes the Site Package root
- missing files
- symlink/resolution results outside the Site Package root
- a missing or unsafe Nav2 map image dependency

A Site Package must remain relocatable as one directory or archive

## Integrity

`hashes.yaml` maps Site-root-relative artifact paths to lowercase SHA-256 digests

Example

```yaml
hashes:
  map/navigation.yaml: 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
  map/navigation.pgm: fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210
```

Every manifest-declared asset must have a hash entry and its current bytes must match that digest

Transitive runtime assets discovered from a declared asset are also integrity-protected. In schema 1.0 this includes the Nav2 map image referenced by `assets.navigation_map`

The manifest itself does not hash itself

## Vehicle Compatibility

The runtime-selected `platform.name` must appear in `compatibility.vehicle_profiles`

A structurally valid Site Package that does not list the selected vehicle is NOT READY

## Fail-Closed Semantics

The runtime validator returns failure for

- unsupported schema version
- invalid manifest shape
- unsafe path
- missing asset
- missing transitive map image
- missing hash entry
- hash mismatch
- incompatible vehicle
- invalid Ackermann geometry in the selected Vehicle Profile

The validator does not guess missing paths or geometry
