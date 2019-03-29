#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/houses.bmp", Color::BLACKWHITE))
    {
        manager->setImage(image);
        image->applyEdgeDetection(LINE_DETECTOR_VER_MASK);
        image->writeImage("Images/cameraman_blured.bmp");    }

    return 0;
}


