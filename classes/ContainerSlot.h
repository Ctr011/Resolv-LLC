//  ContainerSlot.h
#ifndef CONTAINERSLOT_H
#define CONTAINERSLOT_H

#include <iostream>
#include <format>
#include <string>

class Container;

class ContainerSlot {
protected:
    std::string name;
    int xPos;
    int yPos;
    bool movable;
    bool empty;
    int containerMass;

public:
    // Base Constructor here
    ContainerSlot(const std::string n, int x, int y, int mass, bool m, bool e) : name(n), yPos(y), xPos(x), containerMass(mass), movable(m), empty(e) {};
    
    //  @todo: Need to do research here. Not exactly sure why we need this but we do lol
    ContainerSlot() = default;

    std::string getName();
    int getXPos();
    int getYPos();
    int getMass();
    bool isMovable();
    bool isEmpty();

    //  Returns a container object
    virtual Container& getContainer() = 0;

    virtual std::string toString() = 0;

    // Destructor here
    virtual ~ContainerSlot(){};

};

class NANSlot : public ContainerSlot {
public:
    NANSlot(int x, int y);

    Container& getContainer() override;
    virtual std::string toString() override;
};

class EmptySlot : public ContainerSlot{
public: 
    EmptySlot(int x, int y);

    Container& getContainer() override;
    virtual std::string toString() override;
    void changeXPos(int x);
    void changeYPos(int y);
};

class Container: public ContainerSlot{

public:
    Container(std::string name, float mass, int x, int y);

    void changeXPos(int x);
    void changeYPos(int y);

    Container& getContainer() override;
    virtual std::string toString() override;
};



#endif