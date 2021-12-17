   #include "ros/ros.h"
   
   #include "project_avgRobot/navigationInMap.h"
   
   #include <string.h>
   
   #include <cstdlib>

   #include "algorthimAstar.cpp"
   
   int main(int argc, char **argv)
   {
     ros::init(argc, argv, "map_navigation_client");

     Map map;

     std::vector<int> mapArray {1, 1, 1, 1, 0, 0, 0,
                                0, 0, 0, 1, 1, 0, 0,
                                0, 0, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 0};

     
     if (argc == 2) {
      map.setMap(mapArray);
      map.showMap();
     }

     if (argc != 4)
      {
       ROS_INFO("Nhap lai cac tham so [Start] [Package] [End]");
       return 1;
     }
   
     ros::NodeHandle n;
     ros::ServiceClient client = n.serviceClient<project_avgRobot::navigationInMap>("map_navigation");
     project_avgRobot::navigationInMap srv;
     srv.request.startPt = atoi(argv[1]);
     srv.request.packagePt = atoi(argv[2]);
     srv.request.endPt = atoi(argv[3]);
     if (client.call(srv))
     {
       ROS_INFO("Direction Array: %s", srv.response.navigationArray.c_str());
     }
     else
     {
       ROS_ERROR("Failed to call path finder service");
       return 1;
     }
   
     return 0;
  }
