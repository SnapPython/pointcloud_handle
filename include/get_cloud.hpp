#include "pcl/point_cloud.h"
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl/filters/filter.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl_conversions/pcl_conversions.h>
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <iostream>

using namespace std;
using namespace std::chrono_literals;
class GetCloud: public::rclcpp::Node
{
public:
    GetCloud();
    void PointCloud_handle(const sensor_msgs::msg::PointCloud2 &input);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr msg_sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr msg_pub_;
};