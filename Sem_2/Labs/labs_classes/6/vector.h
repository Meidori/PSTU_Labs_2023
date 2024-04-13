#pragma once
#include <iostream>


class Iterator {
    friend class Vector;


public: 
    Iterator() {
        ptr = 0;
    }


    Iterator(const Iterator& iterator) {
        ptr = iterator.ptr;
    }


    bool operator ==(const Iterator& iterator) {
        return ptr == iterator.ptr;
    }


    bool operator !=(const Iterator& iterator) {
        return ptr != iterator.ptr;
    }


    Iterator& operator=(const Iterator& iterator) {
        ptr = iterator.ptr;
        return *this;
    }

    Iterator operator+(int value) {
        Iterator new_iterator;
        new_iterator.ptr = ptr + value;
        return new_iterator;
    }

    Iterator operator-(int value) {
        Iterator new_iterator;
        new_iterator.ptr = ptr - value;
        return new_iterator;
    }



    int& operator *() const { 
        return *ptr;
    }


private:
    int* ptr;    
};


class Vector {
public:
    Vector(int size, int base_value = 0) {
        this -> size = size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = base_value;
        }
        first.ptr = &data[0];
        last.ptr = &data[size - 1];
    }


    Vector(const Vector& vect) {
        size = vect.size;
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = vect.data[i];
        }
        first = vect.first;
        last = vect.last;
    }


    ~Vector() {
        delete[] data;
        data = 0;
    }


    Vector& operator =(const Vector& vect) {
        if (this == &vect) {
            return *this;
        }
        size = vect.size;
        if (data != 0) {
            delete[] data;
        }
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = vect.data[i];
        }
        first = vect.first;
        last = vect.last;
        return *this;
    }


    int& operator [](int index) {
        if (index < size) {
            return data[index];
        }
        else {
            std::cout << "index > size. Возвращено значение -1." << std::endl;
            static int default_value = -1;
            return default_value;
        }
    }


    int operator ()() {
        return size;
    }


    Iterator get_first() {
        return first;
    }


    Iterator get_last() {
        return last;
    }


    friend std::ostream& operator <<(std::ostream& out, const Vector& vect);
    friend std::istream& operator >>(std::istream& in, Vector& vect);


private:
    int size;
    int *data;
    Iterator first;
    Iterator last;
};


std::ostream& operator <<(std::ostream& out, const Vector& vect) {
    for (int i = 0; i < vect.size; i++) {
        out << vect.data[i] << " ";
    }
    return out;
}


std::istream& operator >>(std::istream& in, Vector& vect) {
    for (int i = 0; i < vect.size; i++) {
        in >> vect.data[i];
    }
    return in;
}