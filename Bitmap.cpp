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

void Bitmap::append_horizontally(Graphics* image) {
    Vector<Vector<unsigned int>> appended;
    Vector<Vector<unsigned int>> copy = image->get_image();
    appended.borrow(columns);
    for(int i = 0; i < columns; i++) {
        appended[i].borrow(rows*2);
        for(int j = 0; j < rows; j++) {
            appended[i][j] = this->image[i][j]; 
        }
        for(int j = 0; j < copy[i].get_size(); j++) {
            appended[i][j + rows] = copy[i][j]; 
        }
    }

    this->image = appended;
    rows *= 2;
}

void Bitmap::append_vertically(Graphics* image) {
    Vector<Vector<unsigned int>> appended;
    appended.borrow(columns*2);
    for(int i = 0; i < columns; i++) {
        appended[i].borrow(rows);
        for(int j = 0; j < rows; j++) {
            appended[i][j] = this->image[i][j]; 
        }
    }
    Vector<Vector<unsigned int>> copy = image->get_image();
    for(int i = 0; i < copy.get_size(); i++) {
        appended[i + columns].borrow(rows);
        for(int j = 0; j < copy[i].get_size(); j++) {
            appended[i + columns][j] = copy[i][j]; 
        } 
    } 

    this->image = appended;
    columns *= 2;
}