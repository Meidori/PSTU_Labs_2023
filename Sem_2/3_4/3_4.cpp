#include <iostream>
using namespace std;


int main() {
    int n = 50;
    bool flag = 1;
    int lb = 20, ub = 100;
    int array[n];

    
    for (int i = 0; i < n; i++) {
        array[i] = (rand() % (ub - lb + 1)) + lb;
    } 

    /*
    for (int i = 0; i < n; i++) {
        array[i] = i;  
    }
    */

    for (int i = 1; i < n; i++) {
        if (array[i] <= array[i-1]) {
            flag = 0;
        }
    }

    if (flag) {
        cout << "Упорядочен по возрастанию" << endl;
    }
    else {
        cout << "Не упорядочен по возрастанию" << endl;
    }

    return 0;
}