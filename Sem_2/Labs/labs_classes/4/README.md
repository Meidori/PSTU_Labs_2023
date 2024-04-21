Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 4 - классы

> Будет добавлено позже

# 2.1 Код программы

> 4.cpp
```cpp
#include <iostream>
#include "money.h"
#include "pair.h"


using std::cin, std::cout, std::endl;


int main() {
    // Работа с классом Pair:
    Pair pair1;
    cout << "Введите два целых числа:" << endl;
    cin >> pair1;
    cout << "Объект pair1: " << pair1 << endl;

    Pair pair2;
    cout << "Введите два целых числа:" << endl;
    cin >> pair2;
    cout << "Объект pair2: " << pair2 << endl;

    Pair pair3 = pair1 + pair2;
    cout << "Объект pair3 = pair1 + pair2: " << pair3 << endl;


    // Работа с классом Money:
    Money money1;
    cout << "Введите два целых числа - рубли и копейки:" << endl;
    cin >> money1;
    cout << "Объект money1: " << money1 << endl;

    cout << "Введите два целых числа - рубли и копейки:" << endl;
    int rub, cop; 
    cin >> rub >> cop;
    Money money2(rub, cop);
    cout << "Объект money2, созданный конструктором money2(" << rub << ", " << cop << "): " << money2 << endl;

    Pair pair4 = money2;
    cout << "Принцип подстановки - pair4 = money2: " << pair4 << endl;

    return 0;
}
```

> pair.h
```cpp
#pragma once
#include <iostream>


class Pair {
private:
    int first;
    int second;


public:
    Pair(int first = 0, int second = 0) {
        this -> first = first;
        this -> second = second;
    }


    Pair(const Pair& pair) {
        first = pair.first;
        second = pair.second;
    }


    virtual ~Pair() {}
    

    virtual void set_first(int f) {
        first = f;
    }


    virtual void set_second(int s) {
        second = s;
    }


    virtual int get_first() {
        return first;
    }


    virtual int get_second() {
        return second;
    }


    Pair operator =(const Pair& pair) {
        if (&pair == this) {
            return *this;
        }
        first = pair.first;
        second = pair.second;
        return *this;
    }


    Pair operator +(const Pair& pair) {
        first += pair.first;
        second += pair.second;
        return Pair(first, second);
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
private:
    int rubles;
    int kopecks;


public:
    Money(int rubles = 0, int kopecks = 0) : Pair(rubles, kopecks) {
        this -> kopecks = kopecks % 100;
        this -> rubles = rubles + kopecks / 100;
    }


    Money(const Money& money) {
        rubles = money.rubles;
        kopecks = money.kopecks;
    }


    ~Money() {}


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


    Pair operator =(const Money& money) {
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
    out << money.get_first() <<  " рублей(я) и " << money.get_second() << " копеек(ки).";
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

# 2.2 UML

<image src = "4.png">

# Пример работы

```
Введите два целых числа:
10 330
Объект pair1: 10 330    
Введите два целых числа:
60 45
Объект pair2: 60 45
Объект pair3 = pair1 + pair2: 70 375      
Введите два целых числа - рубли и копейки:
10 70
Объект money1: 10 рублей(я) и 70 копеек(ки).
Введите два целых числа - рубли и копейки:  
900 35
Объект money2, созданный конструктором money2(900, 35): 900 рублей(я) и 35 копеек(ки).
Принцип подстановки - pair4 = money2: 900 35
```

# Вопросы
