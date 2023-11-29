//  Buffer.cpp
#include "Buffer.h"
#include "ContainerSlot.h"

/**
 * 
*/
Buffer::Buffer(std::string bufferData){

    //  If empty, init an empty buffer area
    if(bufferData.empty()){
        int x, y;
        for(x = 0; x < this->size_x; x++){
            
            //  Push back new vector
            std::vector<ContainerSlot*> new_row;
            bufferArea.push_back(new_row);

            //  Push back empty slots for now
            for(y = 0; y < this->size_y; y++){
                this->bufferArea[x].push_back(new EmptySlot(x + 1, y + 1, Origin::BUFFER));
            }
        }
    }else{
        parseContent(bufferData);
    }
    return;
}

/**
 * 11/26/2023
 * @fn parseContent
 * Parses string content and creates the Buffer Area from it
 * @param {string} manifest
 * @return {void}
*/
void Buffer::parseContent(std::string bufferData){
    std::istringstream filestream(bufferData);
    std::vector<std::string> data;
    int entries = 0;

    if (!filestream) {
        std::cout << "File Error";
        throw std::invalid_argument("Unable to parse buffer!");
        return;
    }

    std::string curr_line;
    int curr_col = -1;

    //  Init width and height of cargo bay as null
    int x, y;
    for(x = 0; x < this->size_x; x++){
        
        //  Push back new vector
        std::vector<ContainerSlot*> new_row;
        bufferArea.push_back(new_row);

        //  Push back null for now
        for(y = 0; y < this->size_y; y++){
            this->bufferArea[x].push_back(nullptr);
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
            bufferArea[x - 1][y - 1] = new NANSlot(x, y, Origin::BUFFER);
        }
        else if(label.compare("UNUSED") == 0){ //  If it is empty, return NULL
            bufferArea[x - 1][y - 1] = new EmptySlot(x, y, Origin::BUFFER);
        }else{
             //  Otherwise, data represents a container
            bufferArea[x - 1][y - 1] = new Container(label, weight, x, y, Origin::BUFFER);
        }

       
    }
    return;
}

ContainerSlot* Buffer::getContainer(int x, int y){return this->bufferArea[x][y];};

/**
 * @fn isEmpty
 * Returns boolean value depnding on if buffer is empty or not
 * @return bool
*/
bool Buffer::isEmpty(){
    int x, y;
    for(x = 0; x < this->size_x; x++){
        for(y = 0; y < this->size_y; y++){
            if(bufferArea[x][y]->getName().compare("UNUSED") != 0){
                return false;
            }
        }
    }
    return true;
}

bool Buffer::compareBuffers(Buffer* otherBuffer){
    int x, y;
    for(x = 0; x < this->size_x; x++){
        for(y = 0; y < this->size_y; y++){
            ContainerSlot* thisContainer = bufferArea[x][y];
            ContainerSlot* otherContainer = otherBuffer->getContainer(x,y);

            if(thisContainer->getName().compare(otherContainer->getName()) != 0 
                || thisContainer->getMass() != otherContainer->getMass()){
                    return false;
            }
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
std::vector<int> Buffer::getHeights(int start, int end){

    std::vector<int> heights;

    int x, y;

    for(x = start - 1; x < end; x++){
        for(y = 0; y < this->size_y; y++){
            if(bufferArea.at(x).at(y)->getName().compare("UNUSED") == 0){
                heights.push_back(y);
                break;
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
 * 11/26/2023
 * @fn pickUpCOntainer
 * Picks up the top-most container from the given column
 * @return Container*: Pointer erference to the top-most container
*/
Container* Buffer::pickUpContainer(int column){

    //  Make sure column value is in range
    if(column < 0 || column >= this->size_x){std::invalid_argument("Invalid Ship Column value: " + column);}

    //  Loop from the top, to find the topmost container object
    for(int i = this->size_y - 1; i >= 0; i--){

        //  If the object is an actual container(So not UNUSED or NAN)
        if(!bufferArea[column][i]->getName().compare("NAN") == 0 &&
        !bufferArea[column][i]->getName().compare("UNUSED") == 0){

            //  Get pointer to the container
            Container* curr_container = &bufferArea[column][i]->getContainer();
            
            //  Replace container with a new Empty Slot
            bufferArea[column][i] = nullptr;
            bufferArea[column][i] = new EmptySlot(column + 1, i + 1, Origin::BUFFER);

            std::cout << this->bufferArea[column][i]->getName() << std::endl;

            //  Return the container that was picked up
            return curr_container;
        }else if(bufferArea[column][i]->getName().compare("NAN") == 0){   //  If we reach an NAN slot, there is not container in this column
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
int Buffer::putDownDontainer(Container* container, int column){
    if(container == nullptr){std::invalid_argument("Container is null.");}

    //  Make sure column value is in range
    if(column < 1 || column >= this->size_x){std::invalid_argument("Invalid Column value: " + column);}
    

    //  Search bottom up, to find first empty slot
    for(int i = 0; i < this->size_y; i++){
        if(bufferArea[column][i]->isEmpty()){

            //  Release the EmptySlot object
            ContainerSlot* oldSlot = bufferArea[column][i];
            delete oldSlot;

            bufferArea[column][i] = nullptr;

            //  Assign the container, update the container's x-y position
            bufferArea[column][i] = container;
            container->changeXPos(column + 1);
            container->changeYPos(i + 1);

            //  now return the cost, calculate by subtracting the i by the total height
            return this->bufferArea.size() - i;
        }
    }

    //  return -1 meaning that the column is not empty
    return -1;
}

/**
 * @fn clone()
 * Creates and returns a clone of the current Buffer object
 * @return Buffer*
*/
Buffer* Buffer::clone(){
    std::string cloneBayData = "";

    int x,y;
    for(x = 0; x < this->size_x; x++){
        for(y=0; y < this->size_y; y++){
            cloneBayData += bufferArea[x][y]->toString();
        }
    }

    return new Buffer(cloneBayData);
}

/**
 * 
*/
void Buffer::printBuffer(){


    int x,y;

    for(y = this->size_y - 1; y >= 0; --y){
        for(x = 0; x < this->size_x; ++x){
            if(bufferArea[x][y]->getName().compare("NAN") == 0){
                std::cout << "N|";
            }else if(bufferArea[x][y]->getName().compare("UNUSED") == 0){
                std::cout << " |";
            }else{
                std::cout << "C|";
            }
        }
        std::cout << "\n ============================================== \n";
    }
    std::cout << "\n\n\n";
}