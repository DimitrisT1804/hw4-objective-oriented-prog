#include "GSCImage.hpp"
#include "RGBImage.hpp"
#include "clip.hpp"

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

GSCImage::GSCImage(std::istream& stream)
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

GSCImage::~GSCImage()
{
    // free(currentImage);
    for(int i = 0; i < height; i++)
    {
        delete[] currentImage[i];
    }
    delete[] currentImage;
}

Image& GSCImage::operator += (int times)
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

Image& GSCImage::operator *= (double factor)
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

// int clip(double value)
// {
//     if(value < 0)
//         return 0;
//     else if(value > 255)
//         return 255;
//     else
//         return value;
// }


Image& GSCImage::operator ~ ()
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
        // cout << "The array pos " << i << " is " << histogram_array[i] << endl;
        possibility_array[i] = (double)(histogram_array[i])/ (double)pixels_size;
        //cout << "The possibility array pos " << i << " is " << possibility_array[i] << endl;
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

    // for(int i = 0; i <= max_luminocity; i++)
    // {
    //     cout << "The final possibility array pos " << i << " is " << final_possibility_array[i] << endl;
    // }    

    for(int i = 0; i <= max_luminocity; i++)
    {
        final_array[i] = (int) (235.0*final_possibility_array[i]);
        //cout << "The array pos " << i << " is " << final_array[i] << endl;
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

Pixel& GSCImage::getPixel(int row, int col) const
{
    return currentImage[row][col];
}

// std::ostream& GSCImage::operator << (std::ostream& out, Image& image)
// {
//     out << "P2" << endl;
//     out << to_string(image.getWidth()) << " ";
//     out << to_string(image.getHeight()) << " ";
//     out << to_string(image.getMaxLuminocity()) << endl;


//     for(int i = 0; i < image.getHeight(); i++)
//     {
//         for (int j = 0; j < image.getWidth(); j++)
//         {
//             //out << to_string(image.myImage[i][j].pixel_value) << endl;
//             out << to_string(image.getPixel(i, j).pixel_value) << endl;
//         }
//     }

//     return out;
// }