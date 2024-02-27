#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include "multiple_object_tracking_lidar.hpp"

int main(int argc, char * argv[])
{
    // Force flush of the stdout buffer.
    // This ensures a correct sync of all prints
    // even when executed simultaneously within a launch file.
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    
    rclcpp::init(argc, argv);
    rclcpp::executors::SingleThreadedExecutor exec;

    const rclcpp::NodeOptions options;
    auto my_node = std::make_shared<multiple_object_tracking_lidar::MultipleObjectTrackingLidar>(options);
    //auto pcl_object_detection = rclcpp::Node::make_shared("PclObjectDetection");

    exec.add_node(my_node);
    

    static tf2_ros::StaticTransformBroadcaster static_broadcaster(my_node);
    geometry_msgs::msg::TransformStamped static_transformStamped;

    static_transformStamped.header.stamp = my_node->now();
    static_transformStamped.header.frame_id = "map";
    static_transformStamped.child_frame_id = "your_frame";
    static_transformStamped.transform.translation.x = 0.0;
    static_transformStamped.transform.translation.y = 0.0;
    static_transformStamped.transform.translation.z = 0.0;
    tf2::Quaternion quat;
    quat.setRPY(0, 0, 0);
    static_transformStamped.transform.rotation.x = quat.x();
    static_transformStamped.transform.rotation.y = quat.y();
    static_transformStamped.transform.rotation.z = quat.z();
    static_transformStamped.transform.rotation.w = quat.w();

    static_broadcaster.sendTransform(static_transformStamped);

    exec.spin();
    
    rclcpp::shutdown();
    return 0;
}
