#include <iostream>
using namespace std;


class timing {
private:
    unsigned int hours;
    unsigned int seconds;
    double mins;

public:
    timing(unsigned int constructor_hours = 0, unsigned int constructor_seconds = 0) {
        hours = constructor_hours;
        seconds = constructor_seconds;
    }

    ~timing() {
        cout << "Объект, содержащий " << hours << " часов и " << mins << " минут, уничтожен.\n";
    }

    int minutes() {
        mins = hours * 60 + double(seconds) / 60;
        return mins;
    }

    void show() {
        cout << hours << " часа(ов) + " << seconds << " секунд(ы) = " << mins << " минут.\n";
    }

    void set_hours(int hrs) {
        hours = hrs;
    }

    void set_minutes(int scs) {
        seconds = scs;
    }

    void get_hours() {
        cout << hours << endl;
    }

    void get_seconds() {
        cout << seconds << endl;
    }

    void get_minutes() {
        cout << minutes << endl;
    }
};


int main() {
    unsigned int hours, mins;
    cout << "Введите часы и минуты (целые числа): ";
    cin >> hours >> mins;
    cout << endl;

    timing time1(hours, mins);
    time1.minutes();
    time1.show();

    return 0;
}