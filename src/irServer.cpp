#include "ros/ros.h"

#include "project_avgRobot/irSignal.h"

#include <string.h>
   
bool avg(project_avgRobot::irSignal::Request  &req, project_avgRobot::irSignal::Response &res) {
    ROS_INFO("request: Ir-1=%d, Ir-2=%d, Ir-3=%d, Ir-4=%d, Ir-5=%d", req.IR_1, req.IR_2, req.IR_3, req.IR_4, req.IR_5);

    if (req.IR_2 && req.IR_3 && req.IR_4) {
        if (req.IR_1 && req.IR_5) res.state = "Fork/Crossroad";
        else if (req.IR_1 && !req.IR_5) res.state = "Fork/TurnLeft";
        else if (req.IR_5 && !req.IR_1) res.state = "Fork/TurnRight";
        else res.state = "StraightAhead";
    } else if (req.IR_2 && req.IR_3 && !req.IR_4) {
        res.state = "RightSkew";
    } else if (!req.IR_2 && req.IR_3 && req.IR_4) {
        res.state = "LeftSkew";
    } else if (!req.IR_3) {
        res.state = "MissedLine";
    } else {
        res.state = "ERR";
    }

    ROS_INFO("Server response - Direction: [%s]", res.state.c_str());
    return true;
}
   
int main(int argc, char **argv)
{
    ros::init(argc, argv, "ir_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("ir_signal", avg);
    ROS_INFO("Ready to recieve IR signals.");
    ros::spin();

    return 0;
}
