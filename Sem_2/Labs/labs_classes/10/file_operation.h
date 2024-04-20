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