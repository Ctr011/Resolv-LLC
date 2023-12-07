//  Tree.cpp
#include "Tree.h"

Tree::Tree(Node* startNode, NodeQueue* queueType){
    this->startState = startNode;
    this->frontier = queueType;
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
            std::cout << "Goal Cost: " << next_node->getBalanceCost() << std::endl;

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

        std::cout << "Cost: " << next_node->getBalanceCost() << std::endl;
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

void Tree::solveSIFT(ShipBay* siftedState){

    //  initial check to check if ship is balanced
    if(this->startState->getBay()->compareBays(siftedState)){
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

        if(next_node->getBay()->compareBays(siftedState)){
            std::cout << "GOAL" << std::endl;
            next_node->printState();
            std::cout << "Goal Cost: " << next_node->getMoveCost() << std::endl;

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

        std::cout << "Cost: " << next_node->getMoveCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {
            bool foundInExplored = false;

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

/**
 * @fn solveUnload
 * Unlike the Balance, this will only solve a single unload, webserver will need to loop over
 * this function multiple times for multiple unloads
 * @param unload
*/
Node* Tree::solveUnLoad(std::string unload, Node* state){


    if(unload.size() == 0){
        //  If there are no unloads, we are finished
        return this->startState;
    }

    //  init initial size
    int initSize = state->getBay()->getAllContainers().size();

    //  Get the bay that was loaded
    ShipBay* activeBay = this->startState->getBay();

    //  Create explored tab
    std::vector<Node> explored;
    explored.push_back(*this->startState);

    this->frontier->add(this->startState);

    while(!this->frontier->isEmpty()){
        //  Pop next frontier
        Node* next_node = this->frontier->pop();

        //  Add node to explored set
        explored.push_back(*next_node);

        next_node->printState();

        //  Expand node only if not in explored
        std::vector<Node*> new_nodes = next_node->expandUnload(unload);

        std::cout << "Cost: " << next_node->getUnloadCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {

            if(node->getUnloadTarget().compare("DONE") == 0){
                std::cout << "GOAL" << std::endl;
                node->printState();
                std::cout << "Goal Cost: " << node->getMoveCost() << std::endl;

                Node* solutionNode = node;

                while (solutionNode->getParent() != nullptr) {
                    std::cout << solutionNode->getDescription() << std::endl;

                    // Move to the parent for the next iteration
                    solutionNode = solutionNode->getParent();
                }

                return node;
            }

            bool foundInExplored = false;

            //  Now, check if the container was removed
            //  If the total number of containers are less than original

            for (Node& explored_node : explored) {
                if (explored_node.compareNodes(node)) {
                    foundInExplored = true;
                    break;
                }
            }

            if (!foundInExplored) {
                try{
                    this->frontier->add(node);
                }catch(const std::exception& e){
                    std::cerr << "Caught an exception: " << e.what() << std::endl;
                }
            }
        }
    }

    return nullptr;
}

void Tree::solveLoad(Container* newContainer){

    //  If no container, retunr this state
    if(newContainer == nullptr){
        return;
    }

    //  Expand node only if not in explored
    std::vector<Node*> new_nodes = this->startState->expandLoad(newContainer);

    //  add all nodes to frontier
    for(Node* node : new_nodes){
        this->frontier->add(node);
    }

    //  Get lowest cost Node
    Node* low = this->frontier->pop();

    std::cout << "GOAL" << std::endl;
    low->printState();
    std::cout << "Goal Cost: " << low->getMoveCost() << std::endl;

    Node* solutionNode = low;

    while (solutionNode->getParent() != nullptr) {
        std::cout << solutionNode->getDescription() << std::endl;

        // Move to the parent for the next iteration
        solutionNode = solutionNode->getParent();
    }

}