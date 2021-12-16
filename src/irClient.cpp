#include "ros/ros.h"
   
   #include "project_avgRobot/irSignal.h"
   
   #include <string.h>
   
   #include <cstdlib>
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "ir_client");
     if (argc != 6)
      {
       ROS_INFO("Nhap tin hieu cua 5 den hong ngoai");
       return 1;
     }
   
     ros::NodeHandle n;
     ros::ServiceClient client = n.serviceClient<project_avgRobot::irSignal>("ir_signal");
     project_avgRobot::irSignal srv;
     srv.request.IR_1 = atoi(argv[1]);
     srv.request.IR_2 = atoi(argv[2]);
     srv.request.IR_3 = atoi(argv[3]);
     srv.request.IR_4 = atoi(argv[4]);
     srv.request.IR_5 = atoi(argv[5]);
     if (client.call(srv))
     {
       ROS_INFO("Direction: %s", srv.response.state.c_str());
     }
     else
     {
       ROS_ERROR("Calling IR service failed!");
       return 1;
     }
   
     return 0;
  }
