#include "Image.h"

Image::Image()
{

}

Image::~Image()
{

}

Image::Image(const Image &image)
{
    m_width = image.m_width;
    m_height = image.m_height;
    for(int i = 0; i < HEADER_SIZE; i++)
    {
        m_header[i] = image.m_header[i];
    }
    m_bitDepth = image.m_bitDepth;

    for(int i = 0; i < COLOR_TABLE_SIZE; i++)
    {
        m_colorTable[i] = image.m_colorTable[i];
    }
    m_imageData = new unsigned char[m_width * m_height];
    for(int i = 0; i < m_width * m_height; i++)
    {
        m_imageData[i] = image.m_imageData[i];
    }
}

bool Image::initialize(const std::string &path, const std::string &type)
{
    std::ifstream fin(path + "." + type, std::ios::binary | std::ios::in);
    if(!fin)
    {
        return false;
    }
    read(HEADER_SIZE, m_header, fin);
    m_bitDepth = *(reinterpret_cast<int *>(&m_header[28]));

    if(m_bitDepth <= BIT_DEPTH_SIZE)
    {
        read(COLOR_TABLE_SIZE, m_colorTable, fin);
    }

    m_width = *(reinterpret_cast<int *>(&m_header[18]));
    m_height = *(reinterpret_cast<int *>(&m_header[22]));

    if(m_imageData != nullptr)
    {
        delete [] m_imageData;
    }
    m_imageData = new unsigned char[m_width * m_height];
    read(m_width * m_height, m_imageData, fin);
    fin.close();

    return true;
}

bool Image::writeImage(const std::string &path, const std::string &type)
{
    std::ofstream fout(path + "." + type, std::ios::binary | std::ios::out);
    write(HEADER_SIZE, m_header, fout);

    if(m_bitDepth <= BIT_DEPTH_SIZE)
    {
        write(COLOR_TABLE_SIZE, m_colorTable, fout);
    }
    if(m_imageData != nullptr)
    {
        write(m_width * m_height, m_imageData, fout);
    }
    else
    {
        std::cerr << "Set Image Data";
        return false;
    }
    fout.close();
    return true;
}

void Image::increaseBrightness(unsigned char factor)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        int increasedPixel = m_imageData[i] + factor;
        m_imageData[i] = increasedPixel > MAX_BRIGHTNESS ? 255 : increasedPixel;
    }
}

void Image::decreaseBrightness(unsigned char factor)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        int decreasedPixel = m_imageData[i] - factor;
        m_imageData[i] = decreasedPixel < MIN_BRIGHTNESS ? 0 : decreasedPixel;
    }
}


void Image::read(unsigned int length, unsigned char *buffer, std::ifstream &fin)
{
    while(length--)
    {
        *(buffer++) = fin.get();
    }
}

void Image::write(unsigned int length, unsigned char *buffer, std::ofstream &fout)
{
    while(length--)
    {
        fout <<*(buffer++);
    }
}



