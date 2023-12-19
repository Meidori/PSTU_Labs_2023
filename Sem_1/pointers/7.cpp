#include <iostream>
using namespace std;


int main() {
    int n;
    int* ptr = &n;

    cin >> *ptr;

    cout << n;
    return 0;
}