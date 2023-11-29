//  ContainerSlot.cpp
#include "ContainerSlot.h"

//  Getters
int ContainerSlot::getXPos(){return this->xPos;}
int ContainerSlot::getYPos(){return this->yPos;}
bool ContainerSlot::isMovable(){return this->movable;}
bool ContainerSlot::isEmpty(){return this->empty;};
std::string ContainerSlot::getName(){return this->name;};
int ContainerSlot::getMass(){return this->containerMass;};
Origin ContainerSlot::getOrigin(){return this->origin;};

/**
 * NANSlot Constructor
*/
NANSlot::NANSlot(int x, int y, Origin o) : ContainerSlot("NAN", x, y, 0, false, false, o){};
Container& NANSlot::getContainer(){
    throw std::invalid_argument("Object is not of Container Type");
};

std::string NANSlot::toString(){
    //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    return "[" + formatted_y + "," + formatted_x + "], {00000}, " + this->name + "\r\n";
}


/**
 * EmptySlot Constructor
*/
EmptySlot::EmptySlot(int x, int y, Origin o) : ContainerSlot("UNUSED", x, y, 0, true, true, o){};

void EmptySlot::changeXPos(int x){this->xPos = x; return;};
void EmptySlot::changeYPos(int y){this->yPos = y; return;};
Container& EmptySlot::getContainer(){
    throw std::invalid_argument("Object is not of Container Type");
};

std::string EmptySlot::toString(){
    //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    return "[" + formatted_y + "," + formatted_x + "], {00000}, " + this->name + "\r\n";
}


/**
 * Container Constructor
*/
Container::Container(std::string name, float mass, int x, int y, Origin o) : ContainerSlot(name, x, y, mass, true, false, o){
    
    //  Standard checks here
    if(name.empty() || name == "NAN" || name == "UNUSED"){throw std::invalid_argument("Invalid Container name: " + name);}; //  Check for invalid names
    if(name.length() > 256){throw std::invalid_argument("Container name too long.");} //  Name length
    if(mass < 0 || mass > 99999.0){ throw std::invalid_argument("Invalid mass for container: " + std::to_string(mass));} //  Mass number
};

//  Container changing positions/Mass
void Container::changeXPos(int x){this->xPos = x; return;};
void Container::changeYPos(int y){this->yPos = y; return;};
Container& Container::getContainer(){
    return *this;
};

std::string Container::toString(){
    //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    std::string formatted_mass = (this->containerMass < 10) ? "0000" + std::to_string(this->containerMass)
                                                : (this->containerMass < 100) ? "000" + std::to_string(this->containerMass)
                                                                   : (this->containerMass < 1000) ? "00" + std::to_string(this->containerMass)
                                                                                        : (this->containerMass < 10000) ? "0" + std::to_string(this->containerMass)
                                                                                                             : std::to_string(this->containerMass);

    return "[" + formatted_y + "," + formatted_x + "], {" + formatted_mass + "}, " + this->name + "\r\n";
}