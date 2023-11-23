//  ShipBay.h
#ifndef SHIPBAY_H
#define SHIPBAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include "ContainerSlot.h"

class ShipBay{

    //  Change this back later
    int size_x = 8;
    int size_y = 12;
    std::vector<std::vector<ContainerSlot>> bayArea;
    std::vector<ContainerSlot> temp;

    void parseContent(const std::string manifest);
    ContainerSlot parseLine(std::string entry);

    //  Following functions are used for A* between two points



    public:
        ShipBay() = default;

        ShipBay(std::string manifestContent);
        void addContainer(Container newContainer, int x, int y);

        int moveContainer(Container& container, int x);

        virtual ~ShipBay(){};
};

#endif