#include "Node.h"


/**
 * @fn Node
 * Constructor for the Node class
 * @param {Node*} parent: The parent node of this node. Allowed to be NULL
 * @param {ShipBay} currBay: A copy of the next ShipBay object
 * @param {int} cost: The total cost of the Node
*/
Node::Node(ShipBay* currBay, int cost, Node* parent, Container* container){
    
    this->bay = currBay;
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

std::vector<Node*> Node::expand(){

    //  Create vector for expansion nodes
    std::vector<Node*> expansionNodes;

    //  Get the heights of all the columns
    std::vector<int> heights = this->bay->getHeights(1,12);


    //  Actions if there is not a container currently picked up
    if(!this->pickedUp){

        //  Loop over every columns height
        for(int i = 0; i < heights.size(); i++){

            //  If height != 0 (Meaning it is not empty), pick it up
            if(heights[i] != 0){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();

                Container* heldContainer = bayCopy->pickUpContainer(i);

                if(heldContainer){
                    bayCopy->printShipBay();
                    Node* newNode = new Node(bayCopy, (this->incoming_cost + heldContainer->getYPos()), this, heldContainer);
                    expansionNodes.push_back(newNode);
                }
            }
        }
        return expansionNodes;
    }else{
        for(int i = 0; i < heights.size(); i++){

            //  If height != 0 (Meaning it is not empty), pick it up
            if(heights[i] != 0){
                //  Make a new (deep) copy of current bay, one that no longer has the container that is picked up
                //  Also, the container that is picked up
                ShipBay* bayCopy = this->bay->clone();

                int cost = bayCopy->putDownDontainer(this->pickedUp, i);
                bayCopy->printShipBay();
                Node* newNode = new Node(bayCopy, cost, this);
                expansionNodes.push_back(newNode);
            }
        }
    }

}