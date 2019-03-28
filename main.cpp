#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/cameraman", "bmp"))
    {
        manager->setImage(image);
        image->decreaseBrightness(50);

        image->writeImage("Images/cameraman_copy2", "bmp");
    }

    return 0;
}
