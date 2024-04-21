Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 9 - классы

> Будет добавлено позже

# 2.1 Код программы

> 9_2.cpp
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
    catch (Error error) {
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
            throw Error();
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
            throw Error();
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
            throw Error();
        }
        if (index >= size) {
            throw Error();
        }

        return data[index];
    }


    int operator + (int step) {
        if (size + step > MAX_SIZE) {
            throw Error();
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
    std::string error_message;

public:
    Error(std::string error_message = "Error") {
        this -> error_message = error_message;
    }


    void what() {
        std::cout << error_message;
    }
};
```

# 2.2 UML

<image src = "9_2.png">

# Пример работы

```
vect1: 0 1 2 
Index: 2     
2     
Step: 100
vect1 + step: Error
```

# Вопросы

# Вопросы

1. Что представляет собой исключение в С++?

- Исключение в C++ представляет собой событие, которое возникает во время выполнения программы и влияет на нормальное выполнение кода.

2. На какие части исключения позволяют разделить вычислительный процесс? Достоинства такого подхода?

- Исключения позволяют разделить вычислительный процесс на блоки кода, которые могут возбуждать и обрабатывать исключения. Это позволяет отделить код, обрабатывающий ошибки, от основного бизнес-логики программы.

3. Какой оператор используется для генерации исключительной ситуации?

- Для генерации исключительной ситуации используется оператор throw.

4. Что представляет собой контролируемый блок? Для чего он нужен?

- Контролируемый блок - это блок кода, в котором может возникнуть исключение. Он нужен для определения места, где исключение может быть сгенерировано.

5. Что представляет собой секция-ловушка? Для чего она нужна?

- Секция-ловушка это блок кода, предназначенный для обработки исключений. Она нужна для указания действий, которые нужно выполнить, если произошло исключение.

6. Какие формы может иметь спецификация исключения в секции ловушке? В каких ситуациях используются эти формы?

- Спецификация исключения в секции-ловушке может быть указана как тип данных, так и ключевое слово catch (...), которое указывает на обработку всех типов исключений. Эти формы используются для определения того, какие исключения будут обработаны в данной секции-ловушке.

7. Какой стандартный класс можно использовать для создания собственной иерархии исключений?

- Для создания собственной иерархии исключений можно использовать стандартный класс std::exception или его наследников.

8. Каким образом можно создать собственную иерархию исключений?

- Чтобы создать собственную иерархию исключений, необходимо создать пользовательские классы исключений, которые будут наследоваться от стандартного класса std::exception или его наследников.

9. Если спецификация исключений имеет вид: void f1() throw(int, double); то какие исключения может прождать функция f1()?

- Функция f1() может обрабатывать исключения типа int или double.

10. Если спецификация исключений имеет вид: void f1() throw(); то какие исключения может прождать функция f1()?

- Функция f1() не может обрабатывать никакие исключения, так как спецификация имеет вид throw(), что указывает на отсутствие исключений.

11. В какой части программы может генерироваться исключение?

- Исключение может генерироваться в любой части программы, где это необходимо, например, в блоке try-блока кода или в функции, которая может потенциально вызвать ошибку.

12. Написать функцию, которая вычисляет площадь треугольника по трем сторонам (формула Герона). Функцию реализовать в 4 вариантах:

    1. без спецификации исключений;
    2. со спецификацией throw();
    3. с конкретной спецификацией с подходящим стандартным исключением;
    4. спецификация с собственным реализованным исключением.

```cpp
double area(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
```

```cpp
double area(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw "Side length must be positive";
    }
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
```

```cpp
double area(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
```

```cpp
class InvalidSideLengthException : public std::exception {
public:
    const char* what() const throw() {
        return "Side length must be positive";
    }
};

double area(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        throw InvalidSideLengthException();
    }
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
```