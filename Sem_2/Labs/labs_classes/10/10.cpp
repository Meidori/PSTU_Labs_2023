#include <iostream>
#include <string>
#include <sstream>

#include "time.h"
#include "file_operation.h"


int main() {
    int selector = -1;
    const char* file_name = "file.txt";

    while (selector != 0) {
        std::cout << "1)create_file\n2)print_file\n3)add_record\n4)add_diapason_of_records\
        \n5)delete_record\n6)delete_extra_records\n7)value_increase\n0)exit" << std::endl;

        std::cin >> selector;
        switch(selector) {
        case 0: {
            std::cout << "exit" << std::endl;
            break;
        }

        case 1: {
            create_file(file_name);
            break;
        }

        case 2: {
            print_file(file_name);
            break;
        }

        case 3: {
            Time new_record;
            int position;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> new_record;
            std::cout << "Введите позицию новой записи:" << std::endl;
            std::cin >> position;
            add_record(file_name, position, new_record);
            break;
        }

        case 4: {
            int amount_of_records, start_position;
            std::cout << "Введите количество записей и начальную позицию:" << std::endl;
            std::cin >> amount_of_records >> start_position;
            add_diapason_of_records(file_name, amount_of_records, start_position);
            break;
        }

        case 5: {
            int position;
            std::cout << "Введите позицию удаляемой записи:" << std::endl;
            std::cin >> position;
            delete_record(file_name, position);
            break;
        }

        case 6: {
            Time extra_time;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> extra_time;
            delete_extra_records(file_name, extra_time);
            break;
        }

        case 7: {
            Time target;
            int seconds;
            std::cout << "Введите время (минуты и секунды - целые числа):" << std::endl;
            std::cin >> target;
            std::cout << "Введите секунды:" << std::endl;
            std::cin >> seconds;
            value_increase(file_name, target, seconds);
            break;
        }

        default: {
            break;
        }
        }
    }
        

    return 0;
}