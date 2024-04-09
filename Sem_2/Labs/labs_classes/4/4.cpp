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