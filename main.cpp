#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/girlface.bmp", Color::BLACKWHITE))
    {
        manager->setImage(image);
        image->applyMask(IMAGE_SHARPNER);
        image->writeImage("Images/girlface_sharp.bmp");    }

    return 0;
}

