#ifndef PIXMAP_HPP
#define PIXMAP_HPP
#include "Graphics.hpp"

class Pixmap: public Graphics {
private:
    bool read_binary(std::istream& is) {
        is.ignore(1);
        if(is.peek() == '#') {
            is.ignore(1000, '\n');        
        } 
        is >> rows >> columns >> max_value;
        is.ignore(1);
        uint8_t temp;
        image.borrow(rows*columns);
        for(int i = 0; i < rows*columns; i++) {
            image[i].borrow(3);
            for(int j = 0; j < 3; j++) {
                is.read((char*)&temp, 1);
                image[i][j] = (int) temp;
            }
        }
    }
    bool read_ascii(std::istream& is) {
        is.ignore(1);
        if(is.peek() == '#') {
            is.ignore(1000, '\n');        
        } 
        is >> rows >> columns >> max_value;
        image.borrow(rows*columns);
        for(int i = 0; i < rows*columns; i++) {
            image.borrow(3);
            for(int j = 0; j < 3; j++) {
                is >> image[i][j];
            }
        }
    }     
    bool write_binary(std::ostream& os) {
        os << format << std::endl;
        os << rows << " " << columns << std::endl;
        os << max_value << std::endl;
        for(int i = 0; i < columns*rows; i++) {
            for(int j = 0; j < 3; j++) {
                os.write((char*)(&image[i][j]), 1);
            }
        }
    }
    bool write_ascii(std::ostream& os) {
        os << format << std::endl;
        os << rows << " " << columns << std::endl;
        os << max_value << std::endl;
        for(int i = 0; i < rows*columns; i++) {
            for(int j = 0; j < 3; j++) {
                os << image[i][j] << " ";
            }
            os << std::endl;
        }
    }
public:
    Pixmap(int rows, int columns, String format);
    void grayscale();
    void monochrome();
    void negative();
    void rotate(String direction);
    ~Pixmap();
    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os);
    void append_horizontally(Graphics* image);
    void append_vertically(Graphics* image);
};

#endif 