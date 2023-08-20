#include "Pixel.hpp"

class GSCPixel : public Pixel
{
    public:
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);
        ~GSCPixel();

        unsigned char getValue();
        void setValue(unsigned char value);

        void setValue(int value);
};