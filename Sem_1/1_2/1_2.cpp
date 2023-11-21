#include <iostream>
using namespace std;

int main() {
    float num1, num2;
    cin >> num1 >> num2;
    
    if (num2 == 0) {
        cout << "На ноль делить нельзя!" << endl;
    }
    else {
        cout << num1 / num2 << endl;
    }

    return 0;
}