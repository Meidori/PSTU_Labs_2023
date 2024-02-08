#include <iostream>
using namespace std;


int main() {
    const int m = 5, n = 5;
    int array[m][n];
    int cur_num = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i + j) % 2 != 0) {
                array[i - 1][j - 1] = 0;
            }
            else {
                array[i - 1][j - 1] = cur_num;
                cur_num++;
                if (cur_num == 10) {
                    cur_num = 1;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}