/* Source File for main class from the program hw4 */

// #define PRINT_MENU

#include <vector>
#include "Image.hpp"
#include "Token.hpp"
#include "RGBImage.hpp"
#include "GSCImage.hpp"


using namespace std;

// method that reads file and creates GSCImage or RGBImage
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

// Method that checks if the token has the '$' as first symbol
bool check_symbol(string Token_name)
{
    if(Token_name[0] != '$')
    {
        return true;
    }
    return false;
}

// method that checks if the token exists already
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
    char selection = ' ';
    Image* currentImage;
    string out_file;
    vector<Token> array_token;
    string token_name;
    string filename;
    string as;  // just to take the input word
    string just_input; // just to take the input word
    long unsigned int array_pos = -1;

    double factor;
    int times = 0;
    int token_exists = 0;

    while (selection != 'q')
    {
        #ifdef PRINT_MENU
        std::cout << "i <filename> as <$token>" << endl;
        std::cout << "e <$token> as <filename>" << endl;
        std::cout << "d <$token>" << endl;
        std::cout << "n <$token>" << endl;
        std::cout << "s <$token> by <factor>" << endl;
        std::cout << "r <$token> clockwise <X> times" << endl; 
        std::cout <<"m <$token>" << endl; 
        #endif

        std::cin >> selection;
        if(!isalpha(selection))
        {
            return -1;      // it is not alphabetic input
        }

        switch(selection)
        {
            case 'i':
            {
                cin >> filename;
                cin >> as;
                cin >> token_name;

                if(as != "as")
                {
                    cout << endl << "-- Invalid command! --" << endl;
                    break;
                }

                currentImage = readNetpbmImage(filename.c_str());

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

                if(as != "as")
                {
                    cout << endl << "-- Invalid command! --" << endl;
                    break;
                }

                for(array_pos = 0; array_pos < array_token.size(); array_pos++)
                {
                    if(strcmp(token_name.c_str(), array_token[array_pos].getName().c_str()) == 0)
                    {
                        break;
                    }
                }
                if(array_pos == array_token.size())
                {
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                }
                else
                {
                    currentImage = array_token[array_pos].getPtr();


                    if(currentImage == NULL)
                    {
                        cin >> out_file;
                        break;
                    }

                    ifstream ifile(out_file.c_str());
                    
                    if(ifile.good())
                    {   
                        cout << "[ERROR] File exists" << endl;
                        break;
                    }
                    else
                    {
                        ofstream myfile(out_file);
                        if(!myfile.is_open())
                        {
                            cout << "[ERROR] Unable to create file" << endl;
                        }
                        else
                        {
                            GSCImage* check_image = dynamic_cast<GSCImage*>(currentImage);
                            if(check_image)
                            {
                                myfile << "P2" << endl;
                                myfile << to_string(currentImage->getWidth()) << " ";
                                myfile << to_string(currentImage->getHeight()) << " ";
                                myfile << to_string(currentImage->getMaxLuminocity()) << endl;

                                for(int i = 0; i < currentImage->getHeight(); i++)
                                {
                                    for (int j = 0; j < currentImage->getWidth(); j++)
                                    {
                                        myfile << to_string(currentImage->getPixel(i, j).pixel_value) << endl;
                                    }
                                }
                                cout << "[OK] Export " << token_name << endl;
                                break;
                            }

                            myfile << "P3" << endl;
                            myfile << to_string(currentImage->getWidth()) << " ";
                            myfile << to_string(currentImage->getHeight()) << " ";
                            myfile << to_string(currentImage->getMaxLuminocity()) << endl;


                            for(int i = 0; i < currentImage->getHeight(); i++)
                            {
                                for (int j = 0; j < currentImage->getWidth(); j++)
                                {
                                    myfile << to_string (currentImage->getPixel(i, j).red) << " ";
                                    myfile << to_string (currentImage->getPixel(i, j).green) << " ";
                                    myfile << to_string (currentImage->getPixel(i, j).blue) << endl;
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
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
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
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                (*currentImage) = !(*currentImage);

                std::cout << "[OK] Color Inversion " << token_name << endl;

                break;
            }

            case 's':
            {
                cin >> token_name;
                cin >> as;
                cin >> factor;
                if(as != "by")
                {
                    cout << endl << "-- Invalid command! --" << endl;
                    break;
                }

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                *currentImage = (*currentImage) *= factor;

                cout << "[OK] Scale " << token_name << endl;

                break;

            }

            case 'r':
            {
                cin >> token_name;
                cin >> as;
                cin >> times;
                cin >> just_input;

                if(as != "clockwise" || just_input != "times")
                {
                    cout << endl << "-- Invalid command! --" << endl;
                    break;
                }

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
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                *currentImage = (*currentImage) += times;   

                cout << "[OK] Rotate " << token_name << endl;     

                break;        
            }

            case 'm':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                    break;
                }

                currentImage = array_token[array_pos].getPtr();

                *currentImage =* (*currentImage);

                cout << "[OK] Mirror " << token_name << endl;

                break;
            }

            case 'g':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
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

                GSCImage *convert_image = new GSCImage(rgbRef);

                delete rgbPointer;      // delete previous object with RGB image

                array_token[array_pos].setPtr(convert_image);
                
                cout << "[OK] Grayscale " << token_name << endl;
                break;

            }

            case 'z':
            {
                cin >> token_name;

                array_pos = checkToken(token_name, array_token);
                if( array_pos == array_token.size())
                {
                    cout << "[ERROR] Token " << token_name << " not found!" << endl;
                    break;
                }
                currentImage = array_token[array_pos].getPtr();

                (*currentImage) =~ *currentImage;

                cout << "[OK] Equalize " << token_name << endl;

                break;
            }

            default:
            {
                break;
            }
        }

    }
    int token_size = (int)array_token.size();
    for (int i = 0; i < token_size; i++)
    {
        GSCImage* check_image = dynamic_cast<GSCImage*>(array_token[i].getPtr());
        if(check_image)
        {
            delete check_image;
        }
        else
        {
            delete (RGBImage*) array_token[i].getPtr();
        }
    }

    for (int i = 0; i < token_size; i++)
    {
        array_token.erase(array_token.begin()+i);
    }

    return 0;   // normaly exits main()
}



