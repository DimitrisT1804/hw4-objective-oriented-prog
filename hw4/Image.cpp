/* Source File for Image abstract class*/

#include "Image.hpp"

int Image::getWidth() const { return width; }

int Image::getHeight() const { return height; }
int Image::getMaxLuminocity() const { return max_luminocity;  }
void Image::setWidth(int width) { this->width = width; }
void Image::setHeight(int height) { this->height = height; }
void Image::setMaxLuminocity(int lum) { this->max_luminocity = lum; }

Image::~Image()
{

}