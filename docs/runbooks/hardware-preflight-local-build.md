# Hardware Preflight — Local Humble Build/Test

This runbook is the local-computer software verification path for the Runtime product branch:

```text
feat/field-real-vehicle-integration
```

It deliberately separates **preflight package software verification** from the **full product dependency build** and from **physical robot acceptance**.

## A. Fast software-only smoke (recommended first)

Use this first on any Ubuntu 22.04 + ROS 2 Humble development computer. It does not require BUNKER, MID360, camera, gimbal, CAN, or the full Runtime dependency closure.

### A1. Environment

```bash
source /opt/ros/humble/setup.bash
python3 --version
ros2 --help >/dev/null
colcon --help >/dev/null
```

If the build/test tools are missing:

```bash
sudo apt update
sudo apt install -y \
  python3-colcon-common-extensions \
  python3-pytest \
  python3-yaml \
  ros-humble-ament-cmake-python \
  ros-humble-ament-cmake-pytest
```

### A2. Checkout the frozen field-integration branch

From an existing clone:

```bash
cd ~/agt_navigation_runtime
git fetch origin
git checkout feat/field-real-vehicle-integration
git pull --ff-only origin feat/field-real-vehicle-integration
git status --short
git rev-parse HEAD
```

For a clean disposable clone instead:

```bash
cd ~
git clone -b feat/field-real-vehicle-integration \
  https://github.com/Aldoubt/agt_navigation_runtime.git \
  agt_navigation_runtime_field
cd agt_navigation_runtime_field
```

### A3. Run the same Humble smoke used by CI

```bash
bash tools/test_hardware_preflight_humble.sh
```

The script creates a temporary isolated colcon workspace containing only:

```text
agt_description
agt_hardware_bringup
```

It then performs:

1. ROS 2 Humble build;
2. `colcon test` for both packages;
3. `colcon test-result --verbose`;
4. installed `socketcan_preflight.py --help` smoke;
5. installed `vehicle_preflight.py --help` smoke;
6. installed launch/config asset checks.

Expected final line:

```text
PASS: ROS 2 Humble preflight package build/test/install smoke
```

This proves the two preflight packages themselves build/install correctly on Humble. It does **not** prove that BUNKER/Livox/inspection vendor dependencies or physical hardware are ready.

## B. Full local Runtime dependency build

Run this after A passes. This checks the actual workspace dependency closure that `agt_hardware_bringup` composes at runtime.

### B1. Install resolvable system dependencies

```bash
source /opt/ros/humble/setup.bash
sudo rosdep init 2>/dev/null || true
rosdep update
rosdep install --from-paths src \
  --ignore-src \
  --rosdistro humble \
  -r -y
```

If `rosdep` reports an unresolved key, record the exact package/key instead of installing an unrelated substitute. Vendored/source packages already present under `src/` should normally be excluded by `--ignore-src`.

### B2. Build the real dependency closure

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install \
  --event-handlers console_direct+ \
  --packages-up-to agt_hardware_bringup
```

Then:

```bash
source install/setup.bash
```

### B3. Run package tests

```bash
colcon test \
  --event-handlers console_direct+ \
  --packages-select \
    agt_description \
    agt_hardware_bringup

colcon test-result --verbose
```

Acceptance for this stage:

```text
0 failed tests
```

### B4. Installed software smoke without hardware

```bash
ros2 pkg prefix agt_description
ros2 pkg prefix agt_hardware_bringup

ros2 run agt_hardware_bringup socketcan_preflight.py --help
ros2 run agt_hardware_bringup vehicle_preflight.py --help

ros2 launch agt_hardware_bringup bunker_mid360.launch.py --show-args
```

`--show-args` is a software/launch inspection only. Do not start the hardware launch merely to make this gate green when the computer is not connected/configured for the vehicle.

## C. Local no-ROS contract check

This is useful when modifying parser/contract code:

```bash
python3 -m pytest -q \
  src/agt_hardware_bringup/test \
  src/agt_description/test

python3 -m compileall -q \
  src/agt_hardware_bringup \
  src/agt_description
```

## D. First physical-machine step after software passes

Only when the computer is connected to the real BUNKER/MID360 stack, continue with the read-only procedure in:

```text
docs/acceptance/hardware-first-vehicle-checklist.md
```

The first physical gates remain:

```text
SocketCAN read-only evidence
-> operation_mode:=monitor
-> BUNKER status/RC health
-> MID360 lidar/IMU quality
-> static TF topology
-> physical MID360 extrinsic verification
```

Do not enable Safety motion, publish `cmd_vel`, start a Mission, or command the gimbal during these gates.

## Failure handoff

If any local command fails, retain these outputs before changing code:

```bash
git rev-parse HEAD
colcon list
colcon test-result --verbose
```

For a build failure also copy the **first package that fails** and its first compiler/CMake error. Do not diagnose from the final `Summary:` line alone.
