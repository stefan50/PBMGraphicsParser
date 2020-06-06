#include "Pixmap.hpp"

Pixmap::Pixmap(int rows, int columns, String format) : Graphics(rows, columns, format) {

}

Pixmap::~Pixmap() {
    
}

void Pixmap::grayscale() {
    for(int i = 0; i < rows*columns; i++) {
        int color = 0;
        for(int j = 0; j < 3; j++) {
            color += image[i][j];
        }
        for(int j = 0; j < 3; j++) {
            image[i][j] = color / 3;
        }
    }
}

void Pixmap::monochrome() {
    for(int i = 0; i < rows*columns; i++) {
        int color = 0;
        for(int j = 0; j < 3; j++) {
            color += image[i][j];
        }
        for(int j = 0; j < 3; j++) {
            if(color / 3 >= max_value / 2) {
                image[i][j] = 1;
            }
            else {
                image[i][j] = 0;
            }
        }
    }
    max_value = 1;
}

void Pixmap::rotate(String direction) {
    Pixmap rotated(columns, rows, format);
    rotated.max_value = max_value;
    rotated.image.borrow(rows*columns);
    for(int i = 0; i < rows*columns; i++) {
        rotated.image[i].borrow(3);
    }
    if(direction == "left") {
        int rotation_index = 0;
        for(int temp_row = rows; temp_row != 0; temp_row--) {
            for(int i = 0; i < columns; i++) {
                for(int j = 0; j < 3; j++) {
                    rotated.image[rotation_index][j] = image[i*rows + temp_row - 1][j]; 
                }
                rotation_index++;
            }
        }        
    }
    else if(direction == "right") {
        int rotation_index = 0;
        for(int temp_row = 0; temp_row < rows; temp_row++) {
            for(int i = columns - 1; i >= 0; i--) {
                for(int j = 0; j < 3; j++) {
                    rotated.image[rotation_index][j] = image[i*rows + temp_row][j]; 
                }
                rotation_index++;
            }
        }
    }
    *this = rotated;
}

void Pixmap::negative() {
    for(int i = 0; i < rows*columns; i++) {
        for(int j = 0; j < 3; j++) {
            image[i][j] = max_value - image[i][j];
        }
    }
}

std::istream& Pixmap::read(std::istream& is) {
    if(format == "P3") {
        read_ascii(is);
    }
    else if(format == "P6") {
        read_binary(is);
    }
    return is;
}

std::ostream& Pixmap::write(std::ostream& os) {
    if(format == "P3") {
        write_ascii(os);
    }
    else if(format == "P6") {
        write_binary(os);
    }
    return os;
}

void Pixmap::append_horizontally(Graphics* image) {
    Vector<Vector<unsigned int>> appended;
    Vector<Vector<unsigned int>> copy = image->get_image();
    appended.borrow(2*columns*rows);
    bool switch_var = false;
    int k = 0, n = 0;
    for(int i = 0; i < columns*rows*2; i++) {
        if(i % rows == 0) switch_var = !switch_var;
        appended[i].borrow(3);
        if(switch_var) {
            for(int j = 0; j < 3; j++) {
                appended[i][j] = this->image[k][j]; 
            }
            k++;
        }
        else {
            for(int j = 0; j < 3; j++) {
                appended[i][j] = copy[n][j]; 
            }
            n++;
        }
    }

    this->image = appended;
    rows *= 2;
}

void Pixmap::append_vertically(Graphics* image) {
    Vector<Vector<unsigned int>> appended;
    appended.borrow(2*columns*rows);
    for(int i = 0; i < columns * rows; i++) {
        appended[i].borrow(3);
        for(int j = 0; j < 3; j++) {
            appended[i][j] = this->image[i][j]; 
        }
    }
    Vector<Vector<unsigned int>> copy = image->get_image();
    for(int i = 0; i < copy.get_size(); i++) {
        appended[i + columns*rows].borrow(3);
        for(int j = 0; j < 3; j++) {
            appended[i + columns*rows][j] = copy[i][j]; 
        } 
    } 

    this->image = appended;
    columns *= 2;
}