#include <iostream>
#include <fstream>
#include "Vector.hpp"
#include "Graphics.hpp"
#include "Bitmap.hpp"
#include "Graymap.hpp"
#include "Pixmap.hpp"
#include "GraphicsParser.hpp"

using namespace std;

int main() {
    /*
    char format[3];
    std::ifstream file("sample.ppm");
    std::ofstream out("sample_copy.ppm");
    file >> format;
    Graphics* gmp = new Pixmap(0, 0, String(format));
    gmp->read(file);
    gmp->negative();
    gmp->rotate("right");
    //gmp->rotate("left");
    gmp->grayscale();
    gmp->rotate("right");
    gmp->rotate("left");
    gmp->rotate("left");
    gmp->write(out);
    
    delete gmp;
    */
    GraphicsParser gp;
    gp.run();  
    return 0;
}