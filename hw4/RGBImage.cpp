/* Source File for RGBImage class*/

#include "RGBImage.hpp"
#include "clip.hpp"

// Default constructor
RGBImage::RGBImage()
{
    height = 0;
    width = 0;
}

// Copy constructor
RGBImage::RGBImage(const RGBImage& img)
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

// Constructor from a file
RGBImage::RGBImage(std::istream& stream)
{
    string word;
    int i = 0, j = 0;
    int counter = 0;
    int pixel_counter = 0;
    int red = 0, green = 0, blue = 0;

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
            /* a way to add the value in each pixel */

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
            if(pixel_counter == 2)
                pixel_counter = 0;
            else
                pixel_counter++;

        }
    }
    counter = 0;           
}

// Destructor
RGBImage::~RGBImage()
{
    for(int i = 0; i < height; i++)
    {
        delete[] currentImage[i];
    }
    delete[] currentImage;
}

RGBImage& RGBImage::operator = (const RGBImage& img)
{
    return *this;
}

// Rotate Image n times
Image& RGBImage::operator += (int times)
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
    }
    return *this;
} 

// Resize image factor times, where 0 < factor <= 2.0
Image& RGBImage::operator *= (double factor)
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

// Convert Image to negative
Image& RGBImage::operator !()
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

// Equalize the histogram of the image
Image& RGBImage::operator ~()
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
        possibility_array[i] = (double)(histogram_array[i])/ (double)pixels_size;
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
        final_array[i] = (int) (235.0*final_possibility_array[i]);
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

// reverse image to the vertical axis
Image& RGBImage::operator *()
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

// method to return the specific Pixel
Pixel& RGBImage::getPixel(int row, int col) const
{
    return currentImage[row][col];
}
