/* Source File for clip class*/

#include "clip.hpp"

/* Method that if a value is below 0 returns 0 and if 
it is higher than 255 returns 255 else returns the value */

int clip(double value)
{
    if(value < 0)
        return 0;
    else if(value > 255)
        return 255;
    else
        return value;
}