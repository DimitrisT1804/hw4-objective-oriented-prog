#include <iostream>
#include <fstream>

using namespace std;
// #include "Image.cpp"

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
        
        int colorComb = 0;      // i keep in each byte the colors
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
        Pixel **myImage;
        //Pixel **myImage = NULL;
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
    Image(int width, int height)
    {  
        this->width = width;
        this->height = height;

        myImage = new Pixel* [height];

        for(int i = 0; i < height; i++)
        {
            myImage[i] = new Pixel[width];
        }

        // na thimitho na diagrapso tin mnimi pou desmevoun
        
    }

    ~Image()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] myImage[i];
        }
        delete[] myImage;
    }
};

class GSCImage : public Image 
{
    public:
        GSCPixel** currentImage;   // the array of current image
        GSCImage() = default;

        GSCImage(const GSCImage& img) : Image(3,2)
        {
            height = img.height;
            width = img.width;

            currentImage = new GSCPixel* [height];

            for(int i = 0; i < height; i++)
            {
                currentImage[i] = new GSCPixel[width];
            }
        }
        //GSCImage(const RGBImage& grayscaled);
        GSCImage(std::istream& stream);
        ~GSCImage();


        GSCImage& operator = (const GSCImage& img);

        virtual Image& operator += (int ) override
        {
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {

                }
            }
        }
        virtual Image& operator *= (double factor) override;
        virtual Image& operator ! () override;
        virtual Image& operator ~ () override;
        virtual Image& operator * () override;

        virtual Pixel& getPixel(int row, int col) const override;
        friend std::ostream& operator << (std::ostream& out, Image& image) ;

        // implementations


        // Image& Image::operator+= (int times)
        // {
        //     for(int i = 0; i < times; i++)
        //     {
        //         for(int j = 0; j < )
        //     }
        // }

        // GSCImage(std::istream& stream)
        // {

        // }
};



Image* readNetpbmImage(const char* filename)
{
    ifstream f (filename);
    if(!f.is_open())
    {
        std::cout << "[ERROR] Unable to open " << filename << std::endl;
    }
    Image* img_ptr = nullptr;
    string type;

    if(f.good() && !f.eof())
        f >> type;
    if(!type.compare("P3"))
    {
        //img_ptr = new RGBImage(f);
    }
    else if(!type.compare("P2"))
    {
        img_ptr = new GSCImage(f);
    }
    else if(f.is_open())
    {
        std::cout << "[ERROR] Invalid file format" << std::endl;
    }
    return img_ptr;
}


int main()
{
    //Image kati(100, 50);
    char selection = ' ';

    while (selection != 'q')
    {

        std::cout << "i <filename> as <$token>" << endl;
        std::cout << "e <$token> as <filename>" << endl;
        std::cin >> selection;

        switch(selection)
        {
            case 'a':
            {
                readNetpbmImage("./autolab-photos/photo/2x3.pgm");
            }
        }

    }
    

    return 0;

}



