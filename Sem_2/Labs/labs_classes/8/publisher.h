#pragma once
#include <iostream>
#include <string>

#include "object.h"


class Publisher : public Object {
public:
    Publisher(std::string name = "", std::string author = "") {
        this -> name = name;
        this -> author = author;
    }


    Publisher(const Publisher& publisher) {
        name = publisher.name;
        author = publisher.author;
    }


    ~Publisher() {}


    void set_name(std::string name) {
        this -> name = name;
    }


    void set_author(std::string author) {
        this -> author = author;
    }


    std::string get_name() {
        return name;
    }


    std::string get_author() {
        return author; 
    }


    Publisher& operator = (const Publisher& publisher) {
        name = publisher.name;
        author = publisher.author;
        return *this;
    }


    void print() {
        std::cout << "Название: " << name << std::endl;
        std::cout << "Автор: " << author << std::endl;
    }


    void input() {
        std::cout << "Введие навзание:" << std::endl;
        std::cin >> name;
        std::cout << "Введие автора:" << std::endl;
        std::cin >> author;
    }


    virtual void handle_event(const Event& event) {
        if (event.event_type == event_message) {
            switch (event.command) {
                case command_print_elems_info:std::cout << "Name: " << get_name() << std::endl;
                break;
            }
        }
    }

protected:
    std::string name;
    std::string author;
};