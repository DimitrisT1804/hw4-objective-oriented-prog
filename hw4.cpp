#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <filesystem>

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
        ~GSCPixel()
        {

        }

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
    virtual ~Image()
    {

    }
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

        ~GSCImage()
        {
           // free(currentImage);
            for(int i = 0; i < width; i++)
            {
                delete[] currentImage[i];
            }
           delete[] currentImage;
        }


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
        // {~Token()

        // }
};

class Token
{
    private:
        string name;
        Image* ptr;
    public:
        Token(const string& token_name = "", Image* image_ptr = nullptr)
        {
            this->name = token_name;
            this->ptr = image_ptr;
        }
        ~Token()
        {

        }
        string getName() const
        {
            return name;
        }
        Image*  getPtr() const
        {
            return ptr;
        }
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

long unsigned int checkToken(string Token_name, vector <Token> array_token)
{
    long unsigned int i;
    for(i = 0; i < array_token.size(); i++)
    {
        if( strcmp(array_token[i].getName().c_str(), Token_name.c_str()) == 0)
            break;    // found
    }
    return i;   // not exist!
}


int main()
{
    //Image kati(100, 50);
    char selection = ' ';
    Image* currentImage;
    string out_file;
    //Token **array = NULL;
    //int array_size = 0;
    vector<Token> array_token;
    string token_name;
    string filename;
    string as;  // just to ignore a character
    long unsigned int array_pos = -1;


    //array = (Token **) malloc(sizeof(Token));
    //array_size++;

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
                cin >> filename;
                cin >> as;
                cin >> token_name;

                currentImage = readNetpbmImage(filename.c_str());
                printf("width is %d \nheight is %d \nmaxLuminocity is %d \n", currentImage->getWidth(), currentImage->getHeight(), currentImage->getMaxLuminocity());

                //array = (Token *) realloc(array, array_size*sizeof(Token));
                //Token* Image_token = new Token("kati", currentImage);

                /*New version for array*/
                if(array_token.size() != 0)
                {
                    if(checkToken(token_name, array_token) != array_token.size())
                    {
                        cout << "[ERROR] Token " << token_name << " exists!" << endl;
                        break;
                    }
                }
                //else
                //{
                    array_token.push_back(Token(token_name, currentImage));

                    cout << "[OK] Import " << token_name << endl;
                //}

                break;
            }

            case 'e' :  
            {
                cin >> token_name;
                cin >> as;
                cin >> out_file;

                for(array_pos = 0; array_pos < array_token.size(); array_pos++)
                {
                    if(strcmp(token_name.c_str(), array_token[array_pos].getName().c_str()) == 0)
                    {
                        break;
                    }
                }
                if(array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exist!" << endl;
                }
                else
                {
                    currentImage = array_token[array_pos].getPtr();


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
                    //std::cin >> out_file;
                    //getline(cin, out_file);
                    ifstream ifile(out_file.c_str());
                    
                    if(ifile.good())
                    {   
                        cout << "[ERROR] File exists!" << endl;
                        break;
                    }
                    else
                    {
                        ofstream myfile(out_file);
                        if(!myfile.is_open())
                        {
                            //cout << "Unable to open file " << out_file;
                            cout << "[ERROR] Unable to create file" << endl;
                        }
                        else
                        {
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
                            cout << "[OK] Export " << token_name << endl;

                        }

                    }

                }

                break;

            }

            case 'd':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }

                delete array_token[array_pos].getPtr();
                array_token.erase(array_token.begin()+array_pos);

                cout << "[OK] " << "Delete " << token_name << endl;
                break;
            }

            default:
            {
                break;
            }
        }

    }
    delete array_token[0].getPtr();
    array_token.erase(array_token.begin());


    return 0;

}



