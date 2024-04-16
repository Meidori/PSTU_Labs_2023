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