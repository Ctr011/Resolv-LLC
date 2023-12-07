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

    //  Used only for the unloads, cost calculataions
    std::string unloadTarget;

public:

    Node() = default;
    Node(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent = nullptr, Container* container = nullptr);

    ShipBay* getBay();
    Buffer* getBuffer();
    Container* getPickUpContainer();
    Node* getParent();

    //  Basically for printing the set of instructions
    std::string getDescription();
    void setDescription(const std::string& description);

    //  Used specifically for unloads
    void setUnloadTarget(std::string target);
    std::string getUnloadTarget();
    int getUnloadCost();    //  12/4 Unload and loads are two different sets of problems
    
    //  12/2 Different costs for different tasks
    int getBalanceCost();
    int getSIFTCost();  //  12/2 Added arg, since sift state will not change between nodes
    int getLoadCost();
    int getMoveCost(); //   Gets the pure movement cost to th current stats
    
    std::vector<Node*> expand();    //  For balancing
    std::vector<Node*> expandUnload(std::string unload);  //  For unloading
    std::vector<Node*> expandLoad(Container* newContainer);

    bool compareNodes(Node* otherNode);
    bool isBalanced();
    bool isDoneUnloading(std::vector<std::string> allContainers);

    double getDistanceFromBalanced();


    Node* getSIFT();
    std::string getMoves();

    void printState();
    // void printAncestors();
};

#endif
