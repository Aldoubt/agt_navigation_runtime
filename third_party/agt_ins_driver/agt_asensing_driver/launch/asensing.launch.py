from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    config = os.path.join(get_package_share_directory('agt_asensing_driver'), 'config', 'asensing.yaml')
    return LaunchDescription([Node(package='agt_asensing_driver', executable='asensing_node', name='asensing_driver', output='screen', parameters=[config])])
