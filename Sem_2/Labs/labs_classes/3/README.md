Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 3 - классы

> Будет добавлено позже

# 2.1 Код программы

> 3.cpp
```cpp
#include <iostream>
#include "time.h"


int main() {
    Time time1;
    std::cout << "Введите минуты и секунды для объекта time1:" << std::endl;
    std::cin >> time1;
    std::cout << "time1:" << time1 << std:: endl;

    Time time2 = time1;
    std::cout << "Создан объект time2 и ему присвоено значение time1." << std::endl;
    
    int subtraction_seconds;
    std::cout << "Введите количество секунд, которое будет вычтено из time2:" << std::endl;
    std::cin >> subtraction_seconds;
    time2 = time2 - subtraction_seconds;
    std::cout << "time2:" << time2 << std:: endl;

    bool comparison;
    std::cout << "Результат операции сравнения time1 == time2:" << std::endl;
    comparison = time1 == time2;
    std::cout << comparison << std::endl;
    
    std::cout << "Результат операции сравнения time1 != time2:" << std::endl;
    comparison = time1 != time2;
    std::cout << comparison << std::endl;

    return 0;
}
```

> time.h
```cpp
#pragma once


class Time {
private:
    int minutes;
    int seconds;


public:
    Time(int minutes = 0, int seconds = 0) {
        this -> minutes = minutes;
        this -> seconds = seconds;
        if (seconds >= 60) {
            int extra_mins = this -> seconds / 60;
            this -> seconds -= extra_mins * 60;
            this -> minutes += extra_mins;
        }
    }


    Time(const Time& time) {
        minutes = time.minutes;
        seconds = time.seconds;
    }


    ~Time() {}


    int get_mins() {
        return minutes;
    }


    int get_secs() {
        return seconds;
    }


    void set_mins(int minutes) {
        this -> minutes = minutes;
    }


    void set_secs(int seconds) {
        this -> seconds = seconds;
    }


    Time operator =(const Time& time) {
        if (&time == this) {
            return *this;
        }
        minutes = time.minutes;
        seconds = time.seconds;
        return *this;
    }


    Time operator -(const int secs) {
        seconds += minutes * 60;
        seconds -= secs;
        minutes = seconds / 60;
        seconds -= minutes * 60;

        return Time(minutes, seconds);
    }


    Time operator +(const int secs) {
        seconds += secs;
        int extra_mins = seconds / 60;
        minutes += extra_mins;
        seconds -= extra_mins * 60; 

        return Time(minutes, seconds);
    }


    bool operator ==(const Time& time) {
        return (seconds == time.seconds) && (minutes == time.minutes);
    }


    bool operator !=(const Time& time) {
        return (seconds != time.seconds) || (minutes != time.minutes);
    }


    friend std::ostream& operator <<(std::ostream& out, Time time);
    friend std::istream& operator >>(std::istream& in, Time& time);
};


std::ostream& operator <<(std::ostream& out, Time time) {
    out << time.get_mins() <<  ":" << time.get_secs();
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

# 2.2 UML

# Пример работы

```
Введите минуты и секунды для объекта time1:
10 240
time1:14:0
Создан объект time2 и ему присвоено значение time1.       
Введите количество секунд, которое будет вычтено из time2:
1
time2:13:59
Результат операции сравнения time1 == time2:
0
Результат операции сравнения time1 != time2:
1
```

# Вопросы
