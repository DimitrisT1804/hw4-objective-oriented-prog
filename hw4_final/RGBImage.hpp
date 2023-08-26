#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "Image.hpp"
#include "RGBPixel.hpp"
#include <algorithm>
#include <cmath>

class RGBImage : public Image 
{
    public:
        RGBPixel **currentImage;

        RGBImage();
        
        RGBImage(const RGBImage& img);

        RGBImage(std::istream& stream);

        virtual ~RGBImage();

        RGBImage& operator = (const RGBImage& img);


        virtual Image& operator += (int times) override;


        virtual Image& operator *= (double factor) override;

        virtual Image& operator !() override;

        virtual Image& operator ~() override;

        virtual Image& operator *() override;


        virtual Pixel& getPixel(int row, int col) const override;
 
};

#endif