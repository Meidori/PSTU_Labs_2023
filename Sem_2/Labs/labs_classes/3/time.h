#pragma once


class Time {
private:
    int minutes;
    int seconds;

public:
    Time(int mins, int secs) {
        minutes = mins;
        seconds = secs;
    }
};