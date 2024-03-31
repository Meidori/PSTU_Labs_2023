Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 8 вариант 5

Сформировать двоичный файл из элементов, заданной в варианте структуры, распечатать его содержимое, выполнить удаление и добавление элементов в соответствии со своим вариантом, используя для поиска удаляемых или добавляемых элементов функцию. Формирование, печать, добавление и удаление элементов оформить в виде функций. Предусмотреть сообщения об ошибках при открытии файла и выполнении операций ввода/вывода.

# 2.1 Код программы

```cpp
#include <iostream>
#include <fstream>
using namespace std;


struct Human {
    char first_name[100]{'\0'};
    char last_name[100]{'\0'};
    char surename[100]{'\0'};
    int year_of_birth;
    float height;
    float weight;

    void init() {
        cout << "Введите фамилию, имя, отчество, год рождения, рост, вес:" << endl;
        string tmp;
        
        cin >> tmp;
        for (int i = 0; i < tmp.length(); i++) {
            last_name[i] = tmp[i];
        }

        cin >> tmp;
        for (int i = 0; i < tmp.length(); i++) {
            first_name[i] = tmp[i];
        }

        cin >> tmp;
        for (int i = 0; i < tmp.length(); i++) {
            surename[i] = tmp[i];
        }
        cin >> year_of_birth;
        cin >> height;
        cin >> weight;
    }

    void show() {
        cout << "Фамилия: " << last_name << endl;
        cout << "Имя: " << first_name << endl;
        cout << "Отчество: " << surename << endl;
        cout << "Год рождения: " << year_of_birth << endl;
        cout << "Рост: " << height << endl;
        cout << "Вес: " << weight << endl;
    }
};


void create_notes(int n) {
    ofstream out("file.bin", ios::binary);
    for (int i = 0; i < n; i++) {
        Human human;
        human.init();
        if (out.is_open()) {
            out << human.last_name << endl;
            out << human.first_name << endl;
            out << human.surename << endl;
            out << human.year_of_birth << endl;
            out << human.height << endl;
            out << human.weight << endl;
        }
    }
    out.close();
}


void read_notes(int n, int k) {
    ifstream in("file.bin", ios::binary);
    for (int i = 0; i < n * k; i++) {
        string tmp;
        if (in.is_open()) {
            in >> tmp;
            cout << tmp << endl;
        }
    }
    in.close();
}


void delete_hw(int n, int &k) {
    ifstream in("file.bin", ios::binary);
    ofstream out("tmp.bin", ios::binary);
    for (int i = 0; i < n; i++) {
        Human tmp;
        in >> tmp.last_name >> tmp.first_name >> tmp.surename >> tmp.year_of_birth >> tmp.height >> tmp.weight;
        out << tmp.last_name << endl;
        out << tmp.first_name << endl;
        out << tmp.surename << endl;
        out << tmp.year_of_birth << endl;
    }
    in.close();
    out.close();
    remove("file.bin");
    rename("tmp.bin", "file.bin");
    k -= 2;
}


void add_complete_years(int n, int &k) {
    ifstream in("file.bin", ios::binary);
    ofstream out("tmp.bin", ios::binary);
    int complete_years; 
    cout << "Введите новый элемент для каждой записи - количество полных лет. Количество записей: " << n << endl;
    for (int i = 0; i < n; i++) {
        Human tmp;
        cout << "Для записи №" << i + 1 << endl;
        cin >> complete_years;
        in >> tmp.last_name >> tmp.first_name >> tmp.surename >> tmp.year_of_birth;
        out << tmp.last_name << endl;
        out << tmp.first_name << endl;
        out << tmp.surename << endl;
        out << complete_years << endl ; 
        out << tmp.year_of_birth << endl;
    }
    in.close();
    out.close();
    remove("file.bin");
    rename("tmp.bin", "file.bin");
    k += 1;
}


int main() {
    int n, k = 6;
    cout << "Введите количество записей:" << endl;
    cin >> n;

    create_notes(n);
    cout << "Файл после записи:" << endl;
    read_notes(n, k);
    
    delete_hw(n, k);
    cout << "Файл после удаления элементов со значение роста и веса:" << endl;
    read_notes(n, k);

    add_complete_years(n, k);
    cout << "Файл после добавления элемента - количество полных лет:" << endl;
    read_notes(n, k);

    return 0;
}
```

# 2.2 Блок-схема программы

<image src="images/8_2.png">

<image src="images/8_3.png">

<image src="images/8_1.png">

# Тесты

### Пример 1

```
Введите количество записей:
2
Введите фамилию, имя, отчество, год рождения, рост, вес:
Пушкин
Александр
Сергеевич
1799
165
60.5
Введите фамилию, имя, отчество, год рождения, рост, вес:
Дантес
Жорж
Шарль
1812
183.4
73.2 
Файл после записи:
Пушкин
Александр
Сергеевич
1799
165
60.5
Дантес
Жорж
Шарль
1812
183.4
73.2
Файл после удаления элементов со значение роста и веса:
Пушкин
Александр
Сергеевич
1799
Дантес
Жорж
Шарль
1812
Введите новый элемент для каждой записи - количество полных лет. Количество записей: 2
Для записи №1
37
Для записи №2
83
Файл после добавления элемента - количество полных лет:
Пушкин
Александр
Сергеевич
37
1799
Дантес
Жорж
Шарль
83
1812
```

> С разделением по входным и выходным данным:

Входные данные:

```
Введите количество записей:
2
Введите фамилию, имя, отчество, год рождения, рост, вес:
Пушкин
Александр
Сергеевич
1799
165
60.5
Введите фамилию, имя, отчество, год рождения, рост, вес:
Дантес
Жорж
Шарль
1812
183.4
73.2 

Введите новый элемент для каждой записи - количество полных лет. Количество записей: 2
Для записи №1
37
Для записи №2
83
```

Выходные данные:

```
Файл после записи:
Пушкин
Александр
Сергеевич
1799
165
60.5
Дантес
Жорж
Шарль
1812
183.4
73.2

Файл после удаления элементов со значение роста и веса:
Пушкин
Александр
Сергеевич
1799
Дантес
Жорж
Шарль
1812

Файл после добавления элемента - количество полных лет:
Пушкин
Александр
Сергеевич
37
1799
Дантес
Жорж
Шарль
83
1812
```