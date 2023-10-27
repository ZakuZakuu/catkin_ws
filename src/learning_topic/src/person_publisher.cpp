#include <ros/ros.h>
#include "learning_topic/person.h"

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "person_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/turtle1/cmd_vel的topic，消息类型为geometry_msgs，队列长度为10
    // 队列长度用于缓冲（相当于buffer），以防发送数据来不及
    ros::Publisher turtle_vel_pub = n.advertise<learning_topic::person>("/person_info", 10);

    // 设置循环的速率
    // 一个循环类对象
    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok())
    {
        // 初始化geometry_msgs::Twist类型的消息
        learning_topic::person person_msg;
        person_msg.name = "Tom";
        person_msg.age = 19;
        person_msg.sex = learning_topic::person::male;

        // 发布消息
        turtle_vel_pub.publish(person_msg);
        // ROS的标准日志输出，用法有点像printf
        ROS_INFO("Publish person info: name:%s, age:%d, gender:%d", person_msg.name.c_str(), person_msg.age, person_msg.sex);

        // 按照循环延时
        loop_rate.sleep();
    }
    return 0;
}