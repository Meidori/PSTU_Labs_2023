Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 6 вариант 5

Задана строка, состоящая из символов. Символы объединяются в слова. Слова друг от друга отделяются одним или несколькими пробелами. В конце текста ставится точка. Текст содержит не более 255 символов. Выполнить ввод строки, используя функцию Gets(s) и обработку строки в соответствии со своим вариантом.

Напечатать все слова, которые совпадают с ее первым словом.

# 2.1 Код программы

```cpp
#include <iostream>
#include <cstring>
using namespace std;


int main() {
    int space_counter = 0;               // переменная в которую мы будем записывать количество пробелов строке
    string str;
    getline(cin, str);

    str.erase(str.length() - 1);         // удаляем точку в конце строки
    
    for (char letter : str) {            // считаем количество пробелов
        if (letter == ' ') {
            space_counter++;
        }
    }

    char words[space_counter + 1][255]{'\0'};      // создаем массив, в которой мы будет располагать каждое слово посимвольно на каждую строку массива (максимальная длина слова 255)
    int line_index = 0;                            // переменная, обозначающая строку массива или номер + 1 слова
    int column_index = 0;                          // переменная, обозначаюшая столбец массива или номер + 1 символа в слове

    for (int i = 0; i < str.length(); i++) {       // записываем, в каждую строку массива слова из строки по символьно
        if (str[i] == ' ') {
            line_index++;
            column_index = 0;
        }
        else {
            words[line_index][column_index] = str[i];
            column_index++;
        }
    }

    /*
    // цикл, который выводит слова, введенные пользователем, беря их из массива words
    for (int i = 0; i < space_counter + 1; i++) {
        for (int j = 0; j < 255; j++) {
            cout << words[i][j];
        }
        cout << endl;
    }
    */

    bool flag;
    for (int i = 0; i < space_counter + 1; i++) {
        flag = true;
        for (int j = 0; j < 255; j++) {
            if (words[0][j] != words[i][j]) {
                flag = false;
            }
        }
        if (flag) {
            for (int j = 0; j < 255; j++) {
                cout << words[0][j];
            }
            cout << " ";
        }
    }

    return 0;
}
```

# 2.2 Блок-схема программы

<image src="images/6_5.png">

# Тесты

### Пример 1

Входные данные:

```
line LINE Line line end.
```

Выходные данные:

```
line line
```

### Пример 2

Входные данные:

```
no repetitions in line
```

Выходные данные:

```
no
```

### Пример 3

Входные данные:

```
fish chips fish chips windows chips fish rain
```

Выходные данные:

```
fish fish fish
```