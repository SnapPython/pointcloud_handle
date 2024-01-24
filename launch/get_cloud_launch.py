from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    get_cloud =Node(
        package='pointcloud_handle',
        executable='get_cloud',
        name='get_cloud',
        output='screen'
    )
    return LaunchDescription([get_cloud])