#include "ros/ros.h"
#include "std_msgs/String.h"
#include "project_avgRobot/distance.h"
#include "project_avgRobot/motorWarning.h"

bool enableMotor = true;

void dCallback(const project_avgRobot::distance msg)
{
    ROS_INFO("Received d: [%ld]", msg.distance);

    if (msg.distance <= 10) {
        ROS_INFO("STOP!");
        enableMotor = false;
    } else {
        ROS_INFO("CONTINUE!");
        enableMotor = true;
    }
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "motor_status");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("robot_distance", 1000, dCallback);

    ros::Publisher chatter_pub = n.advertise<project_avgRobot::motorWarning>("motor_warning", 1000);

    ros::Rate loop_rate(1);

    while (ros::ok()) {
        project_avgRobot::motorWarning warningMsg;

        warningMsg.enable = enableMotor;

        ROS_INFO("send Warning to motor [%d]", warningMsg.enable);

        chatter_pub.publish(warningMsg);

        ros::spinOnce();

        loop_rate.sleep();
    }
    
    

    ros::spin();

    return 0;
}
