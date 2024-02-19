#include <iostream>
using namespace std;


int fibonacci(int x) {
    if (x == 0) {
        return 0;
    }
    else if (x == 1) {
        return 1;
    }
    return fibonacci(x - 1) + fibonacci(x - 2);
}


int main() {
    int position;       
    cin >> position;    // номер числа, до которого выводим последовательность Фибоначчи включительно

    for (int i = 0; i < position; i++) {
        cout << fibonacci(i) << " ";
    }

    return 0;
}