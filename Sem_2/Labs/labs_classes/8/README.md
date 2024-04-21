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

<image src = "8.png">

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

1. Что такое класс-группа? Привести примеры таких классов.

- Класс-группа - это группа объектов, которые имеют общие свойства или методы. Примерами таких классов могут быть классы автомобилей (с общими свойствами типа двигателя, количества колес и т. д.), классы животных (с общими свойствами типа питания, характера и т. д.) и т. д.

2. Привести пример описания класса-группы Список (List).

-   ```cpp
    class List {
    private:
        int* array;
        int size;
    public:
        List();  // конструктор без параметров
        List(int);  // конструктор с параметром (выделяет память под массив указанного размера)
        List(const List&);  // конструктор копирования
        ~List();  // деструктор
        void viewElements();  // метод для просмотра элементов
    };
    ```
3. Привести пример конструктора (с параметром, без параметров, копирования) для класса-группы Список.

-   ```cpp
    List() - конструктор без параметров
    List(int) - конструктор с параметром (выделяет память под массив указанного размера)
    List(const List&) - конструктор копирования
    ```
4. Привести пример деструктора для класса-группы Список.

-   ```cpp
    List::~List() {
    delete [] array;
    }
    ```

5. Привести пример метода для просмотра элементов для класса-группы Список.

-   ```cpp
    void List::viewElements() {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    }
    ```

6. Какой вид иерархии дает группа?

- Группа дает вид иерархии их сотрудничества и взаимодействия между участниками.

7. Почему во главе иерархии классов, содержащихся в группе объектов должен находиться абстрактный класс?

- Абстрактный класс находится во главе иерархии, чтобы определить общие свойства и методы для всех классов в данной иерархии, обеспечивая единообразие и структуру.

8. Что такое событие? Для чего используются события?

- Событие – это происшествие или изменение состояния, которое может быть обработано программой. События используются для сигнализации о каких-либо ситуациях или действиях, например, нажатие кнопки, изменение данных и т.д.

9. Какие характеристики должно иметь событие-сообщение?

- Событие-сообщение должно иметь описательное название, точное время и место происшествия, предоставлять достаточную информацию для понимания ситуации и быть доступным для обработки или реагирования.

10. Привести пример структуры, описывающей событие.

-   ```cpp
    struct Event {
        string name;
        string location;
        string date;
        string description;
        int maxAttendees;
        bool isCancelled;
    };

    // Пример использования:
    Event concert;
    concert.name = "Rock Festival";
    concert.location = "Central Park";
    concert.date = "October 15, 2022";
    concert.description = "A day full of rock music and fun activities";
    concert.maxAttendees = 5000;
    concert.isCancelled = false;
    ```

11. Задана структура события. Какие значения, и в каких случаях присваиваются полю what?
```cpp
struct TEvent
{
	int what;
	union
	{
		MouseEventType mouse;
		KeyDownEvent keyDown;
		MessageEvent message;
	}
};
```

- В данной структуре поле "what" предназначено для указания типа события. Значения, которые могут быть присвоены полю "what", зависят от того, какое событие произошло. Например, если произошло событие с мышью(mouse event), то полю "what" может быть присвоено значение, индицирующее это событие; если произошло событие нажатия клавиши(key down event), то полю "what" будет присвоено соответствующее значение для этого события. Таким образом, значение поля "what" будет зависеть от типа события, которое произошло.

12. Задана структура события. Какие значения, и в каких случаях присваиваются полю command?
```cpp
struct TEvent
{
	int what; // тип события
	union
	{
		int command; // код комманды
		struct // параметры команды
		{
			int message;
			int a;
		};
	};
};
```

- Поле command присваивается в случае, когда тип события (поле what) указывает на то, что это командное событие. В этом случае поле command содержит код команды, который указывает, какая именно команда должна быть выполнена.

13. Задана структура события. Для чего используются поля a и message?
```cpp
struct TEvent
{
	int what; // тип события
	union
	{
		int command; // код комманды
		struct // параметры команды
		{
			int message;
			int a;
		};
	};
};
```

- Поля message и a используются как параметры команды. Когда тип события указывает на то, что это командное событие, поля message и a используются для передачи информации, необходимой для выполнения конкретной команды. Например, если команда - это отправка сообщения, то поле message может содержать ID сообщения, а поле a может содержать дополнительные данные для этого сообщения.

14. Какие методы необходимы для организации обработки сообщений?

- Для организации обработки сообщений необходимы методы для создания, отправки, обработки и удаления сообщений. Эти методы могут включать в себя функции для создания сообщения, передачи сообщения в очередь сообщений, обработки сообщений в главном цикле обработки событий и очистки обработанных сообщений.

15. Какой вид имеет главный цикл обработки событий-сообщений?

- Главный цикл обработки событий-сообщений обычно имеет вид бесконечного цикла, в котором происходит постоянная проверка наличия новых сообщений в очереди сообщений и их обработка.

16. Какую функцию выполняет метод ClearEvent()? Каким образом?

- Метод ClearEvent() выполняет функцию очистки обработанных сообщений из очереди сообщений. Он удаляет сообщение из очереди после его обработки.

17. Какую функцию выполняет метод HandleEvent()? Каким образом?

- Метод HandleEvent() выполняет функцию обработки полученных сообщений из очереди сообщений. Этот метод может содержать логику обработки различных типов сообщений и выполнение соответствующих действий.

18. Какую функцию выполняет метод GetEvent()?

- Метод GetEvent() выполняет функцию получения нового сообщения из очереди сообщений для последующей обработки. Он извлекает сообщение из очереди и возвращает его для обработки.

19. Для чего используется поле EndState? Какой класс (объект) содержит это поле?

- Поле EndState используется для определения конечного состояния объекта или процесса. Это поле может содержаться в классе, отвечающем за управление состоянием приложения, и используется для определения, когда приложение достигло своего конечного состояния.

20. Для чего используется функция Valid()?

- Функция Valid() обычно используется для проверки корректности или валидности данных, введенных пользователем или полученных из другого источника. Она может содержать логику для проверки данных на соответствие определенным условиям или критериям и возвращать булево значение (true или false) в зависимости от результата проверки.




