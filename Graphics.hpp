#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "String.hpp"
#include "Vector.hpp"

class Graphics {
private:
    Vector<Vector<int>> image;
    int rows;
    int columns;
public:
    Graphics();
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotate(String direction) = 0;
    virtual ~Graphics();
};

#endif