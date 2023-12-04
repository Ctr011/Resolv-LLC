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
#include <queue>    //  Needed to order containers, and for the SIFT goal state
#include "ContainerSlot.h"

class ContainerComparator{
public:

    /**
     * 12/2: Used for SIFT
     * @fn operator()
     * Basically determines if the two Container objects should be swapped
     * @return true: Means that the order of the two nodes are fine where they are
     * @return false: Means that the two nodes are in the wrong position and need tobe swapped
    */
    bool operator()(Container* c1, Container* c2){
        
        //  Get cost of both nodes
        int cost1 = c1->getMass();
        int cost2 = c2->getMass();
        
        //  Determine order here, and return result
        if(cost1 < cost2){
            return true;
        }else{
            return false;
        }
    }
};

class ShipBay{

    int size_x = 12;
    int size_y = 8;


    std::vector<std::vector<ContainerSlot*>> bayArea;
    std::vector<ContainerSlot*> temp;
    std::string originalText;

    ShipBay* siftState;

    void parseContent(std::string manifest);

    public:
        ShipBay() = default;
        ShipBay(std::string manifestContent, ShipBay* sift = nullptr, std::vector<ContainerSlot*>* tempRow = nullptr);

        ContainerSlot* getContainer(int x, int y);
        ContainerSlot* getContainerByName(std::string name);
        std::vector<ContainerSlot*> getTempRow();
        ShipBay* getSIFTState();
        std::vector<int> getHeights(int start, int end);
        void setSIFTState(ShipBay* state);
        ShipBay* siftBay();

        bool canBalance();
        double calculateBalanceCost();
        bool compareBays(ShipBay* otherBay);

        //  12/2: Required to use SIFT if needed
        std::priority_queue<Container*, std::vector<Container*>, ContainerComparator> getAllContainers();

        int unloadContainer(std::string name, int column);
        int loadContainer(Container* newContainer, int column);
        Container* pickUpContainer(int column);
        int putDownDontainer(Container* container, int column);

        ShipBay* clone();
        void printShipBay();
        virtual ~ShipBay(){};

        int calculateMovementCost(int x1, int y1, int x2, int y2);
};



#endif