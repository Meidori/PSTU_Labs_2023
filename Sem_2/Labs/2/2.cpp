#include <iostream>
using namespace std;


int main() {
    const int n = 15;
    int matrix[n][n];
    int tmp;

    for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                tmp += 1;
                if (tmp == 10) {
                    tmp = 1;
                }
                matrix[j][i] = tmp;
            }
            else {
                matrix[j][i] = 0;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}