#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf_listener");

    ros::NodeHandle n;

    // 请求产生turtle2
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    ros::Publisher turtle_vel = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

    // 创建tf的监听器
    tf::TransformListener listener;

    ros::Rate rate(10.0);
    while(n.ok())
    {
        // 获取turtle1与turtle2坐标系之间的tf数据
        tf::StampedTransform transform;
        try
        {
            // Time(0)表示获取当前时间的数据(最多可获取10s内的数据)
            // 先等待数据,Duration(3.0)表示3.0s内没有等待到数据就超时,然后把结果储存到transform
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
        }        
        catch(tf::TransformException &e)
        {
            ROS_ERROR("%s", e.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        // 根据transform中两个乌龟之间的位置关系,发布控制指令让turtle2追踪turtle1
        geometry_msgs::Twist vel_msg;
        /// 这里atan2是四像限反正切函数
        /// 前面的系数为加速度系数
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(), transform.getOrigin().x()); 
        vel_msg.linear.x = 0.3 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
        turtle_vel.publish(vel_msg);

        rate.sleep();
    }
    return 0;
}