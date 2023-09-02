/* Header File for RGBPixel class*/

#ifndef RGBPIXEL_H  // File guards to avoid multiple definitions
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
};
#endif