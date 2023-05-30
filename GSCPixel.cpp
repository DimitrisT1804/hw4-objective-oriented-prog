//
class GSCPixel : public Pixel
{
    public:
        GSCPixel() = default;
        GSCPixel(const GSCPixel& p);
        GSCPixel(unsigned char value);
        unsigned char getValue();
        void setValue(unsigned char value);   

};
