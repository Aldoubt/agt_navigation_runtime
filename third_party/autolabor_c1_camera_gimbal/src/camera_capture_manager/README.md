# camera_capture_manager

`AcquireView` is the inspection system's visual acquisition capability. A
navigation runtime requests a view, waits for the result, and then sends the
saved image to a vision model. Runtime does not operate the gimbal angle topic,
serial port, or `usb_cam` directly.

The manager sends the existing `MovePantilt` goal, waits for a stable
`camera_gimbal_msgs/msg/GimbalState`, then accepts only a new
`/cv_camera0/image_raw` frame with a timestamp later than the stable point. The
image is saved as a JPEG containing timestamp, yaw and pitch, for example:
`capture_20260901_123000_yaw30_pitch10.jpg`.

This is a capability coordinator, not a hardware driver; it does not implement
the C1 protocol, serial communication, or camera driver.
