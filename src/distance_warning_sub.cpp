#include "ros/ros.h"
#include "std_msgs/String.h"
#include "project_avgRobot/distance.h"

int count = 0;

void dCallback(const project_avgRobot::distance msg)
{
    ROS_INFO("Received d: [%ld] in [%d]", msg.distance, count);

    if (msg.distance <= 10) {
        count++;
    } else {
        count = 0;
    }

    if (count >= 10) {
            ROS_INFO("Alert!");
    }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "d_warning_subscriber");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("robot_d", 1000, dCallback);

  ros::spin();

  return 0;
}
