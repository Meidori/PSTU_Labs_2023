#include <iostream>
using namespace std;


int main() {
    int N, S;
    for (int i = 1; i <= N; i++) {
        if (i % 3 == 0) {
            S -= i;
        }
        else {
            S += i;
        }
    }
    return 0;
}