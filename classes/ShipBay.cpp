//  ShipBay.cpp
#include "ShipBay.h"
#include "ContainerSlot.h"


/**
 * @fn ShipBay (Constructor)
*/
ShipBay::ShipBay(const std::string manifestContent){
    parseContent(manifestContent);
    return;
}

/**
 * @fn parseContent
 * Parses string content and creates the Ship Bay Area from it
 * @param {string} manifest
 * @return {void}
*/
void ShipBay::parseContent(std::string manifest){
    std::istringstream filestream(manifest);
    std::vector<std::string> data;
    int entries = 0;

    if (!filestream) {
        std::cout << "File Error";
        throw std::invalid_argument("Unable to parse manifest!");
        return;
    }

    std::string curr_line;
    int curr_col = -1;
    
    //  Get the next line of the file
    while (std::getline(filestream, curr_line)) {

        //  Make a new container out of the current line
        ContainerSlot curr_container = parseLine(curr_line);
        
        //  Make a new column if 
        if ((curr_container.getXPos() - 1) != curr_col) {
            std::vector<ContainerSlot> new_column;
            bayArea.push_back(new_column);
            curr_col++;
        }
        bayArea.at(curr_col).push_back(curr_container);
    }
    return;
}

/**
 * @fn parseLine
 * Parses a line of string and creates a COntainerSlot object
 * @param {string} entry
 * @return {ContainerSlot}
*/
ContainerSlot ShipBay::parseLine(std::string entry){

    //  Remove return value
    entry.erase(std::remove(entry.begin(), entry.end(), '\r'), entry.end());

    //  First get name of container
    int x = std::stoi(entry.substr(1,2));    //  x Position
    int y = std::stoi(entry.substr(4,2));    //  y Position
    int weight = stoi(entry.substr(10,5));  //  Mass of Container
    std::string label = entry.substr(18);

    //  If container is an NAN slot, return NAN object
    if(label.compare("NAN") == 0){
        return NANSlot(x, y);
    }

    else if(label.compare("UNUSED") == 0){ //  If it is empty, return NULL
        return EmptySlot(x, y);
    }

    //  Otherwise, data represents a container
    return Container(label, weight, x, y);
}

/**
 * @fn moveContainer
 * moves a container within the ship bay, while finding the lowest cost
 * @param {Container} container
 * @return {int}
*/
int ShipBay::moveContainer(Container& container,int endX){
    
}