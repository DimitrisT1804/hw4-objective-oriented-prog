// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string.h>

// #include <math.h>
// #include <algorithm>

#include "hw4.hpp"

using namespace std;

class Pixel
{
    public:
        int pixel_value = -1;    // keep the value of pixel
        unsigned char red = ' ';
        unsigned char green = ' ';
        unsigned char blue = ' ';    
        int Y = -1, U = -1, V = -1;
};

class RGBPixel : public Pixel 
{
    public:
        RGBPixel() = default;
        RGBPixel(const RGBPixel& p)
        {

        }
        RGBPixel(unsigned char r, unsigned char g, unsigned char b)
        {
            setRed(r);
            setGreen(g);
            setBlue(b);
        }
        ~RGBPixel()
        {

        }
        unsigned char getRed() const
        {
            return Pixel::red;
        }
        unsigned char getGreen() const
        {
            return Pixel::green;
        }
        unsigned char getBlue() const
        {
            return Pixel::blue;
        }
        void setRed(int r)
        {
            Pixel::red = static_cast<char> (r);
        }
        void setGreen(int g)
        {
            Pixel::green = (char) g;
        }
        void setBlue(int b)
        {
            Pixel::blue = (char) b;
        }
        
        //char red = ' ', green = ' ', blue = ' ';      // i keep in each byte the colors
};


class GSCPixel : public Pixel
{
    public:
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p) : Pixel(p)
        {

        }
        GSCPixel(unsigned char value);
        ~GSCPixel()
        {

        }

        int getValue()        //kanonika itan unsigned char
        {
            return Pixel::pixel_value;
        }
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

int clip(double value)
{
    if(value < 0)
        return 0;
    else if(value > 255)
        return 255;
    else
        return value;
}

class RGBImage : public Image 
{
    public:
        RGBPixel **currentImage;

        RGBImage()
        {
            height = 0;
            width = 0;
        }
        
        RGBImage(const RGBImage& img)
        {
            height = img.height;
            width = img.width;
            max_luminocity = img.max_luminocity;

            for(int i = 0; i < height; i++)
            {
                currentImage[i] = new RGBPixel[width];
                for (int j = 0; j < width; j++)
                {
                    currentImage[i][j] = img.currentImage[i][j]; // Copy pixel values
                }
            } 

            currentImage = img.currentImage;

        }

        RGBImage(std::istream& stream)
        {
            string word;
            int i = 0, j = 0;
            int counter = 0;
            int pixel_counter = 0;
            int red = 0, green = 0, blue = 0;

            //Image& thisImage = currentImage;

            while(!stream.eof())
            {
                stream >> word;
                counter++;
                if(counter == 1)    // get width
                {
                    width = stoi(word);
                }
                else if(counter == 2)   // get height
                {
                    height = stoi(word);
                    currentImage = new RGBPixel* [height];
                    for(int i = 0; i < height; i++)
                    {
                        currentImage[i] = new RGBPixel[width];
                    }
                }
                else if(counter == 3)   // get max_luminocity
                {
                    max_luminocity = stoi(word);
                }
                else    // it is the value of current pixel
                {
                    /* a way to add the value in each pixel, it works!*/

                    if(pixel_counter == 0)
                    {
                        red = stoi(word);
                        
                    }
                    else if(pixel_counter == 1)
                    {
                        green = stoi(word);
                        
                    }
                    else if(pixel_counter == 2)
                    {
                        blue = stoi(word);

                        currentImage[i][j].setRed(red);
                        currentImage[i][j].setGreen(green);
                        currentImage[i][j].setBlue(blue);
                        //pixel_counter = 0;

                        if(j == width - 1)
                        {
                            i++;
                            j = 0;
                            if(i == height)
                            {
                                i = 0;
                                break;
                            }
                        }
                        else
                        {
                            j++;
                        }
                    }

                    //value = stoi(word);
                    if(pixel_counter == 2)
                        pixel_counter = 0;
                    else
                        pixel_counter++;

                }
                //cout << word << endl;
            }
            counter = 0;           
        }

        ~RGBImage()
        {
            for(int i = 0; i < height; i++)
            {
                delete[] currentImage[i];
            }
           delete[] currentImage;
        }


        RGBImage& operator = (const RGBImage& img)
        {
            return *this;
        }
        virtual Image& operator += (int times) override
        {
            for(int k = 0; k < times; k++)
            {
                int old_width = width;
                int old_height = height;

                width = height;
                height = old_width;

                RGBPixel **newImage = new RGBPixel*[height];
                for(int i = 0; i < height; i++)
                {
                    newImage[i] = new RGBPixel[width];
                }

                for (int i = 0; i < old_height; i++)
                {
                    for(int j = 0; j < old_width; j++)
                    {
                        newImage[j][width-i-1].setRed(currentImage[i][j].getRed()); 
                        newImage[j][width-i-1].setGreen(currentImage[i][j].getGreen()); 
                        newImage[j][width-i-1].setBlue(currentImage[i][j].getBlue()); 
                    }
                }


                for(int i = 0; i < old_height; i++)      // delete the old image
                {
                    delete[] currentImage[i];
                }
                delete[] currentImage;

                currentImage = newImage;

                // for(int i = 0; i < width; i++)
                // {
                //     for (int j = 0; j < height; j++)
                //     {
                //         cout << to_string(currentImage[i][j].getValue()) << endl;
                //     }
                // }            

            }
            return *this;
        } 

        virtual Image& operator *= (double factor) override
        {
            int old_width = width;
            int old_height = height;
            
            width = width * factor;
            height = height * factor;

            RGBPixel** newImage = new RGBPixel*[height];
            for (int i = 0; i < height; i++) 
            {
                newImage[i] = new RGBPixel[width];
            }


            int r1, r2;
            int c1, c2;
            int avg = 0;
            int add;

            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    //red
                    r1 = min((int) floor(i/factor), old_height - 1 );
                    r2 = min((int) ceil(i/factor), old_height - 1);
                    c1 = min((int) floor(j/factor), old_width - 1);
                    c2 = min((int) ceil(j/factor), old_width - 1);

                    add = currentImage[r1][c1].getRed() + currentImage[r1][c2].getRed() + currentImage[r2][c1].getRed() + currentImage[r2][c2].getRed();

                    avg = add / 4;
                    newImage[i][j].setRed(avg);

                    //green
                    r1 = min((int) floor(i/factor), old_height - 1 );
                    r2 = min((int) ceil(i/factor), old_height - 1);
                    c1 = min((int) floor(j/factor), old_width - 1);
                    c2 = min((int) ceil(j/factor), old_width - 1);

                    add = currentImage[r1][c1].getGreen() + currentImage[r1][c2].getGreen() + currentImage[r2][c1].getGreen() + currentImage[r2][c2].getGreen();

                    avg = add / 4;
                    newImage[i][j].setGreen(avg);

                    //blue
                    r1 = min((int) floor(i/factor), old_height - 1 );
                    r2 = min((int) ceil(i/factor), old_height - 1);
                    c1 = min((int) floor(j/factor), old_width - 1);
                    c2 = min((int) ceil(j/factor), old_width - 1);

                    add = currentImage[r1][c1].getBlue() + currentImage[r1][c2].getBlue() + currentImage[r2][c1].getBlue() + currentImage[r2][c2].getBlue();

                    avg = add / 4;
                    newImage[i][j].setBlue(avg);
                }

            }

            for(int i = 0; i < old_height; i++)      // delete the old image
            {
                delete[] currentImage[i];
            }
            delete[] currentImage;

            currentImage = newImage;


            return *this;
        }

        virtual Image& operator !() override
        {
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    currentImage[i][j].setRed(max_luminocity - currentImage[i][j].getRed());
                    currentImage[i][j].setGreen(max_luminocity - currentImage[i][j].getGreen());
                    currentImage[i][j].setBlue(max_luminocity - currentImage[i][j].getBlue());
                    

                }
            }

            return *this;
        } 
        virtual Image& operator ~() override
        {
            int red_value, green_value, blue_value;

            int histogram_array[max_luminocity+1] = {0};
            int pixels_size = height*width;
            double possibility_array[max_luminocity+1] = {0.0}, final_possibility_array[max_luminocity + 1] = {0};
            double possibility = 0;
            int final_array[max_luminocity+1] = {0};
            int C, D, E;


            RGBPixel** newImage = new RGBPixel*[height];
            for (int i = 0; i < height; i++) 
            {
                newImage[i] = new RGBPixel[width];
            }

            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {

                    red_value = currentImage[i][j].getRed();
                    green_value = currentImage[i][j].getGreen();
                    blue_value = currentImage[i][j].getBlue();

                    currentImage[i][j].Y = ((66*red_value + 129*green_value + 25*blue_value + 128) >> 8) + 16;
                    currentImage[i][j].U = ((-38*red_value - 74*green_value + 112*blue_value + 128) >> 8) + 128;
                    currentImage[i][j].V = ((112*red_value - 94*green_value - 18*blue_value + 128) >> 8) + 128;
                    
                    histogram_array[currentImage[i][j].Y]++;

                }
            }   

            for(int i = 0; i <= max_luminocity; i++)
            {
                cout << "The array pos " << i << " is " << histogram_array[i] << endl;
                possibility_array[i] = (double)(histogram_array[i])/ (double)pixels_size;
                cout << "The possibility array pos " << i << " is " << possibility_array[i] << endl;
            }         

            for(int i = 0; i <= max_luminocity; i++)
            {
                for(int j = 0; j <= i; j++)
                {
                    possibility = possibility + possibility_array[j]; 

                }
                final_possibility_array[i] = possibility;
                possibility = 0;
            }       

            for(int i = 0; i <= max_luminocity; i++)
            {
                cout << "The final possibility array pos " << i << " is " << final_possibility_array[i] << endl;
            }    

            for(int i = 0; i <= max_luminocity; i++)
            {
                final_array[i] = (int) (235.0*final_possibility_array[i]);
                cout << "The array pos " << i << " is " << final_array[i] << endl;
            }

            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    newImage[i][j].U = currentImage[i][j].U;
                    newImage[i][j].Y = currentImage[i][j].Y;
                    newImage[i][j].V = currentImage[i][j].V;
                }
            }

            for(int k = 0; k <= max_luminocity; k++)
            {
                for(int i = 0; i < height; i++)
                {
                    for(int j = 0; j < width; j++)
                    {
                        if(currentImage[i][j].Y == k)
                            newImage[i][j].Y = final_array[k];
                    }
                }   
            }

            for(int i = 0; i < height; i++)      // delete the old image
            {
                delete[] currentImage[i];
            }
            delete[] currentImage;
            currentImage = newImage;

           
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    C = currentImage[i][j].Y - 16;
                    D = currentImage[i][j].U - 128;
                    E = currentImage[i][j].V - 128;

                    currentImage[i][j].setRed(clip((298*C + 409*E +128) >> 8) );
                    currentImage[i][j].setGreen(clip((298*C -100*D - 208*E +128) >> 8) );
                    currentImage[i][j].setBlue(clip((298*C + 516*D + 128) >> 8) );
                }
            }  

            return *this;
        }
        virtual Image& operator *() override
        {
            for(int i = 0; i < height; i++)
            {
                for (int j = 0; j < width/2; j++)
                {
                    std::swap(currentImage[i][j], currentImage[i][width-j-1]);
                }
            }

            return *this;
        }

        virtual Pixel& getPixel(int row, int col) const override
        {
            return currentImage[row][col];
        }

        // friend std::ostream& operator << (std::ostream& out, Image& image)
        // {
        //     out << "P3" << endl;
        //     out << to_string(image.getWidth()) << " ";
        //     out << to_string(image.getHeight()) << " ";
        //     out << to_string(image.getMaxLuminocity()) << endl;


        //     for(int i = 0; i < image.getHeight(); i++)
        //     {
        //         for (int j = 0; j < image.getWidth(); j++)
        //         {
        //             //out << to_string(image.myImage[i][j].pixel_value) << endl;
        //             out << to_string(image.getPixel(i, j).red) << " ";
        //             out << to_string(image.getPixel(i, j).green) << " ";
        //             out << to_string(image.getPixel(i, j).blue) << endl;
        //         }
        //     }

        //     return out;            
        // }
};



class GSCImage : public Image 
{
    public:
        GSCPixel** currentImage;   // the array of current image
        int counter = 0;
        GSCImage() = default;

        GSCImage(int width, int height)
        {

            this->width = width;
            this->height = height;

            currentImage = new GSCPixel* [height];

            for(int i = 0; i < height; i++)
            {
                currentImage[i] = new GSCPixel[width];
            }   
        }

        GSCImage(const GSCImage& img)
        {
            this->height = img.height;
            this->width = img.width;
            this->max_luminocity = img.max_luminocity;

            currentImage = new GSCPixel* [height];

            for(int i = 0; i < height; i++)
            {
                currentImage[i] = new GSCPixel[width];
            }
        }

        GSCImage(const RGBImage& grayscaled)
        {
            this->height = grayscaled.getHeight();
            this->width = grayscaled.getWidth();
            this->max_luminocity = grayscaled.getMaxLuminocity();

            currentImage = new GSCPixel* [height];

            for(int i = 0; i < height; i++)
            {
                currentImage[i] = new GSCPixel[width];
            }

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    currentImage[i][j].pixel_value = (int) (grayscaled.getPixel(i,j).red * 0.3) +  (grayscaled.getPixel(i,j).green * 0.59) + (grayscaled.getPixel(i,j).blue * 0.11);
                }
            }
        }

        //GSCImage(const RGBImage& grayscaled);
        GSCImage(std::istream& stream)
        {
            string word;
            int value = 0;
            int i = 0, j = 0;

            //Image& thisImage = currentImage;

            while(!stream.eof())
            {
                stream >> word;
                counter++;
                if(counter == 1)    // get width
                {
                    width = stoi(word);
                }
                else if(counter == 2)   // get height
                {
                    height = stoi(word);
                    currentImage = new GSCPixel* [height];
                    for(int i = 0; i < height; i++)
                    {
                        currentImage[i] = new GSCPixel[width];
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
                    if(j == width - 1)
                    {
                        i++;
                        j = 0;
                        if(i == height)
                        {
                            i = 0;
                            break;
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
            for(int i = 0; i < height; i++)
            {
                delete[] currentImage[i];
            }
           delete[] currentImage;
        }


        GSCImage& operator = (const GSCImage& img);

        virtual Image& operator += (int times) override
        {
            for(int k = 0; k < times; k++)
            {
                int old_width = width;
                int old_height = height;

                width = height;
                height = old_width;

                GSCPixel **newImage = new GSCPixel*[height];
                for(int i = 0; i < height; i++)
                {
                    newImage[i] = new GSCPixel[width];
                }

                for (int i = 0; i < old_height; i++)
                {
                    for(int j = 0; j < old_width; j++)
                    {
                        newImage[j][width-i-1].setValue(currentImage[i][j].getValue()); 
                    }
                }


                for(int i = 0; i < old_height; i++)      // delete the old image
                {
                    delete[] currentImage[i];
                }
                delete[] currentImage;

                currentImage = newImage;

                // for(int i = 0; i < width; i++)
                // {
                //     for (int j = 0; j < height; j++)
                //     {
                //         cout << to_string(currentImage[i][j].getValue()) << endl;
                //     }
                // }            

            }
            return *this;
            // 1 2 3 4  ->  9 5 1
            // 5 6 7 8  ->  1 6 2
            // 9 1 0 3  ->  0 7 3
            //              3 8 4
        }
        virtual Image& operator *= (double factor) override
        {
            //GSCImage *newImage = new GSCImage(width*factor, height*factor);
            int old_width = width;
            int old_height = height;
            
            width = width * factor;
            height = height * factor;

            GSCPixel** newImage = new GSCPixel*[height];
            for (int i = 0; i < height; i++) 
            {
                newImage[i] = new GSCPixel[width];
            }


            int r1, r2;
            int c1, c2;
            int avg = 0;
            int add;


            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    r1 = min((int) floor(i/factor), old_height - 1 );
                    r2 = min((int) ceil(i/factor), old_height - 1);
                    c1 = min((int) floor(j/factor), old_width - 1);
                    c2 = min((int) ceil(j/factor), old_width - 1);

                    add = currentImage[r1][c1].getValue() + currentImage[r1][c2].getValue() + currentImage[r2][c1].getValue() + currentImage[r2][c2].getValue();

                    avg = add / 4;
                    newImage[i][j].setValue(avg);
                }

            }

            for(int i = 0; i < old_height; i++)      // delete the old image
            {
                delete[] currentImage[i];
            }
            delete[] currentImage;

            currentImage = newImage;


            return *this;

        }
        virtual Image& operator ! () override
        {
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    currentImage[i][j].setValue(max_luminocity - currentImage[i][j].getValue());
                }
            }

            return *this;

        }
        virtual Image& operator ~ () override
        {
int red_value, green_value, blue_value;

            int histogram_array[max_luminocity+1] = {0};
            int pixels_size = height*width;
            double possibility_array[max_luminocity+1] = {0.0}, final_possibility_array[max_luminocity + 1] = {0};
            double possibility = 0;
            int final_array[max_luminocity+1] = {0};
            int C, D, E;


            GSCPixel** newImage = new GSCPixel*[height];
            for (int i = 0; i < height; i++) 
            {
                newImage[i] = new GSCPixel[width];
            }

            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {

                    red_value = currentImage[i][j].pixel_value;
                    green_value = currentImage[i][j].pixel_value;
                    blue_value = currentImage[i][j].pixel_value;

                    currentImage[i][j].Y = ((66*red_value + 129*green_value + 25*blue_value + 128) >> 8) + 16;
                    currentImage[i][j].U = ((-38*red_value - 74*green_value + 112*blue_value + 128) >> 8) + 128;
                    currentImage[i][j].V = ((112*red_value - 94*green_value - 18*blue_value + 128) >> 8) + 128;
                    
                    histogram_array[currentImage[i][j].Y]++;

                }
            }   

            for(int i = 0; i <= max_luminocity; i++)
            {
                cout << "The array pos " << i << " is " << histogram_array[i] << endl;
                possibility_array[i] = (double)(histogram_array[i])/ (double)pixels_size;
                cout << "The possibility array pos " << i << " is " << possibility_array[i] << endl;
            }         

            for(int i = 0; i <= max_luminocity; i++)
            {
                for(int j = 0; j <= i; j++)
                {
                    possibility = possibility + possibility_array[j]; 

                }
                final_possibility_array[i] = possibility;
                possibility = 0;
            }       

            for(int i = 0; i <= max_luminocity; i++)
            {
                cout << "The final possibility array pos " << i << " is " << final_possibility_array[i] << endl;
            }    

            for(int i = 0; i <= max_luminocity; i++)
            {
                final_array[i] = (int) (235.0*final_possibility_array[i]);
                cout << "The array pos " << i << " is " << final_array[i] << endl;
            }

            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    newImage[i][j].U = currentImage[i][j].U;
                    newImage[i][j].Y = currentImage[i][j].Y;
                    newImage[i][j].V = currentImage[i][j].V;
                }
            }

            for(int k = 0; k <= max_luminocity; k++)
            {
                for(int i = 0; i < height; i++)
                {
                    for(int j = 0; j < width; j++)
                    {
                        if(currentImage[i][j].Y == k)
                            newImage[i][j].Y = final_array[k];
                    }
                }   
            }

            for(int i = 0; i < height; i++)      // delete the old image
            {
                delete[] currentImage[i];
            }
            delete[] currentImage;
            currentImage = newImage;

           int value;
            for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    C = currentImage[i][j].Y - 16;
                    D = currentImage[i][j].U - 128;
                    E = currentImage[i][j].V - 128;

                    red_value = clip((298*C + 409*E +128) >> 8);
                    green_value = clip((298*C -100*D - 208*E +128) >> 8);
                    blue_value = clip((298*C + 516*D + 128) >> 8);

                    value = 0.3*red_value + 0.59*green_value + 0.11*blue_value;

                    currentImage[i][j].setValue(value);
                }
            }  

            return *this;            
        }
        virtual Image& operator * () override
        {
            for(int i = 0; i < height; i++)
            {
                for (int j = 0; j < width/2; j++)
                {
                    std::swap(currentImage[i][j], currentImage[i][width-j-1]);
                }
            }

            return *this;
        }

        virtual Pixel& getPixel(int row, int col) const override
        {
            return currentImage[row][col];
        }
        
        friend std::ostream& operator << (std::ostream& out, Image& image)
        {
            out << "P2" << endl;
            out << to_string(image.getWidth()) << " ";
            out << to_string(image.getHeight()) << " ";
            out << to_string(image.getMaxLuminocity()) << endl;


            for(int i = 0; i < image.getHeight(); i++)
            {
                for (int j = 0; j < image.getWidth(); j++)
                {
                    //out << to_string(image.myImage[i][j].pixel_value) << endl;
                    out << to_string(image.getPixel(i, j).pixel_value) << endl;
                }
            }

            return out;
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
        void setPtr(Image* ptr)
        {
            this->ptr = ptr;
        }
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
        img_ptr = new RGBImage(f);
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

bool check_symbol(string Token_name)
{
    if(Token_name[0] != '$')
    {
        return true;
    }
    return false;
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
    string just_input;
    long unsigned int array_pos = -1;

    double factor;
    int times = 0;
    int token_exists = 0;


    //array = (Token **) malloc(sizeof(Token));
    //array_size++;

    while (selection != 'q')
    {
        std::cout << "i <filename> as <$token>" << endl;
        std::cout << "e <$token> as <filename>" << endl;
        std::cout << "d <$token>" << endl;
        std::cout << "n <$token>" << endl;
        std::cout << "s <$token> by <factor>" << endl;
        std::cout << "r <$token> clockwise <X> times" << endl; 
        std::cout <<"m <$token>" << endl; 
        std::cin >> selection;
        if(!isalpha(selection))
        {
            return -1;      // it is not alphabetic input
        }
        // std::cin.ignore();

        switch(selection)
        {
            case 'i':
            {
                cin >> filename;
                cin >> as;
                cin >> token_name;

                currentImage = readNetpbmImage(filename.c_str());
                //printf("width is %d \nheight is %d \nmaxLuminocity is %d \n", currentImage->getWidth(), currentImage->getHeight(), currentImage->getMaxLuminocity());

                //array = (Token *) realloc(array, array_size*sizeof(Token));
                //Token* Image_token = new Token("kati", currentImage);

                /*New version for array*/
                if(check_symbol(token_name))
                {
                    cout << "[ERROR] Token " << token_name << " does not have $ as first character!" << endl;
                    break;
                }


                if(array_token.size() != 0)
                {

                    token_exists = 0;
                    if(checkToken(token_name, array_token) != array_token.size())
                    {
                        cout << "[ERROR] Token " << token_name << " exists!" << endl;
                        
                        token_exists = 1;
                        break;
                    }
                    
                }
                
                if (currentImage != nullptr && token_exists == 0)
                {
                    array_token.push_back(Token(token_name, currentImage));

                    cout << "[OK] Import " << token_name << endl;
                }

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
                    // for(int i = 0; i < currentImage->getWidth(); i++)
                    // {
                    //     for (int j = 0; j < currentImage->getHeight(); j++)
                    //     {
                    //         printf("Pixel is: %d\n", currentImage->getPixel(i, j).pixel_value);
                    //     }
                    // }

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
                            // myfile << "P2" << endl;
                            // myfile << to_string(currentImage->getWidth()) << " ";
                            // myfile << to_string(currentImage->getHeight()) << " ";
                            // myfile << to_string(currentImage->getMaxLuminocity()) << endl;

                            // for(int i = 0; i < currentImage->getHeight(); i++)
                            // {
                            //     for (int j = 0; j < currentImage->getWidth(); j++)
                            //     {
                            //         myfile << to_string(GSC->currentImage[i][j].getValue()) << endl;
                            //     }
                            // }
                            // cout << "[OK] Export " << token_name << endl;

                            GSCImage* check_image = dynamic_cast<GSCImage*>(currentImage);
                            if(check_image)
                            {
                                cout << "It is of GSC Image!" << endl;
                                myfile << *currentImage << endl;
                                break;
                            }
                            
                            cout << "It is of RGB Image!" << endl;

                            myfile << "P3" << endl;
                            myfile << to_string(currentImage->getWidth()) << " ";
                            myfile << to_string(currentImage->getHeight()) << " ";
                            myfile << to_string(currentImage->getMaxLuminocity()) << endl;


                            for(int i = 0; i < currentImage->getHeight(); i++)
                            {
                                for (int j = 0; j < currentImage->getWidth(); j++)
                                {
                                    //out << to_string(currentImage->mycurrentImage->i][j].pixel_value) << endl;
                                    myfile << to_string (currentImage->getPixel(i, j).red) << " ";
                                    myfile << to_string (currentImage->getPixel(i, j).green) << " ";
                                    myfile << to_string (currentImage->getPixel(i, j).blue) << endl;
                                }
                            }

                            //myfile << *currentImage << endl;

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

            case 'n':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                //currentImage->operator!();
                (*currentImage) = !(*currentImage);

                std::cout << "[OK] Color" << endl;

                break;
            }

            case 's':
            {
                cin >> token_name;
                cin >> as;
                cin >> factor;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                //(*currentImage) *= factor;
                *currentImage = (*currentImage) *= factor;

                break;

            }

            case 'r':
            {
                cin >> token_name;
                cin >> as;
                cin >> times;
                cin >> just_input;

                if(times > 4)
                    times = times%4;
                else if (times < 0)
                {
                    times = abs(times);
                    if(times > 4)
                        times = times % 4;
                    
                    if(times == 1)
                        times = 3;
                    else if (times == 3)
                        times = 1;
                }

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                //(*currentImage) *= factor;
                *currentImage = (*currentImage) += times;        

                break;        
            }

            case 'm':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                *currentImage =* (*currentImage);

                break;
            }

            case 'g':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "Token " << token_name << " does not exists!" << endl;
                    break;
                }
                currentImage = array_token[array_pos].getPtr();

                GSCImage* check_image = dynamic_cast<GSCImage*>(currentImage);
                if(check_image)
                {
                    cout << "[NOP] Already grayscale " << token_name << endl;
                    break;
                }
                
                RGBImage* rgbPointer = dynamic_cast <RGBImage*>(currentImage);

                RGBImage& rgbRef = *rgbPointer; 

                // GSCImage *convert_image = new GSCImage(static_cast<RGBImage&>(*array_token[array_pos].getPtr()));
                GSCImage *convert_image = new GSCImage(rgbRef);

                delete rgbPointer;      // delete previous object with RGB image

                array_token[array_pos].setPtr(convert_image);

                break;

            }

            case 'z':
            {
                cin >> token_name;

                (*currentImage) =~ *currentImage;

                break;
            }

            default:
            {
                break;
            }
        }

    }
    for (int i = 0; i < (int)array_token.size(); i++)
    {
        delete array_token[i].getPtr();
        array_token.erase(array_token.begin()+i);
    }
    

    return 0;

}



