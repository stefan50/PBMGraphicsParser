#include "Bitmap.hpp"

Bitmap::Bitmap(int rows, int columns) : Graphics(rows, columns) {}

void Bitmap::grayscale() {

}

void Bitmap::monochrome() {

}

void Bitmap::negative() {

}

void Bitmap::rotate(String direction) {

}

std::istream& Bitmap::read(std::istream& is) {
    char c;
    int i = 0;
    Vector<int> row;
    is >> c >> c;
    is.get(c);
    int j = 0;
    while(j < columns) {
        is.get(c);
        if(c == '#') {
            is.ignore(1000, '\n');
            is.ignore(1000, '\n');
        }
        if(c == ' ') continue;
        if(c == '\n') {
            j++;
            image.add_element(row);
            row = Vector<int>();
            continue;
        }
        if(c == '0' || c == '1') {
            row.add_element((int)(c - '0'));
        }
    } 
    return is;
}

std::ostream& Bitmap::write(std::ostream& os) {
    os << "P1" << std::endl;
    os << rows << " " << columns << std::endl;
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            std::cout << image[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Bitmap& bmp) {
    char c;
    int i = 0;
    while(is >> c) {
        Vector<int> row;
        if(c == '#') {
            is.ignore(1000, ' ');
        }
        if(c == ' ' || i >= bmp.rows) {
            i = 0;
            bmp.image.add_element(row);
            row = Vector<int>();
            continue;
        }
        if(c == '0' || c == '1') {
            row.add_element((int)(c - '0'));
        }
        i++;
    } 
}

std::ostream& operator<<(std::ostream& os, Bitmap& bmp) {
    os << "P1" << std::endl;
    os << bmp.rows << " " << bmp.columns << std::endl;
    for(int i = 0; i < bmp.columns; i++) {
        for(int j = 0; j < bmp.rows; j++) {
            std::cout << bmp.image[i][j] << " ";
        }
        std::cout << std::endl;
    }
}