#ifndef GRAYMAP_HPP
#define GRAYMAP_HPP
#include "Graphics.hpp"

class Graymap: public Graphics {
public:
    //Graymap();
    Graymap(int rows, int columns, String format);
    void grayscale();
    void monochrome();
    void rotate(String direction);
    ~Graymap();
    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os);
};

#endif