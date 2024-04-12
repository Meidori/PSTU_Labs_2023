#pragma once
#include "pair.h"


class Vector {
public:
    Vector() {
        vect = 0;
        size = 0;
        current_position = 0;
    }


    Vector(int size) {
        vect = new Object* [size];
        this -> size = size;
        current_position = 0;
    }


    ~Vector() {
        if (vect != 0) {
            delete vect;
        }
    }


    void add(Object* ptr) {
        if (current_position < size) {
            vect[current_position] = ptr;
            current_position++;
        }
    }


    friend std::ostream& operator <<(std::ostream& out, const Vector& v);


private:
    Object** vect;
    int size;
    int current_position;
};


std::ostream& operator <<(std::ostream& out, const Vector& v) {
    if(v.size == 0) {
        out << "Вектор пустой." << std::endl;
    }
    Object **ptr = v.vect;
    for(int i = 0; i < v.current_position; i++) {
        (*ptr) -> print();
        ptr++;
    }
    return out;
}