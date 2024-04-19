#pragma once
#include <iostream>
#include <string>

#include "publisher.h"


class Magazine : public Publisher {
public: 
    Magazine(int pages = 0) {
        this -> pages = pages;
    }


    Magazine(const Magazine& magazine) {
        pages = magazine.pages;
    }


    ~Magazine() {}


    void set_pages(int pages) {
        this -> pages = pages;
    }


    int get_pages() {
        return pages;
    }


    Magazine operator = (const Magazine& magazine) {
        pages = magazine.pages;
        return *this;
    }


    void print() {
        std::cout << "Количество страниц: " << pages << std::endl; 
    }


    void input() {
        std::cout << "Введите количество страниц:" << std::endl;
        std::cin >> pages;
    }



protected:
    int pages;
};