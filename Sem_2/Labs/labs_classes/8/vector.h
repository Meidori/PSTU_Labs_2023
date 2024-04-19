#pragma once
#include <iostream>

#include "object.h"
#include "publisher.h"
#include "magazine.h"


class Vector {
public:
    Vector() {
        first = new Object* [0];
        current_position = 0;
        this -> size = 0;
    }


    Vector(int size) {
        first = new Object* [size];
        current_position = 0;
        this -> size = size;
    }


    ~Vector() {
        if (first != nullptr) {
            delete[] first;
        }
        first = nullptr;
    }


    void add() {
        Object *ptr;
        int selector;
        std::cout << "Выберите объект:\n1) Печатное издание\n2) Журнал" << std::endl;
        std::cin >> selector;

        if (selector == 1) {
            Publisher *group = new Publisher;
            group -> input();
            ptr = group;

            if (current_position < size) {
                first[current_position] = ptr;
                current_position++;
            }
        }
        else if (selector == 2) {
            Magazine *group = new Magazine;
            group -> input();
            ptr = group;
            if (current_position < size) {
                first[current_position] = ptr;
                current_position++; 
            }
        }
        else {
            std::cout << "Введено неверное значение." << std::endl;
            return;
        }
    }


    void print() {
        if (current_position == 0) {
            std::cout << "Empty" << std::endl;
        }
        Object **ptr = first;
        for (int i = 0; i < current_position; i++) {
            (*ptr) -> print();
            ptr++;
        }
    }


    int operator () () {
        return current_position;
    }


    void delete_vector() {
        if (current_position == 0) {
            return;
        }
        current_position--;
    }


    void handle_event(const Event& event) {
        if (event.event_type == event_message) {
            Object **ptr = first;
            for (int i = 0; i < current_position; i++) {
                (*ptr) -> handle_event(event);
                ptr++;
            }
        }
    }

protected:
    Object** first;
    int size;
    int current_position;
};