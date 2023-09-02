/* Source File for GSCImage class*/

#include "GSCImage.hpp"
#include "RGBImage.hpp"
#include "clip.hpp"

// Constructor with width and height
GSCImage::GSCImage(int width, int height)
{
    this->width = width;
    this->height = height;

    currentImage = new GSCPixel* [height];

    for(int i = 0; i < height; i++)
    {
        currentImage[i] = new GSCPixel[width];
    }   
}

// copy constructor
GSCImage::GSCImage(const GSCImage& img)
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

// Constructor from RGBImage to convert it to GSCImage
GSCImage::GSCImage(const RGBImage& grayscaled)
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

// Constructor from a file
GSCImage::GSCImage(std::istream& stream)
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
            /* a way to add the value in each pixel*/
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
    }
    counter = 0;
}

// Destructor
GSCImage::~GSCImage()
{
    for(int i = 0; i < height; i++)
    {
        delete[] currentImage[i];
    }
    delete[] currentImage;
}

// Rotate Image n times
Image& GSCImage::operator += (int times)
{
    // repeat for times
    for(int k = 0; k < times; k++)
    {
        // Create new Image
        int old_width = width;
        int old_height = height;

        width = height;
        height = old_width;

        GSCPixel **newImage = new GSCPixel*[height];

        for(int i = 0; i < height; i++)     // rotate for 90 degrees each time
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


        for(int i = 0; i < old_height; i++)   // delete the old image
        {
            delete[] currentImage[i];
        }
        delete[] currentImage;

        currentImage = newImage;    
    }
    return *this;   // return pointer to GSCImage
}

// Resize image factor times, where 0 < factor <= 2.0
Image& GSCImage::operator *= (double factor)
{
    int old_width = width;
    int old_height = height;
    
    width = width * factor;
    height = height * factor;

    GSCPixel** newImage = new GSCPixel*[height];    // create new Image
    for (int i = 0; i < height; i++) 
    {
        newImage[i] = new GSCPixel[width];
    }


    int r1, r2;     // given parameters
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

// Convert Image to negative
Image& GSCImage::operator ! ()
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

// Equalize the histogram of the image
Image& GSCImage::operator ~ ()
{
    int red_value, green_value, blue_value;

    int histogram_array[max_luminocity+1] = {0};        // array to keep the histogram
    int pixels_size = height*width;
    double possibility_array[max_luminocity+1] = {0.0};     // array to keep the possibility for each pixel to has a value
    double final_possibility_array[max_luminocity + 1] = {0};
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
        possibility_array[i] = (double)(histogram_array[i]) / (double)pixels_size;
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
        final_array[i] = (int) (235.0*final_possibility_array[i]);      // int array to keep to cut the decimals
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            newImage[i][j].U = currentImage[i][j].U;        // add the values
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
                {
                    newImage[i][j].Y = final_array[k];      // replace values of pixels with ones on the final_array
                }
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
    // convert Image from YUV to RGB again
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

// reverse image to the vertical axis
Image& GSCImage::operator * ()
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
Pixel& GSCImage::getPixel(int row, int col) const
{
    return currentImage[row][col];
}
