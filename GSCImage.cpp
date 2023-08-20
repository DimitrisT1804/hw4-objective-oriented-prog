#include "GSCImage.hpp"

// class GSCImage : public Image 
// {
//     public:
//         GSCPixel** currentImage;   // the array of current image
//         int counter = 0;
//         GSCImage() = default;

//         GSCImage(const GSCImage& img)
//         {
//             height = img.height;
//             width = img.width;

//             currentImage = new GSCPixel* [height];

//             for(int i = 0; i < height; i++)
//             {
//                 currentImage[i] = new GSCPixel[width];
//             }
//         }
//         //GSCImage(const RGBImage& grayscaled);
//         GSCImage(std::istream& stream)
//         {
//             string word;
//             int value = 0;
//             int i = 0, j = 0;

//             while(!stream.eof())
//             {
//                 stream >> word;
//                 counter++;
//                 if(counter == 1)    // get width
//                 {
//                     width = stoi(word);
//                     currentImage = new GSCPixel* [width];
//                 }
//                 else if(counter == 2)   // get height
//                 {
//                     height = stoi(word);
//                     for(int i = 0; i < width; i++)
//                     {
//                         currentImage[i] = new GSCPixel[height];
//                     }
//                 }
//                 else if(counter == 3)   // get max_luminocity
//                 {
//                     max_luminocity = stoi(word);
//                 }
//                 else    // it is the value of current pixel
//                 {
//                     /* a way to add the value in each pixel, it works!*/
//                     value = stoi(word);
//                     currentImage[i][j].setValue(value);
//                     if(j >= height-1)
//                     {
//                         i++;
//                         j = 0;
//                         if(i == width)
//                         {
//                             i = 0;
//                         }
//                     }
//                     else
//                     {
//                         j++;
//                     }
//                 }
//                 //cout << word << endl;
//             }
//             counter = 0;
//         }

//         ~GSCImage()
//         {
//            // free(currentImage);
//             for(int i = 0; i < width; i++)
//             {
//                 delete[] currentImage[i];
//             }
//            delete[] currentImage;
//         }


//         GSCImage& operator = (const GSCImage& img);

//         virtual Image& operator += (int times) override
//         {
//             // currentImage
//             // for(int i = 0; i < height; i++)
//             // {
//             //     for(int j = 0; j < width; j++)
//             //     {
//             //         currentImage[i][j] = currentImage[j][i];
//             //     }
//             // }
//         }
//         virtual Image& operator *= (double factor) override
//         {

//         }
//         virtual Image& operator ! () override
//         {

//         }
//         virtual Image& operator ~ () override
//         {

//         }
//         virtual Image& operator * () override
//         {

//         }

//         virtual Pixel& getPixel(int row, int col) const override
//         {
//             return currentImage[row][col];
//         }
//         friend std::ostream& operator << (std::ostream& out, Image& image)
//         {

//         }

//         // implementations


//         // Image& Image::operator+= (int times)
//         // {
//         //     for(int i = 0; i < times; i++)
//         //     {
//         //         for(int j = 0; j < )
//         //     }
//         // }

//         // GSCImage(std::istream& stream)
//         // {~Token()

//         // }
// };

GSCImage::GSCImage(const GSCImage& img)
{
    height = img.height;
    width = img.width;

    currentImage = new GSCPixel* [height];

    for(int i = 0; i < height; i++)
    {
        currentImage[i] = new GSCPixel[width];
    }
}

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


GSCImage::~GSCImage()
{
    // free(currentImage);
    for(int i = 0; i < width; i++)
    {
        delete[] currentImage[i];
    }
    delete[] currentImage;
}
