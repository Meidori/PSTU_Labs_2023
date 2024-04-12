#include <iostream>
#include <fstream>
#include <string>
#include "multiphase_sort.h"


const int SIZE = 25;


void print_array(int size) {
    std::ifstream file;
    file.open("file.txt");
    std::string line;
    while(std::getline(file, line)) {
        std::cout << line << " ";
    }
    std::cout << std::endl;
    file.close();
}


int main() {
    int array_of_numbers[SIZE] =  {56, 74, 95, 104, 13, 14, 1, 4, 7, 0, -1, 15, 34, 106, 23, 56, 17, 45, 76, 100, 34, 22, 25, 27, 75};
    const std::string file_name = "file.txt";
    std::ofstream file;
    file.open(file_name);
    for (int i = 0; i < SIZE; i++) {
        file << array_of_numbers[i] << std::endl;
    }
    file.close();

    std::cout << "Изначальный вид массива:" << std::endl;
    print_array(SIZE);

    multiphase_sort(file_name, SIZE);        

    std::cout << "Вид массива после сортировки, также записан в `file.txt`:" << std::endl;
    print_array(SIZE);

    return 0;
}
