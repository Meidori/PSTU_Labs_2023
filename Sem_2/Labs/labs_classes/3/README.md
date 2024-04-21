Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 3 - классы

Создать класс Time для работы с временными интервалами. Интервал должен быть представлен в виде двух полей: минуты типа int и секунды типа int. при выводе минуты отделяются от секунд двоеточием. Реализовать:

- вычитание секунд

- сравнение временных интервалов (== и !=)

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

<image src = "3.png">

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

1. Для чего используются дружественные функции и классы?

- Они могут получить доступ к закрытым и защищенным членам класса, к которому они дружественны

2. Сформулировать правила описания и особенности дружественных функций.

- Имеют доступ ко всем полям и методам класса, могут быть определены в другом классе.

3. Каким образом можно перегрузить унарные операции?

-   ```cpp
    // бинарный оператор
    ReturnType operator Op(Type right_operand);
    // унарный оператор
    ClassType& operator Op();
    ```

4. Сколько операндов должна иметь унарная функция-операция, определяемая внутри класса?

- ноль или один

5. Сколько операндов должна иметь унарная функция-операция, определяемая вне класса?

- должна иметь один операнд в явном виде

6. Сколько операндов должна иметь бинарная функция-операция, определяемая внутри класса?

- должна иметь один-два операнда в явном виде

7. Сколько операндов должна иметь бинарная функция-операция, определяемая вне класса?

- два операнда в явном виде

8. Чем отличается перегрузка префиксных и постфиксных унарных операций?

-   ```cpp
    // префиксные операторы
    Counter operator++ ();
    // постфиксные операторы
    Counter operator++ (int)
    ```

9. Каким образом можно перегрузить операцию присваивания?

-   ```cpp
    Type operator= ()
    ```

10. Что должна возвращать операция присваивания?

-  ссылку на объект

11. Каким образом можно перегрузить операции ввода-вывода?

- вне класса как дружественную функцию

12. В программе описан класс и определен объект этого класса. Каким образом, компилятор будет воспринимать вызов функции-операции?
```cpp 
class Student
{
	Student& operator++();
};
// и определен объект этого класса
Student s;
// Выполняется операция
++s;
```

- будет вызван operator++() внутри класса Student, возвращаемый тип данных: ссылка на Student

13. В программе описан класс. Каким образом, компилятор будет воспринимать вызов функции-операции?
```cpp
class Student
{
	friend Student& operator ++( Student&);
};
// и определен объект этого класса
Student s;
// Выполняется операция
++s;
```

- будет вызвана дружественная функция operator++(Student&), возвращаемый тип данных: ссылка на Student

14. В программе описан класс. Каким образом, компилятор будет воспринимать вызов функции-операции?
```cpp
class Student
{
	bool operator<(Student &P);
};
// и определены объекты этого класса
Student a,b;
// Выполняется операция
cout << a < b;
```

- будет вызвана bool operator<(Student &P), возвращаемый тип данных: bool

15. В программе описан класс. Каким образом, компилятор будет воспринимать вызов функции-операции?
```cpp
class Student
{
	friend bool operator >(const Person&, Person&)
};
// и определены объекты этого класса
Student a,b;
// Выполняется операция
cout << a > b;
```

- будет вызвана дружественная функция operator >(const Person&, Person&), возвращаемый тип данных: bool