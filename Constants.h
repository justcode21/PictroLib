#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BIT_DEPTH_SIZE 8
#define HEADER_SIZE 54
#define COLOR_TABLE_SIZE 1024
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define NO_OF_GREYSCALES 256

static const float KERNAL_FILTER[3][3] =  {
    {1.0/9.0, 1.0/9.0, 1.0/9.0},
    {1.0/9.0, 1.0/9.0, 1.0/9.0},
    {1.0/9.0, 1.0/9.0, 1.0/9.0}
};

static const int LINE_DETECTION_MASKS[27][3][3] = {

    //Convolution Masks
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
        {2,-1,-1}
    },

    //Prewitt Masks
    {
        {-1,-1,-1},
        {0, 0, 0},
        {1, 1, 1}
    },

    {
        {-1, 0, 1},
        {-1, 0, 1},
        {-1, 0, 1}
    },

    //Sobel Masks
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    },

    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    },

    //Robinson Masks
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    },

    {
        {-2, -1, 0},
        {-1, 0, 1},
        {0, 1, 2}
    },

    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    },

    {
        {0, -1, -2},
        {1, 0, -1},
        {2, 1, 0}
    },

    {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, 1}
    },

    {
        {2, 1, 0},
        {1, 0, -1},
        {0, -1, -2}
    },

    {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    },

    {
        {0, 1, 2},
        {-1, 0, 1},
        {-2, -1, 0}
    },

    //Kirsch Masks
    {
        {5, 5, 5},
        {-3, 0, -3},
        {-3, -3, -3}
    },

    {
        {-3, 5, 5},
        {-3, 0, 5},
        {-3, -3, -3}
    },

    {
        {-3, -3, 5},
        {-3, 0, 5},
        {-3, -3, 5}
    },

    {
        {-3, -3, 5},
        {-3, 0, 5},
        {-3, 5, 5}
    },

    {
        {-3, -3, -3},
        {-3, 0, -3},
        {5, 5, 5}
    },

    {
        {-3, -3, -3},
        {5, 0, -3},
        {5, 5, -3}
    },

    {
        {5, -3, -3},
        {5, 0, -3},
        {5, -3, -3}
    },

    {
        {5, 5, -3},
        {5, 0, -3},
        {-3, -3, -3}
    },

    //laplacian Masks
    {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    },

    {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0}
    },

    //Sharpner
    {
        {-1, -1, -1},
        {-1, 9, -1},
        {-1, -1, -1}
    }
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
    LINE_DETECTOR_RDIA_MASK,

    //Prewitt Masks
    PREWITT_HOR,
    PREWITT_VER,

    //Sobel Masks
    SOBEL_HOR,
    SOBEL_VER,

    //Robinson Masks(Compass Operator)
    ROBINSON_NORTH,
    ROBINSON_NORTHEAST,
    ROBINSON_EAST,
    ROBINSON_SOUTHEAST,
    ROBINSON_SOUTH,
    ROBINSON_SOUTHWEST,
    ROBINSON_WEST,
    ROBINSON_NORTHWEST,

    //Kirsch Masks(Compass Operator)
    KIRSCH_NORTH,
    KIRSCH_NORTHEAST,
    KIRSCH_EAST,
    KIRSCH_SOUTHEAST,
    KIRSCH_SOUTH,
    KIRSCH_SOUTHWEST,
    KIRSCH_WEST,
    KIRSCH_NORTHWEST,

    //Laplacian Masks
    LAPLACIAN_NEGETIVE,
    LAPLACIAN_POSITIVE,

    //High Pass FIlter(Sharpner)
    IMAGE_SHARPNER
};

#endif // CONSTANTS_H
