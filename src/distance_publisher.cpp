#include "ros/ros.h"

#include "std_msgs/String.h"

#include "project_avgRobot/distance.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "distance_publisher");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<project_avgRobot::distance>("robot_distance", 1000);

  ros::Rate loop_rate(1);

  while (ros::ok())
  {
    project_avgRobot::distance msg;
   
    msg.distance = atoi(argv[1]);

    ROS_INFO("%ld", msg.distance);

    chatter_pub.publish(msg);
    
    ros::spinOnce();

    loop_rate.sleep();

  }


  return 0;
}

