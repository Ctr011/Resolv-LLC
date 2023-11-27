//  Buffer.h

#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "ContainerSlot.h"


class Buffer{
    int size_x = 24;
    int size_y = 4;
    std::vector<std::vector<ContainerSlot*>> bufferArea;

    void parseContent(const std::string bufferData);

public: 

    Buffer() = default;

    ContainerSlot* getContainer(int x, int y);

    bool isEmpty();
    bool compareBuffers(Buffer* otherBuffer);

    Buffer(std::string bufferData);

    std::vector<int>getHeights(int start, int end);

    Container* pickUpContainer(int column);

    int putDownDontainer(Container* container, int column);

    Buffer* clone();

    void printBuffer();

    virtual ~Buffer(){};
};

#endif