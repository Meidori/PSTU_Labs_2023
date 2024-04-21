Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 13 - классы

> Будет добавлено позже

# 2.1 Код программы

> 13.cpp
```cpp
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>

#include "time.h"
#include "operation_of_list.h"
#include "operation_of_vector.h"
#include "operation_of_set.h"



int main() {
    int size, index;


    // list:
    std::list<Time> list_of_time;
    std::cout << "Введите размер для списка: ";
    std::cin >> size;
    list_of_time = create_list(size);
    std::cout << "list_of_time:" << std::endl;
    print_list(list_of_time);

    std::cout << "Введите индекс на который будет добавлен минимальный элемент контейнера: ";
    std::cin >> index;
    list_of_time = add_min_elem(list_of_time, index);
    std::cout << "list_of_time:" << std::endl;
    print_list(list_of_time);

    std::cout << "remove_more_average:" << std::endl;
    list_of_time = remove_more_average(list_of_time);
    std::cout << "list_of_time:" << std::endl;
    print_list(list_of_time);

    std::cout << "add_max_elem_to_all:" << std::endl;
    list_of_time = add_max_elem_to_all(list_of_time);
    std::cout << "list_of_time:" << std::endl;
    print_list(list_of_time);

    
    // vector:
    std::vector<Time> vect_of_time;
    std::cout << "Введите размер для вектора: ";
    std::cin >> size;
    vect_of_time = create_vector(size);
    std::cout << "vect_of_time:" << std::endl;
    print_vector(vect_of_time);

    std::cout << "Введите индекс на который будет добавлен минимальный элемент контейнера: ";
    std::cin >> index;
    vect_of_time = add_min_elem(vect_of_time, index);
    std::cout << "vect_of_time:" << std::endl;
    print_vector(vect_of_time);

    std::cout << "remove_more_average:" << std::endl;
    vect_of_time = remove_more_average(vect_of_time);
    std::cout << "vect_of_time:" << std::endl;
    print_vector(vect_of_time);

    std::cout << "add_max_elem_to_all:" << std::endl;
    vect_of_time = add_max_elem_to_all(vect_of_time);
    std::cout << "vect_of_time:" << std::endl;
    print_vector(vect_of_time);


    // set:
    std::set<Time> set_of_time;
    std::cout << "Введите размер для множества: ";
    std::cin >> size;
    set_of_time = create_set(size);
    std::cout << "set_of_time:" << std::endl;
    print_set(set_of_time);

    std::cout << "remove_more_average:" << std::endl;
    set_of_time = remove_more_average(set_of_time);
    std::cout << "set_of_time:" << std::endl;
    print_set(set_of_time);

    std::cout << "add_max_elem_to_all:" << std::endl;
    set_of_time = add_max_elem_to_all(set_of_time);
    std::cout << "set_of_time:" << std::endl;
    print_set(set_of_time);


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


    int get_time_in_seconds() const {
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

    
    bool operator > (const Time& time) const {
        return (get_time_in_seconds() > time.get_time_in_seconds());
    }


    bool operator < (const Time& time) const {
        return (get_time_in_seconds() < time.get_time_in_seconds());
    }


    bool operator >= (const Time& time) const {
        return (get_time_in_seconds() >= time.get_time_in_seconds());
    }


    bool operator <= (const Time& time) const {
        return (get_time_in_seconds() <= time.get_time_in_seconds());
    }


    Time operator + (Time time) {
        seconds += time.minutes * 60 + time.seconds + minutes * 60;
        minutes = seconds / 60;
        seconds = seconds % 60;
        return *this; 
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

> operation_of_list.h
```cpp
#pragma once
#include <iostream>
#include <list>
#include <algorithm>

#include "time.h"


std::list<Time> create_list(int amount_of_records) {
    Time time;
    std::list<Time> list_of_time;
    for (int i = 0; i < amount_of_records; i++) {
        std::cout << "Введите время (минуты и секунды - целые числа): ";
        std::cin >> time;
        list_of_time.push_back(time);
    }
    return list_of_time;
}


void print_list(std::list<Time> list_of_time) {
    for (Time i : list_of_time) {
        std::cout << i << std::endl;
    }
}


Time get_max(std::list<Time> list_of_time) {
    Time max_time;
    for (Time i : list_of_time) {
        if (i > max_time) {
            max_time = i;
        }
    }
    return max_time;
}


Time get_min(std::list<Time> list_of_time) {
    Time min_time = list_of_time.front();
    for (Time i : list_of_time) {
        if (i < min_time) {
            min_time = i;
        }
    }
    return min_time;
}


std::list<Time> add_max_elem_to_all(std::list<Time> list_of_time) {
    Time max_time = get_max(list_of_time);
    std::transform(list_of_time.begin(), list_of_time.end(), list_of_time.begin(), [max_time](Time i){return i + max_time;});
    return list_of_time;
}


std::list<Time> add_min_elem(std::list<Time> list_of_time, int index) {
    std::list<Time> result;
    Time min_time = get_min(list_of_time);
    std::list<Time>::iterator it = list_of_time.begin();
    std::advance(it, index);
    
    std::copy(list_of_time.begin(), it, std::back_inserter(result));
    result.push_back(min_time);
    std::copy(it, list_of_time.end(), std::back_inserter(result));

    return result;    
}


std::list<Time> remove_more_average(std::list<Time> list_of_time) {
    double avg_seconds = 0;
    for (Time i : list_of_time) {
        avg_seconds += i.get_time_in_seconds();
    }
    avg_seconds = avg_seconds / list_of_time.size();

    list_of_time.remove_if([avg_seconds](Time i){return i.get_time_in_seconds() > avg_seconds;});
    return list_of_time;
}
```

> operation_of_set.h
```cpp
#pragma once
#include <iostream>
#include <set>
#include <algorithm>

#include "time.h"


std::set<Time> create_set(int amount_of_records) {
    Time time;
    std::set<Time> set_of_time;
    for (int i = 0; i < amount_of_records; i++) {
        std::cout << "Введите время (минуты и секунды - целые числа): ";
        std::cin >> time;
        set_of_time.insert(time);
    }
    return set_of_time;
}


void print_set(std::set<Time> set_of_time) {
    for (Time i : set_of_time) {
        std::cout << i << std::endl;
    }
}


Time get_max(std::set<Time> set_of_time) {
    return *std::max_element(set_of_time.begin(), set_of_time.end());
}


Time get_min(std::set<Time> set_of_time) {
    return *std::min_element(set_of_time.begin(), set_of_time.end());
}


std::set<Time> add_max_elem_to_all(std::set<Time>& set_of_time) {
    std::set<Time> result;
    Time max_time = get_max(set_of_time);
    for (Time i : set_of_time) {
        result.insert(i + max_time);
    }
    return result;
}


std::set<Time> remove_more_average(const std::set<Time>& set_of_time) {
    double avg_seconds = 0;
    for (const Time& i : set_of_time) {
        avg_seconds += i.get_time_in_seconds();
    }
    avg_seconds /= set_of_time.size();

    std::set<Time> result;
    for (const Time& i : set_of_time) {
        if (!(i.get_time_in_seconds() > avg_seconds)) {
            result.insert(i);
        }
    }
    return result;
}
```

> operation_of_vector.h
```cpp
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "time.h"


std::vector<Time> create_vector(int amount_of_records) {
    Time time;
    std::vector<Time> vector_of_time;
    for (int i = 0; i < amount_of_records; i++) {
        std::cout << "Введите время (минуты и секунды - целые числа): ";
        std::cin >> time;
        vector_of_time.push_back(time);
    }
    return vector_of_time;
}


void print_vector(std::vector<Time> vector_of_time) {
    for (Time i : vector_of_time) {
        std::cout << i << std::endl;
    }
}


Time get_max(std::vector<Time> vector_of_time) {
    Time max_time;
    for (Time i : vector_of_time) {
        if (i > max_time) {
            max_time = i;
        }
    }
    return max_time;
}


Time get_min(std::vector<Time> vector_of_time) {
    Time min_time = vector_of_time.front();
    for (Time i : vector_of_time) {
        if (i < min_time) {
            min_time = i;
        }
    }
    return min_time;
}


std::vector<Time> add_max_elem_to_all(std::vector<Time> vector_of_time) {
    Time max_time = get_max(vector_of_time);
    std::transform(vector_of_time.begin(), vector_of_time.end(), vector_of_time.begin(), [max_time](Time i){return i + max_time;});
    return vector_of_time;
}


std::vector<Time> add_min_elem(std::vector<Time> vector_of_time, int index) {
    std::vector<Time> result;
    Time min_time = get_min(vector_of_time);
    std::vector<Time>::iterator it = vector_of_time.begin();
    std::advance(it, index);
    
    std::copy(vector_of_time.begin(), it, std::back_inserter(result));
    result.push_back(min_time);
    std::copy(it, vector_of_time.end(), std::back_inserter(result));

    return result;    
}


std::vector<Time> remove_more_average(std::vector<Time> vector_of_time) {
    double avg_seconds = 0;
    for (Time i : vector_of_time) {
        avg_seconds += i.get_time_in_seconds();
    }
    avg_seconds = avg_seconds / vector_of_time.size();

    vector_of_time.erase(std::remove_if(vector_of_time.begin(), vector_of_time.end(), [avg_seconds](Time i){return i.get_time_in_seconds() > avg_seconds;}), vector_of_time.end());

    return vector_of_time;
}
```

# 2.2 UML

<image src = "13.png">

# Пример работы

```
Введите размер для списка: 4
Введите время (минуты и секунды - целые числа): 10 20
Введите время (минуты и секунды - целые числа): 30 40
Введите время (минуты и секунды - целые числа): 50 60
Введите время (минуты и секунды - целые числа): 70 80
list_of_time:
10:20
30:40
51:0
71:20
Введите индекс на который будет добавлен минимальный элемент контейнера: 3
list_of_time:       
10:20
30:40
51:0
10:20
71:20
remove_more_average:
list_of_time:       
10:20
30:40
10:20
add_max_elem_to_all:
list_of_time:
41:0
61:20
41:0
Введите размер для вектора: 7
Введите время (минуты и секунды - целые числа): 10 1
Введите время (минуты и секунды - целые числа): 10 2
Введите время (минуты и секунды - целые числа): 10 3
Введите время (минуты и секунды - целые числа): 10 4
Введите время (минуты и секунды - целые числа): 10 5
Введите время (минуты и секунды - целые числа): 10 6
Введите время (минуты и секунды - целые числа): 10 7
vect_of_time:
10:1
10:2
10:3
10:4
10:5
10:6
10:7
Введите индекс на который будет добавлен минимальный элемент контейнера: 6
vect_of_time:
10:1
10:2
10:3
10:4
10:5
10:6
10:1
10:7
remove_more_average:
vect_of_time:
10:1
10:2
10:3
10:1
add_max_elem_to_all:
vect_of_time:
20:4
20:5
20:6
20:4
Введите размер для множества: 2
Введите время (минуты и секунды - целые числа): 10 40
Введите время (минуты и секунды - целые числа): 1000 10
set_of_time:
10:40
1000:10
remove_more_average:
set_of_time:
10:40
add_max_elem_to_all:
set_of_time:
21:20
```

# Вопросы
