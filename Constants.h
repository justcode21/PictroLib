#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BIT_DEPTH_SIZE 8
#define HEADER_SIZE 54
#define COLOR_TABLE_SIZE 1024
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define NO_OF_GREYSCALES 256

static const float KERNAL_FILTER[3][3] =  {{1.0/9.0, 1.0/9.0, 1.0/9.0},
                                           {1.0/9.0, 1.0/9.0, 1.0/9.0},
                                           {1.0/9.0, 1.0/9.0, 1.0/9.0}};

static const int LINE_DETECTION_MASKS[4][3][3] = {
    {
        {-1,2,-1},
        {-1,2,-1},
        {-1,2,-1}
    },

    {
        {-1,-1,-1},
        {2, 2, 2},
        {-1,-1,-1}
    },

    {
        {2,-1,-1},
        {-1,2,-1},
        {-1,-1,2}
    },

    {
        {-1,-1,2},
        {-1,2,-1},
        {2,-1,-1}}
};

enum Direction
{
    LEFT,
    RIGHT,
    UPSIDEDOWN,
    MIRROR
};

enum Color
{
    BLACKWHITE = 1,
    RGB = 3
};

enum MASK
{
    LINE_DETECTOR_HOR_MASK,
    LINE_DETECTOR_VER_MASK,
    LINE_DETECTOR_LDIA_MASK,
    LINE_DETECTOR_RDIA_MASK
};


#endif // CONSTANTS_H
