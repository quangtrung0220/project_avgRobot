#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include "algorthimAstar.cpp"

#define debug

int main() {
    algorthimAstar a;
    Map map;
    #ifdef debug
     std::vector<int> mapArray {1, 1, 1, 1, 0, 0, 0,
                                0, 0, 0, 1, 1, 0, 0,
                                0, 0, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 0};
    #endif
    int startPt, endPt;
    int userChoice;
    map.setMap(mapArray);
    map.showMap();
    std::cout << "The numbers in the map indicate the node index ";
    std::cout << "and \"X\" indicate obstacles. Enter the ";
    std::cout << "node index of the Start and End points: ";
    std::cout << std::endl;
    std::cin >> startPt >> endPt;
    bool success = a.createNodeList(map, startPt-1, endPt-1);
    std::string result = a.planPath();

    std::list<Nodes> directions = a.GetCloseList();

    // std::list<string> dir_string ;

    for (auto i : directions) {
        std::cout << i.getnodeId() + 1 <<std::endl;
        std::cout << i.getRowId()<<" "<< i.getColumnId() <<std::endl;
    }


    return 0;
}

