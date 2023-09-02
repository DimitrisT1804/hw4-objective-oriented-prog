/* Source File for Token class */

#include "Token.hpp"

Token::Token(const string& token_name, Image* image_ptr)
{
    this->name = token_name;
    this->ptr = image_ptr;
}

 string Token::getName() const
{
    return name;
}

Image*  Token::getPtr() const
{
    return ptr;
}

void Token::setPtr(Image* ptr)
{
    this->ptr = ptr;
}