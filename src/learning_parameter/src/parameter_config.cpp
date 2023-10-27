#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <string.h>

int main(int argc, char **argv)
{
    int red, green, blue;
    
    ros::init(argc, argv, "parameter_config");

    ros::NodeHandle n;

    ros::param::get("/turtlesim/background_r", red);
    ros::param::get("/turtlesim/background_g", green);
    ros::param::get("/turtlesim/background_b", blue);

    ROS_INFO("Get background color{%d %d %d}", red, green, blue);

    ros::param::set("/turtlesim/background_r", 255);
    ros::param::set("/turtlesim/background_g", 255);
    ros::param::set("/turtlesim/background_b", 255);

    ROS_INFO("Set background color(%d %d %d)", 0, 0, 0);

    ros::param::get("/turtlesim/background_r", red);
    ros::param::get("/turtlesim/background_g", green);
    ros::param::get("/turtlesim/background_b", blue);

    ROS_INFO("Check background color{%d %d %d}", red, green, blue);

    /// 等待刷新颜色
    ros::service::waitForService("/clear");
    ros::ServiceClient clear_background = n.serviceClient<std_srvs::Empty>("/clear");   // 这里使用的标准请求数据为Empty，即不包含任何数据
    std_srvs::Empty srv;
    clear_background.call(srv);

    //? 啥意思
    sleep(1);

    return 0;
}