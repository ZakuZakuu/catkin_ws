import sys
import rospy
from turtlesim import Spawn

def turtle_spawn():

    rospy.init_node('turtle_spawn2')

    rospy.wait_for_service('/spawn')
    try:
        add_turtle = rospy.ServiceProxy('/spawn', Spawn)

        response = add_turtle(2.0, 2.0, 0.0, "turtle2")
        return response.name
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

if __name__ == "__main__":
    print("Spawn turtle2 successfilly!" %(turtle_spawn()))