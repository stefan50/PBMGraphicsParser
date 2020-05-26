#include <iostream>
#include <fstream>
#include "Graphics.hpp"
#include "Bitmap.hpp"

using namespace std;

int main() {
    char c;
    String format;
    ifstream file("jj.pbm");
    file >> format;
    Graphics* bmp = new Bitmap(0, 0);
    bmp->read(file);
    //bmp->rotate("right");
    bmp->write(std::cout);
    delete bmp;    
    return 0;
}