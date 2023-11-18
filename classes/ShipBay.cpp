//  ShipBay.cpp
#include "ShipBay.h"

/**
 * @fn ShipBay (Constructor)
*/
ShipBay::ShipBay(std::string filePath){
    //  @todo: Load manifest into bayArea martix here

    //  Define filepath here
    this->manifestFilePath = filePath;
    
    //  Open file stream
    std::ifstream manifest(filePath);

    //  String value for content of manifest
    std::string manifestContent;

    //  @todo: There has to be a better way to do this
    int containerInfo = 0;
    if(manifest.is_open()){
        while(manifest.good()){
            manifest >> manifestContent;
            std::cout << manifestContent;
        }
    }else{
        throw std::invalid_argument("The file '" + filePath +"' is unable to be opened");
    }
    
}