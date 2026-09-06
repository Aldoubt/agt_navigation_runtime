# camera_gimbal_manager

This node provides hardware feedback abstraction, median filtering, health and
stability detection, and `/camera_gimbal/state` publication above
`pantilt_camera_serial`.

The node subscribes to `/pantilt_camera_serial0/pantilt_angle_info`. Encoder values
are median-filtered with a five-sample window by default. Stability requires ten
filtered samples within 1.5 degrees of the reported target for 0.5 seconds.

This package does not send commands and does not replace or modify the hardware driver.
