from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    return LaunchDescription([Node(package='agt_bt_executor', executable='bt_smoke_runner', name='agt_bt_smoke_runner', output='screen')])
