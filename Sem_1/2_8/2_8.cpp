#include <iostream>
using namespace std;

int main() {
    int N, stars, spaces;
    cin >> N;

    stars = 1;

    for (int i = 1; i <= N; i++) {

        for (int j = 1; j <= stars; j++) {
            cout << "*";
        }
        
        stars++;
        cout << "\n";
    }

    return 0;
}