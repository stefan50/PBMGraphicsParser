#include "Graymap.hpp"

Graymap::Graymap(int rows, int columns, String format) : Graphics(rows, columns, format) {
    for(int i = 0; i < columns; i++) {    
        Vector<unsigned int> temp;
        image.add_element(temp);
    }
    max_value = 15;
}

void Graymap::grayscale() {

}
void Graymap::monochrome() {
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            if(image[i][j] >= max_value / 2) {
                image[i][j] = 0;
            }
            else {
                image[i][j] = 1;
            }
        }
    }
    max_value = 1;
}

/*Graymap& Graymap::operator=(Graymap& other) {
    rows = other.rows;
    columns = other.columns;
    format = other.format;
    image.~Vector();
    image.borrow(columns);
    for(int i = 0; i < columns; i++) {
        image[i].borrow(rows);
        for(int j = 0; j < rows; j++) {
            image[i][j] = other.image[i][j];
        }
    }
}*/

void Graymap::rotate(String direction) {
    Graymap rotated(columns, rows, format);
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
Graymap::~Graymap() {

}
std::istream& Graymap::read(std::istream& is) {
    if(format == "P2") {
        read_ascii(is);
    }
    else if(format == "P5") {
        read_binary(is);
    }
    return is;
}

std::ostream& Graymap::write(std::ostream& os) {
    if(format == "P2") {
        write_ascii(os);
    }
    else if(format == "P5") {
        write_binary(os);
    }    
    return os;
}