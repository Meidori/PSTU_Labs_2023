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