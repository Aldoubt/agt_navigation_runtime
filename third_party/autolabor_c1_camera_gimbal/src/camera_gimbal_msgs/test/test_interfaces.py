import subprocess


def show(interface):
    return subprocess.run(
        ['ros2', 'interface', 'show', interface],
        check=True,
        capture_output=True,
        text=True,
    ).stdout


def test_gimbal_state_interface_is_generated():
    output = show('camera_gimbal_msgs/msg/GimbalState')
    for field in ('builtin_interfaces/Time stamp', 'float32 yaw_encoder',
                  'float32 yaw_filtered', 'bool stable', 'bool healthy',
                  'string status'):
        assert field in output


def test_acquire_view_interface_is_generated():
    output = show('camera_gimbal_msgs/action/AcquireView')
    for field in ('float32 yaw', 'float32 pitch', 'float32 settle_timeout',
                  'string save_dir', 'bool success', 'string image_path',
                  'builtin_interfaces/Time image_stamp', 'string message',
                  'float32 current_yaw', 'float32 current_pitch',
                  'bool stable', 'string state'):
        assert field in output
