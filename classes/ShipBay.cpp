//  ShipBay.cpp
#include "ShipBay.h"
#include "ContainerSlot.h"


/**
 * 11/23/2023
 * @fn ShipBay (Constructor)
*/
ShipBay::ShipBay(const std::string manifestContent){
    this->originalText = manifestContent;
    parseContent(manifestContent);
    return;
}

/**
 * 11/23/2023
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

        curr_line.erase(std::remove(curr_line.begin(), curr_line.end(), '\r'), curr_line.end());

        int y = std::stoi(curr_line.substr(1,2));    //  x Position
        int x = std::stoi(curr_line.substr(4,2));    //  y Position
        int weight = stoi(curr_line.substr(10,5));  //  Mass of Container
        std::string label = curr_line.substr(18);   //  get name of container
        
        //  Make a new row if row has reached capacity
        if ((y - 1) != curr_col) {
            std::vector<ContainerSlot*> new_column;
            bayArea.push_back(new_column);
            curr_col++;
        }

        //  If container is an NAN slot, return NAN object
        if(label.compare("NAN") == 0){
            bayArea.at(curr_col).push_back(new NANSlot(x, y));
        }
        else if(label.compare("UNUSED") == 0){ //  If it is empty, return NULL
            bayArea.at(curr_col).push_back(new EmptySlot(x, y));
        }else{
             //  Otherwise, data represents a container
            bayArea.at(curr_col).push_back(new Container(label, weight, x, y));
        }

       
    }
    return;
}

std::vector<int> ShipBay::getHeights(int start, int end){

    std::vector<int> heights;

    int x, y;

    

    for(y = start - 1; y < end; y++){
        for(x = 0; x < this->size_x; x++){
            if(bayArea.at(x).at(y)->getName().compare("UNUSED") == 0){
                heights.push_back(x);
                break;
            }
        }
    }
    if(y == this->size_y){
        heights.push_back(this->size_y);
    }

    return heights;
}

/**
 * 11/23/2023
 * @fn pickUpCOntainer
 * Picks up the top-most container from the given column
 * @return Container*: Pointer erference to the top-most container
*/
Container* ShipBay::pickUpContainer(int column){

    //  Make sure column value is in range
    if(column < 1 || column >= this->size_x){std::invalid_argument("Invalid Column value: " + column);}

    //  Loop from the top, to find the topmost container object
    for(int i = this->size_y - 1; i >= 0; i--){

        //  If the object is an actual container(So not UNUSED or NAN)
        if(!bayArea[i][column]->getName().compare("NAN") == 0 &&
        !bayArea[i][column]->getName().compare("UNUSED") == 0){

            //  Get pointer to the container
            Container* curr_container = &bayArea[i][column]->getContainer();
            
            //  Replace container with a new Empty Slot
            bayArea[i][column] = nullptr;
            bayArea[i][column] = new EmptySlot(column, i);

            std::cout << this->bayArea[i][column]->getName() << std::endl;

            //  Now modify the text info

            curr_container->toString();

            //  Return the container that was picked up
            return curr_container;
        }else if(bayArea[i][column]->getName().compare("NAN") == 0){   //  If we reach an NAN slot, there is not container in this column
            return nullptr;
        }
    }
    //  If all containers are "UNUSED", then colmun is empty
    return nullptr;
}

/**
 * 11/23/2023
 * @fn putDownContainer
 * Puts a container down at the lowest point of a column
 * @param {Container*} Container to be put down
 * @param {int} The column for container to be put down into
 * @return int: The cost to put down
*/
int ShipBay::putDownDontainer(Container* container, int column){
    if(container == nullptr){std::invalid_argument("Container is null.");}

    //  Make sure column value is in range
    if(column < 1 || column >= this->size_x){std::invalid_argument("Invalid Column value: " + column);}
    

    //  Search bottom up, to find first empty slot
    for(int i = 0; i < this->size_y; i++){
        if(bayArea[i][column]->isEmpty()){

            //  Release the EmptySlot object
            ContainerSlot* oldSlot = bayArea[i][column];
            delete oldSlot;

            bayArea[i][column] = nullptr;

            //  Assign the container, update the container's x-y position
            bayArea[i][column] = container;
            container->changeXPos(column + 1);
            container->changeYPos(i + 1);

            //  now return the cost, calculate by subtracting the i by the total height
            return this->bayArea.size() - i;
        }
    }

    //  return -1 meaning that the column is not empty
    return -1;
}

/**
 * @fn clone()
 * Creates and returns a clone of the current SHipBay object
 * @return ShipBay*
*/
ShipBay* ShipBay::clone(){
    return new ShipBay(this->originalText);
}

/**
 * 
*/
void ShipBay::printShipBay(){
    for(int x = bayArea.size() - 1; x >= 0 ; x--){
        for(int y = 0; y < bayArea[x].size(); y++){
            if(bayArea[x][y]->getName().compare("NAN") == 0){
                std::cout << "N|";
            }else if(bayArea[x][y]->getName().compare("UNUSED") == 0){
                std::cout << " |";
            }else{
                std::cout << "C|";
            }
        }
        std::cout << "\n=========================\n";
    }
    std::cout << "\n\n\n";
}