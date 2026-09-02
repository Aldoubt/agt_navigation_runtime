# AGT Robot HMI

ROS2 Humble based inspection robot operator console for AGT Robotics.

The HMI handles map/status display, operator interaction and inspection-task
editing. Robot business logic remains in `agt_navigation_runtime` and
`agt_vision_runtime`; the Qt process does not directly control Nav2, drivers,
gimbals, or AI models.

Inspection points are stored in `config/tasks/*.yaml`. The current ROS boundary
uses standard-message placeholders; see [`docs/architecture.md`](docs/architecture.md)
for the contract and migration path to `agt_robot_hmi_interfaces`.

## Build

### Offline/system-dependency build

This checkout can build without FetchContent downloads when the system Qt5,
nlohmann-json and yaml-cpp development packages are installed. The docking
system is supplied as a fixed local source checkout:

```bash
git clone --depth 1 --branch 4.4.0 \
  https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git \
  vendor/qt-advanced-docking-system
cmake -S . -B build-offline2 -DCMAKE_BUILD_TYPE=Release \
  -DAGT_HMI_USE_SYSTEM_DEPS=ON \
  -DAGT_HMI_DOCKWIDGET_SOURCE_DIR="$PWD/vendor/qt-advanced-docking-system"
cmake --build build-offline2 -j2
cmake --install build-offline2
```

Set `map_config.path` to a YAML map, not directly to a PGM. HMI map editing
writes back PGM/YAML and an optional `.topology` beside the loaded map. Use a
working copy under `runtime/hmi_working/`; never edit an Active Site or the
original `pcd2pgm` output in place.

```bash
source /opt/ros/humble/setup.bash
colcon build --packages-select agt_robot_hmi
source install/setup.bash
ros2 run agt_robot_hmi agt_robot_hmi
```

The application displays `/map`, `/agt/robot/pose`, and `/agt/robot/battery`,
and accepts task status and JSON vision results from the AGT runtime/mock.
Right-click the map to add an inspection point or set a navigation goal.
