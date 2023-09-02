/* Header File for GSCImage class*/

#ifndef PIXEL_H
#define PIXEL_H

#include "Image.hpp"
#include "GSCPixel.hpp"
#include "RGBImage.hpp"

#include <string.h>
#include <iostream>
#include <algorithm>
#include <cmath>



using namespace std;


class GSCImage : public Image 
{
    public:
        GSCPixel** currentImage;   // the array of current image
                                   // double pointer to GSCPixel to represent a 2D array of GSCPixels
        int counter = 0;
        GSCImage() = default;

        GSCImage(int width, int height);

        GSCImage(const GSCImage& img);

        GSCImage(const RGBImage& grayscaled);

        GSCImage(std::istream& stream);     // constructor from file

        virtual ~GSCImage();


        GSCImage& operator = (const GSCImage& img);

        virtual Image& operator += (int times) override;

        virtual Image& operator *= (double factor) override;

        virtual Image& operator ! () override;

        virtual Image& operator ~ () override;

        virtual Image& operator * () override;

        virtual Pixel& getPixel(int row, int col) const override;

        friend std::ostream& operator << (std::ostream& out, Image& image);
};

#endif 