#ifndef VECTOR_HPP
#define VECTOR_HPP

template <class T>
class Vector {
private:
    T* elements;
    int size;
    int capacity;
    void erase() {
        delete[] elements;
    }
    void copy(const Vector& other) {
        capacity = other.capacity;
        size = other.size;
        elements = new T[capacity];
        for(int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
    }
    void resize() {
        capacity *= 2;
        T* new_els = new T[capacity];
        for(int i = 0; i < size; i++) {
            new_els[i] = elements[i]; 
        }
        erase();
        elements = new_els;
    }
public:
    Vector() {
        capacity = 16;
        size = 0;
        elements = new T[capacity];
    }
    Vector(int size) {
        this->size = size;
        capacity = size;
        elements = new T[capacity];
    }
    Vector(const Vector& other) {
        copy(other);
    }
    ~Vector() {
        erase(); 
    }
    Vector& operator=(const Vector& other) {
        if(this != &other) {
            erase();
            copy(other);
        }
        return *this;
    }

    T& operator[](int i) {
        return elements[i]; 
    }

    int add_element(T element) {
        if(size >= capacity) {
            resize();
        }
        elements[size++] = element;
        return 0;
    }

    void remove_element(T element) {
        Vector temp;
        bool is_skip = false;
        for(int i = 0; i < size; i++) {
            if(elements[i] != element || is_skip) {
                temp.add_element(elements[i]);
            }
            else {
                is_skip = true;
            }
        }
        size--;
        erase();
        copy(temp);
    }

    void remove_last_element() {
        Vector temp;
        if(size > 0) {
            size--; 
            for(int i = 0; i < size; i++) {
                temp.add_element(elements[i]);
            }
            *this = temp; 
        }
    }

    int get_size() const {
        return size;
    }

    T find_element(T element) {
        for(int i = 0; i < size; i++) {
            if(elements[i] == element) {
                return elements[i];
            }
        }   
    }

    void fill(T element) {
        for(int i = 0; i < size; i++) {
            elements[i] = element;    
        }
    }

    void borrow(int size) {
        if(this->size >= size) {
            return;
        }
        this->size = size;
        this->capacity = size + 1;
        erase();
        elements = new T[capacity];
    }
};

#endif