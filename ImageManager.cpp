#include "ImageManager.h"
#include <iostream>

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{

}


bool ImageManager::setImage(Image *image)
{
    if(image == nullptr)
    {
        std::cerr << "Please initialize the image first";
        return false;
    }
    else
    {
        m_image = image;
        return true;
    }
}






