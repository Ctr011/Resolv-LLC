cmake_minimum_required(VERSION 3.8)

set (This Deckware)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

enable_testing()

add_subdirectory(googletest)

set(Headers
    Buffer.h
    ContainerSlot.h
    Misc.h
    Node.h
    NodeQueue.h
    ShipBay.h
)

set(Sources
    Buffer.cpp
    ContainerSlot.cpp
    Node.cpp
    ShipBay.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
