#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "String.hpp"
#include "Vector.hpp"
#include <iostream>

class Graphics {
protected:
    Vector<Vector<int>> image;
    int rows;
    int columns;
public:
    Graphics(int rows, int columns);
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotate(String direction) = 0;
    virtual ~Graphics();
    virtual std::istream& read(std::istream& is) = 0;
    virtual std::ostream& write(std::ostream& os) = 0;
};

#endif