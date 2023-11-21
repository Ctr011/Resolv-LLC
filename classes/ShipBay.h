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
    std::vector<std::vector<ContainerSlot>> bayArea;

    void parseContent(std::string manifest);
    ContainerSlot parseLine(std::string entry);


    public:

        ShipBay() = default;

        ShipBay(std::string manifestContent);
        void addContainer(Container newContainer, int x, int y);

        virtual ~ShipBay(){};
};

#endif