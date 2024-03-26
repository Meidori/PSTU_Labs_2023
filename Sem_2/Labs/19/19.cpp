#include <iostream>
#include "timing.h"
using namespace std;


class timing {
    private:
    int hours;
    int seconds;
    double mins;

    public:
    timing(int constructor_hours = 0, int constructor_seconds = 0) {
        hours = constructor_hours;
        seconds = constructor_seconds;
    }

    ~timing() {
        cout << "Объект, содержащий " << hours << " часов и " << mins << " минут, уничтожен.\n";
    }

    int minutes() {
        double mins = hours * 60 + double(seconds) / 60;
        return mins;
    }

    void show() {
        cout << hours << " часа(ов) + " << seconds << " секунд(ы) = " << mins << " минут.\n";
    }
};


int main() {
    int hours, mins;
    cout << "Введите часы и минуты (целые числа): ";
    cin >> hours >> mins;
    cout << endl;

    timing time1(hours, mins);
    time1.minutes();
    time1.show();

    return 0;
}