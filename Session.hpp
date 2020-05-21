#ifndef SESSION_HPP
#define SESSION_HPP
#include "Vector.hpp"
#include "String.hpp"
#include "Graphics.hpp"
#include "Bitmap.hpp"
#include "Graymap.hpp"
#include "Pixmap.hpp"

class Session {
private:
    int id;
    Vector<Graphics*> images;
    Vector<String> commands;
public:
    Session();
    void undo();
    void add(Graphics image);
    void session_info();
    void collage(String direction, Graphics image1, Graphics image2, String outimage);
    void load(Vector<Graphics*> images, int id);
};

#endif