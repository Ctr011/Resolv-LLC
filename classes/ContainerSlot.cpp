//  ContainerSlot.cpp
#include "ContainerSlot.h"

//  Getters
int ContainerSlot::getXPos(){return this->xPos;}
int ContainerSlot::getYPos(){return this->yPos;}
bool ContainerSlot::isMovable(){return this->movable;}
string ContainerSlot::getName(){return this->name;};

/**
 * NANSlot Constructor
*/
NANSlot::NANSlot(int x, int y) : ContainerSlot("NAN", x, y, false){};

/**
 * Container Constructor
*/
Container::Container(string name, float mass, int x, int y) : ContainerSlot(name, x, y, true){
    if(name.empty() || name == "NAN" || name == "UNUSED"){throw std::invalid_argument("Invalid Container name: " + name);}; //  Check for invalid names
    if(name.length() > 256){throw std::invalid_argument("Container name too long.");} //  Name length
    if(mass < 0 || mass > 99999.0){ throw std::invalid_argument("Invalid mass for container: " + to_string(mass));} //  Mass number
    containerMass = mass;
};

//  COntainer Getters
float Container::getMass(){return this->containerMass;};

//  Container changing positions
void Container::changeXPos(int x){this->xPos = x; return;};
void Container::changeYPos(int y){this->yPos = y; return;};
void Container::changeMass(float mass){this->containerMass = mass; return;};

//  Just for our use
void Container::toString(){
    string output = "Container Info";
    std::cout << "Container Info" << endl;
    std::cout << "==================" << endl;
    std::cout << "Name: " << this->name << endl;
    std::cout << "Mass: " << to_string(this->containerMass) << endl;
    std::cout << "Position: {" << to_string(this->xPos) << ", " << to_string(this->yPos) << "}" << endl;
    std::cout << "==================" << endl;
}