#include "ImageManager.h"
int main(int argc, char *argv[])
{
    ImageManager *manager = new ImageManager();
    Image *image = new Image();
    if(image->initialize("Images/fruits.bmp", Image::Color::RGB))
    {
        manager->setImage(image);
        image->applySepia();
        image->writeImage("Images/cameraman_blured.bmp");    }

    return 0;
}


