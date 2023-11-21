//  ShipBay.h
#ifndef SHIPBAY_H
#define SHIPBAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ContainerSlot.h"

class ShipBay{

    int size_x = 12;
    int size_y = 8;
    vector<vector<ContainerSlot>> bayArea;

    void parseContent(string manifest);
    ContainerSlot parseLine(string entry);


    public:
        ShipBay(std::string manifestContent);
        void addContainer(Container newContainer, int x, int y);


};

#endif