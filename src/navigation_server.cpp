#include "ros/ros.h"

#include "project_avgRobot/navigationInMap.h"

#include "algorthimAstar.cpp"

#include <string.h>


std::string path_finder(algorthimAstar a, Map map, int startPt, int endPt);
   
   
bool path_finder_service(project_avgRobot::navigationInMap::Request  &req, project_avgRobot::navigationInMap::Response &res) {
    ROS_INFO("request: startPt=%d, endPt=%d", req.startPt, req.endPt);

    algorthimAstar a;

    Map map;

    std::string result_finder = "";

    result_finder = path_finder(a, map, req.startPt, req.endPt);
    
    res.navigationArray = result_finder;

    ROS_INFO("sending back response - Path finder: [%s]", res.navigationArray.c_str());
    return true;
}
   
int main(int argc, char **argv)
{
    ros::init(argc, argv, "map_navigation_server");

    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("map_navigation", path_finder_service);
    
    ROS_INFO("Nhap cac tham so [Start] [End] o Client");
    
    ros::spin();

    return 0;
}

std::string path_finder(algorthimAstar a, Map map, int startPt, int endPt) {
    std::vector<int> mapArray {1, 1, 1, 1, 0, 0, 0,
                               0, 0, 0, 1, 1, 0, 0,
                               0, 0, 1, 1, 1, 1, 1,
                               1, 1, 1, 1, 1, 1, 0};
    
    map.setMap(mapArray);
    map.showMap();

    bool success = a.createNodeList(map, startPt-1, endPt-1);

    if (success == true) {
        return a.planPath();
    } else {
        std::cout << "Enter a valid start and end point" << std::endl;
    }

    return "";

}
