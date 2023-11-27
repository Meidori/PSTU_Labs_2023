#include <iostream>
using namespace std;

int main() {
    int n, temp;
    bool flag_positive, flag_negative;
    flag_positive = 0;
    flag_negative = 0;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> temp;
        if (flag_negative == 0 and flag_positive == 0) {
            if (temp > 0) {
                flag_positive = 1;
            }
            else if (temp < 0) {
                flag_negative = 1;
            }
        }
    }

    if (flag_positive == 1) {
        cout << "Положительное число было введено раньше отрицательного" << endl;
    }
    else if (flag_negative == 1) {
        cout << "Отрицательное число было введено раньше положительного" << endl;
    }
    else if (flag_positive == 0 and flag_negative == 0) {
        cout << "В последовательности встречались только нули" << endl;
    }
    return 0;
}