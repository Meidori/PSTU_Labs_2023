#include <iostream>

#include "object.h"
#include "pair.h"
#include "money.h"
#include "vector.h"


int main() {
    /*
    Pair pair;
    std::cin >> pair;
    std::cout << pair << std::endl;

    Object *ptr = &pair;
    ptr -> print(); 
    */

    /*
    Money money; 
    std::cin >> money;
    std::cout << money << std::endl;
    Object *ptr = &money;
    ptr -> print();  
    */
    
    Vector vect(5);
    
    Pair pair;
    std::cout << "Введите два целых числа:" << std::endl;
    std::cin >> pair;

    Money money;
    std::cout << "Введите два целых числа - рубли и копейки:" << std::endl;
    std::cin >> money;

    Object *ptr = &pair;
    vect.add(ptr);
    ptr = &money;
    vect.add(ptr);

    std::cout << "Содержимое вектора:" << std::endl;
    std::cout << vect;

    return 0;
}