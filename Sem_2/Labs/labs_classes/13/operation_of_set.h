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


