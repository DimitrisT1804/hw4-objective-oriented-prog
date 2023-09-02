/* Source File for Pixel class*/

#include "GSCPixel.hpp"


int GSCPixel::getValue()
{
    return Pixel::pixel_value;
}

void GSCPixel::setValue(int value)
{
    pixel_value = value;
}