#include "ros/ros.h"

#include "std_msgs/String.h"

#include "project_avgRobot/keyboard.h"

//#include "avg_robot/MotorWarning.h"

//#include "avg_robot/MotorControl.h"

#include <algorithm>

#include <string>

bool canMove = true;

std::string controlRobot = "";

std::string change = "";

void chatterCallback(const project_avgRobot::keyboard keyb)
{

//  if (canMove) {
//    ROS_INFO("receive direction: [%s]", keyb.navigation.c_str());
//    change = keyb.navigation.c_str();
    
//    std::transform(change.begin(), change.end(),change.begin(), ::toupper);

//    controlRobot = change;
//  } else {
//    ROS_INFO("Robot stop!");
//    controlRobot="STOP";
//  }
  
	ROS_INFO("receive direction: [%s]", keyb.navigation.c_str());
}

//void warningCallback(const avg_robot::MotorWarning warning)
//{
//
//  // ROS_INFO("receive warning: [%d]", warning.enable);
//  if (warning.enable) {
//    ROS_INFO("GO!");
//    canMove = true;
//  } else {
//    ROS_INFO("CANCEL!");
//    canMove = false;
//    controlRobot="STOP";
//  }
//
//}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "keyboard_subscriber");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("input_keyboard", 1, chatterCallback);

//  ros::Subscriber motor_sub = n.subscribe("motor_warning", 1, warningCallback);
//
//  ros::Publisher chatter_pub = n.advertise<project_avgRobot::MotorControl>("motor_control", 1000);
//
//  ros::Rate loop_rate(1);

//  while (ros::ok()) {
//      project_avgRobot::MotorControl controlMsg;
//
//      controlMsg.control = controlRobot;
//
//      ROS_INFO("send Control to motor [%s]", controlMsg.control.c_str());
//
//      chatter_pub.publish(controlMsg);
//
//      ros::spinOnce();
//
//      loop_rate.sleep();
//  }
//    

  ros::spin();

  return 0;
}
