#include <iostream>
#include <fstream>

using namespace std;
// #include "Image.cpp"

class Pixel
{
    public:
        int pixel_value = 0;    // keep the value of pixel
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

        void setValue(int value)
        {
            pixel_value = value;
        }   
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
};

class GSCImage : public Image 
{
    public:
        GSCPixel** currentImage;   // the array of current image
        int counter = 0;
        GSCImage() = default;

        GSCImage(const GSCImage& img)
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
        GSCImage(std::istream& stream)
        {
            string word;
            int value = 0;
            int i = 0, j = 0;

            while(!stream.eof())
            {
                stream >> word;
                counter++;
                if(counter == 1)    // get width
                {
                    width = stoi(word);
                    currentImage = new GSCPixel* [width];
                }
                else if(counter == 2)   // get height
                {
                    height = stoi(word);
                    for(int i = 0; i < width; i++)
                    {
                        currentImage[i] = new GSCPixel[height];
                    }
                }
                else if(counter == 3)   // get max_luminocity
                {
                    max_luminocity = stoi(word);
                }
                else    // it is the value of current pixel
                {
                    /* a way to add the value in each pixel, it works!*/
                    value = stoi(word);
                    currentImage[i][j].setValue(value);
                    if(j >= height-1)
                    {
                        i++;
                        j = 0;
                        if(i == width)
                        {
                            i = 0;
                        }
                    }
                    else
                    {
                        j++;
                    }
                }
                //cout << word << endl;
            }
            counter = 0;
        }

        ~GSCImage();


        GSCImage& operator = (const GSCImage& img);

        virtual Image& operator += (int times) override
        {
            // currentImage
            // for(int i = 0; i < height; i++)
            // {
            //     for(int j = 0; j < width; j++)
            //     {
            //         currentImage[i][j] = currentImage[j][i];
            //     }
            // }
        }
        virtual Image& operator *= (double factor) override
        {

        }
        virtual Image& operator ! () override
        {

        }
        virtual Image& operator ~ () override
        {

        }
        virtual Image& operator * () override
        {

        }

        virtual Pixel& getPixel(int row, int col) const override
        {
            return currentImage[row][col];
        }
        friend std::ostream& operator << (std::ostream& out, Image& image)
        {

        }

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

class Token
{
    private:
        string name;
        Image* ptr;
    public:
        Token(const string = "", Image* = nullptr);
        ~Token();
        string getName() const;
        Image*  getPtr() const;
        void setName(const string& );
        void setPtr(Image* ptr);
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
    Image* currentImage;
    string out_file;
    Token **array = NULL;
    int array_size = 0;

    array = (Token **) malloc(sizeof(Token));
    array_size++;

    while (selection != 'q')
    {

        std::cout << "i <filename> as <$token>" << endl;
        std::cout << "e <$token> as <filename>" << endl;
        std::cin >> selection;
        // std::cin.ignore();

        switch(selection)
        {
            case 'a':
            {
                currentImage = readNetpbmImage("./autolab-photos/photo/ein.pgm");
                printf("width is %d \nheight is %d \nmaxLuminocity is %d \n", currentImage->getWidth(), currentImage->getHeight(), currentImage->getMaxLuminocity());
                
                array = (Token *) realloc(array, array_size*sizeof(Token));
                Token* Image_token = new Token("kati", currentImage);


                break;
            }

            case 'b' :  
            {
                if(currentImage == NULL)
                {
                    cin >> out_file;
                    break;
                }
                for(int i = 0; i < currentImage->getWidth(); i++)
                {
                    for (int j = 0; j < currentImage->getHeight(); j++)
                    {
                        printf("Pixel is: %d\n", currentImage->getPixel(i, j).pixel_value);
                    }
                }

                // Generate the output file with pgm format
                //std::cin.ignore(256, '\n');
                std::cin >> out_file;
                //getline(cin, out_file);
                ofstream myfile(out_file);
                if(!myfile.is_open())
                {
                    cout << "Unable to open file " << out_file;
                    return -1; 
                }

                myfile << "P2" << endl;
                myfile << to_string(currentImage->getWidth()) << " ";
                myfile << to_string(currentImage->getHeight()) << " ";
                myfile << to_string(currentImage->getMaxLuminocity()) << endl;

                for(int i = 0; i < currentImage->getWidth(); i++)
                {
                    for (int j = 0; j < currentImage->getHeight(); j++)
                    {
                        myfile << to_string(currentImage->getPixel(i, j).pixel_value) << endl;
                    }
                }

                break;

            }

            default:
            {
                break;
            }
        }

    }
    

    return 0;

}



