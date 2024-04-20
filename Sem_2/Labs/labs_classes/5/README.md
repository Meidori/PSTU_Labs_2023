Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 5 - классы

> Будет добавлено позже

# 2.1 Код программы

> 5.cpp
```cpp
#include <iostream>

#include "object.h"
#include "pair.h"
#include "money.h"
#include "vector.h"


int main() {
    /*
    Pair pair;
    std::cin >> pair;
    std::cout << pair << std::endl;

    Object *ptr = &pair;
    ptr -> print(); 
    */

    /*
    Money money; 
    std::cin >> money;
    std::cout << money << std::endl;
    Object *ptr = &money;
    ptr -> print();  
    */
    
    Vector vect(5);
    
    Pair pair;
    std::cout << "Введите два целых числа:" << std::endl;
    std::cin >> pair;

    Money money;
    std::cout << "Введите два целых числа - рубли и копейки:" << std::endl;
    std::cin >> money;

    Object *ptr = &pair;
    vect.add(ptr);
    ptr = &money;
    vect.add(ptr);

    std::cout << "Содержимое вектора:" << std::endl;
    std::cout << vect;

    return 0;
}
```

> object.h
```cpp
#pragma once
#include <iostream>


class Object {
public:
    Object () {};
    ~Object () {};
    virtual void print() = 0;
};
```

> pair.h
```cpp
#pragma once
#include <iostream>
#include "object.h"


class Pair : public Object {
protected:
    int first;
    int second;


public:
    Pair(int first = 0, int second = 0) {
        this -> first = first;
        this -> second = second;
    };


    Pair(const Pair& pair) {
        first = pair.first;
        second = pair.second;
    }


    virtual ~Pair() {};


    void set_first(int first) {
        this -> first = first;
    } 
    
    
    void set_second(int second) {
        this -> second = second;
    }


    int get_first() {
        return first;
    }


    int get_second() {
        return second;
    }


    void print() {
        std::cout << first << " " << second << std::endl;
    }


    Pair& operator =(const Pair& pair) {
        if (&pair == this) {
            return *this;
        }
        first = pair.first;
        second = pair.second;
        return *this;
    }


    Pair& operator +(const Pair& pair) {
        first += pair.first;
        second += pair.second;
        return *this;
    }


    friend std::ostream& operator <<(std::ostream& out, Pair& pair);
    friend std::istream& operator >>(std::istream& in, Pair& pair);
};


std::ostream& operator <<(std::ostream& out, Pair& pair) {
    out << pair.get_first() <<  " " << pair.get_second();
    return out;
}


std::istream& operator >>(std::istream& in, Pair& pair) {
    int fst, snd;
    in >> fst;
    in >> snd;
    pair.set_first(fst);
    pair.set_second(snd);
    return in;
}
```

> money.h
```cpp
#pragma once
#include <iostream>
#include "pair.h"


class Money : public Pair {
protected:
    int rubles;
    int kopecks;


public:
    Money(int rubles = 0, int kopecks = 0) {
        this -> kopecks = kopecks % 100;
        this -> rubles = rubles + kopecks / 100;
    }


    Money(const Money& money) {
        rubles = money.rubles;
        kopecks = money.kopecks;
    }


    ~Money() {}


    void print() {
        std::cout << rubles << " рублей, " << kopecks << " копеек." << std::endl; 
    }


    int get_first() {
        return rubles;
    }


    int get_second() {
        return kopecks;
    }


    void set_first(int rubles) {
        this -> rubles = rubles;
    }


    void set_second(int kopecks) {
        this -> kopecks = kopecks;
    }


    Money operator =(const Money& money) {
        if (&money == this) {
            return *this;
        }
        rubles = money.rubles;
        kopecks = money.kopecks;
        return *this;
    }


    Money operator +(const Money& money) {
        kopecks += money.kopecks;
        rubles = rubles + money.rubles + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, kopecks);
    }


    Money operator -(const Money& money) {
        kopecks -= money.kopecks;
        rubles = rubles - money.rubles + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, abs(kopecks));
    }


    Money operator *(const int& multiplier) {
        kopecks *= multiplier;
        rubles = rubles * multiplier + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, kopecks);
    }


    friend std::ostream& operator <<(std::ostream& out, Money& money);
    friend std::istream& operator >>(std::istream& in, Money& money);
};


std::ostream& operator <<(std::ostream& out, Money& money) {
    out << money.get_first() <<  " рублей и " << money.get_second() << " копеек.";
    return out;
}


std::istream& operator >>(std::istream& in, Money& money) {
    int rub, kop;
    in >> rub;
    in >> kop;
    rub += kop / 100;
    kop = kop % 100;
    money.set_first(rub);
    money.set_second(kop);
    return in;
}
```

> vector.h
```cpp
#pragma once
#include "pair.h"


class Vector {
public:
    Vector() {
        vect = 0;
        size = 0;
        current_position = 0;
    }


    Vector(int size) {
        vect = new Object* [size];
        this -> size = size;
        current_position = 0;
    }


    ~Vector() {
        if (vect != 0) {
            delete vect;
        }
    }


    void add(Object* ptr) {
        if (current_position < size) {
            vect[current_position] = ptr;
            current_position++;
        }
    }


    friend std::ostream& operator <<(std::ostream& out, const Vector& v);


private:
    Object** vect;
    int size;
    int current_position;
};


std::ostream& operator <<(std::ostream& out, const Vector& v) {
    if(v.size == 0) {
        out << "Вектор пустой." << std::endl;
    }
    Object **ptr = v.vect;
    for(int i = 0; i < v.current_position; i++) {
        (*ptr) -> print();
        ptr++;
    }
    return out;
}
```

# 2.2 UML

# Пример работы

```
Введите два целых числа:
5 49
Введите два целых числа - рубли и копейки:
7 79
Содержимое вектора: 
5 49
7 рублей, 79 копеек.
```

# Вопросы
