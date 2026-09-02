# camera_gimbal_msgs

`camera_gimbal_msgs` is the frozen capability-interface package between the
hardware driver and the navigation runtime. It defines only the public
`GimbalState` message and `AcquireView` action; it contains no node or
implementation.

The future `agt_navigation_runtime` must depend on these capability interfaces,
not on C1-specific details. In particular, runtime does not depend on:

- the C1 protocol;
- CH340;
- the serial driver;
- `usb_cam`.

Build and inspect the generated interfaces with:

```bash
colcon build --symlink-install --packages-select camera_gimbal_msgs
source install/setup.bash
ros2 interface show camera_gimbal_msgs/msg/GimbalState
ros2 interface show camera_gimbal_msgs/srv/AcquireView
```

This package intentionally does not implement a manager node, filter, action,
or service server.
