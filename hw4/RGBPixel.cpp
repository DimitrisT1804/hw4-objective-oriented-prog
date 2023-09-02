/* Source File for Pixel class*/

#include "RGBPixel.hpp"

RGBPixel::RGBPixel(unsigned char r, unsigned char g, unsigned char b)
{
    setRed(r);
    setGreen(g);
    setBlue(b);
}

unsigned char RGBPixel::getRed() const
{
    return Pixel::red;
}
unsigned char RGBPixel::getGreen() const
{
    return Pixel::green;
}
unsigned char RGBPixel::getBlue() const
{
    return Pixel::blue;
}
void RGBPixel::setRed(int r)
{
    Pixel::red = static_cast<char> (r);     // transform from int to char
}
void RGBPixel::setGreen(int g)
{
    Pixel::green = (char) g;
}
void RGBPixel::setBlue(int b)
{
    Pixel::blue = (char) b;
}