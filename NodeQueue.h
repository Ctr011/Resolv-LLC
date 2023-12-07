//  NodeQueue.h
#ifndef NODEQUEUE_H
#define NODEQUEUE_H
#include <vector>
#include <queue>
#include "Node.h"

class NodeComparator{

public:
     bool operator()(Node* node1, Node* node2){
        
        //  Get cost of both nodes
        int cost1 = node1->getCost();
        int cost2 = node2->getCost();
        
        //  Determine order here, and return result
        if(cost1 > cost2){
            return true;
        }else{
            return false;
        }
    }
};

class NodeQueue{

public:

    NodeQueue(){};

    //  Start with the unifrom function first
    void add(Node* newNode);
    bool isEmpty(); //  Checks if NodeQueue is Empty
    Node* pop();   //  Pops top-most Node from priority queue
    void printFrontier();   //  Debugging purposes?


};
#endif