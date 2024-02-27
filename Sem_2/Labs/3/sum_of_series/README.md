Бакин Владислав Артемович

ИВТ-23-1б

# 1 Вариант задания

Лабораторная работа № 3 (Сумма ряда)

Приближенно вычислить значение функции двумя способами:

$S=1+(x/1!)+(x^2/2!)+...+(x^n/n!)$

1) Через сумму функционального ряда с помощью рекурсивной функции. Аргументы функции — n и x, где n — количество членов ряда, x — переменная. 
2) Через прямое вычисление значения функции. Аргумент функции — переменная x.

Сравнить полученные результаты

# 2.1 Код программы

**Первая реализация**

```cpp
#include <iostream>
#include <cmath>
using namespace std;
// Вариант 5


int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}


float sum_of_series(int n, int x) {
    if (n == 0) {
        return 1;
    }
    return (pow(x, n) / factorial(n)) + sum_of_series(n - 1, x);
}


int main() {
    int n;  // количество членов ряда
    cin >> n;
    int x;
    cin >> x;

    cout << sum_of_series(n - 1, x) << endl;

    return 0;
}   
```

**Вторая реализация**

```cpp
#include <iostream>
#include <cmath>
using namespace std;


int factorial(int num) {
    if (num == 0) {
        return 1;
    }
    return num * factorial(num - 1);
}


int main() {
    int n, x;
    float sum = 0;
    cin >> n;
    cin >> x;

    for (int i = 0; i < n; i++) {
        sum += pow(x, i) / factorial(i);
    }
    
    cout << sum << endl;
    return 0;
}
```

# 2.2 Блок-схема программы

<image src="sum_of_series1.png">

<image src="sum_of_series2.png">

# Тесты

### Пример 1

Входные данные:

```
7
2
```

Выходные данные:

```
7.35556
```

### Пример 2

Входные данные:

```
15
5
```

Выходные данные:

```
153.518
```

### Пример 3

Входные данные:

```
5
2
```

Выходные данные:

```
7
```