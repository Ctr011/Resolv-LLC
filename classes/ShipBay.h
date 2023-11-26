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


    int buffer_x = 24;
    int buffer_y = 4;
    std::vector<std::vector<ContainerSlot*>> bayArea;
    std::vector<std::vector<ContainerSlot*>> bufferArea;    //  11/25: Decided to cinlude Buffer here, as it structurally is very similar to Bay, but more simple
    std::vector<ContainerSlot> temp;
    std::string originalText;

    void parseContent(std::string manifest);

    //  For looking for containers in the data
    void replaceSubstring(std::string &input, const std::string &searchStr, const std::string &replaceStr);

    



    public:
        ShipBay() = default;

        ShipBay(std::string manifestContent);

        std::vector<int>getHeights(int start, int end);
        std::vector<int>getBufferHeights();
        void addContainer(Container newContainer, int x, int y);

        Container* pickUpContainer(int column);
        Container* pickUpContainerB(int column);

        int putDownDontainer(Container* container, int column);
        int putDownDontainerB(Container* container, int column);

        ShipBay* clone();

        void printShipBay();

        virtual ~ShipBay(){};
};

#endif