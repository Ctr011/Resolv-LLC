// Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "../ShipBay.h"
#include "../ContainerSlot.h"


class Node {
    Node* parent;
    ShipBay* bay;
    Container* pickedUp;
    int incoming_cost;

public:
    Node() = default;
    Node(ShipBay* currBay, int cost, Node* parent = nullptr, Container* container = nullptr);
    int getCost();
    std::vector<Node*> expand();
    // void printState();
    // void printAncestors();
};

#endif
