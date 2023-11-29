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

protected:

    ShipBay* getBay();
    Buffer* getBuffer();
    Container* getPickUpContainer();

public:
    Node() = default;
    Node(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent = nullptr, Container* container = nullptr);
    int getCost();
    std::vector<Node*> expand();

    bool compareNodes(Node* otherNode);

    double getDistanceFromBalanced();

    void printState();
    // void printAncestors();
};

#endif