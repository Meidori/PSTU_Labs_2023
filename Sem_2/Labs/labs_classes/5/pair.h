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