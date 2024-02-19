Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 9 вариант 5

1. Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию.
2. Выполнить задание.

Вариант: 
1. Скопировать из файла F1 в файл F2 строки, начиная с К до К+5.
2. Подсчитать количество гласных букв в файле F2.

# 2.1 Код программы

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
    ofstream file1;
    ofstream file2;

    file1.open("F1.txt");
    file2.open("F2.txt");

    if (file1.is_open() && file2.is_open()) {
        cout << "Файлы открыты." << endl; 
        cout << "Введите сколько вы хотите заполнить строк в файле: " << endl;
        int lines;
        cin >> lines;
        cout << "Введите строки: " << endl;
                
        for (int i = 0; i < lines; i++) {
            string line;
            cin >> line;
            file1 << line;
            file1 << "\n";
        }

        file1.close();
        ifstream file1;
        file1.open("F1.txt");
        
        cout << "Введите число k: " << endl;
        int k;
        cin >> k;
        string str;
        int i = 1;

        while(!file1.eof()) {
            getline(file1, str);
            if ((i >= k) && (i - k < 5)) {
                file2 << str;
                file2 << "\n";
            }
            i++;
        }

        file2.close();
        ifstream file2;
        file2.open("F2.txt");
        int vowel_counter = 0;
        char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
        char symbol;
        while(file2.get(symbol)) {
            symbol = tolower(symbol);
            for (int i = 0; i < 6; i++) {
                if (symbol == vowels[i]) {
                    vowel_counter++;
                }
            }
        }

        cout << "Гласных в файле F2.txt: " << vowel_counter << endl;
        
    }
    else {
        cout << "Файл не открыт" << endl;
    }

    file1.close();
    file2.close();

    return 0;
}
```

# 2.2 Блок-схема программы

<image src="9_5.png">

# Тесты

### Пример 1

Входные данные:

```
Введите сколько вы хотите заполнить строк в файле: 
10
Введите строки: 
asd
zxc
wqe
sad
dsa
fgh
mbm
yui
pio
dfg
Введите число k: 
3
```

Выходные данные:

```
Гласных в файле F2.txt: 3
```

F2.txt:

```
wqe
sad
dsa
fgh
mbm
```

### Пример 2

Входные данные:

```
Введите сколько вы хотите заполнить строк в файле: 
10
Введите строки: 
1
2
3
4
5
6
7
8
9
10
Введите число k: 
10
```

Выходные данные:

```
Гласных в файле F2.txt: 0
```

F2.txt: 

```
10
```

### Пример 3

Входные данные:

```
Файлы открыты.
Введите сколько вы хотите заполнить строк в файле: 
20
Введите строки: 
a
AAAAAAAAAAAAAAAAA
o
o
o
o
o
o
o
o
o
o
o
o
o
o
o
o
o
o
Введите число k: 
2
```

Выходные данные:

```
Гласных в файле F2.txt: 21
```

F2.txt: 

```
AAAAAAAAAAAAAAAAA
o
o
o
o
```