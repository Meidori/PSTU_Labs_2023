#pragma once
#include <iostream>


const int MAX_SIZE = 30;    // максимальный размер вектора для генерации исключительных ситуаций


class Vector {
public:
    Vector() {
        size = 0;
        data = nullptr;
    }


    Vector(int size) {
        if (size > MAX_SIZE) {
            throw 1;
        }
        this -> size = size;
        data = new int [size];
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }


    Vector(const Vector& vector) {
        size = vector.size;
        data = new int [size];
        for (int i = 0; i < size; i++) {
            data[i] = vector.data[i];
        }
    }


    Vector(int size, int* arr) {
        if (size > MAX_SIZE) {
            throw 1;
        }
        this -> size = size;
        data = new int [size];
        for (int i = 0; i < size; i++) {
            data[i] = arr[i];
        }
    }


    ~Vector() {
        if (data != nullptr) {
            delete[] data;
        }
    }


    const Vector& operator = (const Vector &vector) {
        if (data != nullptr) {
            delete[] data; 
        }
        size = vector.size;
        data = new int [size];
        for (int i = 0; i < size; i++) {
            data[i] = vector.data[i];
        }
        return *this;
    }


    int operator [] (int index) {
        if (index < 0) {
            throw 2;
        }
        if (index >= size) {
            throw 3;
        }

        return data[index];
    }


    int operator + (int step) {
        if (size + step > MAX_SIZE) {
            throw 4;
        }
        int* ptr = data;
        return *(ptr + step);
    }


    int operator () () {
        return size;
    }


    friend std::ostream& operator << (std::ostream& out, const Vector& vector);
    friend std::istream& operator >> (std::istream& in, const Vector& vector);
 
private:
    int size;
    int *data;
};


std::ostream& operator << (std::ostream& out, const Vector& vector) {
    if (vector.size == 0) {
        out << "Empty";
    }
    else {
        for (int i = 0; i < vector.size; i++) {
            out << vector.data[i] << " ";
        }
    }
    return out;
}


std::istream& operator >> (std::istream& in, const Vector& vector) {
    for (int i = 0; i < vector.size; i++) {
        std::cout << "Введите значение:" << std::endl;
        in >> vector.data[i];
    }
    return in;
    
}