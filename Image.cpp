#include "Image.h"
#include <algorithm>

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
    m_color = image.m_color;
    for(int i = 0; i < HEADER_SIZE; i++)
    {
        m_header[i] = image.m_header[i];
    }
    m_bitDepth = image.m_bitDepth;

    for(int i = 0; i < COLOR_TABLE_SIZE; i++)
    {
        m_colorTable[i] = image.m_colorTable[i];
    }
    m_imageData = new unsigned char*[m_width * m_height];
    for(int i = 0; i < m_width * m_height; i++)
    {
        m_imageData[i] = new unsigned char[m_color];
    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        for(int j = 0; j < m_color; j++)
        {
            m_imageData[i][j] = image.m_imageData[i][j];
        }
    }
}

bool Image::initialize(const std::string &path, const Color &color)
{
    m_color = color;
    std::ifstream fin(path , std::ios::binary | std::ios::in);
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
    m_imageData = new unsigned char *[m_width * m_height];
    for(int i = 0; i < m_width * m_height; i++)
    {
        m_imageData[i] = new unsigned char[m_color];
    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        for(int j = m_color - 1; j >= 0; j--)
        {
            m_imageData[i][j] = fin.get();
        }
    }
    fin.close();

    return true;
}

bool Image::writeImage(const std::string &path)
{
    std::ofstream fout(path , std::ios::binary | std::ios::out);
    write(HEADER_SIZE, m_header, fout);

    if(m_bitDepth <= BIT_DEPTH_SIZE)
    {
        write(COLOR_TABLE_SIZE, m_colorTable, fout);
    }
    if(m_imageData != nullptr)
    {
        for(int i = 0; i < m_width * m_height; i++)
        {
            for(int j = m_color - 1; j >= 0; j--)
            {
                fout << m_imageData[i][j];
            }
        }
    }
    else
    {
        std::cerr << "Set Image Data";
        return false;
    }
    fout.close();
    return true;
}

void Image::rotate(const Image::Direction &direction)
{
    unsigned char **rotatedImageData = new unsigned char*[m_width * m_height];
    for(int i = 0; i < m_width * m_height; i++)
    {
        rotatedImageData[i] = new unsigned char[m_color];
    }

    for(int i = 0; i < m_height; i++)
    {
        for(int j = 0; j < m_width; j++)
        {
            for(int k = 0; k < m_color; k++)
            {
                switch (direction)
                {
                case Direction::LEFT:
                {
                    rotatedImageData[j * m_width + (m_height - i - 1)][k] = m_imageData[i * m_width + j][k];
                    break;
                }

                case Direction::RIGHT:
                {
                    rotatedImageData[(m_width - j - 1) * m_width + i][k] = m_imageData[i * m_width + j][k];
                    break;
                }
                case Direction::UPSIDEDOWN:
                {
                    rotatedImageData[(m_height - i - 1) * m_width + (m_width - j - 1)][k] = m_imageData[i * m_width + j][k];
                    break;
                }

                case Direction::MIRROR:
                {
                    rotatedImageData[i * m_width + (m_width - j - 1)][k] = m_imageData[i * m_width + j][k];
                    break;
                }
                }
            }
        }
    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        for(int k = 0; k < m_color; k++)
        {
            m_imageData[i][k] = rotatedImageData[i][k];
        }

    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        delete [] rotatedImageData[i];
    }
    delete [] rotatedImageData;
}

void Image::increaseBrightness(const unsigned char &factor)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        for(int j = 0; j < m_color; j++)
        {
            int increasedPixel = m_imageData[i][j] + factor;
            m_imageData[i][j] = increasedPixel > MAX_BRIGHTNESS ? 255 : increasedPixel;
        }

    }
}

void Image::decreaseBrightness(const unsigned char &factor)
{
    for (int i = 0; i < m_width * m_height; i++)
    {
        for(int j = 0; j < m_color; j++)
        {
            int decreasedPixel = m_imageData[i][j] - factor;
            m_imageData[i][j] = decreasedPixel < MIN_BRIGHTNESS ? 0 : decreasedPixel;
        }
    }
}

void Image::applyContrast()
{
    float *eqHistogram = new float[NO_OF_GREYSCALES], sum = 0;
    for(int i = 0; i < NO_OF_GREYSCALES; i++)
    {
        eqHistogram[i] = 0;
    }

    float *histogram = computeHistogram();
    for(int i = 0; i < NO_OF_GREYSCALES; i++)
    {
        sum = 0;
        for(int j = 0; j <= i; j++)
        {
            sum += histogram[j];
        }
        eqHistogram[i] = 255 * sum + 0.5;
    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        for(int j = 0; j < m_color; j++)
        {
            m_imageData[i][j] = (int)eqHistogram[m_imageData[i][j]];
        }

    }
    delete [] histogram;
    delete [] eqHistogram;
    computeHistogram();
}

void Image::applyNegetive()
{
    for(int i = 0; i < m_height * m_width; i++)
    {
        for(int j = 0; j < m_color; j++)
        {
            m_imageData[i][j] = MAX_BRIGHTNESS - m_imageData[i][j];
        }
    }
}

void Image::applyBlur()
{
    float kernalFilter[3][3] = {{1.0/9.0, 1.0/9.0, 1.0/9.0},
                                {1.0/9.0, 1.0/9.0, 1.0/9.0},
                                {1.0/9.0, 1.0/9.0, 1.0/9.0}};

    for(int i = 1; i < m_height - 1; i++)
    {
        for(int j = 1 ; j < m_width - 1; j++)
        {
            float *sum = new float[m_color];

            //Make 0, possible to optimize
            for(int k = 0; k < m_color; k++)
            {
                sum[k] = 0;
            }

            for(int x = -1 ; x <= 1; x++)
            {
                for(int y = -1; y <= 1; y++)
                {
                    for(int k = 0; k < m_color; k++)
                    {
                        sum[k] += kernalFilter[x + 1][y + 1] * m_imageData[(i + x) * m_width + (j + y)][k];
                    }
                }
            }
            for(int k = 0; k < m_color; k++)
            {
                m_imageData[i * m_width + j][k] = sum[k];
            }
            delete [] sum;
        }
    }
}

//Values for other filters can also be searched on internet
void Image::applySepia()
{
    if(m_color != Color::RGB)
    {
        std::cerr << "Can't Apply Sepia to Black and White Image";
        return;
    }
    for(int i = 0; i < m_width * m_height; i++)
    {
        int r = 0, b = 0, g = 0;
        r = (m_imageData[i][0] * 0.393) + (m_imageData[i][1] * 0.769) + (m_imageData[i][2] * 0.189);
        g = (m_imageData[i][0] * 0.349) + (m_imageData[i][1] * 0.686) + (m_imageData[i][2] * 0.168);
        b = (m_imageData[i][0] * 0.272) + (m_imageData[i][1] * 0.534) + (m_imageData[i][2] * 0.131);

        if(r > MAX_BRIGHTNESS){r = MAX_BRIGHTNESS;}
        if(g > MAX_BRIGHTNESS){g = MAX_BRIGHTNESS;}
        if(b > MAX_BRIGHTNESS){b = MAX_BRIGHTNESS;}

        m_imageData[i][0] = r;
        m_imageData[i][1] = g;
        m_imageData[i][2] = b;
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

float* Image::computeHistogram()
{
    float *histogram = new float[NO_OF_GREYSCALES], sum = 0;
    for(int i = 0; i < NO_OF_GREYSCALES; i++)
    {
        histogram[i] = 0;
    }
    for(int i = 0; i < m_height * m_width; i++)
    {
        //Possible Error
        for(int j = 0; j < m_color; j++)
        {
            histogram[m_imageData[i][j]]++;
        }
        sum++;
    }
    for(int i = 0; i < NO_OF_GREYSCALES; i++)
    {
        histogram[i] /= (float)sum;
    }
    return histogram;
}




