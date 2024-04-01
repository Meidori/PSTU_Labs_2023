Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 11 вариант 5

Написать программу, в которой создаются динамические структуры и выполнить их обработку в соответствии со своим вариантом. Для каждого вариант разработать следующие функции:
1. Создание списка.
2. Добавление элемента в список (в соответствии со
своим вариантом).
3. Удаление элемента из списка (в соответствии со
своим вариантом).
4. Печать списка.
5. Запись списка в файл.
6. Уничтожение списка.
7. Восстановление списка из файла.

Записи в линейном списке содержат ключевое поле типа int. Сформировать однонаправленный список. Удалить из него К элементов, начиная с заданного номера, добавить К элементов, начиная с заданного номера.

# 2.1 Код программы

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node {
    int data;
    Node *ptr_to_next = nullptr;
};


struct List {
    Node *ptr_to_first = nullptr;
    Node *ptr_to_last = nullptr;


    void init() {
        ptr_to_first = nullptr;
        ptr_to_last = nullptr;
    }


    bool is_empty() {
        return ptr_to_first == nullptr;
    }


    int get_length() {
        if (is_empty()) {
            return 0;
        }
        else {
            Node *tmp = new Node;
            int counter = 1;
            tmp = ptr_to_first;
            while (tmp -> ptr_to_next != nullptr) {
                counter++;
                tmp = tmp -> ptr_to_next;
            }
            return counter;
        }
    }

    
    void push_back(int value) {
        Node *tmp = new Node;
        tmp -> data = value;
        if (is_empty()) {
            ptr_to_first = tmp;
            ptr_to_last = tmp;
        }
        else {
            ptr_to_last -> ptr_to_next = tmp;
            ptr_to_last = tmp;
        }
    }


    int pop(int index) {
        int list_length = get_length();
        if ((!(is_empty())) && (index < list_length) && (index >= 0)) {
            Node *tmp_cur = ptr_to_first, *tmp_prev = ptr_to_first;
            for (int i = 0; i < index; i++) {
                tmp_prev = tmp_cur;
                tmp_cur = tmp_cur -> ptr_to_next;
            }
            if (index == 0) {
                if (list_length == 1) {
                    ptr_to_first = nullptr;
                    ptr_to_last = nullptr;
                }
                else {
                    ptr_to_first = tmp_cur -> ptr_to_next;
                }
            }
            else if (index == list_length) {
                tmp_prev -> ptr_to_next = tmp_cur -> ptr_to_next;
                ptr_to_last = tmp_prev;
            }
            else {
                tmp_prev -> ptr_to_next = tmp_cur -> ptr_to_next;
            }
            int deleted_value = tmp_cur -> data;
            delete tmp_cur;
            return deleted_value;
            }
        cout << "Не удалось получить данные по данному индексу. Возвращено значение 0." << endl;
        return 0;
    }


    void add_value_by_position(int pos) {
        Node *new_node = new Node;
        Node *tmp_cur = ptr_to_first, *tmp_prev = ptr_to_first;
        int list_length = get_length();
        if (pos <= list_length + 1 && pos > 0) {
            int index = pos - 1;
            for (int i = 0; i < index; i++) {
                tmp_prev = tmp_cur;
                tmp_cur = tmp_cur -> ptr_to_next;
            }
            int value;
            cout << "Введите значение элемента:" << endl;
            cin >> value;
            new_node -> data = value;
            if (index == 0 && is_empty()) {
                ptr_to_first = new_node;
                ptr_to_last = new_node;
            }
            else if (index == 0) {
                new_node -> ptr_to_next = ptr_to_first;
                ptr_to_first = new_node;
            }
            else if (index == list_length) {
                ptr_to_last -> ptr_to_next = new_node;
                tmp_prev -> ptr_to_next = new_node;
                ptr_to_last = new_node;
            }
            else {
                tmp_prev -> ptr_to_next = new_node;
                new_node -> ptr_to_next = tmp_cur;
            }
        }
    }


    void write_in_file() {
        int list_length = get_length();
        ofstream out;
        out.open("file_11_1.txt");
        if (out.is_open()) {
            for (int i = 0; i < list_length; i++) {
                out << pop(0) << endl;
            } 
        }
        out.close();

    }


    void resotre_from_file(List list) {
        ifstream in;
        in.open("file_11_1.txt");
        int value;
        while (in >> value) {
            push_back(value);
        }
        in.close();
    }


    void show_list() {
        if (is_empty()) {
            cout << "Список пустой." << endl;
            return;
        }
        else {
            Node *tmp = ptr_to_first;
            cout << tmp -> data;
            int list_length = get_length();
            if (list_length > 1) {
                for (int i = 1; i < list_length; i++) {
                    tmp = tmp -> ptr_to_next; 
                    cout << " " << tmp -> data;
                }
            }
            cout << endl;
        }
    }
};


int main() {
    List *list_of_nums = new List;
    list_of_nums -> init();
    int number_of_values, new_value;
    cout << "Введите количество значений, которое будет содержаться в списке:" << endl;
    cin >> number_of_values;
    for (int i = 0; i < number_of_values; i++) {
        cout << "Введите значение:" << endl;
        cin >> new_value;
        list_of_nums -> push_back(new_value);
    }

    cout << "Список после заполнения:" << endl;
    list_of_nums -> show_list();

    int number_of_changes, pos;
    cout << "Введите число K - количество элементов, которые будут удалены/добавлены:" << endl;
    cin >> number_of_changes;
    cout << "Введите номер элемента, с которого нужно удалить K элементов:" << endl;
    cin >> pos;
    for (int i = 0; i < number_of_changes; i++) {
        cout << "Удаляем элемент: " << list_of_nums -> pop(pos - 1) << endl;
    }
    
    cout << "Список после удаления K элементов:" << endl;
    list_of_nums -> show_list();

    cout << "Введите номер элемента, с которого нужно добавить K элементов:" << endl;
    cin >> pos;
    for (int i = 0; i < number_of_changes; i++) {
        list_of_nums -> add_value_by_position(pos);
        pos++;
    }
    
    cout << "Список после добавления K элементов:" << endl;
    list_of_nums -> show_list();

    list_of_nums -> write_in_file();
    delete list_of_nums;
    cout << "Список записан в файл и удален из памяти." << endl;

    cout << "Содержимое файла:" << endl;
    ifstream in("file_11_1.txt");
    if (in.is_open()) {
        int x;
        while (in >> x) {
            cout << x << " ";
        }
        cout << endl;
    }
    in.close();

    List *restored_list_of_nums = new List;
    restored_list_of_nums -> init();
    cout << "Создан новый список." << endl;

    restored_list_of_nums -> resotre_from_file(*restored_list_of_nums);
    cout << "Содержимое списка, после взятия данных из файла:" << endl;
    restored_list_of_nums -> show_list();

    return 0;
}
```

# 2.2 Блок-схема программы

<image src="images/11_1_1.png">

<image src="images/11_1_2.png">

# Тесты

### Пример 1

```
Введите количество значений, которое будет содержаться в списке:
15
Введите значение:
11
Введите значение:
43
Введите значение:
23
Введите значение:
93
Введите значение:
184
Введите значение:
392
Введите значение:
23
Введите значение:
64
Введите значение:
532
Введите значение:
985
Введите значение:
346
Введите значение:
103
Введите значение:
106
Введите значение:
342
Введите значение:
396
Список после заполнения:
11 43 23 93 184 392 23 64 532 985 346 103 106 342 396
Введите число K - количество элементов, которые будут удалены/добавлены:
7
Введите номер элемента, с которого нужно удалить K элементов:
2
Удаляем элемент: 43
Удаляем элемент: 23
Удаляем элемент: 93
Удаляем элемент: 184
Удаляем элемент: 392
Удаляем элемент: 23
Удаляем элемент: 64
Список после удаления K элементов:
11 532 985 346 103 106 342 396
Введите номер элемента, с которого нужно добавить K элементов:
5
Введите значение элемента:
1
Введите значение элемента:
2
Введите значение элемента:
3
Введите значение элемента:
4
Введите значение элемента:
5
Введите значение элемента:
6
Введите значение элемента:
7
Список после добавления K элементов:
11 532 985 346 1 2 3 4 5 6 7 103 106 342 396
Список записан в файл и удален из памяти.
Содержимое файла:
11 532 985 346 1 2 3 4 5 6 7 103 106 342 396 
Создан новый список.
Содержимое списка, после взятия данных из файла:
11 532 985 346 1 2 3 4 5 6 7 103 106 342 396
```