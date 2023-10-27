#include <ros/ros.h>
#include "learning_topic/person.h"

// 收到消息后的回调函数
void personCallback(const learning_topic::person::ConstPtr msg)
{
    // 将收到的消息打印出来
    ROS_INFO("Person Info: name:%s, age:%d, gender:%d", msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "person_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Subscriber，订阅名为/turtle1/pose的topic，注册回调函数personCallback
    ros::Subscriber pos_sub = n.subscribe("/person_info", 10, personCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}