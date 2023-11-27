#include <iostream>
#include <cmath>
using namespace std;


int main() {
    int N, sum = 0;
    bool flag = 0;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        if (flag == 1) {
            sum += i;
        }
        else {
            sum -= i;
        }
        flag = not(flag);
    }

    cout << sum << endl;

    return 0;
}   