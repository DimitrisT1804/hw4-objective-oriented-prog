#include "pixel.hpp"

class GSCPixel : public Pixel
{
    public:
        GSCPixel() = default;
        //GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);

        int getValue();
        void setValue(unsigned char value);

        void setValue(int value);
};