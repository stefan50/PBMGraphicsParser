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

}
void Graymap::rotate(String direction) {

}
Graymap::~Graymap() {

}
std::istream& Graymap::read(std::istream& is) {

}
std::ostream& Graymap::write(std::ostream& os) {
    
}