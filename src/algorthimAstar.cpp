#include <stdio.h>
#include <math.h>
#include <typeinfo>
#include <vector>
#include <list>
#include "nodes.cpp"
#include "map.cpp"
#include <iostream>
#include <memory>

#define OBSTACLE 9999

class algorthimAstar {
 private:
    int startPt;
    int endPt;
    int column;
    int row;
    std::list<Nodes> openList;
    std::list<Nodes> closedList;
    std::vector<Nodes> nodeList;
    std::vector<double> neighbourNodes;
    std::list<Nodes> path;

 public:
    algorthimAstar() {
    	startPt = 0;
    	endPt = 0;
    	column = 0;
    	row = 0;
    }

    std::list<Nodes>GetCloseList();
    void setStartPt(int startId);
    void setEndPt(int endId);

    void calcPathCost(int id);

    void calcHCost(int node, Nodes goal);

    bool createNodeList(Map mapLayout, int startPt, int endPt);

    std::string planPath();

    int identifyNode(int x, int y);

    bool inOpenList(int id);

    bool inClosedList(int id);

    ~algorthimAstar() {};
};
    bool priorityNode(Nodes &node1, Nodes &node2);

std::list<Nodes> algorthimAstar::GetCloseList() {
    return algorthimAstar::closedList;
}

// #define testing
bool algorthimAstar::createNodeList(Map mapLayout, int startPt, int endPt) {
    std::vector<int> map = mapLayout.getMap();
    Nodes node;
    column = mapLayout.getColumn();
    row = mapLayout.getRow();
    int index = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (map[i*column + j] == 1) {
                node.setNode(index++, j, i);
                nodeList.emplace_back(node);
            }
        }
    }
    #ifdef testing
    for (int i =0; i < index; i++) {
        nodeList[i].output();
    }
    #endif
    if (startPt >= 0 && endPt >= 0 && (unsigned)startPt < nodeList.size() && (unsigned)endPt < nodeList.size()) {
        setStartPt(startPt);
        setEndPt(endPt);
        return true;
    } else {
        return false;
    }
}

void algorthimAstar::setStartPt(int startId) {
    startPt = startId;
}

void algorthimAstar::setEndPt(int endId) {
    endPt = endId;
}

std::string algorthimAstar::planPath() {
    nodeList[startPt].setHCost(1);
    nodeList[startPt].setPathCost(0);
    nodeList[startPt].setTotalCost();

    for (auto a : nodeList) {
        calcHCost(a.getnodeId(), nodeList[endPt]);
    }

    openList.emplace_back(nodeList[startPt]);
    #ifdef testing
    for (auto i : openList) {
        std::cout << "cost" << i.getCost() << std::endl;
    }
    // std::cout << "openList: " << openList.size() << std::endl;
    #endif

    Map map;
    auto directions = map.getDirection();
    int finalFoundFlag = 0;
    while (!openList.empty()) {
        openList.sort(priorityNode);
        Nodes currentNode = openList.front();
        closedList.emplace_back(currentNode);

        openList.pop_front();

        if (currentNode.getnodeId() == nodeList[endPt].getnodeId()) {

            finalFoundFlag = 1;
            #ifdef testing
            for (auto i : closedList) {
                std::cout << "\n Node Index: "<< i.getIndex() << " Hcost: " << i.returnHCost() << "  Totalcost: " << i.getCost() << " Parent: " << i.getParent();
            }
            #endif
            break;
        } else {
        // neighbour
        int cRow = currentNode.getRowId();
        int cCol = currentNode.getColumnId();
        // std::cout << "\ncrow " << cRow << "\tccol " << cCol;
        std::vector<int> neighbourID;
        for (int i = 0; i < 4; i++) {
            int x = directions[2*i] + cRow;
            int y = directions[2*i +1] + cCol;
            // std::cout << "\nx: " << x << "y: " << y << std::endl;
            if (x < 0 || y < 0 || x > 3 || y > 6) {
            continue;
            } else {
                int id = identifyNode(x, y);
                if (id != OBSTACLE) {
                    bool closed = inClosedList(id);
                    if (closed == true) {
                        continue;
                    } else {
                        bool open1 = inOpenList(id);
                        if (open1 == false) {
                            neighbourID.emplace_back(id);
                        }
                    }
                }
            }
        }
        for (auto i : neighbourID) {
            nodeList[i].setParent(currentNode.getnodeId());
            nodeList[i].setPathCost(1);
            nodeList[i].setTotalCost();
            openList.push_back(nodeList[i]);
            #ifdef testing
            std::cout << "\nThe openlist size is: " << openList.size();
            std::cout << "\nThe closedlist size is: " << closedList.size();
            #endif
        }
        }
    }
    
    // #ifdef testing

    std::string path = "";

    for (auto i : closedList) {
        // std::cout << ", " << i.getIndex() + 1;
        path += " " + std::to_string(i.getnodeId() + 1);
    }

    return path; 
}

bool algorthimAstar::inOpenList(int id) {
    int openFlag = 0;
    for (auto l : openList) {
        if (l.getnodeId() == id) {
            if (l.getCost() > nodeList[id].getCost()) {
                l.setCost(nodeList[id].getCost());
            }
            openFlag = 1;
        }
    }
    if (openFlag == 1) {
        return true;
    } else {
        return false;
    }
}

int algorthimAstar::identifyNode(int x, int y) {
    int found = 0;
    int index = 0;
    for (auto n : nodeList) {
        // std::cout<<"\n row col"<<n.getRowIndex()<<" "<<n.getColumnIndex();
        if (n.getRowId() == x && n.getColumnId() == y) {
            found = 1;
            index = n.getnodeId();
        }
    }
    if (found == 1) {
        return index;
    } else {
        return OBSTACLE;
    }
}

bool algorthimAstar::inClosedList(int id) {
    int closedFlag = 0;
    for (auto l : closedList) {
        if (l.getnodeId() == id)
           closedFlag = 1;
    }
    if (closedFlag == 1)
        return true;
    else
        return false;
}


void algorthimAstar::calcHCost(int node, Nodes goal) {
    int x1 = nodeList[node].getColumnId();
    int y1 = nodeList[node].getRowId();
    int x2 = goal.getColumnId();
    int y2 = goal.getRowId();
    double distance = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    nodeList[node].setHCost(distance);
}

bool priorityNode(Nodes &node1, Nodes &node2) {
    if (node1.getCost() < node2.getCost())
        return true;
    else
        return false;
}

