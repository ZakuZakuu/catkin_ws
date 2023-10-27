#include <ros/ros.h>
#include "learning_service/Person.h"

bool personCallback(learning_service::Person::Request &req, learning_service::Person::Response &res)
{
    ROS_INFO("Person: name:%s age:%d gender:%d", req.name.c_str(), req.age, req.gender);
    
    res.result = "OK";
    
    return true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "person_server");

    ros::NodeHandle n;

    ros::ServiceServer person_service = n.advertiseService("/show_person", personCallback);

    ROS_INFO("Server Started! Ready to receive requests!");
    ros::spin();

    return 0;
}