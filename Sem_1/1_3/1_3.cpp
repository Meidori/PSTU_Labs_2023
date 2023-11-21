#include <iostream>
using namespace std;

int main() {
    float number;
    cin >> number;

    if (number < 5) {
        cout << number * 3 << endl;
    }
    else if (number > 7) {
        cout << number + 3 << endl;
    }
    else {
        cout << number / 10 << endl;
    }

    return 0;
}