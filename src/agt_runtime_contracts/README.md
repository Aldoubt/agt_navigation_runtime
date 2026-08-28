# agt_runtime_contracts

Installable, ROS-node-free Runtime deployment-contract validation library.

This package owns the canonical Python validation behavior used by both repository tooling and installed Runtime components. It validates Vehicle Profiles and Site Packages, including schema shape, path containment, required assets, Nav2 map-image dependencies, SHA-256 integrity, vehicle compatibility, and Ackermann geometry.

The package installs the canonical Site Package and Vehicle Profile JSON schemas under:

```text
share/agt_runtime_contracts/schemas/
```

`tools/runtime_contracts` remains a compatibility import/CLI layer and must not contain a second validator implementation.
