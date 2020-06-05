#include "Bitmap.hpp"

Bitmap::Bitmap(int rows, int columns, String format) : Graphics(rows, columns, format) {
    /*for(int i = 0; i < columns; i++) {    
        Vector<unsigned int> temp;
        image.add_element(temp);
    }*/
    max_value = 1;
}

void Bitmap::grayscale() {

}

void Bitmap::monochrome() {

}

void Bitmap::negative() {
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            image[i][j] = max_value - image[i][j];
        }
    }
}

void Bitmap::rotate(String direction) {
    Bitmap rotated(columns, rows, format);
    rotated.max_value = max_value;
    rotated.image.borrow(rows);
    for(int i = 0; i < rows; i++) {
        rotated.image[i].borrow(columns);
    }
    if(direction == "left") {
        for(int i = 0; i < columns; i++) {
            for(int j = 0; j < rows; j++) {
                rotated.image[rows - j - 1][i] = image[i][j]; 
            }
        }        
    }
    else if(direction == "right") {
        for(int i = columns - 1; i >= 0; i--) {
            for(int j = rows - 1; j >= 0; j--) {
                rotated.image[j][i] = image[columns - i - 1][j];
            }
        }
    }
    *this = rotated;
}

std::istream& Bitmap::read(std::istream& is) {
    if(format == "P1") {
        read_ascii(is);
    }
    else if(format == "P4") {
        read_binary(is);
    }
    return is;    
}

std::ostream& Bitmap::write(std::ostream& os) {
    if(format == "P1") {
        write_ascii(os);
    }
    else if(format == "P4") {
        write_binary(os);
    }
    return os;
}

Bitmap::~Bitmap() {

}