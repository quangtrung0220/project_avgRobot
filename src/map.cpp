#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Map {
 private:
    std::vector<int> currentMap;
    int columns = 7;
    int rows = 4;
    int direction[8] = {-1, 0,    // top
                         0, 1,    // right
                         1, 0,    // bottom
                         0, -1};  // left

 public:   
    Map() {}
    void showMap();
    void loadMap(std::string mapPath);
    void deleteMap();

	void setColumn(int col);
    int getColumn();
    void setRow(int row);
	int getRow();

    int* getDirection();

	void setMap(std::vector<int> map);
	std::vector<int> getMap();
    ~Map() {}
};


void Map::showMap() {
    std::vector<int> displayLayout = currentMap;
    int node = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (displayLayout[i*columns + j] == 1) {
                std::cout << node++ <<"\t";
            } else {
                std::cout << "x" << "\t";
            }
        }
        std::cout << std::endl;
    }
}

void Map::setMap(std::vector<int> map) {
    currentMap = map;
}

void Map::loadMap(std::string mapPath) {
    std::ifstream file(mapPath);
    std::string row, cell;
    int rCount = 0;
    if (file.good()) {
        while (std::getline(file, row)) {
            int cCount = 0;
            std::istringstream linestream(row);
            while (getline(linestream, cell, ',')) {
                ++cCount;
                if (cell == "0")
                    currentMap.emplace_back(0);
                else
                    currentMap.emplace_back(1);
            }
            ++rCount;
            setColumn(cCount);
        }
    } else {
        std::cout << "The File path entered is not correct";
        setColumn(0);
        setRow(0);
    }
    setRow(rCount);
}

std::vector<int> Map::getMap() {
    return currentMap;
}

int Map::getColumn() {
    return columns;
}

int Map::getRow() {
    return rows;
}

void Map::setColumn(int col) {
    columns = col;
}

void Map::setRow(int row) {
    rows = row;
}

int* Map::getDirection() {
    return direction;
}
