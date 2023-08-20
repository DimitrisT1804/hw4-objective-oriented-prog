#include "Image.hpp"
// #include "GSCPixel.hpp"
#include <string.h>
#include <iostream>

using namespace std;


class GSCImage : public Image 
{
    public:
        GSCPixel** currentImage;   // the array of current image
        int counter = 0;
        GSCImage() = default;

        GSCImage(const GSCImage& img);

        //GSCImage(const RGBImage& grayscaled);
        GSCImage(std::istream& stream);

        ~GSCImage();


        GSCImage& operator = (const GSCImage& img);

        virtual Image& operator += (int times) override;

        virtual Image& operator *= (double factor) override;

        virtual Image& operator ! () override;

        virtual Image& operator ~ () override;

        virtual Image& operator * () override;

        virtual Pixel& getPixel(int row, int col) const override;

        friend std::ostream& operator << (std::ostream& out, Image& image);
};