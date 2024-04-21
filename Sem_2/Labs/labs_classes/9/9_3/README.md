Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 9 - классы

> Будет добавлено позже

# 2.1 Код программы

> 9_3.cpp
```cpp
#include <iostream>

#include "vector.h"
#include "error.h"


int main() {
    try {
        Vector vect1(3);
        std::cout << "vect1: ";
        std::cout << vect1 << std::endl;

        int index;
        std::cout << "Index: ";
        std::cin >> index;
        std::cout << vect1[index] << std::endl;

        int step;
        std::cout << "Step: ";
        std::cin >> step;

        std::cout << "vect1 + step: ";
        std::cout << vect1 + step << std::endl;

        int size;
        std::cout << "Введите размер вектора (MAX_SIZE = 30): ";
        std::cin >> size;
        Vector vect2(size);
        std::cout << "vect2: ";
        std::cout << vect2 << std::endl; 
        
    }
    catch (Error& error) {
        error.what();
    }


    return 0;
}
```

> vector.h
```cpp
#pragma once
#include <iostream>

#include "error.h"


const int MAX_SIZE = 30;    // максимальный размер вектора для генерации исключительных ситуаций


class Vector {
public:
    Vector() {
        size = 0;
        data = nullptr;
    }


    Vector(int size) {
        if (size > MAX_SIZE) {
            throw Size_Error();
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
            throw Size_Error();
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
            throw Index_Error();
        }
        if (index >= size) {
            throw Index_Error();
        }

        return data[index];
    }


    int operator + (int step) {
        if (size + step > MAX_SIZE) {
            throw Step_Error();
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
```

> error.h
```cpp
#pragma once
#include <iostream>
#include <string>


class Error {
public:
    virtual void what() {};
};


class Index_Error : public Error {
public:
    Index_Error() {
        error_message = "Index_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};


class Size_Error : public Error {
public:
    Size_Error() {
        error_message = "Size_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};


class Step_Error : public Error {
public:
    Step_Error() {
        error_message = "Step_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};
```

# 2.2 UML

<image src = "9_3.png">

# Пример работы

```
vect1: 0 1 2 
Index: 100   
Index_Error
```

# Вопросы
