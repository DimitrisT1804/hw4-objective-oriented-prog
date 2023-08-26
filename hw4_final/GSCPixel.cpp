#include "GSCPixel.hpp"


int GSCPixel::getValue()        //kanonika itan unsigned char
{
    return Pixel::pixel_value;
}

void GSCPixel::setValue(int value)
{
    pixel_value = value;
}