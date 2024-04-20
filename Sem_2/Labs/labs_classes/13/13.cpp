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