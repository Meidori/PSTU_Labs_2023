Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 2

Задача 7: Заполнить двумерный массив, все элементы выше главной диагонали равны 0, но элементы стоящие на главной диагонали и стоящие паралелльно этой диагонали заполняется одинаковыми цифрами. до 9, потом снова 1

```
1 0 0 0 0
2 1 0 0 0
3 2 1 0 0
4 3 2 1 0
5 4 3 2 1
```

# 2.1 Код программы

```cpp
#include <iostream>
using namespace std;


int main() {
    const int n = 5;
    int matrix[n][n];
    int tmp;

    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                tmp += 1;
                if (tmp == 10) {
                    tmp = 1;
                }
                matrix[j][i] = tmp;
            }
            else {
                matrix[j][i] = 0;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
```

# 2.2 Блок-схема программы

<image src="images/2.png">

# 3 Тесты

### Пример 1.

Входные данные:

`const int n = 5;`

Выходные данные:

```
1 0 0 0 0 
2 1 0 0 0 
3 2 1 0 0 
4 3 2 1 0 
5 4 3 2 1 
```

### Пример 2.

Входные данные:

`const int n = 7;`

Выходные данные:

```
1 0 0 0 0 0 0 
2 1 0 0 0 0 0 
3 2 1 0 0 0 0 
4 3 2 1 0 0 0 
5 4 3 2 1 0 0 
6 5 4 3 2 1 0 
7 6 5 4 3 2 1 
```

### Пример 3.

Входные данные:

`const int n = 15;`

Выходные данные:

```
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
2 1 0 0 0 0 0 0 0 0 0 0 0 0 0 
3 2 1 0 0 0 0 0 0 0 0 0 0 0 0 
4 3 2 1 0 0 0 0 0 0 0 0 0 0 0 
5 4 3 2 1 0 0 0 0 0 0 0 0 0 0 
6 5 4 3 2 1 0 0 0 0 0 0 0 0 0 
7 6 5 4 3 2 1 0 0 0 0 0 0 0 0 
8 7 6 5 4 3 2 1 0 0 0 0 0 0 0 
9 8 7 6 5 4 3 2 1 0 0 0 0 0 0 
1 9 8 7 6 5 4 3 2 1 0 0 0 0 0 
2 1 9 8 7 6 5 4 3 2 1 0 0 0 0 
3 2 1 9 8 7 6 5 4 3 2 1 0 0 0 
4 3 2 1 9 8 7 6 5 4 3 2 1 0 0 
5 4 3 2 1 9 8 7 6 5 4 3 2 1 0 
6 5 4 3 2 1 9 8 7 6 5 4 3 2 1 
```