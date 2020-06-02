#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Graphics.hpp"
#include "Bitmap.hpp"

using namespace std;

int main() {
    char format[3];
    std::ifstream file("binaryj.pbm");
    std::ofstream out("out.pbm");
    file >> format;
    Graphics* bmp = new Bitmap(6, 10, String(format));
    //file.ignore(2);
    //file.ignore(1000, '\n');
    bmp->read(file);
    bmp->negative();
    bmp->rotate("left");
    bmp->write(out);

    delete bmp; 
    /*unsigned int a = 1;
    char c = static_cast<char>(a);
    std::cout << a << std::endl;*/ 
    return 0;
}