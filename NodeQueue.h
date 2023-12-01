//  NodeQueue.h
#ifndef NODEQUEUE_H
#define NODEQUEUE_H
#include <vector>
#include <queue>
#include "Node.h"

/**
 * @class NodeComparator
 * used to compare two nodes, and decide which one gets higher priority in the
 * priority queue
*/
class NodeComparator{
public:

    /**
     * @fn operator()
     * Basically determines if the two Node objects should be swapped
     * @return true: Means that the order of the two nodes are fine where they are
     * @return false: Means that the two nodes are in the wrong position and need tobe swapped
    */
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

    //  Define our prioirty queue object here, using our custom comparator
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> ds;
    int maxNodes;

public:

    NodeQueue();

    //  Start with the unifrom function first
    void add(Node* newNode);
    
    bool isEmpty(); //  Checks if NodeQueue is Empty
    Node* pop();    //  Pops top-most Node from priority queue
    void printFrontier();   //  Debugging purposes?


};
#endif