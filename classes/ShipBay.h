//  ShipBay.h
#ifndef SHIPBAY_H
#define SHIPBAY_H

#include <fstream> // for file input
#include <string>
#include "ContainerSlot.h"

class ShipBay{

    string manifestFilePath;
    ContainerSlot bayArea[12][8];

    public:
        ShipBay(std::string filePath);
        std::string getFileName();
        void addContainer(Container newContainer, int x, int y);


};

#endif