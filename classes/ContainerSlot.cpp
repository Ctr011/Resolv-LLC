//  ContainerSlot.cpp
#include "ContainerSlot.h"

//  Getters
int ContainerSlot::getXPos(){return this->xPos;}
int ContainerSlot::getYPos(){return this->yPos;}
bool ContainerSlot::isMovable(){return this->movable;}
bool ContainerSlot::isEmpty(){return this->empty;};
std::string ContainerSlot::getName(){return this->name;};

/**
 * NANSlot Constructor
*/
NANSlot::NANSlot(int y, int x) : ContainerSlot("NAN", y, x, false, false){
    
    //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    this->containerData = "[" + formatted_y + "," + formatted_x + "], {00000}, " + this->name;
};
Container& NANSlot::getContainer(){
    throw std::invalid_argument("Object is not of Container Type");
};


/**
 * EmptySlot Constructor
*/
EmptySlot::EmptySlot(int y, int x) : ContainerSlot("UNUSED", y, x, true, true){
     //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    this->containerData = "[" + formatted_y + "," + formatted_x + "], {00000}, " + this->name;
};

void EmptySlot::changeXPos(int x){this->xPos = x; return;};
void EmptySlot::changeYPos(int y){this->yPos = y; return;};
Container& EmptySlot::getContainer(){
    throw std::invalid_argument("Object is not of Container Type");
};


/**
 * Container Constructor
*/
Container::Container(std::string name, float mass, int y, int x){
    
    //  Standard checks here
    if(name.empty() || name == "NAN" || name == "UNUSED"){throw std::invalid_argument("Invalid Container name: " + name);}; //  Check for invalid names
    if(name.length() > 256){throw std::invalid_argument("Container name too long.");} //  Name length
    if(mass < 0 || mass > 99999.0){ throw std::invalid_argument("Invalid mass for container: " + std::to_string(mass));} //  Mass number
    
    this->name = name;
    this->xPos = x;
    this->yPos = y;
    this->containerMass = mass;
    this->movable = true;
    this->empty = false;

    //  Construct Container data here (text data):
    // Format integer values with leading zeros if necessary
    std::string formatted_x = (this->xPos < 10) ? "0" + std::to_string(this->xPos) : std::to_string(this->xPos);
    std::string formatted_y = (this->yPos < 10) ? "0" + std::to_string(this->yPos) : std::to_string(this->yPos);

    this->containerData = "[" + formatted_y + "," + formatted_x + "], {00000}, " + this->name;
};

//  Container-Specific Getter
float Container::getMass(){return this->containerMass;};

//  Container changing positions/Mass
void Container::changeXPos(int x){this->xPos = x; return;};
void Container::changeYPos(int y){this->yPos = y; return;};
void Container::changeMass(float mass){this->containerMass = mass; return;};
Container& Container::getContainer(){
    return *this;
};


//  For Debugging
std::string Container::toString(){

    
    
}
