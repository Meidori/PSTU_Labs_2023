Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 10 - классы

> Будет добавлено позже

# 2.1 Код программы

> 10.cpp
```cpp
#include <iostream>
#include <string>
#include <sstream>

#include "time.h"
#include "file_operation.h"


int main() {
    int selector = -1;
    const char* file_name = "file.txt";

    while (selector != 0) {
        std::cout << "1)create_file\n2)print_file\n3)add_record\n4)add_diapason_of_records\
        \n5)delete_record\n6)delete_extra_records\n7)value_increase\n0)exit" << std::endl;

        std::cin >> selector;
        switch(selector) {
        case 0: {
            std::cout << "exit" << std::endl;
            break;
        }

        case 1: {
            create_file(file_name);
            break;
        }

        case 2: {
            print_file(file_name);
            break;
        }

        case 3: {
            Time new_record;
            int position;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> new_record;
            std::cout << "Введите позицию новой записи:" << std::endl;
            std::cin >> position;
            add_record(file_name, position, new_record);
            break;
        }

        case 4: {
            int amount_of_records, start_position;
            std::cout << "Введите количество записей и начальную позицию:" << std::endl;
            std::cin >> amount_of_records >> start_position;
            add_diapason_of_records(file_name, amount_of_records, start_position);
            break;
        }

        case 5: {
            int position;
            std::cout << "Введите позицию удаляемой записи:" << std::endl;
            std::cin >> position;
            delete_record(file_name, position);
            break;
        }

        case 6: {
            Time extra_time;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> extra_time;
            delete_extra_records(file_name, extra_time);
            break;
        }

        case 7: {
            Time target;
            int seconds;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> target;
            std::cout << "Введите секунды:" << std::endl;
            std::cin >> seconds;
            value_increase(file_name, target, seconds);
            break;
        }

        default: {
            break;
        }
        }
    }
        

    return 0;
}
```

> time.h
```cpp
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


    int get_time_in_seconds() {
        return seconds + minutes * 60;
    }


    Time operator = (const Time& time) {
        minutes = time.minutes;
        seconds = time.seconds;
        return *this;
    }


    bool operator == (const Time& time) {
        return (minutes == time.minutes && seconds == time.seconds);
    }


    bool operator != (const Time& time) {
        return (minutes != time.minutes || seconds != time.seconds);
    }


    Time operator - (int secs) {
        seconds += minutes * 60;
        seconds -= secs;
        if (seconds < 0) {
            seconds = 0;
        }
        minutes = seconds / 60;
        seconds = seconds % 60;
        return *this; 
    }


    Time operator + (int secs) {
        seconds += minutes * 60;
        seconds += secs;
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
```

> file_operation.h
```cpp
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "time.h"


int create_file(const char* file_name) {
    std::fstream file(file_name, std::ios::out | std::ios::trunc);
    if (!file) {
        return -1;
    }

    int number_of_records;
    std::cout << "number_of_records: ";
    std::cin >> number_of_records;

    Time tmp;
    std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
    for (int i = 0; i < number_of_records; i++) {
        std::cin >> tmp;
        file << tmp << std::endl;
    }

    file.close();
    return number_of_records;
}


int print_file(const char* file_name) {
    std::fstream file(file_name, std::ios::in);
    if (!file) {
        return -1;
    }

    int counter;
    std::string tmp;
    while(file >> tmp) {
        std::cout << tmp << std::endl;
        counter++;
    }

    file.close();
    return counter;
}


int delete_record(const char* file_name, int record_position) {
    std::fstream file(file_name, std::ios::in);
    std::fstream temp("tmp.txt", std::ios::out);
    if (!file) {
        return -1;
    }

    int counter = 0;
    std::string str, tmp1, tmp2;

    while(file >> str) {
        counter++;
        if (counter != record_position) {
            std::istringstream ss(str);
            std::getline(ss, tmp1, ':');
            std::getline(ss, tmp2);
            Time tmp(std::stoi(tmp1), std::stoi(tmp2));
            temp << tmp << std::endl;
        }
    }

    file.close();
    temp.close();
    remove(file_name);
    rename("tmp.txt", file_name);

    return counter;
}


int delete_extra_records(const char* file_name, Time extra_time) {
    std::fstream file(file_name, std::ios::in);
    std::fstream temp("tmp.txt", std::ios::out);
    if (!file) {
        return -1;
    }

    int counter = 0;
    std::string str, tmp1, tmp2;

    while(file >> str) {
        counter++;
        std::istringstream ss(str);
        std::getline(ss, tmp1, ':');
        std::getline(ss, tmp2);
        Time tmp(std::stoi(tmp1), std::stoi(tmp2));
        
        if (tmp.get_time_in_seconds() <= extra_time.get_time_in_seconds()) {
            temp << tmp << std::endl;
        }
    }

    file.close();
    temp.close();
    remove(file_name);
    rename("tmp.txt", file_name);

    return counter;
}


int add_record(const char* file_name, int record_position, Time new_record) {
    std::fstream file(file_name, std::ios::in);
    std::fstream temp("tmp.txt", std::ios::out);
    if (!file) {
        return -1;
    }

    std::string str, tmp1, tmp2;
    int counter = 0, index = 0;
    while(file >> str) {
        index++;
        if (index == record_position) {
            temp << new_record << std::endl;
            counter++;
        }
        std::istringstream ss(str);
        std::getline(ss, tmp1, ':');
        std::getline(ss, tmp2);
        Time tmp(std::stoi(tmp1), std::stoi(tmp2));
        temp << tmp << std::endl;
    }

    if (index < record_position) {
        temp << new_record << std::endl;
        counter++;
    }

    file.close();
    temp.close();
    remove(file_name);
    rename("tmp.txt", file_name);

    return counter;
}


int add_diapason_of_records(const char* file_name, int amount_of_records, int start_position) {
    std::fstream file(file_name, std::ios::in);
    std::fstream temp("tmp.txt", std::ios::out);
    if (!file) {
        return -1;
    }

    std::string str, tmp1, tmp2;
    int counter = 0, index = 0;
    while(file >> str) {
        index++;
        if (index == start_position) {
            for (int i = 0; i < amount_of_records; i++) {
                Time new_record;
                std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
                std::cin >> new_record;
                temp << new_record << std::endl;
                counter++;
            } 
        }
        std::istringstream ss(str);
        std::getline(ss, tmp1, ':');
        std::getline(ss, tmp2);
        Time tmp(std::stoi(tmp1), std::stoi(tmp2));
        temp << tmp << std::endl;
    }

    for (int i = counter; i < amount_of_records; i++) {
        Time new_record;
        std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
        std::cin >> new_record;
        temp << new_record << std::endl;
        counter++;
    }

    file.close();
    temp.close();
    remove(file_name);
    rename("tmp.txt", file_name);

    return counter;
}


int value_increase(const char* file_name, Time target, int seconds) {
    std::fstream file(file_name, std::ios::in);
    std::fstream temp("tmp.txt", std::ios::out);
    if (!file) {
        return -1;
    }

    std::string str, tmp1, tmp2;
    int counter = 0;
    while(file >> str) {
        counter++;
        std::istringstream ss(str);
        std::getline(ss, tmp1, ':');
        std::getline(ss, tmp2);
        Time tmp(std::stoi(tmp1), std::stoi(tmp2));
        if (tmp == target) {
            tmp = tmp + seconds;
            temp << tmp << std::endl;
        }
        else {
            temp << tmp << std::endl;
        }
    }

    file.close();
    temp.close();
    remove(file_name);
    rename("tmp.txt", file_name);
    
    return counter;
}
```

# 2.2 UML

<image src = "10.png">

# Пример работы

```
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records        
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
1
number_of_records: 7
Введите время (минуты и секунды - целые числа):
10 230
42 246
23 65
45 345
34 45
3 30
100 5
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records        
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
13:50
46:6
24:5
50:45
34:45
3:30
100:5
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
3
Введите время (минуты и секунды - целые числа):
10 10
Введите позицию новой записи:
4
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
13:50
46:6
24:5
10:10
50:45
34:45
3:30
100:5
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
4
Введите количество записей и начальную позицию:
2
1
Введите время (минуты и секунды - целые числа):
10 120
Введите время (минуты и секунды - целые числа):
20 230
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
12:0
23:50
13:50
46:6
24:5
10:10
50:45
34:45
3:30
100:5
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
5
Введите позицию удаляемой записи:
7
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
6
Введите время (минуты и секунды - целые числа):
40 0
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
12:0
23:50
13:50
24:5
10:10
34:45
3:30
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
7
Введите время (минуты и секунды - целые числа):
7 7
Введите секунды:
60
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
12:0
23:50
13:50
24:5
10:10
34:45
3:30
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
7
Введите время (минуты и секунды - целые числа):
12 0
Введите секунды:
45
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
2
12:45
23:50
13:50
24:5
10:10
34:45
3:30
1)create_file
2)print_file
3)add_record
4)add_diapason_of_records
5)delete_record
6)delete_extra_records
7)value_increase
0)exit
0
exit
```

# Вопросы
