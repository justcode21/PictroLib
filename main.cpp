#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/houses.bmp", Color::BLACKWHITE))
    {
        manager->setImage(image);
        image->generateSaltAndPeperNoise(0.6);
        image->writeImage("Images/cameraman_blured.bmp");    }

    return 0;
}


