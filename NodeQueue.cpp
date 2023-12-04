//  NodeQueue.cpp

#include "NodeQueue.h"

BalanceQueue::BalanceQueue(){}

/**
 * @fn addUniform
 * Add a Node to the queue using a UCS heuristic
*/
void BalanceQueue::add(Node* newNode){
    this->ds.push(newNode);
}

bool BalanceQueue::isEmpty(){return ds.empty();}

/**
 * 
*/
Node* BalanceQueue::pop(){
    Node* topNode = ds.top();
    ds.pop();
    return topNode;
}

void BalanceQueue::printFrontier(){
    std::priority_queue<Node*, std::vector<Node*>, NodeBalanceComparator> dsCopy = ds;

    while (!dsCopy.empty()) {
        std::cout << ' ' << dsCopy.top()->getBalanceCost() <<std::endl;
        dsCopy.top()->printState();
        dsCopy.pop();
    }
    std::cout << '\n';
}

SIFTQueue::SIFTQueue(){}

/**
 * @fn add
 * Add a Node to the queue using a UCS heuristic
*/
void SIFTQueue::add(Node* newNode){
    this->ds.push(newNode);
}

bool SIFTQueue::isEmpty(){return ds.empty();}

/**
 * 
*/
Node* SIFTQueue::pop(){
    Node* topNode = ds.top();
    ds.pop();
    return topNode;
}

void SIFTQueue::printFrontier(){
    std::priority_queue<Node*, std::vector<Node*>, NodeSIFTComparator> dsCopy = ds;

    while (!dsCopy.empty()) {
        std::cout << ' ' << dsCopy.top()->getSIFTCost() <<std::endl;
        dsCopy.top()->printState();
        dsCopy.pop();
    }
    std::cout << '\n';
}

UnloadQueue::UnloadQueue(){}

/**
 * @fn add
 * Add a Node to the queue using a UCS heuristic
*/
void UnloadQueue::add(Node* newNode){
    this->ds.push(newNode);
}

bool UnloadQueue::isEmpty(){return ds.empty();}

/**
 * 
*/
Node* UnloadQueue::pop(){
    Node* topNode = ds.top();
    ds.pop();
    return topNode;
}

void UnloadQueue::printFrontier(){
    std::priority_queue<Node*, std::vector<Node*>, NodeUnloadComparator> dsCopy = ds;

    while (!dsCopy.empty()) {
        std::cout << ' ' << dsCopy.top()->getSIFTCost() <<std::endl;
        dsCopy.top()->printState();
        dsCopy.pop();
    }
    std::cout << '\n';
}

