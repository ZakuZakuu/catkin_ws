#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "turtle_spawn");

    // 创建节点句柄
    ros::NodeHandle n;

    // 发现"/spawn"服务后，创建一个客户端(client)，连接名为"/spawn"的服务
    ros::service::waitForService("/spawn");     //!!!阻塞性函数，在发现目标服务前不继续执行程序
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");    //创建了一个客户端实体

    // 初始化turtlesim::Spawn的请求数据
    turtlesim::Spawn srv;   //这里创建了一个turtlesim::Spawn类，用于储存要发送的消息和接收到的消息
    srv.request.x = 2.0;
    srv.request.y = 2.0;
    srv.request.name = "turtle2";

    // 请求服务调用
    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", srv.request.x, srv.request.y, srv.request.name.c_str());
    add_turtle.call(srv);   //!!!这也是个阻塞性函数，直到收到回复时才会继续执行程序

    // 用于接受消息
    ROS_INFO("Turtle %s spawn success!", srv.response.name.c_str());

    return 0;
}