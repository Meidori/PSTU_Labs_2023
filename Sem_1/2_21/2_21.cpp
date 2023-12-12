#include <iostream>
using namespace std;


int main() {
    bool flag = true;
    int num, temp;

    cin >> num;
    temp = num;

    if (num == 0) {
        cout << "Введен сразу ноль" << endl;
    }
    else {
        while (num != 0) {
            cin >> num;
            if (num < temp and num != 0) {
                flag = false;
            }
            temp = num;
        }
    }

    if (flag) {
        cout << "Числа упорядочены по возрастанию" << endl;
    }
    else {
        cout << "Числа не упорядочены по возрастанию" << endl;
    }

    return 0;
}