#include <iostream>
using namespace std;

class Pixel
{

};

class RGBPixel : public Pixel 
{
    public:
        RGBPixel() = default;
        RGBPixel(const RGBPixel& p);
        RGBPixel(unsigned char r, unsigned char g, unsigned char b);
        unsigned char getRed() const;
        unsigned char getGreen() const;
        unsigned char getBlue() const;
        void setRed(int r);
        void setGreen(int g);
        void setBlue(int b);
};


class GSCPixel : public Pixel
{
    public:
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);
        unsigned char getValue();
        void setValue(unsigned char value);   
};

class Image 
{
    protected:
        int width;
        int height;
        int max_luminocity;
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
};



