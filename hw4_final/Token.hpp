#include <string.h>
#include <iostream>
#include "Image.hpp"

using namespace std;

class Token
{
    private:
        string name;
        Image* ptr;
    public:
        Token(const string& = "", Image* = nullptr);

        string getName() const;

        Image*  getPtr() const;

        void setName(const string& );
        void setPtr(Image* ptr);
};