colcon build --symlink-install
cmds=( "ros2 launch pointcloud_handle get_cloud_launch.py")

cmd=("ros2 launch livox_ros2_driver livox_lidar_launch.py")

for cmd in "${cmd[@]}";
do
    gnome-terminal -- bash -c "cd /home/livox_ros2_driver/livox_ros2_driver;source install/setup.bash;$cmd;exec bash;"
    sleep 0.2
done

for cmd in "${cmds[@]}"; 
do
    echo Current CMD : "$cmd"
  	gnome-terminal -- bash -c "cd $(pwd);source install/setup.bash;$cmd;exec bash;"
    sleep 0.2
done
