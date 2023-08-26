#ifndef RGBPIXEL_H
#define RGBPIXEL_H

#include "pixel.hpp"

class RGBPixel : public Pixel 
{
    public:
        RGBPixel() = default;
        //RGBPixel(const RGBPixel& p);

        RGBPixel(unsigned char r, unsigned char g, unsigned char b);

        unsigned char getRed() const;

        unsigned char getGreen() const;

        unsigned char getBlue() const;

        void setRed(int r);

        void setGreen(int g);

        void setBlue(int b);

        //char red = ' ', green = ' ', blue = ' ';      // i keep in each byte the colors
};
#endif