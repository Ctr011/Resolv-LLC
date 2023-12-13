//  NodeQueue.cpp

#include "NodeQueue.h"

NodeQueue::NodeQueue(){}

/**
 * @fn addUniform
 * Add a Node to the queue using a UCS heuristic
*/
void NodeQueue::add(Node* newNode){
    this->ds.push(newNode);
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