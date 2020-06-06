#ifndef BITMAP_HPP
#define BITMAP_HPP
#include "Graphics.hpp"
#include <iostream>
#include <cmath>

//inspiration:
// https://stackoverflow.com/questions/20088612/save-pbm-ascii-to-pbm-binary-c

class Bitmap : public Graphics {
private:
    bool read_binary(std::istream& is) {
        is.ignore(1);
        //std::string id;
        if(is.peek() == '#' /*&& !std::getline(f, comment)*/) {
            is.ignore(1000, '\n');
            //is.ignore(1);
        }
        is >> rows >> columns;
        image.borrow(columns);
        uint8_t temp;
        for(int i = 0; i < columns; i++) {
            image[i].borrow(rows);
        }
        //is.ignore(1);
        for(int i = 0; i < columns; i++) {
            for(int j = 0; j < rows; j++) {
                if(j % 8 == 0) {
                    is.read((char*)(&temp), 1);
                }
                image[i][j] = (temp & (int)pow(2, 7 - (j % 8))) >> (7 - (j % 8));
            }
        }
        return true;
    }
    bool read_ascii(std::istream& is) {
        char c;
        int i = 0, j = 0;
        is.ignore(1);
        while(is.peek() == '#') {
            is.ignore(1000, '\n');
        }
        is >> rows >> columns;
        is.ignore(1);
        //*this = Bitmap(rows, columns, format);
        image.borrow(columns);
        //image[0].borrow(rows);
        while(j < columns) {
            while(is.peek() == '#') {
                is.ignore(1000, '\n');
            }
            is >> c;
            if(i == rows - 1) {
                i = 0;
                image[j].add_element((int)(c - '0'));
                j++;
                //image[j].borrow(rows);
                continue;
            }
            if(c == '0' || c == '1') {
                image[j].add_element((int)(c - '0'));
                i++;
            }
        } 
        return true;
    }
    bool write_binary(std::ostream& os) {
        Vector<Vector<char>> image_binary;
        image_binary.borrow(columns);
        for(size_t y = 0; y < image_binary.get_size(); ++y) {
            image_binary[y].borrow(rows);
            for(size_t x = 0; x < rows; ++x) {
                image_binary[y][x] = static_cast<char>(image[y][x]);
            }
        }
        if(!(os << "P4\n")) {
            return false;
        }
        /*if(!comment.empty() && !(f << comment << "\n")) {
            return false;
        }*/
        if(!(os << rows << " " << columns << "\n")) {
            return false;
        }
        Vector<char> linebits((rows + 7) / 8);
        for(int y = 0; y < image_binary.get_size(); ++y) {
            linebits.fill(0);
            for(size_t x = 0; x < rows; ++x) {
                const int byte_pos = x / 8;
                const int bit_pos = 7 - (x % 8);
                linebits[byte_pos] |= (image_binary[y][x] << bit_pos);
            }
            if(!os.write(&linebits[0], linebits.get_size())) {
                return false;
            }
        }
        return true;
    }
    bool write_ascii(std::ostream& os) {
        os << format << std::endl;
        os << rows << " " << columns << std::endl;
        for(int i = 0; i < columns; i++) {
            for(int j = 0; j < rows; j++) {
                os << image[i][j] << " ";
            }
            os << std::endl;
        }
    }
public:
    Bitmap();
    Bitmap(int rows, int columns, String format);
    void grayscale();
    void monochrome();
    void negative();
    void rotate(String direction);
    ~Bitmap();
    std::istream& read(std::istream& is);
    std::ostream& write(std::ostream& os);
    void append_horizontally(Graphics* image);
    void append_vertically(Graphics* image);
};

#endif