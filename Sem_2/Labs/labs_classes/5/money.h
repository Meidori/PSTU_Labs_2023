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