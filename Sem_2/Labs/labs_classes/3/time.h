#pragma once


class Time {
private:
    int minutes;
    int seconds;

public:
    Time(int mins = 0, int secs = 0) {
        minutes = mins;
        seconds = secs;
        if (seconds >= 60) {
            int extra_mins = seconds / 60;
            seconds -= extra_mins * 60;
            minutes += extra_mins;
        }
    }


    int get_mins() {
        return minutes;
    }


    int get_secs() {
        return seconds;
    }


    void set_mins(int mins) {
        minutes = mins;
    }


    void set_secs(int secs) {
        seconds = secs;
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


    bool operator ==(const Time& time) const {
        return (seconds == time.seconds) && (minutes == time.minutes);
    }


    bool operator !=(const Time& time) const {
        return (seconds != time.seconds) && (minutes != time.minutes);
    }
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
