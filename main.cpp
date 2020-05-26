#include <iostream>
#include <fstream>
#include "Graphics.hpp"
#include "Bitmap.hpp"

using namespace std;

int main() {

    ifstream file("letterj.pbm");
    Graphics* bmp = new Bitmap(6, 10);
    bmp->read(file);
    bmp->write(std::cout);

/*    char c;
    while(true) {
        cin.get(c);
        if(c == '\n') {
            std::cout << true << std::endl;
        } 
    }
*/    
    return 0;
}