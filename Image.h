#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Constants.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:

    Image();
    virtual ~Image();
    Image(const Image &image);
    virtual bool initialize(const std::string &path, const Color &color);
    virtual bool writeImage(const std::string &path);
    virtual void rotate(const Direction &direction);
    virtual void increaseBrightness(const unsigned char &factor);
    virtual void decreaseBrightness(const unsigned char &factor);
    virtual void applyContrast();
    virtual void applyNegetive();
    virtual void applyBlur();
    virtual void applySepia();
    virtual void applyMaxFilter(const unsigned char &area);
    virtual void applyMinFilter(const unsigned char &area);
    virtual void applyMedianFilter(const unsigned char &area);
    virtual void applyMask(const MASK &mask);
    virtual void generateNoise(const float &variance, const float &mean);
    virtual void generateSaltAndPeperNoise(const float &intensity);

private:

    float* computeHistogram();

    unsigned char m_header[HEADER_SIZE];
    unsigned char m_colorTable[COLOR_TABLE_SIZE];
    unsigned char m_bitDepth;
    unsigned int m_height;
    unsigned int m_width;
    unsigned char **m_imageData;
    unsigned int m_color;
};

#endif // IMAGE_H
