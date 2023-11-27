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
    this->incoming_cost = cost;

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

//  Getters
int Node::getCost(){return this->incoming_cost;};

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
                    Node* newNode = new Node(bayCopy, bufferCopy, (this->incoming_cost + heldContainer->getYPos()), this, heldContainer);
                    expansionNodes.push_back(newNode);
                    bayCopy->printShipBay();
                    bufferCopy->printBuffer();
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
                    Node* newNode = new Node(bayCopy, bufferCopy, (this->incoming_cost + heldContainer->getYPos()), this, heldContainer);
                    expansionNodes.push_back(newNode);
                    bayCopy->printShipBay();
                    bufferCopy->printBuffer();
                }
            }
        }


        return expansionNodes;
    }else{
        for(int i = 0; i < heights.size(); i++){

            //  If height != 8 (Meaning it is not full), put it down
            if(heights[i] != 8){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();
                Buffer* bufferCopy = this->buffer->clone();

                int cost = bayCopy->putDownDontainer(this->pickedUp, i);
                Node* newNode = new Node(bayCopy, bufferCopy, cost, this);
                expansionNodes.push_back(newNode);
                bayCopy->printShipBay();
                bufferCopy->printBuffer();
            }
        }

        for(int i = 0; i < bufferHeights.size(); i++){

            //  If height != 8 (Meaning it is not full), put it down
            if(bufferHeights[i] != 8){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();
                Buffer* bufferCopy = this->buffer->clone();

                int cost = bufferCopy->putDownDontainer(this->pickedUp, i);
                Node* newNode = new Node(bayCopy, bufferCopy, cost, this);
                expansionNodes.push_back(newNode);
                bayCopy->printShipBay();
                bufferCopy->printBuffer();
            }
        }

        return expansionNodes;
    }

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
                delete otherContainer;
                delete otherBay;
                delete otherBuffer;
                return false;
        }
    }

    //  Then compare bays
    if(!otherBay->compareBays(this->bay)){
        delete otherContainer;
        delete otherBay;
        delete otherBuffer;
        return false;
    }

    //  Lastly compare Buffers
    if(!otherBuffer->compareBuffers(this->buffer)){
        delete otherContainer;
        delete otherBay;
        delete otherBuffer;
        return false;
    }

    //  Delete pointers
    delete otherContainer;
    delete otherBay;
    delete otherBuffer;

    //  If all passes return true
    return true;
}