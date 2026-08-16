# V3-04 MK-mini Virtual-CAN Software HIL Design

## Goal

Add a software-only hardware-in-the-loop path for the MK-mini chassis backend using Linux `vcan`, so the real `agt_chassis_mk_mini` adapter, fail-safe state machine, protocol codec, SocketCAN transport, and ROS feedback publishers can be exercised before connecting a physical VCU.

This substage validates the CAN execution boundary. It does not replace Gazebo/vehicle dynamics simulation and it does not change the real backend control contract.

## Scope

The HIL loop is:

```text
/agt/chassis/cmd_vel
        |
        v
agt_mk_mini_adapter
        |
        v
/agt/chassis/backend/ackermann_command
        |
        v
agt_mk_mini_can_backend
        |
        v
      vcan0
        |
        v
agt_chassis_mk_mini_sim / MK-mini VCU simulator
        |
        +--> ctrl_fb
        +--> left/right rear wheel feedback
        +--> BMS feedback
        |
        v
      vcan0
        |
        v
agt_mk_mini_can_backend
        |
        +--> /agt/chassis/backend/ackermann_feedback
        +--> /agt/chassis/wheel_twist
        +--> /agt/chassis/status
        +--> /agt/chassis/connected
        +--> /battery
```

Out of scope:

- Gazebo/world rendering
- obstacle simulation
- Nav2 planner/controller tuning
- real steering calibration
- automatic `sudo ip link` or host network mutation from ROS launch
- changes to the physical MK-mini protocol or control topic contract

## Package boundary

Create a separate ROS 2 package:

```text
src/agt_chassis_mk_mini_sim/
```

The simulator is development/test-only. `agt_chassis_mk_mini` remains the real runtime backend and must not depend on the simulator package.

The simulator package may depend on `agt_chassis_mk_mini` for public protocol constants/enums and SocketCAN frame transport primitives, but feedback frame bytes are packed independently in the simulator rather than by reusing backend feedback-decoder implementation. This prevents a feedback packing/decoding bug from becoming self-consistent in the HIL loop.

## Simulated VCU behavior

### Command reception

The simulator listens on a configurable SocketCAN interface, default `vcan0`, for logical extended CAN ID:

```text
0x18C4D2D0  ctrl_cmd
```

It validates:

- DLC = 8
- BCC/XOR checksum
- AliveCounter progression
- gear field
- speed field
- steering field

Malformed frames are counted and ignored.

### Vehicle state

The simulator models only enough dynamics to validate protocol/state transitions:

- gear state
- longitudinal speed
- steering command
- left/right rear wheel speed
- encoder pulse count
- battery voltage/current/capacity
- VCU mode

Longitudinal velocity follows the commanded target with bounded first-order acceleration/deceleration. It is not a tire/vehicle dynamics model.

Direction changes do not instantly reverse velocity. The simulated VCU confirms D/R only when speed is within the stationary threshold. This allows the real backend's gear-feedback interlock to be exercised.

### Feedback production

The simulator publishes the same logical feedback frames expected by the real backend:

```text
0x18C4D2EF  ctrl_fb
0x18C4D7EF  left rear wheel feedback
0x18C4D8EF  right rear wheel feedback
0x18C4E1EF  BMS info feedback
```

Default feedback period is 10 ms for control and wheel feedback. BMS may run at a lower configurable rate.

All feedback frames carry valid BCC and rolling counters according to the protocol contract.

## Safety behavior

The HIL launch must default to safe values:

```text
operation_mode:=monitor
can_interface:=vcan0
steering_calibration_confirmed:=false
allow_uncalibrated_control:=false
```

A dedicated HIL launch may opt into control only through explicit launch arguments. It must never configure a host CAN interface and must never execute `sudo`, `ip link`, or shell commands.

The simulator is the only peer expected on `vcan0` during the software-HIL run. No physical `can0` device is required.

## Test scenarios

The acceptance suite must cover all of these scenarios.

### 1. Monitor-only startup

- simulator starts
- real backend starts in monitor mode
- feedback is received
- `/agt/chassis/connected` becomes true
- no `ctrl_cmd` frame is transmitted by the backend

### 2. Forward command

- explicit control mode
- steering calibration gate explicitly opened for HIL only
- publish positive Twist
- adapter produces AckermannCommand
- backend requests D
- simulator confirms D
- backend does not send nonzero speed before D feedback confirmation
- simulated speed converges positive
- Ackermann feedback and wheel twist become positive

### 3. Reverse interlock

- command reverse while moving forward
- backend first requests zero speed
- simulator decelerates to stationary
- backend requests R
- simulator confirms R
- only then does negative signed ROS feedback appear

### 4. Command timeout

- stop publishing Twist
- adapter stops refreshing AckermannCommand
- backend continues 100 Hz VCU heartbeat
- backend requests zero speed
- simulator reaches standstill
- after park hold, backend requests P
- simulator confirms P

### 5. Corrupted feedback

The simulator supports an opt-in fault parameter that corrupts BCC or drops feedback frames. The backend must expose disconnected/error diagnostics after its existing feedback timeout rather than continuing to report healthy state.

## Observability

The simulator publishes a small ROS diagnostic/status surface for test visibility, but the primary acceptance evidence comes from the real backend topics:

```text
/agt/chassis/connected
/agt/chassis/status
/agt/chassis/backend/ackermann_feedback
/agt/chassis/wheel_twist
/battery
```

The simulator additionally exposes counters for received commands, checksum failures, AliveCounter gaps, and transmitted feedback frames.

## Host setup

Host vcan setup is intentionally outside ROS launch. The documented setup is:

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan 2>/dev/null || true
sudo ip link set up vcan0
ip -details link show vcan0
```

Teardown is optional:

```bash
sudo ip link del vcan0
```

## Acceptance

Software-HIL is PASS only when:

1. the new simulator package builds under ROS 2 Humble;
2. pure simulator protocol/state tests pass;
3. existing V3-01/V3-02/V3-03/V3-04 tests remain green;
4. `ros2 launch ... --show-args` resolves without import/package errors;
5. the five HIL scenarios above pass on local `vcan0`;
6. no real `can0` device is opened during the HIL run;
7. the physical backend's default mode remains `monitor` and uncalibrated control remains blocked.

## Warning cleanup boundary

The existing CMake stderr cleanup is intentionally separate from the HIL implementation. After the HIL loop is green, warning cleanup can be applied as repository hygiene without mixing third-party build-system edits into the simulator feature commits.
