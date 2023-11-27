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

    void parseContent(std::string manifest);

    public:
        ShipBay() = default;

        bool isBalanced();

        ShipBay(std::string manifestContent);

        std::vector<int>getHeights(int start, int end);

        Container* pickUpContainer(int column);

        int putDownDontainer(Container* container, int column);

        ShipBay* clone();

        void printShipBay();

        virtual ~ShipBay(){};
};

#endif