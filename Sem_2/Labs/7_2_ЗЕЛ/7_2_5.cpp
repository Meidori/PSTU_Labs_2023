#include <iostream>
#include <stdarg.h>
using namespace std;


int sum(const int k, ...) {
    va_list args;
    va_start(args, k);
    int result = 0;
    int tmp = 0;
    int cur_term = 0;
    int terms[k - 1];

    for (int i = 0; i < k; i++) {
        tmp = va_arg(args, int);
        if (i == 0) {
            cur_term = tmp;
        }
        else {
            cur_term *= tmp;
            terms[i - 1] = cur_term;
            cur_term = tmp;
        }
    }

    for (int i = 0; i < k - 1; i++) {
        if (i % 2 == 0) {
            result += terms[i];
        }
        else {
            result -= terms[i];
        }
    }

    va_end(args);
    return result;
}




int main() {
    cout << sum(5, 1, 2, 3, 4, 5) << endl;
    cout << sum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
    cout << sum(12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12) << endl;


    return 0;
}
