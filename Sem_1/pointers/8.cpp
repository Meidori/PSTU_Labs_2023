#include <iostream>
#include <string>
using namespace std;


int main() {
    string st, low, up, tmp;
    int countLow = 0, countUp = 0;
    const char *ptrLow = low.c_str();
    const char *ptrUp = up.c_str();
    cout << "Введите строку:" << endl;
    cin >> st;
    cout << "Введите два символа (строчную букву и большую):" << endl;
    cin >> low >> up;

    for (int i = 0; i < st.length(); i++) {
        tmp = st[i];
        const char *ptr = tmp.c_str();
        if (*ptr == *ptrLow) {
            countLow++;
        }
        else if (*ptr == *ptrUp) {
            countUp++;
        }
    }

    cout << low << ": " << countLow << endl;
    cout << up << ": " << countUp << endl;
    cout << "Длина строки: " << st.length() << endl;
    return 0;
}