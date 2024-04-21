Бакин Владислав Артемович

ИВТ-23-1б

# 5 Вариант задания

## Простое наследование. Принцип подстановки.

Лабораторная работа № 4 - классы

Базовый класс:

ПАРА_ЧИСЕЛ (PAIR)

Первое_число (first) - int

Второе_число (second) – int

Определить методы изменения полей и операцию сложения пар (a,b)+(c,d)=(a+b,c+d)

Создать производный класс ДЕНЕЖНАЯ_СУММА(MONEY), с полями Рубли и Копейки. Переопределить операцию сложения и определить операции вычитания и деления денежных сумм.

# 2.1 Код программы

> 4.cpp
```cpp
#include <iostream>
#include "money.h"
#include "pair.h"


using std::cin, std::cout, std::endl;


int main() {
    // Работа с классом Pair:
    Pair pair1;
    cout << "Введите два целых числа:" << endl;
    cin >> pair1;
    cout << "Объект pair1: " << pair1 << endl;

    Pair pair2;
    cout << "Введите два целых числа:" << endl;
    cin >> pair2;
    cout << "Объект pair2: " << pair2 << endl;

    Pair pair3 = pair1 + pair2;
    cout << "Объект pair3 = pair1 + pair2: " << pair3 << endl;


    // Работа с классом Money:
    Money money1;
    cout << "Введите два целых числа - рубли и копейки:" << endl;
    cin >> money1;
    cout << "Объект money1: " << money1 << endl;

    cout << "Введите два целых числа - рубли и копейки:" << endl;
    int rub, cop; 
    cin >> rub >> cop;
    Money money2(rub, cop);
    cout << "Объект money2, созданный конструктором money2(" << rub << ", " << cop << "): " << money2 << endl;

    Pair pair4 = money2;
    cout << "Принцип подстановки - pair4 = money2: " << pair4 << endl;

    return 0;
}
```

> pair.h
```cpp
#pragma once
#include <iostream>


class Pair {
private:
    int first;
    int second;


public:
    Pair(int first = 0, int second = 0) {
        this -> first = first;
        this -> second = second;
    }


    Pair(const Pair& pair) {
        first = pair.first;
        second = pair.second;
    }


    virtual ~Pair() {}
    

    virtual void set_first(int f) {
        first = f;
    }


    virtual void set_second(int s) {
        second = s;
    }


    virtual int get_first() {
        return first;
    }


    virtual int get_second() {
        return second;
    }


    Pair operator =(const Pair& pair) {
        if (&pair == this) {
            return *this;
        }
        first = pair.first;
        second = pair.second;
        return *this;
    }


    Pair operator +(const Pair& pair) {
        first += pair.first;
        second += pair.second;
        return Pair(first, second);
    }


    friend std::ostream& operator <<(std::ostream& out, Pair& pair);
    friend std::istream& operator >>(std::istream& in, Pair& pair);
};


std::ostream& operator <<(std::ostream& out, Pair& pair) {
    out << pair.get_first() <<  " " << pair.get_second();
    return out;
}


std::istream& operator >>(std::istream& in, Pair& pair) {
    int fst, snd;
    in >> fst;
    in >> snd;
    pair.set_first(fst);
    pair.set_second(snd);
    return in;
}
```

> money.h
```cpp
#pragma once
#include <iostream>
#include "pair.h"


class Money : public Pair {
private:
    int rubles;
    int kopecks;


public:
    Money(int rubles = 0, int kopecks = 0) : Pair(rubles, kopecks) {
        this -> kopecks = kopecks % 100;
        this -> rubles = rubles + kopecks / 100;
    }


    Money(const Money& money) {
        rubles = money.rubles;
        kopecks = money.kopecks;
    }


    ~Money() {}


    int get_first() {
        return rubles;
    }


    int get_second() {
        return kopecks;
    }


    void set_first(int rubles) {
        this -> rubles = rubles;
    }


    void set_second(int kopecks) {
        this -> kopecks = kopecks;
    }


    Pair operator =(const Money& money) {
        if (&money == this) {
            return *this;
        }
        rubles = money.rubles;
        kopecks = money.kopecks;
        return *this;
    }


    Money operator +(const Money& money) {
        kopecks += money.kopecks;
        rubles = rubles + money.rubles + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, kopecks);
    }


    Money operator -(const Money& money) {
        kopecks -= money.kopecks;
        rubles = rubles - money.rubles + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, abs(kopecks));
    }


    Money operator *(const int& multiplier) {
        kopecks *= multiplier;
        rubles = rubles * multiplier + kopecks / 100;
        kopecks = kopecks % 100;
        return Money(rubles, kopecks);
    }


    friend std::ostream& operator <<(std::ostream& out, Money& money);
    friend std::istream& operator >>(std::istream& in, Money& money);
};


std::ostream& operator <<(std::ostream& out, Money& money) {
    out << money.get_first() <<  " рублей(я) и " << money.get_second() << " копеек(ки).";
    return out;
}


std::istream& operator >>(std::istream& in, Money& money) {
    int rub, kop;
    in >> rub;
    in >> kop;
    rub += kop / 100;
    kop = kop % 100;
    money.set_first(rub);
    money.set_second(kop);
    return in;
}
```

# 2.2 UML

<image src = "4.png">

# Пример работы

```
Введите два целых числа:
10 330
Объект pair1: 10 330    
Введите два целых числа:
60 45
Объект pair2: 60 45
Объект pair3 = pair1 + pair2: 70 375      
Введите два целых числа - рубли и копейки:
10 70
Объект money1: 10 рублей(я) и 70 копеек(ки).
Введите два целых числа - рубли и копейки:  
900 35
Объект money2, созданный конструктором money2(900, 35): 900 рублей(я) и 35 копеек(ки).
Принцип подстановки - pair4 = money2: 900 35
```

# Вопросы

1. Для чего используется механизм наследования?

- Для создания новых классов на основе существующих. Он позволяет классам наследовать свойства и методы других классов.

2. Каким образом наследуются компоненты класса, описанные со спецификатором public?

- наследуются также с модификатором public

3. Каким образом наследуются компоненты класса, описанные со спецификатором private?

- private компоненты класса остаются скрытыми и недоступными для других классов

4. Каким образом наследуются компоненты класса, описанные со спецификатором protected?

- наследуются с модификатором protected в производном классе

5. Каким образом описывается производный класс?

- `class <имя потомка> : <модификатор наследования> <имя родительского класса>{};`

6. Наследуются ли конструкторы?

- Да, но не вызываются автоматически

7. Наследуются ли деструкторы?

- Да, но не вызываются автоматически

8. В каком порядке конструируются объекты производных классов?

-   1. Вызывается конструктор базового класса.
    2. Конструируются члены базового класса.
    3. Вызывается конструктор производного класса.
    4. Конструируются члены производного класса.

9. В каком порядке уничтожаются объекты производных классов? 

-   1. Вызывается деструктор производного класса.
    2. Разрушаются члены производного класса.
    3. Вызывается деструктор базового класса.
    4. Разрушаются члены базового класса.

10. Что представляют собой виртуальные функции и механизм позднего связывания?

- Виртуальные функции предназначенные для переопределения в производных классах. Механизм позднего связывания используется для разрешения вызова виртуальных функций во время выполнения программы.

11. Могут ли быть виртуальными конструкторы? Деструкторы?

- Только деструкторы.

12. Наследуется ли спецификатор virtual?

- нет, но его использование в производном классе позволяет переопределить функцию как виртуальную.

13. Какое отношение устанавливает между классами открытое наследование?

- производный класс наследует все открытые члены базового класса (поля, методы) и может использовать их в своем собственном контексте.

14. Какое отношение устанавливает между классами закрытое наследование?

- При закрытом наследовании, все публичные и защищенные члены базового класса становятся частными членами производного класса.

15. В чем заключается принцип подстановки?

- Принцип подстановки заключается в том, что объект производного класса может использоваться везде, где используется объект базового класса.

16. Имеется иерархия классов. Какие компонентные данные будет иметь объект х?
```cpp
class Student
{
	int age;
public:
	string name;
	...
};
class Employee : public Student
{
protected:
	string post;
	...
};
class Teacher : public Employee
{
	protected: int stage;
	...
};

Teacher x;
```

- public: name / protected: post, stage 

17. Для классов Student, Employee и Teacher написать конструкторы без параметров.

```cpp
class Student {
public:
    Student() {
		age = 0;
		name = "";
	}
};


class Employee : public Student {
public:
    Employee() : Student() {
		post = "";
	}
};


class Teacher : public Employee {
public:
    Teacher() : Employee() {
		stage = 0;
	}
};
```

18. Для классов Student, Employee и Teacher написать конструкторы с параметрами.

```cpp
class Student {
public:
    Student(int age, std::string name) {
		this -> age = age;
		this -> name = name;
	}
};


class Employee : public Student {
public:
    Employee(std::string post) : Student(age, name) {
		this -> post = post;
	}
};


class Teacher : public Employee {
public:
    Teacher(int stage) : Employee(post) {
		this -> stage = stage;
	}
};
```

19. Для классов Student, Employee и Teacher написать конструкторы копирования.

```cpp
class Student {
public:
    Student(const Student& student) {
		age = student.age;
		name = student.name;
	}
};


class Employee : public Student {
public:
    Employee(const Employee& employee) {
		post = employee.post;
	}
};


class Teacher : public Employee {
public:
    Teacher(const Teacher& teacher) {
		stage = teacher.stage;
	}
};
```

20. Для классов Student, Employee и Teacher определить операцию присваивания.

```cpp
Student operator=(const Student& student) {
    age = student.age;
	name = student.name;
	return *this;
}


Employee operator=(const Employee& employee) {
	name = employee.name;
	post = employee.post;
	return *this;
}


Teacher operator=(const Teacher& teacher) {

	name = teacher.name;
	post = teacher.post;
	stage = teacher.stage;
	return *this;
}

```