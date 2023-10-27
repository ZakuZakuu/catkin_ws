#include <ros/ros.h>
#include "learning_service/Person.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "person_client");

    ros::NodeHandle n;

    ros::service::waitForService("/show_person");

    // 建立客户端实体
    ros::ServiceClient person_client = n.serviceClient<learning_service::Person>("/show_person");

    // 编辑请求信息
    learning_service::Person srv;
    srv.request.age = 18;
    srv.request.name = "Tom";
    srv.request.gender = learning_service::Person::Request::male;

    ROS_INFO("Call service to show person [name:%s]", srv.request.name.c_str());

    // 让客户端实体将请求信息发布
    person_client.call(srv);

    ROS_INFO("Request result:%s", srv.response.result.c_str());

    return 0;
}