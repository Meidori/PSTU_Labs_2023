Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

Лабораторная работа № 8 - классы

> Будет добавлено позже

# 2.1 Код программы

> 8.cpp
```cpp
#include <iostream>

#include "dialoge.h"

int main() {
    Dialoge dialoge;
    dialoge.execute();

    return 0;
}
```

> vector.h
```cpp
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
```

> object.h
```cpp
#pragma once
#include <iostream>

#include "event.h"


class Object {
public:
    Object() {};
    virtual void print() = 0;
    virtual void input() = 0;
    virtual ~Object() {};
    virtual void handle_event(const Event& event) = 0;
};
```

> publisher.h
```cpp
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
```

> magazine.h
```cpp
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
```

> event.h
```cpp
#pragma once


const int event_nothing = 0;
const int event_message = 100;
const int command_add = 1;
const int command_delete = 2;
const int command_print_elems_info = 3;
const int command_print_elems_names = 4;
const int command_make_group = 6;
const int command_quit = 101;


class Event {
public:
    int event_type;
    union {
        int command;
        struct {
            int message;
            int parameter;
        };
    };
};
```

> dialoge.h
```cpp
#pragma once
#include <iostream>
#include <string>

#include "vector.h"
#include "event.h"

class Dialoge : public Vector {
public:
    Dialoge() {
        end_state = 0;
    }


    virtual ~Dialoge() {}


    virtual void get_event(Event &event) {
        std::string operation_codes = "m+-szq";
        std::string selector;
        std::string parametr;

        char code;
        std::cout << ">";
        std::cin >> selector;
        code = selector[0];

        if (operation_codes.find(code) >= 0) {
            event.event_type = event_message;
            switch (code) {
            case 'm':
                event.command = command_make_group;
                break;
            
            case '+':
                event.command = command_add;
                break;

            case '-':
                event.command = command_delete;
                break;

            case 's':
                event.command = command_print_elems_info;
                break;

            case 'z':
                event.command = command_print_elems_names;
                break;

            case 'q':
                event.command = command_quit;
                break;
            
            default:
                break;
            }

            if (size > 1) {
                parametr = selector.substr(1, selector.length() - 1);
                int parametr_code = atoi(parametr.c_str());
                event.parameter = parametr_code;
            }
        }
        else {
            event.event_type = event_nothing;
        }
    }


    virtual int execute() {
        Event event;
        do {
            end_state = 0;
            get_event(event);
            handle_event(event);
        }
        while(!valid());
        return end_state;
    }


    int valid() {
        if (end_state == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }


    virtual void clear_event(Event& event) {
        event.event_type = event_nothing;
    }

    
    void end_exec() {
        end_state = 1;
    }


    virtual void handle_event(Event &event) {
        if (event.event_type == event_message) {
            switch (event.command) {
                case command_make_group:
                    size = event.parameter;
                    first = new Object* [size];
                    current_position = 0;
                    clear_event(event);
                    break;

                case command_add:
                    add();
                    clear_event(event);
                    break;

                case command_delete:
                    delete_vector();
                    clear_event(event);
                    break;

                case command_print_elems_info:
                    print();
                    clear_event(event);
                    break;

                case command_print_elems_names:
                    print();
                    clear_event(event);
                    break;

                case command_quit:
                    end_exec();
                    clear_event(event);
                    break;

                default:
                    Vector::handle_event(event);
                    break;
            }
        }
    }

protected:
    int end_state;
};
```

# 2.2 UML

# Пример работы

```
>m
>+
Выберите объект:   
1) Печатное издание
2) Журнал
1
Введие навзание:
Name1
Введие автора:
Author1
>+
Выберите объект:   
1) Печатное издание
2) Журнал
2
Введите количество страниц:
240
>s
Название: Name1        
Автор: Author1
Количество страниц: 240
>z
Название: Name1
Автор: Author1
Количество страниц: 240
>-
>s
Название: Name1
Автор: Author1
>-
>s
Empty
>q
```

# Вопросы
