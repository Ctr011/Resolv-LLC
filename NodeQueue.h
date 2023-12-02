//  NodeQueue.h
#ifndef NODEQUEUE_H
#define NODEQUEUE_H
#include <vector>
#include <queue>
#include "Node.h"

/**
 * @class NodeBalanceComparator
 * used to compare two nodes via balance, and decide which one gets higher priority in the
 * priority queue
*/
class NodeBalanceComparator{
public:

    /**
     * @fn operator()
     * Basically determines if the two Node objects should be swapped
     * @return true: Means that the order of the two nodes are fine where they are
     * @return false: Means that the two nodes are in the wrong position and need tobe swapped
    */
    bool operator()(Node* node1, Node* node2){
        
        //  Get cost of both nodes
        int cost1 = node1->getBalanceCost();
        int cost2 = node2->getBalanceCost();
        
        //  Determine order here, and return result
        if(cost1 > cost2){
            return true;
        }else{
            return false;
        }
    }
};

/**
 * @class NodeSIFTComparator
 * used to compare two nodes via balance, and decide which one gets higher priority in the
 * priority queue
*/
class NodeSIFTComparator{


    ShipBay* siftedState;

public:

    /**
     * 12/2
     * Needed to 
    */
    void loadSIFTState(ShipBay* newBay){
        this->siftedState = newBay;
    }

    /**
     * @fn operator()
     * Basically determines if the two Node objects should be swapped
     * @return true: Means that the order of the two nodes are fine where they are
     * @return false: Means that the two nodes are in the wrong position and need tobe swapped
    */
    bool operator()(Node* node1, Node* node2){
        
        //  Get cost of both nodes
        int cost1 = node1->getSIFTCost();
        int cost2 = node2->getSIFTCost();
        
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
    int maxNodes;

public:

    NodeQueue(){
        this->maxNodes = 0;
    };

    //  Start with the unifrom function first
    virtual void add(Node* newNode) = 0;
    virtual bool isEmpty() = 0; //  Checks if NodeQueue is Empty
    virtual Node* pop() = 0;   //  Pops top-most Node from priority queue
    virtual void printFrontier() = 0;   //  Debugging purposes?


};

class BalanceQueue : public NodeQueue{

    std::priority_queue<Node*, std::vector<Node*>, NodeBalanceComparator> ds;

public:

    BalanceQueue();

    virtual void add(Node* newNode) override;
    virtual bool isEmpty() override; //  Checks if NodeQueue is Empty
    virtual Node* pop() override;   //  Pops top-most Node from priority queue
    virtual void printFrontier() override;   //  Debugging purposes?

};

class SIFTQueue : public NodeQueue{

    std::priority_queue<Node*, std::vector<Node*>, NodeSIFTComparator> ds;
    ShipBay* siftState;

public:

    SIFTQueue();

    virtual void add(Node* newNode) override;
    virtual bool isEmpty() override; //  Checks if NodeQueue is Empty
    virtual Node* pop() override;   //  Pops top-most Node from priority queue
    virtual void printFrontier() override;   //  Debugging purposes?

};
#endif