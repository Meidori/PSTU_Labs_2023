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

<image src = "6.png">

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

1. Что такое абстрактный тип данных? Привести примеры АТД.

- Абстрактный тип данных (Abstract Data Type, ADT) в программировании представляет собой математическую модель для организации данных и их операций, независимо от конкретной реализации. ADT определяет набор операций, которые могут быть выполнены над данными, но не определяет, как эти операции должны быть реализованы внутри структуры данных или объекта. Это позволяет отделять интерфейс (операции над данными) от реализации (внутренние детали хранения и обработки данных).

2. Привести примеры абстракции через параметризацию

-   ```cpp
    template <typename T>
    class Box {
    private:
        T data;
    public:
        Box(T val) : data(val) {}
        T getData() { return data; }
    };

    int main() {
        Box<int> intBox(5);  // Создание объекта класса Box для int
        Box<double> doubleBox(3.14);  // Создание объекта класса Box для double
        return 0;
    }
    ```

3. Привести примеры абстракции через спецификацию.

-   ```cpp
    class Shape {
    public:
        virtual double area() const = 0;  // Чисто виртуальная функция для вычисления площади
        virtual void draw() const = 0;  // Чисто виртуальная функция для отрисовки
        virtual ~Shape() {}  // Виртуальный деструктор
    };

    // Конкретный класс, реализующий интерфейс
    class Circle : public Shape {
    private:
        double radius;

    public:
        Circle(double r) : radius(r) {}

        double area() const override {
            return 3.14159 * radius * radius;
        }

        void draw() const override {
            std::cout << "Drawing a circle" << std::endl;
        }
    };

    // Конкретный класс, реализующий интерфейс
    class Rectangle : public Shape {
    private:
        double width;
        double height;

    public:
        Rectangle(double w, double h) : width(w), height(h) {}

        double area() const override {
            return width * height;
        }

        void draw() const override {
            std::cout << "Drawing a rectangle" << std::endl;
        }
    };

    int main() {
        Circle c(5);
        Rectangle r(3, 4);
        
        std::cout << "Circle area: " << c.area() << std::endl;  // Используем метод area через общий интерфейс Shape
        c.draw();  // Используем метод draw через общий интерфейс Shape
        
        std::cout << "Rectangle area: " << r.area() << std::endl;  // Используем метод area через общий интерфейс Shape
        r.draw();  // Используем метод draw через общий интерфейс Shape
        return 0;
    }
    ```

4. Что такое контейнер? Привести примеры.

- Контейнер в программировании - это тип, позволяющий инкапсулировать в себе объекты других типов. Примеры контейнеров: vector, list, map.

5.  Какие группы операций выделяют в контейнерах?

- Операции доступа, Операции изменения размера, Операции итерации, Операции сравнения

6. Какие виды доступа к элементам контейнера существуют? Привести примеры.

- По индексу, По ключу, С помощью итераторов, Через методы поиска. 

7. Что такое итератор?

- Итератор - это объект, который позволяет перебирать элементы контейнера и предоставляет доступ к каждому элементу в коллекции.

8. Каким образом может быть реализован итератор?

- Итератор может быть реализован как объект с методами для перемещения по контейнеру

9. Каким образом можно организовать объединение контейнеров?

- С помошью встроенных функций, с помощью итератора, использование алгоритмов и т. д.

10. Какой доступ к элементам предоставляет контейнер, состоящий из элементов «ключ-значение»?

- Контейнеры, состоящие из элементов "ключ-значение", такие как std::map, std::unordered_map в C++, предоставляют доступ к элементам через ключ.

11. Как называется контейнер, в котором вставка и удаление элементов выполняется на одном конце контейнера?

- stack

12. Какой из объектов (a,b,c,d) является контейнером?
```cpp
a. int mas = 10;
b. int mas;
c. struct {char name[30]; int age;} mas;
d. int mas[100].
```

- d

13. Какой из объектов (a,b,c,d) не является контейнером?
```cpp
a. int a[] = {1,2,3,4,5};
b. int mas[30];
c. struct {char name[30]; int age;} mas[30];
d. int mas.
```

- d

14. Контейнер реализован как динамический массив, в нем определена операция доступ по индексу. Каким будет доступ к элементам контейнера?

- Для доступа к элементам контейнера по индексу можно использовать оператор доступа к элементу "[]". Например, если у нас есть динамический массив с именем array, то доступ к элементу по индексу i будет выглядеть как array[i]

15. Контейнер реализован как линейный список. Каким будет доступ к элементам контейнера?

- указатель или итератор