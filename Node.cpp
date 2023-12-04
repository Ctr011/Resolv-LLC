#include "Node.h"


/**
 * @fn Node
 * Constructor for the Node class
 * @param {Node*} parent: The parent node of this node. Allowed to be NULL
 * @param {ShipBay} currBay: A copy of the next ShipBay object
 * @param {int} cost: The total cost of the Node
*/
Node::Node(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent, Container* container){
    
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

std::string Node::getDescription(){
    return move_description;
}

// Setter for move_description
void Node::setDescription(const std::string& description) {
    move_description = description;
}

void Node::setUnloadTarget(std::string target){
    this->unloadTarget = target;
}

std::string Node::getUnloadTarget(){
    return this->unloadTarget;
}

//  Getters
int Node::getBalanceCost(){

    //  Below can be tweaked
    const double distanceWeight = 0.6;
    const double balanceWeight = 0.4;
    if(this->buffer->isEmpty()){
        return (distanceWeight * this->incoming_cost) + (balanceWeight * this->bay->calculateBalanceCost());
    }else{
        return (distanceWeight * this->incoming_cost) + (balanceWeight * this->bay->calculateBalanceCost()) + 10 * this->incoming_cost;
    }

};

int Node::getSIFTCost(){

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
        cost += std::abs(sift_c->getXPos() - init_c->getXPos() + (28 - init_c->getXPos())) + std::abs(sift_c->getYPos() - init_c->getYPos() + 4);
        }else{
            //  Callculate the manhattan distance between, add to cost
        cost += std::abs(sift_c->getXPos() - init_c->getXPos()) + std::abs(sift_c->getYPos() - init_c->getYPos());
        }

        //  Pop both 
        siftContainers.pop();
        allContainers.pop();
    }

    return cost + this->incoming_cost;

}

int Node::getUnloadCost(){
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

int Node::getMoveCost(){
    return this->incoming_cost;
}

Node* Node::getParent(){
    return this->parent;
}

//  Only available to other node classes, mostly for cthe compareNodes() function
ShipBay* Node::getBay(){return this->bay;};
Buffer* Node::getBuffer(){return this->buffer;};
Container* Node::getPickUpContainer(){return this->pickedUp;};

std::vector<Node*> Node::expand(){

    //  Create vector for expansion nodes
    std::vector<Node*> expansionNodes;

    //  Get the heights of all the columns
    std::vector<int> heights = this->bay->getHeights(1,12);
    std::vector<int> bufferHeights = this->buffer->getHeights(1, 24);


    //  Actions if there is not a container currently picked up
    if(!this->pickedUp){


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
                    Node* newNode = new Node(bayCopy, bufferCopy, this->incoming_cost, this, heldContainer);
                    newNode->setDescription("UP: '" + heldContainer->getName() + "' {" + std::to_string(heldContainer->getXPos()) + ", " + std::to_string(heldContainer->getYPos()) + "}");
                    expansionNodes.push_back(newNode);
                }
            }
        }

        //  Now the same for the buffer
        for(int i = 0; i < bufferHeights.size(); i++){

            //  If height != 0 (Meaning it is not empty), pick it up
            if(bufferHeights[i] != 0){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();
                Buffer* bufferCopy = this->buffer->clone();

                Container* heldContainer = bufferCopy->pickUpContainer(i);

                if(heldContainer){
                    Node* newNode = new Node(bayCopy, bufferCopy, this->incoming_cost, this, heldContainer);
                    newNode->setDescription("UP: '" + heldContainer->getName() + "' *{" + std::to_string(heldContainer->getXPos()) + ", " + std::to_string(heldContainer->getYPos()) + "}");
                    expansionNodes.push_back(newNode);
                }
            }
        }


        return expansionNodes;
    }else{

        //  First, init picked up container's data
        std::string p_name = this->pickedUp->getName();
        int p_mass = this->pickedUp->getMass();
        int p_x = this->pickedUp->getXPos();
        int p_y = this->pickedUp->getYPos();
        Origin p_origin = this->pickedUp->getOrigin();

        for(int i = 0; i < heights.size(); i++){

            //  If height != 8 (Meaning it is not full), put it down
            if(heights[i] < 9){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();
                Buffer* bufferCopy = this->buffer->clone();

                //  Create new container based off one picked up
                

                //  New copy of container
                Container* newContainer = new Container(p_name, p_mass, p_x, p_y, p_origin);
                int cost = bayCopy->putDownDontainer(newContainer, i);
                Node* newNode = new Node(bayCopy, bufferCopy, cost + this->incoming_cost, this);
                newNode->setDescription("DN: '" + p_name + "' {" + std::to_string(newContainer->getXPos()) + ", " + std::to_string(newContainer->getYPos()) + "}");
                expansionNodes.push_back(newNode);
            }
        }

        for(int i = 0; i < bufferHeights.size(); i++){

            //  If height != 8 (Meaning it is not full), put it down
            if(bufferHeights[i] != 4){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();
                Buffer* bufferCopy = this->buffer->clone();

                //  Put in new copy of container
                Container* newContainer = new Container(p_name, p_mass, p_x, p_y, p_origin);
                int cost = bufferCopy->putDownDontainer(newContainer, i);
                Node* newNode = new Node(bayCopy, bufferCopy, cost + this->incoming_cost, this);
                newNode->setDescription("DN: '" + p_name + "' *{" + std::to_string(newContainer->getXPos()) + ", " + std::to_string(newContainer->getYPos()) + "}");
                expansionNodes.push_back(newNode);
            }
        }

        return expansionNodes;
    }

}

std::vector<Node*> Node:: expandUnload(std::string unload){

    std::vector<Node*> expansions;
    ShipBay* baycopy = this->bay->clone();
    Buffer* bufferCopy = this->buffer->clone();

    //  Get heights, to find out where we can put the other onctainers
    std::vector<int> heights = baycopy->getHeights(1, 12);

    //  If we are holding onto an unrelated container, move it somewhere
    if(this->pickedUp != nullptr){
        
        int x;
        for(x = 0; x < BAY_MAX_X; x++){
            //  Clone
            baycopy = this->bay->clone();
            bufferCopy = this->buffer->clone();

            //  Create copy of picked up container
            Container* containerCopy = new Container(this->pickedUp->getName(), this->pickedUp->getMass(), this->pickedUp->getXPos(), this->pickedUp->getYPos(), this->pickedUp->getOrigin());

            //  Unload options here
            if(heights[x] < 8){
                int cost = baycopy->putDownDontainer(containerCopy, x);
                Node* newNode = new Node(baycopy, bufferCopy, this->incoming_cost + cost, this);
                newNode->setUnloadTarget(this->unloadTarget);
                expansions.push_back(newNode);
            }
        }

        return expansions;
    }

    //  Search for container
    Container* foundContainer = &baycopy->getContainerByName(unload)->getContainer();

    //  if found, unload
    int cost = 0;
    if(foundContainer != nullptr){

        //  pick up the container in this copy
        Container* picked_up = baycopy->pickUpContainer(foundContainer->getXPos() - 1);

        //  If container is not what we wanted, move to side somewhere
        if(picked_up->getName().compare(unload) != 0){

            //  Copy the container
            Container* pickedUp_copy = new Container(picked_up->getName(), picked_up->getMass(), picked_up->getXPos(), picked_up->getYPos(), picked_up->getOrigin());

            //  Push back this copy
            Node* newNode = new Node(baycopy, bufferCopy, this->incoming_cost, this, pickedUp_copy);
            newNode->setUnloadTarget(this->unloadTarget);
            expansions.push_back(newNode);
        }else{
            //  Load onto a truck
            int cost = baycopy->putDownDontainer(foundContainer, TRUCK_COLUMN);

            //  Add to expansions
            Node* newNode = new Node(baycopy, bufferCopy, this->incoming_cost + cost, this);
            newNode->printState();
            newNode->setUnloadTarget("DONE");
            expansions.push_back(newNode);
        }
    }

    return expansions;
}

bool Node::compareNodes(Node* otherNode){


    ContainerSlot* otherContainer = otherNode->getPickUpContainer();
    ShipBay* otherBay = otherNode->getBay();
    Buffer* otherBuffer = otherNode->getBuffer();

    //  First, compare the container picked up

    //  Handle nullptrs here
    if(this->pickedUp == nullptr && otherContainer != nullptr 
    ||  this->pickedUp != nullptr && otherContainer == nullptr){
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

bool Node::isBalanced(){
    if(bay->calculateBalanceCost() < 10 && buffer->isEmpty() && pickedUp == nullptr){
        return true;
    }else{
        return false;
    }
}

/**
 * @fn getDistanceFromBalanced
 * Calculates a numberical value of how far the current ship bay is from being balanced
 * @returns {double}: value represnting distance 
 * @todo: Need to adjust this accordingly
*/
double Node::getDistanceFromBalanced(){
    return 0.0;
}

void Node::printState(){
    this->bay->printShipBay();
    this->buffer->printBuffer();
}