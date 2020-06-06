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
    
    /*char format[3];
    std::ifstream file("sample.ppm");
    std::ifstream file2("samples.ppm");
    std::ofstream out("sample_copy.ppm");
    file >> format;
    Graphics* gmp = new Pixmap(0, 0, String(format));
    Graphics* gmp2 = new Pixmap(0, 0, String(format));
    gmp->read(file);
    file2 >> format;
    gmp2->read(file2);
    //gmp2->negative();
    //gmp2->rotate("right");
    //gmp2->rotate("right");
    //std::cout << gmp2->get_image().get_size() << std::endl;
    gmp->append_horizontally(gmp2);
    //gmp->negative();
    //gmp->rotate("right");
    //gmp->rotate("left");
    //gmp->grayscale();
    //gmp->rotate("right");
    //gmp->rotate("left");
    //gmp->rotate("left");
    gmp->write(out);
    */
    //delete gmp;
    
    GraphicsParser gp;
    gp.run();  
    return 0;
}