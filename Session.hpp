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
    Vector<String> file_names;
public:
    Session() {
        
    }
    Session(Vector<Graphics*> images, Vector<String> file_names, int id);
    Graphics* find_image(String name) {
        int i = 0;
        for(; i < file_names.get_size(); i++) {
            if(name == file_names[i]) {
                break;
            }
        }
        return images[i];
    }
    void undo();
    void add(Graphics* image);
    void add_file(String file);
    void add_command(String command);
    void session_info();
    void collage(String direction, Graphics* image1, Graphics* image2, String outimage);
    void grayscale();
    void monochrome();
    void negative();
    void rotate(String direction);
    void save();
    void save_as(Vector<String> file_names);
};

#endif