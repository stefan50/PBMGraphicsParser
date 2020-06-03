#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Graphics.hpp"
#include "Bitmap.hpp"
#include "Graymap.hpp"

using namespace std;

int main() {
    char format[3];
    std::ifstream file("baboon.pgm");
    std::ofstream out("baboon_copy.pgm");
    file >> format;
    Graphics* gmp = new Graymap(0, 0, String(format));
    //file.ignore(2);
    //file.ignore(1000, '\n');
    gmp->read(file);
    //gmp->negative();
    //gmp->rotate("right");
    //gmp->rotate("left");
    /*for(int i = 0; i < gmp->get_image().get_size(); i++) {
        for(int j = 0; j < gmp->get_image()[i].get_size(); j++) {
            //std::cout <<
        }
    }*/
    gmp->monochrome();
    gmp->write(out);

    delete gmp; 
    /*unsigned int a = 1;
    char c = static_cast<char>(a);
    std::cout << a << std::endl;*/ 
    return 0;
}