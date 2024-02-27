#include "get_cloud.hpp"
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
GetCloud::GetCloud(): Node("get_cloud")
{
    // Create a subscriber on the "/camera/depth/points" topic
    msg_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
        "/livox/lidar", 10, std::bind(&GetCloud::PointCloud_handle, this, std::placeholders::_1));
    // Create a publisher for the "filtered_cloud" topic
    msg_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(
        "filtered_cloud",1);
}

void GetCloud::PointCloud_handle(const sensor_msgs::msg::PointCloud2 &input)
{   
    // RCLCPP_INFO(get_logger(), "get pointcloud success");
    // Create two new PointClouds for input and output
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::fromROSMsg(input,*input_cloud);
   
    // Create a new PointCloud for the indices
    std::vector<int> indices;

    // Remove NaN values from the point cloud
    pcl::removeNaNFromPointCloud(*input_cloud, *output_cloud, indices);

    // Convert the pcl data back to sensor_msgs/PointCloud2
    sensor_msgs::msg::PointCloud2 output_message;
    pcl::toROSMsg(*output_cloud,output_message);

    msg_pub_->publish(output_message);
    // RCLCPP_INFO(get_logger(), "publish pointcloud success");
}


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GetCloud>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}