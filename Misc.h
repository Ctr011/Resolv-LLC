//  Misc.h

#ifndef MISC_H
#define MISC_H

//  constant for container exit for Buffer
const static int buffer_exit_x = 24;
const static int buffer_exit_y = 5;

//  constant for container exit for Bay
const static int bay_exit_x = 1;
const static int bay_exit_y = 9;

enum class Origin{
    BAY = 0,
    BUFFER = 1,
    TRUCK = 2
};

#endif