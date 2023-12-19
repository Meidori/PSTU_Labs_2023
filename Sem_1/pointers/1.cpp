#include <iostream>
using namespace std;


int main() {
    int num1, num2, tmp;
    int *ptr1;
    int *ptr2;
    int *ptr3;

    cin >> num1;
    cin >> num2;

    ptr1 = &num1;
    ptr2 = &num2;

    *ptr3 = *ptr2;
    *ptr2 = *ptr1;
    *ptr1 = *ptr3;

    cout << *ptr1 << endl;
    cout << *ptr2 << endl;

    return 0;
}