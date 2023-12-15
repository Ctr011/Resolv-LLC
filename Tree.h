#ifndef TREE_H
#define TREE_H

//  Tree.h
#include "NodeQueue.h"
#include ".\webserver\nlohmann\json.hpp"
using Json = nlohmann::json;

class Tree{
    
    //  These are set immeditaley
    int expansions = 0;
    NodeQueue* frontier;

    Node* startState;

public:
    
    Tree(Node* startNode);


    //  void for now
    Json solveBalance();
    Json solveSIFT(ShipBay* siftedState);
    Json solveUnLoad(std::string target);
    Json solveLoad();
};

#endif // TREE_H