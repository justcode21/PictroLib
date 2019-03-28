#include <fstream>
#include <iostream>

#ifndef IMAGE_H
#define IMAGE_H

#define BIT_DEPTH_SIZE 8
#define HEADER_SIZE 54
#define COLOR_TABLE_SIZE 1024
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define NO_OF_GREYSCALES 256

class Image
{
public:
    Image();
    virtual ~Image();
    Image(const Image &image);
    virtual bool initialize(const std::string &path, const std::string &type);
    virtual bool writeImage(const std::string &path, const std::string &type);
    virtual void increaseBrightness(unsigned char factor);
    virtual void decreaseBrightness(unsigned char factor);
    virtual void applyContrast();

private:
    void read(unsigned int length, unsigned char *buffer, std::ifstream &fin);
    void write(unsigned int length, unsigned char *buffer, std::ofstream &fout);
    float* computeHistogram();

    unsigned char m_header[HEADER_SIZE];
    unsigned char m_colorTable[COLOR_TABLE_SIZE];
    unsigned char m_bitDepth;
    unsigned int m_height;
    unsigned int m_width;
    unsigned char *m_imageData;
};

#endif // IMAGE_H
