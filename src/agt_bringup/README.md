# agt_bringup

Runtime-only composition for `agt_navigation_runtime`.

It may compose robot description, sensors, sensor monitoring, continuous odometry,
localization, local perception, Nav2, safety, and chassis. It must not contain Qt,
semantic-map generation, coverage planning, offline map production, or dependencies on
`agt_navigation_v2` source/install trees.

The default `system.launch.py` startup is motion-safe: localization, Nav2, and the BUNKER
CAN driver remain opt-in until their required map/calibration inputs are supplied.
