//  ShipBay.cpp
#include "ShipBay.h"
#include "ContainerSlot.h"


/**
 * 11/23/2023
 * @fn ShipBay (Constructor)
*/
ShipBay::ShipBay(const std::string manifestContent, std::vector<ContainerSlot*>* tempRow){
    this->originalText = manifestContent;
    parseContent(manifestContent);

    if(tempRow == nullptr){
        for(int x = 0; x < this->size_x; x++){
            this->temp.push_back(new EmptySlot(x + 1, this->size_y + 1, Origin::BAY));
        }
    }else{
        this->temp = *tempRow;
    }

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

    //  Init width and height of cargo bay as null
    int x, y;
    for(x = 0; x < this->size_x; x++){
        
        //  Push back new vector
        std::vector<ContainerSlot*> new_row;
        bayArea.push_back(new_row);

        //  Push back null for now
        for(y = 0; y < this->size_y; y++){
            this->bayArea[x].push_back(nullptr);
        }
    }

    x,y= 0;
    
    //  Get the next line of the file
    while (std::getline(filestream, curr_line)) {

        curr_line.erase(std::remove(curr_line.begin(), curr_line.end(), '\r'), curr_line.end());

        y = std::stoi(curr_line.substr(1,2));    //  x Position
        x = std::stoi(curr_line.substr(4,2));    //  y Position
        int weight = stoi(curr_line.substr(10,5));  //  Mass of Container
        std::string label = curr_line.substr(18);   //  get name of container
        
        

        //  TODO: Out of bounds handling
        //  If container is an NAN slot, return NAN object
        if(label.compare("NAN") == 0){
            bayArea[x - 1][y - 1] = new NANSlot(x, y, Origin::BAY);
        }
        else if(label.compare("UNUSED") == 0){ //  If it is empty, return NULL
            bayArea[x - 1][y - 1] = new EmptySlot(x, y, Origin::BAY);
        }else{
             //  Otherwise, data represents a container
            bayArea[x - 1][y - 1] = new Container(label, weight, x, y, Origin::BAY);
        }

       
    }
    return;
}

ContainerSlot* ShipBay::getContainer(int x, int y){

    //  If within range, grab the normal containerslot
    if(y <= this->size_y - 1){
        return this->bayArea[x][y];
    }else{
        //  Otherwise, grab from temp
        return this->temp[x];
    }
};

std::vector<ContainerSlot*> ShipBay::getTempRow(){return this->temp;};

/**
 * 11/26
 * @fn isBalanced
 * return boolean value if the carhgobay is balanced or not
 * 
*/
double ShipBay::calculateBalanceCost(){

    double mass1 = 0;
    double mass2 = 0;
    int x, y;

    //  Get mass of both sides
    for(x = 0; x < this->size_x; x++){
        for(y = 0; y < this->size_y; y++){
            if(x <= 5){
                mass1 += bayArea[x][y]->getMass();
            }else{
                mass2 += bayArea[x][y]->getMass();
            }
        }
    }

    //  Get 10% difference value, return if less than or qual to 10%
    double diff = std::abs(mass1 - mass2) * 100 / std::max(std::abs(mass1), std::abs(mass2));

    //  Return % difference here
    return diff;
    
}

bool ShipBay::compareBays(ShipBay* otherBay){
    int x, y;
    for(x = 0; x < this->size_x; x++){
        for(y = 0; y < this->size_y; y++){
            ContainerSlot* thisContainer = bayArea[x][y];
            ContainerSlot* otherContainer = otherBay->getContainer(x,y);

            if(thisContainer->getName().compare(otherContainer->getName()) != 0 
                || thisContainer->getMass() != otherContainer->getMass()){
                    return false;
            }
        }

        ContainerSlot* thisTemp = this->temp[x];
        ContainerSlot* otherTemp = otherBay->getContainer(x, this->size_y);

        //  Also check the temp rows here
        if(thisTemp->getName().compare(otherTemp->getName()) != 0
            || thisTemp->getMass() != otherTemp->getMass()){
            return false;
        }

    }

    return true;
}


/**
 * @fn getHeights
 * Retrieve a vector of the total stack heighst of every column in the Ship Bay
 * @param start: 1st column to be searched
 * @param end: last column to be searched
 * @returns std::vector<int>
*/
std::vector<int> ShipBay::getHeights(int start, int end){

    std::vector<int> heights;

    int x, y;

    for(x = start - 1; x < end; x++){
        for(y = 0; y <= this->size_y; y++){

            if(y < this->size_y){
                if(bayArea.at(x).at(y)->getName().compare("UNUSED") == 0){
                    heights.push_back(y);
                    break;
                }
            }else{
                if(this->temp[x]->getName().compare("UNUSED") == 0){
                    heights.push_back(y);
                    break;
                }
            }
        }
    }

    //  TODO: Consider the temporary row on top of cargo bay
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
    if(column < 0 || column > this->size_x){std::invalid_argument("Invalid Ship Column value: " + column);}

    //  Loop from the top, to find the topmost container object
    for(int i = this->size_y; i >= 0; i--){

        ContainerSlot* slot;
        if(i >= this->size_y){
            slot = this->temp[column];
        }else{
            slot = this->bayArea[column][i];
        }

        //  If the object is an actual container(So not UNUSED or NAN)
        if(slot->getName().compare("NAN") != 0 &&
        slot->getName().compare("UNUSED") != 0){

            //  Get pointer to the container
            Container* curr_container = &slot->getContainer();

            //  Dependant on 
            if(i >= this->size_y){
                this->temp[i] = new EmptySlot(column + 1, i + 1, Origin::BAY);;
            }else{
                this->bayArea[column][i] = new EmptySlot(column + 1, i + 1, Origin::BAY);;
            }

            //  Return the container that was picked up
            return curr_container;
        }else if(slot->getName().compare("NAN") == 0){   //  If we reach an NAN slot, there is not container in this column
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
    if(column < 1 || column > this->size_x){std::invalid_argument("Invalid Column value: " + column);}
    

    //  Search bottom up, to find first empty slot
    for(int i = 0; i <= this->size_y; i++){
        if(bayArea[column][i]->isEmpty()){

            //  Logic for temp row
            ContainerSlot* oldSlot;
            if(i >= this->size_y){
                oldSlot = temp[i];
                delete oldSlot;
                temp[i] = nullptr;
                temp[i] = container;
            }else{
                oldSlot = bayArea[column][i];
                delete oldSlot;
                bayArea[column][i] = nullptr;
                bayArea[column][i] = container;
            }

            //  now return the cost.
            int cost = 0;

            //  First, determine if there is any transfer penalty
            if(container->getOrigin() == Origin::BUFFER){
                //  Movement penalty
                cost += 4;

                //  Plus however long it take to get out of the buffer (manhattan distance)
                cost += std::abs(buffer_exit_x - container->getXPos()) + std::abs(buffer_exit_y - container->getYPos());

            }else if(container->getOrigin() == Origin::TRUCK){
                //  Just add the truck transfer penalty
                cost += 2;
            }

            //  Then, find manhattan distance within bay
            //  If container comes from the bay, just calculate manhattan distance bewteen the two spots
            if(container->getOrigin() == Origin::BAY){
                cost += calculateMovementCost((column + 1), (i + 1), container->getXPos(), container->getYPos());
            }else{
                //  Otherwise, calculate from the exit/enter point
                cost += calculateMovementCost((column + 1), (i + 1), bay_exit_x, bay_exit_y);
            }


            //  Update container info after calculating cost
            //  Assign the container, update the container's x-y position, and new origin
            container->changeXPos(column + 1);
            container->changeYPos(i + 1);
            container->setOrigin(Origin::BAY);
            this->bayArea[column][i] = container;

            return cost;
            
        }
    }

    //  return absurdly high number meaning that the column is not empty
    return 99999;
}

/**
 * @fn clone()
 * Creates and returns a clone of the current SHipBay object
 * @return ShipBay*
*/
ShipBay* ShipBay::clone(){
    std::string cloneBayData = "";
    std::vector<ContainerSlot*> newTemp;

    //  Clone bayArea using string info
    int x,y;
    for(x = 0; x < this->size_x; x++){
        for(y=0; y < this->size_y; y++){
            cloneBayData += bayArea[x][y]->toString();
        }

        //  Also populate temp with new COntainers
        if(this->temp[x]->getName().compare("NAN") == 0){
            newTemp.push_back(new NANSlot(x + 1, BAY_TEMP_Y, Origin::BAY));
        }else if(this->temp[x]->getName().compare("UNUSED") == 0){
            newTemp.push_back(new EmptySlot(x + 1, BAY_TEMP_Y, Origin::BAY));
        }else{
            newTemp.push_back(new Container(this->temp[x]->getName(), this->temp[x]->getMass(), x + 1, BAY_TEMP_Y, Origin::BAY));
        }

    }
    
    //  Return a new ShipBay Object after cloning
    return new ShipBay(cloneBayData, &newTemp);
}

/**
 * 
*/
void ShipBay::printShipBay(){


    int x,y;

    //  First print temp
    for(x = 0; x < this->size_x; ++x){
            if(temp[x]->getName().compare("NAN") == 0){
                std::cout << "N|";
            }else if(temp[x]->getName().compare("UNUSED") == 0){
                std::cout << " |";
            }else{
                std::cout << "C|";
            }
    }
    std::cout << "\n========================\n";
    std::cout << "\n========================\n";
    for(y = this->size_y - 1; y >= 0; --y){
        for(x = 0; x < this->size_x; ++x){
            if(bayArea[x][y]->getName().compare("NAN") == 0){
                std::cout << "N|";
            }else if(bayArea[x][y]->getName().compare("UNUSED") == 0){
                std::cout << " |";
            }else{
                std::cout << "C|";
            }
        }
        std::cout << "\n========================\n";
    }
    std::cout << "\n\n\n";
}

int ShipBay::calculateMovementCost(int x1, int y1, int x2, int y2){

    //  If its the same spot, just return the y position
    if(x1 == x2){return y1;};

    //  First get the current heights of all columns between the two positions
    std::vector<int> heights;
    if(x1 < x2){
         heights = getHeights(x1, x2);
    }else{
        heights = getHeights(x2, x1);
    }

    //  Find highest height of the vector
    auto maxElement = std::max_element(heights.begin(), heights.end());
    int maxVal = *maxElement;

    //  Find max between y1, y2, and the list
    int max_height = std::max(maxVal, std::max(y1, y2));

    int cost = 0;
    //  Meaning, if the position of one of the containers is taller than anything between the two
    if(max_height > maxVal){
        //  Calculate the basic manhattan distance
        cost += std::abs(x1 - x2) + std::abs(y1 - y2);
    }else{
        //  Calculate the manhattan distance from the lowest y-position container to the highest y-position
        //  Then the manhattan distance from there to the end position
        int max_starting = std::max(y1, y2);
        cost += max_height - max_starting;
        
        if(max_starting == y1){
            cost += std::abs(x1 - x2) + std::abs(max_starting - y2);
        }else{
            cost += std::abs(x1 - x2) + std::abs(y2 - max_starting);
        }
    }

    //  Return calculated cost
    return cost;

}