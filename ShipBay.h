//  ShipBay.h
#ifndef SHIPBAY_H
#define SHIPBAY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "ContainerSlot.h"

class ShipBay{

    int size_x = 12;
    int size_y = 8;


    std::vector<std::vector<ContainerSlot*>> bayArea;
    std::vector<ContainerSlot*> temp;
    std::string originalText;

    void parseContent(std::string manifest);

    public:
        ShipBay() = default;
        ShipBay(std::string manifestContent, std::vector<ContainerSlot*>* tempRow = nullptr);

        ContainerSlot* getContainer(int x, int y);
        std::vector<ContainerSlot*> getTempRow();

        double calculateBalanceCost();
        bool compareBays(ShipBay* otherBay);

        std::vector<int>getHeights(int start, int end);
        Container* pickUpContainer(int column);
        int putDownDontainer(Container* container, int column);
        ShipBay* clone();
        void printShipBay();
        virtual ~ShipBay(){};

        int calculateMovementCost(int x1, int y1, int x2, int y2);
};

#endif