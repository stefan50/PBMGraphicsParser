#include "Bitmap.hpp"

Bitmap::Bitmap(int rows, int columns) : Graphics(rows, columns) {
    for(int i = 0; i < columns; i++) {    
        Vector<int> temp;
        image.add_element(temp);
    }
}

void Bitmap::grayscale() {

}

void Bitmap::monochrome() {

}

void Bitmap::rotate(String direction) {
    Bitmap rotated(columns, rows);
    if(direction == "left") {
        for(int i = 0; i < columns; i++) {
            for(int j = 0; j < rows; j++) {
                rotated.image[rows - j - 1].add_element(image[i][j]);
            }
        }        
    }
    else if(direction == "right") {
        for(int i = columns - 1; i >= 0; i--) {
            for(int j = rows - 1; j >= 0; j--) {
                rotated.image[j].add_element(image[i][j]);
            }
        }
    }
    *this = rotated;
}

std::istream& Bitmap::read(std::istream& is) {
    char c;
    int i = 0, j = 0;
    is.ignore(1);
    while(is.peek() == '#') {
        is.ignore(1000, '\n');
    }
    is >> rows >> columns;
    is.ignore(1);
    *this = Bitmap(rows, columns);
    while(j < columns) {
        while(is.peek() == '#') {
            is.ignore(1000, '\n');
        }
        is >> c;
        if(i == rows - 1) {
            i = 0;
            image[j].add_element((int)(c - '0'));
            j++;
            continue;
        }
        if(c == '0' || c == '1') {
            image[j].add_element((int)(c - '0'));
            i++;
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

Bitmap::~Bitmap() {

}

void Bitmap::negative() {
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            image[i][j] = 1 - image[i][j];
        }
    }
}