// Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "./ShipBay.h"
#include "./Buffer.h"
#include "./ContainerSlot.h"


class Node {
    Node* parent;
    ShipBay* bay;
    Buffer* buffer;
    Container* pickedUp;
    int incoming_cost;
    std::string move_description;

public:

    ShipBay* getBay();
    Buffer* getBuffer();
    Container* getPickUpContainer();
    Node* getParent();
    std::string getDescription();
    void setDescription(const std::string& description);

    Node() = default;
    Node(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent = nullptr, Container* container = nullptr);
    
    //  12/2 Different costs for different tasks
    int getBalanceCost();
    int getSIFTCost();  //  12/2 Added arg, since sift state will not change between nodes
    int getMoveCost(); //   Gets the pure movement cost to th current stats
    
    std::vector<Node*> expand();

    bool compareNodes(Node* otherNode);
    bool isBalanced();

    double getDistanceFromBalanced();


    Node* getSIFT();
    std::string getMoves();

    void printState();
    // void printAncestors();
};

#endif
