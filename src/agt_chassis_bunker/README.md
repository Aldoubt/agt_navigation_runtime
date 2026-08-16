# agt_chassis_bunker

BUNKER-specific runtime backend for the AGT navigation execution chain.

## Boundary

```text
/agt/navigation/cmd_vel_raw
  -> Nav2 Collision Monitor
  -> /agt/navigation/cmd_vel
  -> agt_safety
  -> /agt/safety/cmd_vel
  -> agt_chassis
  -> /agt/chassis/cmd_vel
  -> agt_chassis_bunker / bunker_base
```

This package owns only BUNKER-specific runtime integration:

- BUNKER launch composition
- `bunker_base` dependency
- `bunker_msgs` status conversion
- BUNKER status/battery/connectivity bridge
- BUNKER-specific safety envelope defaults

The generic `agt_safety` package contains no tracked-vehicle projection and the generic `agt_chassis` package contains no BUNKER dependencies.
