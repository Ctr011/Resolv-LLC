//  Misc.h

#ifndef MISC_H
#define MISC_H

//  constant for container exit for Buffer
const static int buffer_exit_x = 24;
const static int buffer_exit_y = 5;
const static int BUFFER_MAX_X = 24;
const static int BUFFER_MAX_Y = 4;

//  constant for container exit for Bay
const static int bay_exit_x = 1;
const static int bay_exit_y = 9;

const static int BAY_MAX_X = 12;
const static int BAY_MAX_Y = 8;
const static int BAY_TEMP_Y = 9;

enum class Origin{
    BAY = 0,
    BUFFER = 1,
    TRUCK = 2
};

#endif