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