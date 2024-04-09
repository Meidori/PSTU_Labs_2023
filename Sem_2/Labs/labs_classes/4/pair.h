#pragma once
#include <iostream>


class Pair {
private:
    int first;
    int second;


public:
    Pair (int first = 0, int second = 0) {
        this -> first = first;
        this -> second = second;
    }
    

    void set_first(int f) {
        first = f;
    }


    void set_second(int s) {
        second = s;
    }


    int get_first() {
        return first;
    }


    int get_second() {
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
};


std::ostream& operator <<(std::ostream& out, Pair& pair) {
    out << pair.get_first() <<  "\t" << pair.get_second();
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