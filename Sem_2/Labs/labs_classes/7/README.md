Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 7 - классы

> Будет добавлено позже

# 2.1 Код программы

> 7.cpp
```cpp
#include <iostream>

#include "vector.h"
#include "time.h"


int main() {
    Time time;
    std::cout << "Введите время - минуты и секунды:" << std::endl;
    std::cin >> time;
    std::cout << "time:" << std::endl;
    std::cout << time << std::endl;

    int size1 = 5;
    Vector<Time> vect1(size1, time);
    std::cout << "Введите элементы vect1 (тип Time):" << std::endl;
    std::cin >> vect1;
    std::cout << "vect1:" << std::endl;
    std::cout << vect1 << std::endl;;

    int size2 = 10;
    Vector<Time> vect2(size2, time);
    std::cout << "vect2(size2, time):" << std::endl;
    std::cout << vect2 << std::endl;
    vect2 = vect1;
    std::cout << "vect2 = vect1:" << std::endl;
    std::cout << vect2 << std::endl;

    int index, multiplier;
    std::cout << "Введите индекс:" << std::endl;
    std::cin >> index;
    std::cout << "Введите множитель:" << std::endl;
    std::cin >> multiplier;

    vect2[index] = vect2[index] * multiplier;
    std::cout << "vect2[index] = vect2[index] * multiplier:" << std::endl;
    std::cout << vect2[index] << std::endl;

    return 0;
}
```

> time.h
```cpp
#pragma once
#include <iostream>


class Time {
public:
    Time(int minutes = 0, int seconds = 0) {
        minutes += seconds / 60;
        seconds = seconds % 60;
        this -> minutes = minutes;
        this -> seconds = seconds;
    }


    Time(const Time& time) {
        minutes = time.minutes;
        seconds = time.seconds;
    }


    ~Time() {}


    void set_mins(int minutes) {
        this -> minutes = minutes;
    }


    void set_secs(int seconds) {
        this -> seconds = seconds;
    }


    Time operator =(const Time& time) {
        minutes = time.minutes;
        seconds = time.seconds;
        return *this;
    }


    Time operator *(int multiplier) {
        seconds += minutes * 60;
        seconds *= multiplier;
        minutes = seconds / 60;
        seconds = seconds % 60;
        return *this; 
    }


    friend std::ostream& operator<< (std::ostream& out, const Time&);
    friend std::istream& operator>> (std::istream& in, Time&);


private:
    int seconds;
    int minutes;
};


std::ostream& operator<< (std::ostream& out, const Time& time) {
    out << time.minutes << ":" << time.seconds;
    return out;
}


std::istream& operator >>(std::istream& in, Time& time) {
    int mins, secs;
    in >> mins;
    in >> secs;
    mins += secs / 60;
    secs -= secs / 60 * 60;
    time.set_mins(mins);
    time.set_secs(secs);
    return in;
}
```

> vector.h
```cpp
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
```

# 2.2 UML

<image src = "7.png">

# Пример работы

```
Введите время - минуты и секунды:
20 330
time:
25:30
Введите элементы vect1 (тип Time):
40 45
53 45
65 456
34 32
12 696
vect1:
40:45 53:45 72:36 34:32 23:36 
vect2(size2, time):
25:30 25:30 25:30 25:30 25:30 25:30 25:30 25:30 25:30 25:30 
vect2 = vect1:
40:45 53:45 72:36 34:32 23:36 
Введите индекс:
3
Введите множитель:
5
vect2[index] = vect2[index] * multiplier:
172:40
```

# Вопросы