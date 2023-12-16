//  Tree.cpp
#include "Tree.h"

Tree::Tree(Node* startNode){
    this->startState = startNode;
    this->frontier = new NodeQueue();
}

Json Tree::solveBalance(){

    // //  initial check to check if ship is balanced
    // if(this->startState->isGoal()){
    //     std::cout << "GOAL" << std::endl;
    //     this->startState->printState();

    //     std::map<std::string, std::string> nodeMap = this->startState->getDescription();
    //     return nodeMap;
    // }

    //  Create explored tab
    std::vector<Node*> explored;
    explored.push_back(this->startState);

    //  Add first nodes to Node Queue
    std::vector<Node*> init_frontier = this->startState->expand();
    for(Node* node : init_frontier){
        this->frontier->add(node);
    }

    //  While not empty...
    while(!this->frontier->isEmpty()){

        //  Pop next frontier
        Node* next_node = this->frontier->pop();

        if(next_node->isGoal()){
            std::cout << "GOAL" << std::endl;
            next_node->printState();
            std::cout << "Goal Cost: " << next_node->getMoveCost() << std::endl;

            Node* solutionNode = next_node;

            Json reversedData;
            int moveNumber = 1;
            while (solutionNode->getParent() != nullptr) {

                std::map<std::string, std::string> nodeMap = solutionNode->getDescription();

                for(const auto& pair : nodeMap){
                    reversedData[std::to_string(moveNumber)][pair.first] = pair.second;
                }

                // Move to the parent for the next iteration
                solutionNode = solutionNode->getParent();

                moveNumber++;
            }

            //  Reverse the json here:
            Json solutionData;
            int size = reversedData.size();
            int reversedKey = 1;

            //  Populate here
            for(int i = size; i >= 1; i--){
                solutionData[std::to_string(reversedKey++)] = reversedData[std::to_string(i)];
            }

            std::string start = this->startState->getBay()->getText();
            std::string end = next_node->getBay()->getText();

            solutionData["startState"] = start;
            solutionData["endState"] = end;

            std::cout << "JSON Object:\n" << solutionData.dump(2) << std::endl;

            return solutionData;
        }

        //  Add node to explored set
        explored.push_back(next_node);

        //  Expand node only if not in explored
        std::vector<Node*> new_nodes = next_node->expand();

        next_node->printState();

        std::cout << "Cost: " << next_node->getMoveCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {
            bool foundInExplored = false;

            for (Node* explored_node : explored) {
                if (explored_node->compareNodes(node)) {
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

Json Tree::solveSIFT(ShipBay* siftedState){

    //  initial check to check if ship is balanced
    // if(this->startState->getBay()->compareBays(siftedState)){
    //     std::cout << "GOAL" << std::endl;
    //     this->startState->printState();
    //     return;
    // }
    
    //  Create explored tab
    std::vector<Node*> explored;
    explored.push_back(this->startState);

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

            Json reversedData;
            int moveNumber = 1;
           while (solutionNode->getParent() != nullptr) {

                std::map<std::string, std::string> nodeMap = solutionNode->getDescription();

                for(const auto& pair : nodeMap){
                    reversedData[std::to_string(moveNumber)][pair.first] = pair.second;
                }

                // Move to the parent for the next iteration
                solutionNode = solutionNode->getParent();

                moveNumber++;
            }

            std::cout << "Reversed JSON Object:\n" << reversedData.dump(2) << std::endl;

            //  Reverse the json here:
            Json solutionData;
            int size = reversedData.size();
            int reversedKey = 1;

            for(int i = size; i >= 1; i--){
                solutionData[std::to_string(reversedKey++)] = reversedData[std::to_string(i)];
            }

            std::string start = this->startState->getBay()->getText();
            std::string end = next_node->getBay()->getText();

            solutionData["startState"] = start;
            solutionData["endState"] = end;

            std::cout << "JSON Object:\n" << solutionData.dump(2) << std::endl;

            return solutionData;

        }

        //  Add node to explored set
        explored.push_back(next_node);

        //  Expand node only if not in explored
        std::vector<Node*> new_nodes = next_node->expand();

        next_node->printState();

        std::cout << "Cost: " << next_node->getMoveCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {
            bool foundInExplored = false;

            for (Node* explored_node : explored) {
                if (explored_node->compareNodes(node)) {
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
Json Tree::solveUnLoad(std::string target){

    //  init initial size
    int initSize = this->startState->getBay()->getAllContainers().size();

    //  Get the bay that was loaded
    ShipBay* activeBay = this->startState->getBay();

    //  Create explored tab
    std::vector<Node*> explored;
    explored.push_back(this->startState);

    this->frontier->add(this->startState);

    while(!this->frontier->isEmpty()){
        //  Pop next frontier
        Node* next_node = this->frontier->pop();

        //  Add node to explored set
        explored.push_back(next_node);

        next_node->printState();

        //  Expand node only if not in explored
        std::vector<Node*> new_nodes = next_node->expand();

        std::cout << "Cost: " << next_node->getCost() << std::endl;
        std::cout << std::endl;


        for (Node* node : new_nodes) {

            if(node->isGoal()){
                std::cout << "GOAL" << std::endl;
                node->printState();
                std::cout << "Goal Cost: " << node->getMoveCost() << std::endl;

                Node* solutionNode = node;
                std::string end = solutionNode->getBay()->getText();

                Json reversedData;
                int moveNumber = 1;
                while (solutionNode->getParent() != nullptr) {

                        std::map<std::string, std::string> nodeMap = solutionNode->getDescription();

                        for(const auto& pair : nodeMap){
                            reversedData[std::to_string(moveNumber)][pair.first] = pair.second;

                            //  Temp fix
                            std::string name = reversedData[std::to_string(moveNumber)]["containerName"];
                            if(name.compare("") == 0){
                                reversedData[std::to_string(moveNumber)]["containerName"] = target;
                            }
                        }

                        // Move to the parent for the next iteration
                        solutionNode = solutionNode->getParent();

                        moveNumber++;
                }

                //  Reverse the json here:
                Json solutionData;
                int size = reversedData.size();
                int reversedKey = 1;

                //  Populate here
                for(int i = size; i >= 1; i--){
                    solutionData[std::to_string(reversedKey++)] = reversedData[std::to_string(i)];
                }

                std::string start = this->startState->getBay()->getText();
                

                solutionData["startState"] = start;
                solutionData["endState"] = end;
                

                std::cout << "JSON Object:\n" << solutionData.dump(2) << std::endl;

                return solutionData;
            }

            bool foundInExplored = false;

            //  Now, check if the container was removed
            //  If the total number of containers are less than original

            for (Node* explored_node : explored) {
                if (explored_node->compareNodes(node)) {
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

Json Tree::solveLoad(){

    //  Expand node only if not in explored
    std::vector<Node*> new_nodes = this->startState->expand();

    //  add all nodes to frontier
    for(Node* node : new_nodes){
        this->frontier->add(node);
    }

    //  Get lowest cost Node
    Node* solutionNode = this->frontier->pop();

    std::cout << "GOAL" << std::endl;
    solutionNode->printState();
    std::cout << "Goal Cost: " << solutionNode->getMoveCost() << std::endl;

    Json solutionData;
    int moveNumber = 1;

    std::map<std::string, std::string> nodeMap = solutionNode->getDescription();

    for(const auto& pair : nodeMap){
        solutionData[pair.first] = pair.second;
    }

    solutionData["endState"] = solutionNode->getBay()->getText();

    std::cout << "JSON Object:\n" << solutionData.dump(2) << std::endl;

    return solutionData;

}