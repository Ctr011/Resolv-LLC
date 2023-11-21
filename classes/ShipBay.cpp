//  ShipBay.cpp
#include "ShipBay.h"
#include "ContainerSlot.h"

/**
 * @fn ShipBay (Constructor)
*/
ShipBay::ShipBay(std::string manifestContent){
    parseContent(manifestContent);
}

/**
 * @fn parseContent
 * Parses string content and creates the Ship Bay Area from it
 * @param {string} manifest
 * @return {void}
*/
void ShipBay::parseContent(std::string manifest){
    std::ifstream filestream;
    std::vector<std::string> data;
    int entries = 0;

    filestream.open(manifest);
    if (!filestream.is_open()) {
        std::cout << "File Error";
    }

    std::string curr_line;
    int curr_col = -1;
    while (std::getline(filestream, curr_line)) {
        ContainerSlot curr_container = parseLine(curr_line);
        if ((curr_container.getXPos() - 1) != curr_col) {
            std::vector<ContainerSlot> new_column;
            bayArea.push_back(new_column);
            curr_col++;
        }
        bayArea.at(curr_col).push_back(curr_container);
    }
}

/**
 * @fn parseLine
 * Parses a line of string and creates a COntainerSlot object
 * @param {string} entry
 * @return {ContainerSlot}
*/
ContainerSlot ShipBay::parseLine(std::string entry){

    //  First get name of container
    int x = std::stoi(entry.substr(1,2));    //  x Position
    int y = std::stoi(entry.substr(4,2));    //  y Position
    int weight = stoi(entry.substr(10,5));  //  Mass of Container
    std::string label = entry.substr(18);

    //  If container is an NAN slot, return NAN object
    if(label.compare("NAN") == 0){
        return NANSlot(x, y);
    }

    // else if(label.compare("UNUSED") == 0){ //  If it is empty, return NULL
    //     return NULL;
    // }

    //  Otherwise, data represents a container
    return Container(label, weight, x, y);
}

/**
 * @fn addContainer
 * @todo: Create addContainer function
*/
void ShipBay::addContainer(Container newContainer, int x, int y){
    return;
}