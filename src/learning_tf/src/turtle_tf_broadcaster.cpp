#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg)
{
    // 创建tf的广播器
    static tf::TransformBroadcaster br;

    // 初始化tf数据
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x, msg->y, 0.0));  /// 平移参数(z=0)
    tf::Quaternion q;           // 四元数
    q.setRPY(0, 0, msg->theta); // 绕三个坐标轴的旋转
    transform.setRotation(q);

    // 广播world与海龟坐标系之间的tf数据
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_tf_broadcaster");

    ros::NodeHandle n;

    // 重映射
    /// 在使用的时候需要添加参数"turtle1" 或 "turtle2" 来确定订阅的乌龟数据
    if (argc != 2)
    {
        ROS_ERROR("need turtle name as argument!");
        return -1;
    }
    ROS_INFO("argv[0]:%s", argv[0]);
    turtle_name = argv[1];

    // 订阅海龟的位姿话题
    ros::Subscriber sub = n.subscribe("/"+turtle_name+"/pose", 10, &poseCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}