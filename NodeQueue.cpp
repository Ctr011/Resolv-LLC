//  NodeQueue.cpp

#include "NodeQueue.h"

/**
 * @fn Constructor
*/
NodeQueue::NodeQueue(){
    //  Only need to init the max nodes    
    this->maxNodes = 0;
};

/**
 * @fn addUniform
 * Add a Node to the queue using a UCS heuristic
*/
void NodeQueue::add(Node* newNode){
    this->ds.push(newNode);
    maxNodes++;
}

bool NodeQueue::isEmpty(){return ds.empty();}

/**
 * 
*/
Node* NodeQueue::pop(){
    Node* topNode = ds.top();
    ds.pop();
    return topNode;
}

void NodeQueue::printFrontier(){
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> dsCopy = ds;

    while (!dsCopy.empty()) {
        std::cout << ' ' << dsCopy.top()->getCost() <<std::endl;
        dsCopy.top()->printState();
        dsCopy.pop();
    }
    std::cout << '\n';
}

