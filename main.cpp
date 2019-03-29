#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/cameraman.bmp", Color::BLACKWHITE))
    {
        manager->setImage(image);
        image->applyEdgeDetection(PREWITT_HOR);
        image->writeImage("Images/cameraman_blured.bmp");    }

    return 0;
}


