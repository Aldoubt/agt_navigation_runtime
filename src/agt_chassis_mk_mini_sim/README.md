# agt_chassis_mk_mini_sim

Development-only MK-mini virtual VCU for the V3-04 SocketCAN software-HIL loop.

## Boundary

This package is not a vehicle runtime backend and must never be a dependency of `agt_chassis_mk_mini`.

```text
/agt/chassis/cmd_vel
        |
        v
real agt_mk_mini_adapter
        |
        v
real agt_mk_mini_can_backend
        |
        v
      vcan0
        |
        v
agt_mk_mini_vcu_sim
        |
        +-- ctrl_fb
        +-- left/right rear wheel feedback
        +-- BMS feedback
        |
        v
      vcan0
        |
        v
real backend decoder / diagnostics
```

The simulator independently packs VCU feedback bytes. It intentionally does not call the real backend feedback decoders while generating feedback, so the HIL loop does not validate one codec with itself.

## Host setup

The launch file never configures host networking. Create `vcan0` explicitly before launching:

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan 2>/dev/null || true
sudo ip link set up vcan0
ip -details link show vcan0
```

## Safe default launch

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py
```

Defaults are:

```text
can_interface=vcan0
operation_mode=monitor
steering_calibration_confirmed=false
allow_uncalibrated_control=false
drop_feedback=false
corrupt_bcc=false
```

Monitor mode must receive simulated feedback while the real backend transmits no `ctrl_cmd` frames.

## Control-mode HIL

For the virtual VCU only, use the simulator's exact 1:1 steering convention to open the normal calibration gate:

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=control \
  steering_calibration_confirmed:=true
```

This flag in virtual-CAN HIL is **not** evidence that the physical chassis steering mapping has been calibrated. Real hardware acceptance still requires measured steering calibration.

## Fault injection

Drop all simulated feedback:

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=monitor \
  drop_feedback:=true
```

Or transmit feedback with a deliberately bad BCC:

```bash
ros2 launch agt_chassis_mk_mini_sim mk_mini_vcan_hil.launch.py \
  operation_mode:=monitor \
  corrupt_bcc:=true
```

The real backend should report disconnected/error once valid `ctrl_fb` is stale or unavailable.

## Acceptance runner

The runner does not create `vcan0` and does not start or stop the HIL launch. Start the required launch in one terminal, then run one scenario in another:

```bash
ros2 run agt_chassis_mk_mini_sim vcan_hil_acceptance.py \
  --scenario <monitor_only|forward|reverse_interlock|command_timeout|feedback_fault>
```

Restart the HIL launch between scenarios so state, gears, feedback freshness, and counters start from a known baseline. See `docs/acceptance/v3-04-vcan-hil.md` for the exact five-scenario procedure.
