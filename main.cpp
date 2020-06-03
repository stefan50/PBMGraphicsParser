#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Graphics.hpp"
#include "Bitmap.hpp"
#include "Graymap.hpp"
#include "Pixmap.hpp"

using namespace std;

int main() {
    char format[3];
    std::ifstream file("sample.ppm");
    std::ofstream out("sample_copy.ppm");
    file >> format;
    Graphics* gmp = new Pixmap(0, 0, String(format));
    //file.ignore(2);
    //file.ignore(1000, '\n');
    gmp->read(file);
    //gmp->negative();
    gmp->rotate("right");
    //gmp->rotate("left");
    /*for(int i = 0; i < gmp->get_image().get_size(); i++) {
        for(int j = 0; j < gmp->get_image()[i].get_size(); j++) {
            //std::cout <<
        }
    }*/
    //gmp->grayscale();
    gmp->write(out);

    delete gmp; 
    /*unsigned int a = 1;
    char c = static_cast<char>(a);
    std::cout << a << std::endl;*/ 
    return 0;
}