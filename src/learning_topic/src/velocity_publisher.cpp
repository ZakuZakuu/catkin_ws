/*
    学习publisher的创建
*/
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "velocity_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry_msgs，队列长度为10
    // 队列长度用于缓冲（相当于buffer），以防发送数据来不及
    ros::Publisher turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // 设置循环的速率
    // 一个循环类对象
    ros::Rate loop_rate(5);

    int count = 0;
    while (ros::ok())
    {
        // 初始化geometry_msgs::Twist类型的消息
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.5;
        vel_msg.angular.z = 0.2;

        // 发布消息
        turtle_vel_pub.publish(vel_msg);
        // ROS的标准日志输出，用法有点像printf
        ROS_INFO("Publish turtle velocity command[%0.2f m/s, %0.2f rad/s]", vel_msg.linear.x, vel_msg.angular.z);

        // 按照循环延时
        loop_rate.sleep();
    }
    return 0;
}