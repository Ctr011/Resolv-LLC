#ifndef TREE_H
#define TREE_H

//  Tree.h
#include "NodeQueue.h"

class Tree{
    
    //  These are set immeditaley
    int expansions = 0;
    NodeQueue* frontier;

    Node* startState;

public:
    
    Tree(Node* startNode, NodeQueue* queueType);


    //  void for now
    void solveBalance();
    void solveSIFT(ShipBay* siftedState);
    Node* solveUnLoad(std::string unload, Node* state = nullptr);
    void solveLoad();
};

#endif // TREE_H