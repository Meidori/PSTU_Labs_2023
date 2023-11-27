#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a, b, c, D;
    cin >> a >> b >> c;
    
    D = pow(b, 2) - 4 * a * c;
    if (D > 0) {
        cout << ((-b + sqrt(D)) / (2 * a)) << endl;
        cout << ((-b - sqrt(D)) / (2 * a)) << endl;
    }
    else if (D == 0) {
        cout << (-b / (2 * a)) << endl;
    }
    else {
        cout << "Корней нет" << endl;
    }

    return 0;
}