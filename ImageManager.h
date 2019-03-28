#ifndef IMAGECOPY_H
#define IMAGECOPY_H
#include <iostream>
#include <fstream>
#include "Image.h"

class ImageManager
{
public:
    ImageManager();
    virtual ~ImageManager();
    virtual bool setImage(Image *image);

private:

    Image *m_image;
};

#endif // IMAGECOPY_H
