#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include "String.hpp"
#include "Vector.hpp"
#include <iostream>
#include <fstream>

class Graphics {
protected:
    Vector<Vector<unsigned int>> image;
    int rows;
    int columns;
    int max_value;
    String format;
    virtual bool read_binary(std::istream& is) = 0;
    virtual bool read_ascii(std::istream& is) = 0;
    virtual bool write_binary(std::ostream& os) = 0;
    virtual bool write_ascii(std::ostream& os) = 0;
public:
    Graphics(int rows, int columns, String format);
    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotate(String direction) = 0;
    virtual ~Graphics();
    virtual std::istream& read(std::istream& is) = 0;
    virtual std::ostream& write(std::ostream& os) = 0;
    Vector<Vector<unsigned int>> get_image() const {
        return image;
    }
    String get_format() const {
        return format;
    }
    void set_image(Vector<Vector<unsigned int>> other) {
        image = other;
    }
    int get_rows() const {
        return rows;
    }
    int get_columns() const {
        return columns;
    }
    int get_max_value() const {
        return max_value;
    }
    void set_max_value(int max_value) {
        this->max_value = max_value;
    }
    virtual void append_horizontally(Graphics* image) = 0;
    virtual void append_vertically(Graphics* image) = 0;
};

#endif