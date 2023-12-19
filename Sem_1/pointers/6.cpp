#include <iostream>
#include <string>
using namespace std;


int main() {
    int countC, countV;
    countC = countV = 0;
    string st, tmp;
    cout << "Введите строку:" << endl;
    cin >> st;

    for (int i = 0; i < st.length(); i++) {
        tmp = st[i];
        const char *ptr = tmp.c_str();
        if (*ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u' || *ptr == 'y') {
            countV++;
        }
        else {
            countC++;
        }
    }

    cout << "Количество гласных: " << countV << endl;
    cout << "Количество согласных: " << countC << endl;

    return 0;
}