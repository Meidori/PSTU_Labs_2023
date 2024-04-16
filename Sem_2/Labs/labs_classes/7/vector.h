#pragma once
#include <iostream>


template <class T>
class Vector;


template <class T>
std::ostream& operator <<(std::ostream& out, const Vector<T>& vect) {
    for (int i = 0; i < vect.size; i++) {
        out << vect.data[i] << " ";
    }
    return out;
}


template <class T>
std::istream& operator >>(std::istream& in, Vector<T>& vect) {
    for (int i = 0; i < vect.size; i++) {
        in >> vect.data[i];
    }
    return in;
}


template <class T>
class Vector {
public:
    Vector(int size, T base_value = 0) {
        this -> size = size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = base_value;
        }
    }


    Vector(const Vector<T>& vect) {
        size = vect.size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = vect.data[i];
        }
    }


    ~Vector() {
        delete[] data;
        data = 0;
    }


    Vector& operator =(const Vector<T>& vect) {
        if (this == &vect) {
            return *this;
        }
        size = vect.size;
        if (data != 0) {
            delete[] data;
        }
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = vect.data[i];
        }
        return *this;
    }


    T& operator [](int index) {
        if (index < size) {
            return data[index];
        }
        else {
            std::cout << "index > size. Возвращено значение -1." << std::endl;
            static T default_value = -1;
            return default_value;
        }
    }


    int operator ()() {
        return size;
    }


    friend std::ostream& operator << <T>(std::ostream & out, const Vector& vect);
    friend std::istream& operator >> <T>(std::istream& in, Vector& vect);


private:
    int size;
    T *data;
};
