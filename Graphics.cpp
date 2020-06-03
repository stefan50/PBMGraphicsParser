#include "Graphics.hpp"

Graphics::Graphics(int rows, int columns, String format) {
    this->rows = rows;
    this->columns = columns;
    this->format = format;
}

Graphics::~Graphics() {
    
}

/*void Graphics::negative() {
    for(int i = 0; i < columns; i++) {
        for(int j = 0; j < rows; j++) {
            image[i][j] = max_value - image[i][j];
        }
    }
}*/