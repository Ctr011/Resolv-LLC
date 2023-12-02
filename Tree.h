#ifndef TREE_H
#define TREE_H

//  Tree.h
#include "NodeQueue.h"

class Tree{
    
    //  These are set immeditaley
    int expansions = 0;
    NodeQueue* frontier = new NodeQueue();

    Node* startState;

public:
    
    Tree(Node* startNode);


    //  void for now
    void solveBalance();
    void solveLoad();
};

#endif // TREE_H