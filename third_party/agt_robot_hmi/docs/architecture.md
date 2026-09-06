# AGT Robot HMI architecture

The HMI is a ROS 2 Humble presentation and task-editing client. It does not
call Nav2, camera drivers, gimbal drivers, or AI models. Those responsibilities
belong to `agt_navigation_runtime` and `agt_vision_runtime`.

The current transport uses stable placeholder contracts while the dedicated
`agt_robot_hmi_interfaces` package is being finalized:

| Purpose | ROS 2 endpoint | Placeholder type |
|---|---|---|
| task file handoff | `/agt/task/request` | `std_msgs/msg/String` |
| start/pause/cancel | `/agt/task/{start,pause,cancel}` | `std_srvs/srv/Trigger` |
| task status | `/agt/task/status` | `std_msgs/msg/String` |
| vision result | `/agt/vision/result` | JSON in `std_msgs/msg/String` |

The placeholder boundary can be replaced in `src/ros_interface` without
changing the inspection widgets.
