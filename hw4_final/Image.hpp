#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "pixel.hpp"

using namespace std;

class Image 
{
    protected:
        int width;
        int height;
        int max_luminocity;
        Pixel **myImage = NULL;
    public:
        int getWidth() const;
        int getHeight() const;
        int getMaxLuminocity() const;
        void setWidth(int width);
        void setHeight(int height);
        void setMaxLuminocity(int lum);

       virtual Image& operator += (int times) = 0;
       virtual Image& operator *= (double factor) = 0;
       virtual Image& operator !() = 0;
       virtual Image& operator ~() = 0;
       virtual Image& operator *() = 0;  
       virtual Pixel& getPixel(int row, int col) const = 0;  
       friend std::ostream& operator << (std::ostream& out, Image& image);

    virtual ~Image();
};

#endif