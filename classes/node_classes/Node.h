//  Node.h
#ifndef NODE_H
#define NODE_H
#include <vector>
#include <queue>
#include "../classes/ShipBay.h"

class Node{
    
    Node* parent;
    ShipBay* bay;
    int incoming_cost;

    public:

        Node() = default;
        Node(Node* Parent, ShipBay* currBay, int cost); //  Constructor
        int getCost();  //  Get current cost of node
        std::vector<Node> expand(); //  Expand all possible moves from the Node
        void printState(); 
        void printAncestors();

};

#endif