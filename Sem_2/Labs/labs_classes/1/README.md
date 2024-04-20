Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 1 - классы

> Будет добавлено позже

# 2.1 Код программы

> 1.cpp
```cpp
#include <iostream>
using namespace std;


class Timing {
private:
    unsigned int hours;
    unsigned int seconds;
    double mins;


public:
    Timing(unsigned int hours = 0, unsigned int seconds = 0) {
        this -> hours = hours;
        this -> seconds = seconds;
    }


    Timing(const Timing& time) {
        hours = time.hours;
        seconds = time.seconds;
    }


    ~Timing() {
        cout << "Объект, содержащий " << hours << " часа(ов) и " << seconds << " секунд(ы), уничтожен.\n";
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

    void set_seconds(int scs) {
        seconds = scs;
    }

    void get_hours() {
        cout << hours << endl;
    }

    void get_seconds() {
        cout << seconds << endl;
    }

    void get_minutes() {
        cout << mins << endl;
    }
};


int main() {
    unsigned int hours, secs;
    cout << "Введите два целых числа: часы и секунды: ";
    cin >> hours >> secs;
    cout << endl;

    Timing time1(hours, secs);
    time1.minutes();
    time1.show();

    return 0;
}
```

# 2.2 UML

# Пример работы

```
Введите два целых числа: часы и секунды: 10 240

10 часа(ов) + 240 секунд(ы) = 604 минут.
Объект, содержащий 10 часа(ов) и 240 секунд(ы), уничтожен.
```

# Вопросы
