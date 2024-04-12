#pragma once


const int HASH_TABLE_SIZE = 100;


struct elem_of_table {
    std::string name = "";          // key
    unsigned int passport = 0;
    std::string adress = "";
    elem_of_table* ptr_to_next = nullptr;
    elem_of_table* ptr_to_first = nullptr;
    elem_of_table* ptr_to_last = nullptr;
};


struct hash_table {
    

    elem_of_table* elements = new elem_of_table[HASH_TABLE_SIZE];
    int filled_part_counter = 0;
    int collision_counter = 0;


    void init() {
        this -> elements = new elem_of_table[HASH_TABLE_SIZE];
        int filled_part_counter = 0;
        int collision_counter = 0;
    }


    unsigned int get_hash(const std::string str, int size) {        // логика hash-функции дана в варианте
        int hash = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            hash += str[i];
        }
        hash %= size;
        return abs(hash);
    }


    void add(elem_of_table* elem, int mode = 0) {
        switch (mode) {
        case 0: {
                unsigned int hash = get_hash(elem -> name, HASH_TABLE_SIZE);
                if (filled_part_counter == HASH_TABLE_SIZE) {
                    std::cout << "Вся таблица уже заполнена." << std::endl;
                    return;
                }
                if (this -> elements[hash].name != "") {
                    unsigned int tmp = hash + 1;
                    while ((this -> elements[tmp].name != "") && (tmp != hash)) {
                        tmp++;
                        if (tmp >= HASH_TABLE_SIZE) {
                            tmp = 0;
                        }
                    }
                    this -> elements[tmp].name = elem -> name;
                    this -> elements[tmp].passport = elem -> passport;
                    this -> elements[tmp].adress = elem -> adress;
                    collision_counter++;
                }
                else {
                    this -> elements[hash].name = elem -> name;
                    this -> elements[hash].passport = elem -> passport;
                    this -> elements[hash].adress = elem -> adress;
                }
                filled_part_counter++;
                break;
            }
        
        case 1: {
                unsigned int hash = get_hash(elem -> name, HASH_TABLE_SIZE);
                elem_of_table* tmp = new elem_of_table;
                *tmp = *elem;
                tmp -> ptr_to_next = nullptr;

                if (this -> elements[hash].ptr_to_first == nullptr) {
                    this -> elements[hash].ptr_to_first = tmp;
                }
                else {
                    this -> elements[hash].ptr_to_last -> ptr_to_next = tmp;
                    collision_counter++;
                }
                this -> elements[hash].ptr_to_last = tmp;
                filled_part_counter++;
                break;
            }

        default:
            break;
        }
    }


    elem_of_table get(std::string key) {
        unsigned int hash = get_hash(key, HASH_TABLE_SIZE);
        if (this -> elements[hash].name == key) {
            return this -> elements[hash];
        }
        else {
            for (int i = hash + 1; i != hash; i++) {
                if (i + 1 == HASH_TABLE_SIZE) {
                    i = 0;
                }
                if (this -> elements[i].name == key) {
                    return this -> elements[i];
                }
            }
            std::cout << "Не найдено элемента с данным ключом.\nВозвращено значение по умолчанию." << std::endl;
            elem_of_table default_value;
            return default_value;
        }
    }


    void print_hash_table(int mode = 0) {
        switch (mode) {
        case 0: {
                for (int i = 0; i < HASH_TABLE_SIZE; i++) {
                    elem_of_table data;
                    data = this -> elements[i];
                    if (data.name != "") {
                        std::cout << "Ячейка " << i + 1 << ".\n";
                        std::cout << data.name << std::endl;
                        std::cout << "Паспорт:" << data.passport << std::endl;
                        std::cout << data.adress << std::endl;
                    }
                    else {
                        std::cout << "Ячейка " << i + 1 << " пустая." <<std::endl;
                    }
                    std::cout << "---------------" << std::endl;
                    
                }
                break;
            }

        case 1: {
                for (int i = 0; i < HASH_TABLE_SIZE; i++) {
                    elem_of_table* tmp = this -> elements[i].ptr_to_first;
                    if (tmp != nullptr) {
                        std::cout << "Ячейка " << i + 1 << ".\n";              
                        while (tmp != nullptr) {
                            std::cout << tmp -> name << std::endl; 
                            std::cout << "Паспорт:" << tmp -> passport << std::endl; 
                            std::cout << tmp -> adress << std::endl;
                            tmp = tmp -> ptr_to_next;
                        }
                    }
                    else {
                        std::cout << "Ячейка " << i + 1 << " пустая." <<std::endl;
                    }
                    std::cout << "---------------" << std::endl;
                }
                break;
            }
        default:
            break;
        }
    }
};