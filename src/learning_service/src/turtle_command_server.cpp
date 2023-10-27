#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>

ros::Publisher turtle_vel_pub;
bool pubCommand = false;

// service回调函数，输入参数
bool commandCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
    // 整段函数都没有用到Request? 因为request就是空的，收到请求执行函数就行，不需要过多说明

    pubCommand = !pubCommand;

    // 显示请求内容
    ROS_INFO("Publish turtle velocity command [%s]", pubCommand==true?"Yes":"No");

    // 设置反馈数据，发送给客户端
    /* 
        std_srvs::Trigger::Response的数据结构:
            bool success
            string message
    */
    res.success = true;
    res.message = "Change turtle command state!";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_command_server");

    ros::NodeHandle n;

    ros::ServiceServer command_service = n.advertiseService("/turtle_command", commandCallback);

    turtle_vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ROS_INFO("Ready to recive turtle command");

    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        // 收到请求的回调函数会先排队，当程序执行到spin时队列中函数才开始陆续执行。spinOnce的话只执行队列中第一个
        ros::spinOnce();

        if(pubCommand)
        {
            geometry_msgs::Twist vel_msg;
            vel_msg.linear.x = 0.5;
            vel_msg.angular.z = 0.5;
            turtle_vel_pub.publish(vel_msg);
        }

        loop_rate.sleep();
    }

    return 0;
}