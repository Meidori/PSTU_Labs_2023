Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 6 - классы

> Будет добавлено позже

# 2.1 Код программы

> 6.cpp
```cpp
#include <iostream>

#include "vector.h"


int main() {
    int size1 = 5;
    Vector vect1(size1);
    std::cout << "Создан вектор (vect1) размера " << size1 << ":\n";
    std::cout << vect1 << std::endl;

    std::cout << "Введите значения элементов вектора:" << std::endl;
    std::cin >> vect1;

    std::cout << "vect1:" << std::endl;
    std::cout << vect1 << std::endl;

    int size2 = 10;
    Vector vect2(size2);
    std::cout << "Создан вектор (vect2) размера " << size2 << ":\n";
    std::cout << vect2 << std::endl;

    std::cout << "vect2 = vect1" << std::endl;
    vect2 = vect1;
    std::cout << "vect2:" << std::endl;
    std::cout << vect2 << std::endl;

    std::cout << "vect2[0]: " << vect2[0] << std::endl; 
    std::cout << "vect2[2]: " << vect2[2] << std::endl; 
    std::cout << "vect2[7]: " << vect2[7] << std::endl;

    int size3 = 7;
    Vector vect3(size3);
    std::cout << "Создан вектор (vect3) размера " << size3 << ":\n";
    std::cout << vect3 << std::endl;

    std::cout << "Размер вектора: vect3()" << std::endl;
    std::cout << vect3() << std::endl;

    std::cout << "Разыменовавыем значение vect1.get_first():" << std::endl;
    std::cout << *(vect1.get_first()) << std::endl; 

    std::cout << "Разыменовавыем значение vect2.get_last():" << std::endl;
    std::cout << *(vect2.get_last()) << std::endl; 

    std::cout << "Создан итератор, указывающий на первый элемент вектора vect1." << std::endl;
    Iterator i = vect1.get_first();
    std::cout << *(i) << std::endl;

    std::cout << "Увеличиваем итератор на 1." << std::endl;
    i = i + 1;
    std::cout << *(i) << std::endl;

    std::cout << "Увеличиваем итератор еще на 3." << std::endl;
    i = i + 3;
    std::cout << *(i) << std::endl;

    std::cout << "Уменьшаем итератор на 2." << std::endl;
    i = i - 2;
    std::cout << *(i) << std::endl;


    return 0;
}
```

> vector.h
```cpp
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
```

# 2.2 UML

# Пример работы

```
Создан вектор (vect1) размера 5:   
0 0 0 0 0 
Введите значения элементов вектора:
75 34 12 95 31
vect1:
75 34 12 95 31 
Создан вектор (vect2) размера 10:
0 0 0 0 0 0 0 0 0 0 
vect2 = vect1
vect2:
75 34 12 95 31 
vect2[0]: 75
vect2[2]: 12
vect2[7]: index > size. Возвращено значение -1.
-1
Создан вектор (vect3) размера 7:
0 0 0 0 0 0 0 
Размер вектора: vect3()
7
Разыменовавыем значение vect1.get_first():     
75
Разыменовавыем значение vect2.get_last():      
31
Создан итератор, указывающий на первый элемент вектора vect1.
75
Увеличиваем итератор на 1.
34
Увеличиваем итератор еще на 3.
31
Уменьшаем итератор на 2.
12
```

# Вопросы
