//  ShipBay.h
#ifndef SHIPBAY_H
#define SHIPBAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "ContainerSlot.h"

class ShipBay{

    //  Change this back later
    int size_x = 12;
    int size_y = 8;
    std::vector<std::vector<ContainerSlot*>> bayArea;
    std::vector<ContainerSlot> temp;
    std::string originalText;

    void parseContent(const std::string manifest);
    ContainerSlot* parseLine(std::string entry);

    //  Following functions are used for A* between two points



    public:
        ShipBay() = default;

        ShipBay(std::string manifestContent);

        std::vector<int>getHeights(int start, int end);
        void addContainer(Container newContainer, int x, int y);

        Container* pickUpContainer(int column);
        int putDownDontainer(Container* container, int column);

        ShipBay* clone();

        void printShipBay();

        virtual ~ShipBay(){};
};

#endif