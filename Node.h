// Node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "./ShipBay.h"
#include "./Buffer.h"
#include "./ContainerSlot.h"

class BalanceNode;
class UnloadNode;
class LoadNode;

class Node {

protected:
    Node* parent;
    ShipBay* bay;
    Buffer* buffer;
    Container* pickedUp;
    int incoming_cost;
    std::string move_description;

public:

    //  I'm too lazy to implement getters/setters lol
    bool isSIFT = false;

    //  Base constuctor
    Node() = default;
    Node(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent = nullptr, Container* container = nullptr);

    //  Basic getters
    ShipBay* getBay();
    Buffer* getBuffer();
    Container* getPickUpContainer();
    Node* getParent();


    //  Basically for printing the set of instructions
    std::string getDescription();
    void setDescription(const std::string& description);
    
    //  Required by subclasses
    virtual int getCost() = 0;
    virtual std::vector<Node*> expand() = 0;
    virtual bool isGoal() = 0;

    //   Gets the pure movement cost to th current stats
    int getMoveCost();

    //  Checks to see if two nodes match
    bool compareNodes(Node* otherNode);

    void printState();
};

class BalanceNode : public Node {

protected:

    bool canSIFT;

public:
    BalanceNode() = default;
    BalanceNode(ShipBay* currBay, Buffer* currBuffer, int cost, Node* parent = nullptr, Container* container = nullptr);

    int getSIFTCost();  //  12/2 Added arg, since sift state will not change between nodes

    int getCost() override;
    std::vector<Node*> expand() override;
    bool isGoal() override;
    

    bool isBalanced();

    // Node* getSIFT();
    //std::string getMoves();
};

class UnloadNode : public Node{

    //  Used only for the unloads, cost calculataions
    std::string unloadTarget;

public:

    UnloadNode() = default;
    UnloadNode(ShipBay* currBay, Buffer* currBuffer, int cost, std::string unloadTarget, Node* parent = nullptr, Container* container = nullptr);

    int getCost() override;
    std::vector<Node*> expand() override;
    bool isGoal() override;

    //bool isDoneUnloading(std::vector<std::string> allContainers);
};

class LoadNode : public Node{

public:

    //  Container picked up is required, to load into bay
    LoadNode() = default;
    LoadNode(ShipBay* currBay, Buffer* currBuffer, int cost, Container* container, Node* parent = nullptr);

    int getCost() override;
    std::vector<Node*> expand() override;
    bool isGoal() override;
};
#endif
