#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/houses.bmp", Color::RGB))
    {
        manager->setImage(image);
        image->applyMask(MASK::LINE_DETECTOR_VER_MASK);
        image->writeImage("Images/houses_vertical.bmp");    }

    return 0;
}

