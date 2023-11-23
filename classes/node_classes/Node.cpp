#include "Node.h"

/**
 * @fn Node
 * Constructor for the Node class
 * @param {Node*} parent: The parent node of this node. Allowed to be NULL
 * @param {ShipBay} currBay: A copy of the next ShipBay object
 * @param {int} cost: The total cost of the Node
*/
Node::Node(Node* parent, ShipBay currBay, int cost){
    this->parent = parent;
    this->bay = currBay;
    this->incoming_cost = cost;

    //  Automatically start with picking up a container
    this->isPickingUp = true;
}

//  Getter
int Node::getCost(){return this->incoming_cost;};

std::vector<Node> Node::expand(){

}