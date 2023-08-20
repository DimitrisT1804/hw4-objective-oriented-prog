#include "Token.hpp"

// class Token
// {
//     private:
//         string name;
//         Image* ptr;
//     public:
//         Token(const string& token_name = "", Image* image_ptr = nullptr)
//         {
//             this->name = token_name;
//             this->ptr = image_ptr;
//         }
//         ~Token()
//         {

//         }
//         string getName() const
//         {
//             return name;
//         }
//         Image*  getPtr() const
//         {
//             return ptr;
//         }
//         void setName(const string& );
//         void setPtr(Image* ptr);
// };

Token::Token(const string& token_name, Image* image_ptr)
{
    this->name = token_name;
    this->ptr = image_ptr;
}