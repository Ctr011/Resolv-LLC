//  ContainerSlot.h
#ifndef CONTAINERSLOT_H
#define CONTAINERSLOT_H

#include <iostream>
#include <string>

#include "Misc.h"

class Container;

class ContainerSlot {
protected:
    std::string name;
    int xPos;
    int yPos;
    bool movable;
    bool empty;
    int containerMass;

    Origin origin;

public:
    // Base Constructor here
    ContainerSlot(const std::string n, int x, int y, int mass, bool m, bool e, Origin o) : name(n), yPos(y), xPos(x), containerMass(mass), movable(m), empty(e), origin(o) {
        //  Positional checks here for bay and buffer containers. Truck doesnt matter
        if(this->origin == Origin::BAY){
            if(x < 1 || x > BAY_MAX_X){
                throw std::invalid_argument("Invalid x_position for Ship Bay: " + std::to_string(x));
            }else if(y < 1 || y > BAY_TEMP_Y){
                throw std::invalid_argument("Invalid y_position for Ship Bay: " + std::to_string(y));
            }
        }else if(this->origin == Origin::BUFFER){
            if(y < 1 || y > BUFFER_MAX_X){
                throw std::invalid_argument("Invalid x_position for Buffer: " + std::to_string(x));
            }else if(y < 1 || y > BUFFER_MAX_Y){
                throw std::invalid_argument("Invalid y_position for Buffer: " + std::to_string(y));
            }
        }
    };
    
    //  @todo: Need to do research here. Not exactly sure why we need this but we do lol
    ContainerSlot() = default;

    //  Getters
    std::string getName();
    int getXPos();
    int getYPos();
    int getMass();
    bool isMovable();
    bool isEmpty();
    Origin getOrigin();

    //  Setters
    void setOrigin(Origin newOrigin);

    //  Returns a container object
    virtual Container& getContainer() = 0;


    virtual std::string toString() = 0;

    // Destructor here
    virtual ~ContainerSlot(){};

};

class NANSlot : public ContainerSlot {
public:
    NANSlot(int x, int y, Origin o);

    Container& getContainer() override;
    virtual std::string toString() override;
};

class EmptySlot : public ContainerSlot{
public: 
    EmptySlot(int x, int y, Origin o);

    Container& getContainer() override;
    virtual std::string toString() override;
    void changeXPos(int x);
    void changeYPos(int y);
};

class Container: public ContainerSlot{

public:
    Container(std::string name, int mass, int x, int y, Origin o);

    void changeXPos(int x);
    void changeYPos(int y);

    //  Exclusive to  Containers: Will be able to clone self
    Container* clone();

    Container& getContainer() override;
    virtual std::string toString() override;
};



#endif
