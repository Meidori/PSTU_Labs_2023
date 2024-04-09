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


    int get_rubles() {
        return rubles;
    }


    int get_kopecks() {
        return kopecks;
    }


    void set_rubles(int rubles) {
        this -> rubles = rubles;
    }


    void set_kopecks(int kopecks) {
        this -> kopecks = kopecks;
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
};


std::ostream& operator <<(std::ostream& out, Money& money) {
    out << money.get_rubles() <<  "." << money.get_kopecks();
    return out;
}


std::istream& operator >>(std::istream& in, Money& money) {
    int rub, kop;
    in >> rub;
    in >> kop;
    money.set_rubles(rub);
    money.set_kopecks(kop);
    return in;
}