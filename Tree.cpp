//  Tree.cpp
#include "Tree.h"

Tree::Tree(Node* startNode){
    this->startState = startNode;
}

void Tree::solveBalance(){

    //  initial check to check if ship is balanced
    if(this->startState->isBalanced()){
        std::cout << "GOAL" << std::endl;
        this->startState->printState();
        return;
    }

    //  Create explored tab
    std::vector<Node> explored;
    explored.push_back(*this->startState);

    //  Add first nodes to Node Queue
    std::vector<Node*> init_frontier = this->startState->expand();
    for(Node* node : init_frontier){
        this->frontier->add(node);
    }

    //  While not empty...
    while(!this->frontier->isEmpty()){

        //  Pop next frontier
        Node* next_node = this->frontier->pop();

        if(next_node->isBalanced()){
            std::cout << "GOAL" << std::endl;
            next_node->printState();
            std::cout << "Goal Cost: " << next_node->getCost() << std::endl;

            Node* solutionNode = next_node;

            while (solutionNode->getParent() != nullptr) {
                std::cout << solutionNode->getDescription() << std::endl;

                // Move to the parent for the next iteration
                solutionNode = solutionNode->getParent();
            }

            return;
        }

        //  Add node to explored set
        explored.push_back(*next_node);

        //  Expand node only if not in explored
        std::vector<Node*> new_nodes = next_node->expand();

        next_node->printState();

        std::cout << "Cost: " << next_node->getCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {
            bool foundInExplored = false;
            node->printState();

            for (Node& explored_node : explored) {
                if (explored_node.compareNodes(node)) {
                    foundInExplored = true;
                    break;
                }
            }

            if (!foundInExplored) {
                this->frontier->add(node);
            }
        }

    }
}

void Tree::solveLoad(){
    std::cout << "test" << std::endl;
}