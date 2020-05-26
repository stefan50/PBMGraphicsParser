#ifndef BITMAP_HPP
#define BITMAP_HPP
#include "Graphics.hpp"
#include <iostream>

class Bitmap : public Graphics {
public:
    Bitmap();
    Bitmap(int rows, int columns);
    void grayscale();
    void monochrome();
    void negative();
    void rotate(String direction);
    ~Bitmap();
    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os);
};

#endif