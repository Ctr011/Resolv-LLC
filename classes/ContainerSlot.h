//  ContainerSlot.h
#ifndef CONTAINERSLOT_H
#define CONTAINERSLOT_H

#include <iostream>
#include <string>

class ContainerSlot {
protected:
    std::string name;
    int xPos;
    int yPos;
    bool movable;

public:
    // Base Constructor here
    ContainerSlot(const std::string n, int x, int y, bool m) : name(n), xPos(x), yPos(y), movable(m) {};
    
    //  @todo: Need to do research here. Not exactly sure why we need this but we do lol
    ContainerSlot() = default;

    std::string getName();
    int getXPos();
    int getYPos();
    bool isMovable();

    // Destructor here
    virtual ~ContainerSlot(){};
};

class NANSlot : public ContainerSlot {
public:
    NANSlot(int x, int y);
};

class Container: public ContainerSlot{

    float containerMass;

public:
    Container(std::string name, float mass, int x, int y);

    void changeXPos(int x);
    void changeYPos(int y);

    float getMass();
    void changeMass(float mass); //  Do we need this?

    void toString();
};

#endif