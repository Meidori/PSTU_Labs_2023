#include <iostream>
#include "money.h"
#include "pair.h"


int main() {
    Money m1(140, 10000);
    Money m2(14, 5);
    Money m3 = m1 + m2;
    std::cout << m3.get_rubles() << std::endl;   
}