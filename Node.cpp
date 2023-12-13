#ifndef NODE_CPP
#define NODE_CPP
#include "Node.h"

std::map<std::string, std::string> Node::getDescription(){
    return this->move_description;
}

// Setter for move_description
void Node::setDescription(std::string name, std::string pickup_x, std::string pickup_y, std::string pickup_origin, std::string mass, std::string putdown_x, std::string putdown_y, std::string putdown_origin, std::string cost) {
    this->move_description["containerName"] = name;
    this->move_description["pickup_x"] = pickup_x;
    this->move_description["pickup_y"] = pickup_y;
    this->move_description["pickup_origin"] = pickup_origin;
    this->move_description["mass"] = mass;
    this->move_description["putdown_x"] = putdown_x;
    this->move_description["putdown_y"] = putdown_y;
    this->move_description["putdown_origin"] = putdown_origin;
    this->move_description["cost"] = cost;
}

int Node::getMoveCost(){
    return this->incoming_cost;
}

Node* Node::getParent(){
    return this->parent;
}

//  Only available to other node classes, mostly for cthe compareNodes() function
ShipBay* Node::getBay(){return this->bay;};
Buffer* Node::getBuffer(){return this->buffer;};
Container* Node::getPickUpContainer(){return this->pickedUp;}

bool Node::compareNodes(Node* otherNode){


    ContainerSlot* otherContainer = otherNode->getPickUpContainer();
    ShipBay* otherBay = otherNode->getBay();
    Buffer* otherBuffer = otherNode->getBuffer();

    //  First, compare the container picked up
    //  Handle nullptrs here
    if(this->pickedUp == nullptr && otherContainer != nullptr ||  this->pickedUp != nullptr && otherContainer == nullptr){
        return false;
    }

    //  If both are null, we can skip this. Otherwise, make sure they are the same.
    if(this->pickedUp != nullptr && otherContainer != nullptr){
            if(otherContainer->getName().compare(this->pickedUp->getName()) != 0
                || otherContainer->getMass() != this->pickedUp->getMass()){
                return false;
        }
    }

    //  Then compare bays
    if(!otherBay->compareBays(this->bay)){
        return false;
    }

    //  Lastly compare Buffers
    if(!otherBuffer->compareBuffers(this->buffer)){
        return false;
    }

    //  If all passes return true
    return true;
}

void Node::printState(){
    this->bay->printShipBay();
    this->buffer->printBuffer();
}

BalanceNode::BalanceNode(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent, Container* container){
    this->bay = currBay;
    this->buffer = currBuffer;
    this->incoming_cost = cost; //  Set up for uniform now. Change later

    if(parent){
        this->parent = parent;
    }else{
        this->parent = nullptr;
    }
    if(container){
        this->pickedUp = container;
    }else{
        this->pickedUp = nullptr;
    }
}

/**
 * 12/6
 * @fn expand()
 * Returns All possible child nodes from the current state
 * @param NONE
 * @return std::vector<Node*> (BalanceNode Objects)
*/
std::vector<Node*> BalanceNode::expand(){

    //  Create vector for expansion nodes
    std::vector<Node*> expansionNodes;

    //  Get the heights of all the columns
    std::vector<int> heights = this->bay->getHeights(1,12);
    std::vector<int> bufferHeights = this->buffer->getHeights(1, 24);

    int pickup_x, pickup_y, putdown_x, putdown_y, container_mass;

     //  Loop over every columns height in the ship bay
    for(int i = 0; i < heights.size(); i++){

        //  If height != 0 (Meaning it is not empty), pick it up
        if(heights[i] != 0){


            

            //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
            //  Also, the container that is picked up
            ShipBay* bayCopy = this->bay->clone();
            Buffer* bufferCopy = this->buffer->clone();
            Container* heldContainer = bayCopy->pickUpContainer(i);

            if(heldContainer){

                //  Get pickup COntainer info
                pickup_x = heldContainer->getXPos();
                pickup_y = heldContainer->getYPos();
                container_mass = heldContainer->getMass();

                for(int e = 0; e < heights.size(); e++){

                    if(i == e){
                        continue;
                    }

                    //  If height != 8 (Meaning it is not full), put it down
                    if(heights[e] < 9){
                        //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                        //  Also, the container that is picked up
                        ShipBay* bayInnerCopy = bayCopy->clone();
                        Buffer* bufferInnerCopy = bufferCopy->clone();

                        //  Get putdown position info
                        putdown_x = e + 1;
                        putdown_y = heights[e] + 1;


                        //  New copy of container
                        Container* newContainer = heldContainer->clone();
                        int cost = bayInnerCopy->putDownDontainer(newContainer, e);
                        Node* newNode = new BalanceNode(bayInnerCopy, bufferInnerCopy, cost + this->incoming_cost, this);
                        newNode->isSIFT = this->isSIFT;
                        newNode->setDescription(newContainer->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BAY", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BAY", std::to_string(cost));
                        expansionNodes.push_back(newNode);
                    }
                }

                for(int e = 0; e < bufferHeights.size(); e++){

                    if(i == e){
                        continue;
                    }

                    //  If height != 8 (Meaning it is not full), put it down
                    if(bufferHeights[e] != 4){
                        //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                        //  Also, the container that is picked up
                        ShipBay* bayInnerCopy = bayCopy->clone();
                        Buffer* bufferInnerCopy = bufferCopy->clone();

                        //  Get putdown position info
                        putdown_x = e + 1;
                        putdown_y = heights[e] + 1;

                        //  Put in new copy of container
                        Container* newContainer = heldContainer->clone();
                        int cost = bufferInnerCopy->putDownDontainer(newContainer, e);
                        Node* newNode = new BalanceNode(bayInnerCopy, bufferInnerCopy, cost + this->incoming_cost, this);
                        newNode->isSIFT = this->isSIFT;
                        newNode->setDescription(newContainer->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BAY", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BUFFER", std::to_string(cost));
                        expansionNodes.push_back(newNode);
                    }
                }
            }
        }
    }

    for(int i = 0; i < bufferHeights.size(); i++){

        //  If height != 0 (Meaning it is not empty), pick it up
        if(bufferHeights[i] != 0){
            //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
            //  Also, the container that is picked up
            ShipBay* bayCopy = this->bay->clone();
            Buffer* bufferCopy = this->buffer->clone();
            Container* heldContainer = bufferCopy->pickUpContainer(i);

            if(heldContainer){
                
                //  Get pickup COntainer info
                pickup_x = heldContainer->getXPos();
                pickup_y = heldContainer->getYPos();
                container_mass = heldContainer->getMass();

                for(int i = 0; i < heights.size(); i++){

                    //  If height != 8 (Meaning it is not full), put it down
                    if(heights[i] < 9){
                        //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                        //  Also, the container that is picked up
                        ShipBay* bayInnerCopy = bayCopy->clone();
                        Buffer* bufferInnerCopy = bufferCopy->clone();

                        //  Get putdown position info
                        putdown_x = i + 1;
                        putdown_y = heights[i] + 1;

                        //  New copy of container
                        Container* newContainer = heldContainer->clone();
                        int cost = bayInnerCopy->putDownDontainer(newContainer, i);
                        Node* newNode = new BalanceNode(bayInnerCopy, bufferInnerCopy, cost + this->incoming_cost, this);
                        newNode->isSIFT = this->isSIFT;
                        newNode->setDescription(newContainer->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BUFFER", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BAY", std::to_string(cost));
                        expansionNodes.push_back(newNode);
                    }
                }

                for(int i = 0; i < bufferHeights.size(); i++){

                    //  If height != 8 (Meaning it is not full), put it down
                    if(bufferHeights[i] != 4){
                        //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                        //  Also, the container that is picked up
                        ShipBay* bayInnerCopy = bayCopy->clone();
                        Buffer* bufferInnerCopy = bufferCopy->clone();

                        //  Get putdown position info
                        putdown_x = i;
                        putdown_y = heights[i];

                        //  Put in new copy of container
                        Container* newContainer = heldContainer->clone();
                        int cost = bufferInnerCopy->putDownDontainer(newContainer, i);
                        Node* newNode = new BalanceNode(bayInnerCopy, bufferInnerCopy, cost + this->incoming_cost, this);
                        newNode->isSIFT = this->isSIFT;
                        newNode->setDescription(newContainer->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BUFFER", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BUFFER", std::to_string(cost));
                        expansionNodes.push_back(newNode);
                    }
                }
            }
        }
    }

    return expansionNodes;

}

/**
 * 12.6
 * @fn getSIFTCost()
 * Given a SIFT solution state, finds the current distance from the state given the current state
 * @param NONE
 * @return {int} cost from goal
*/
int BalanceNode::getSIFTCost(){

    int cost = 0;

    //  Get all containers from the current bay
    std::priority_queue<Container*, std::vector<Container*>, ContainerComparator> allContainers = this->bay->getAllContainers();

    //  And the sift'd bay
    std::priority_queue<Container*, std::vector<Container*>, ContainerComparator> siftContainers = this->bay->getSIFTState()->getAllContainers();

    while(!siftContainers.empty()){

        //  Get both containers
        Container* sift_c = siftContainers.top();
        Container* init_c = allContainers.top();

        if(sift_c->getOrigin() != init_c->getOrigin()){
            //  Callculate the manhattan distance between, add to cost
            cost += std::sqrt(std::pow(sift_c->getXPos() - (init_c->getXPos() + 28), 2) + std::pow(sift_c->getYPos() - (init_c->getYPos() + 4), 2));
        }else{
            //  Callculate the manhattan distance between, add to cost
            cost += std::sqrt(std::pow(sift_c->getXPos() - (init_c->getXPos()), 2) + std::pow(sift_c->getYPos() - (init_c->getYPos()), 2));
        }

        //  Pop both 
        siftContainers.pop();
        allContainers.pop();
    }

    return (5 * cost) + this->incoming_cost;
}

int BalanceNode::getCost(){

    if(this->isSIFT){
        return this->getSIFTCost();
    }

    //  Below can be tweaked
    const double distanceWeight = 0.1f;
    const double balanceWeight = 0.9f;
    if(this->buffer->isEmpty()){
        return (distanceWeight * this->incoming_cost) + (balanceWeight * this->bay->calculateBalanceCost());
    }else{
        return (distanceWeight * this->incoming_cost) + (balanceWeight * this->bay->calculateBalanceCost()) + 10 * this->incoming_cost;
    }

};

/**
 * @fn isBalanced
 * Checks if current state of the cargo area is balanced
 * @param NONE
 * @return bool
*/
bool BalanceNode::isGoal(){
    if(bay->calculateBalanceCost() < 10 && buffer->isEmpty()){
        return true;
    }else{
        return false;
    }
}



UnloadNode::UnloadNode(ShipBay* currBay, Buffer* currBuffer, int cost, std::string unloadTarget, Node* parent, Container* container){
    
    this->bay = currBay;
    this->buffer = currBuffer;
    this->incoming_cost = cost; //  Set up for uniform now. Change later

    if(parent){
        this->parent = parent;
    }else{
        this->parent = nullptr;
    }
    if(container){
        this->pickedUp = container;
    }else{
        this->pickedUp = nullptr;
    }
    
    this->unloadTarget = unloadTarget;
}

int UnloadNode::getCost(){
    const double containersRemainingWeight = 0.7f;
    const double movesWeight = 0.3f;

    //  Get the containerPosition
    ContainerSlot* target = this->bay->getContainerByName(unloadTarget);

    //  Get the height of the column the container is in

    

    int height = this->bay->getHeights(target->getXPos() - 1, target->getXPos() - 1)[0];

    //  We are closer if the number of containers on top of the target is smaller
    int locationCost =  height - target->getYPos();


    //  12/4: Probably a better way to measure this, track the number of remaining containers to be unloaded
    if(this->buffer->isEmpty()){
        return (movesWeight * this->incoming_cost) + (containersRemainingWeight * height);
    }else{
        return (movesWeight * this->incoming_cost) + (containersRemainingWeight * height) + 10 * this->incoming_cost;
    }
}

bool UnloadNode::isGoal(){
    if(this->unloadTarget.compare("DONE") == 0){
        return true;
    }else{
        return false;
    }
}

std::vector<Node*> UnloadNode::expand(){

    std::vector<Node*> expansions;
    ShipBay* baycopy = this->bay->clone();
    Buffer* bufferCopy = this->buffer->clone();

    //  Search for container
    Container* foundContainer = &baycopy->getContainerByName(this->unloadTarget)->getContainer();

    int pickup_x, pickup_y, putdown_x, putdown_y, container_mass;

    //  if found, unload
    int cost = 0;
    if(foundContainer != nullptr){

        //  pick up the container in this copy
        Container* picked_up = baycopy->pickUpContainer(foundContainer->getXPos() - 1);

        //  Get pickup COntainer info
        pickup_x = picked_up->getXPos();
        pickup_y = picked_up->getYPos();
        container_mass = picked_up->getMass();


        //  If container is not what we wanted, move to side somewhere
        if(picked_up->getName().compare(this->unloadTarget) != 0){
            
             //  Get heights, to find out where we can put the other onctainers
            std::vector<int> heights = baycopy->getHeights(1, 12);
            
            int x;
            for(x = 0; x < BAY_MAX_X; x++){

                //  Unload options here
                if(heights[x] < 8){

                    //  Clone
                    ShipBay* bayInnerCopy = baycopy->clone();
                    Buffer* bufferInnerCopy = bufferCopy->clone();

                    //  Copy the container
                    Container* pickedUp_copy = picked_up->clone();

                    int cost = baycopy->putDownDontainer(pickedUp_copy, x);

                    putdown_x = pickedUp_copy->getXPos();
                    putdown_y = pickedUp_copy->getYPos();
                    container_mass = pickedUp_copy->getMass();

                    Node* newNode = new UnloadNode(bayInnerCopy, bufferInnerCopy, this->incoming_cost + cost, this->unloadTarget, this);
                    newNode->setDescription(pickedUp_copy->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BAY", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BAY", std::to_string(cost));
                    expansions.push_back(newNode);
                }
            }

            return expansions;
        }else{
            //  Load onto a truck
            int cost = baycopy->putDownDontainer(foundContainer, TRUCK_COLUMN);

            //  Add to expansions
            Node* newNode = new UnloadNode(baycopy, bufferCopy, this->incoming_cost + cost, "DONE", this);
            newNode->printState();
            newNode->setDescription(foundContainer->getName(), std::to_string(pickup_x), std::to_string(pickup_y), "BAY", std::to_string(container_mass), "N/A", "N/A", "TRUCK", std::to_string(cost));
            expansions.push_back(newNode);
        }
    }

    return expansions;
}



LoadNode::LoadNode(ShipBay* currBay, Buffer* currBuffer, int cost, Container* container, Node* parent){
    this->bay = currBay;
    this->buffer = currBuffer;
    this->incoming_cost = cost; //  Set up for uniform now. Change later

    if(parent){
        this->parent = parent;
    }else{
        this->parent = nullptr;
    }
    if(container){
        this->pickedUp = container;
    }else{
        this->pickedUp = nullptr;
    }
};

int LoadNode::getCost(){
    const double closestSlotWeight = 0.5f;
    const double movesWeight = 0.5f;

    //  Find all UNUSED slots
    int x, y, curr_distance;
    int shortest_distance = 99999;

    //  Find shortest distance of the unused spot
    for(x = 0; x < BAY_MAX_X; x++){
        for(y = 0; y < BAY_MAX_Y; y++){

            ContainerSlot* slot = this->bay->getSlot(x,y);
            if(slot->getName().compare("UNUSED") == 0){
                curr_distance = abs(slot->getXPos() - bay_exit_x) + abs(slot->getYPos() - bay_exit_y);

                if(curr_distance < shortest_distance){  
                    shortest_distance = curr_distance;
                }
            }
        }
    }

    //  Return weighted cost
    return (movesWeight * this->incoming_cost) + (closestSlotWeight * shortest_distance);
}

std::vector<Node*> LoadNode::expand(){

    //  init cots
    int cost;

    std::vector<Node*> expansions;

    
    int putdown_x, putdown_y, container_mass;

    //  Put down container in every possible column
    int x;
    for(x = 0; x < BAY_MAX_X; x++){

         //  Create a copy of the newContainer
        Container* container_copy = this->pickedUp->clone();

        ShipBay* baycopy = this->bay->clone();
        Buffer* bufferCopy = this->buffer->clone();

        //  Put down container into copy of bay
        cost = baycopy->putDownDontainer(container_copy, x);

        putdown_x = container_copy->getXPos();
        putdown_y = container_copy->getYPos();
        container_mass = container_copy->getMass();

        Node* newNode = new LoadNode(baycopy, bufferCopy, this->incoming_cost + cost, container_copy, this);
        newNode->setDescription(container_copy->getName(), "N/A", "N/A", "BAY", std::to_string(container_mass), std::to_string(putdown_x), std::to_string(putdown_y), "BAY", std::to_string(cost));
        newNode->printState();
        expansions.push_back(newNode);
        
    }

    return expansions;

}

//  Probably a better way to handle this lmao
bool LoadNode::isGoal(){return false;}
#endif