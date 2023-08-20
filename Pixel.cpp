#include "Pixel.hpp"
// class Pixel
// {
//     public:
//         int pixel_value = 0;    // keep the value of pixel
// };

//Pixel: pixel_value = 0;
int Pixel::getPixel()
{
    return Pixel::pixel_value;
}

//
// class GSCPixel : public Pixel
// {   
//     ~GSCPixel()
//     {

//     }

//     void setValue(int value)
//     {
//         pixel_value = value;
//     }   
// };

void GSCPixel::setValue(int value)
{
    pixel_value = value;
}
