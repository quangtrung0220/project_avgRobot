#pragma once
#include <iostream>
/**
 * Class Nodes lưu trữ thông tin chi tiết về các nút của một bản đồ.  	
 * Nó lưu trữ dữ liệu liên quan đến index của nút, nút cha của nó, cost, chỉ số hàng và cột
 */
class Nodes {
 private:
    int nodeId;
    int parentId;
    int rowId;
    int columnId;
    double heuristicCost;
    double pathCost;
    double totalCost;

 public:
     Nodes() {
         nodeId = 0;
         parentId = 0;
         rowId = 0;
         columnId = 0;
         heuristicCost = 0;
         pathCost = 0;
         totalCost = 0;
     }
    void setNode(int id, int column, int row);

    void setParent(int id);
    int getParent();

    void setHCost(double heuristic);
	double getHCost();

    void setPathCost(double cost);
    void setTotalCost();


    void setCost(double cost);
	double getCost();

    void output();
    
    int getRowId();
    int getColumnId();
    int getnodeId();
    
    ~Nodes() {}
};

void Nodes::setNode(int id, int column, int row) {
    nodeId = id;
    columnId = column;
    rowId = row;
    }

void Nodes::setParent(int id) {
    parentId = id;
}

int Nodes::getParent() {
    return parentId;
}

void Nodes::setPathCost(double cost) {
    pathCost = cost;
}

void Nodes::setTotalCost() {
    totalCost = pathCost + 0.1*heuristicCost;
}

void Nodes::setCost(double cost) {
    totalCost = cost;
}

void Nodes::output() {
    std::cout << rowId << " " << columnId << std::endl;
}

double Nodes::getCost() {
    return totalCost;
}

int Nodes::getRowId() {
    return rowId;
}

int Nodes::getColumnId() {
    return columnId;
}

int Nodes::getnodeId() {
    return nodeId;
}

void Nodes::setHCost(double heuristic) {
    heuristicCost = heuristic;
}

double Nodes::getHCost() {
    return heuristicCost;
}

