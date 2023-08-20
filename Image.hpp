#include <iostream>
#include <fstream>
#include <string.h>
#include "Pixel.hpp"

using namespace std;

class Image 
{
    protected:
        int width;
        int height;
        int max_luminocity;
        Pixel **myImage = NULL;
    public:
        int getWidth() const { return width; }
        int getHeight() const { return height; }
        int getMaxLuminocity() const { return max_luminocity;  }
        void setWidth(int width) { this->width = width; }
        void setHeight(int height) { this->height = height; }
        void setMaxLuminocity(int lum) { this->max_luminocity = lum; }

       virtual Image& operator += (int times) = 0;
       virtual Image& operator *= (double factor) = 0;
       virtual Image& operator !() = 0;
       virtual Image& operator ~() = 0;
       virtual Image& operator *() = 0;  
       virtual Pixel& getPixel(int row, int col) const = 0;  
       friend std::ostream& operator << (std::ostream& out, Image& image);


    // constuctor
    // Image(int width, int height)
    // {  
    //     this->width = width;
    //     this->height = height;

    //     myImage = new Pixel* [height];

    //     for(int i = 0; i < height; i++)
    //     {
    //         myImage[i] = new Pixel[width];
    //     }

    //     // na thimitho na diagrapso tin mnimi pou desmevoun
    // }

    // virtual ~Image()
    // {
    //     for (int i = 0; i < height; i++)
    //     {
    //         delete[] myImage[i];
    //     }
    //     delete[] myImage;
    // }
    virtual ~Image();
};

class Token
{
    private:
        string name;
        Image* ptr;
    public:
        Token(const string& = "", Image* = nullptr);

        ~Token();

        string getName() const;

        Image*  getPtr() const;

        void setName(const string& );
        void setPtr(Image* ptr);
};