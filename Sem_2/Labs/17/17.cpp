#include <iostream>
#include <string>
using namespace std;


const int CHAR_NUM = 256;


void calc_char_table(string str, int size, int char_table[CHAR_NUM]) {
    for (int i = 0; i < CHAR_NUM; i++) {
        char_table[i] = -1; 
    }

    for (int i = 0; i < size; i++) {
        char_table[(int)str[i]] = i;       // принудительное приведение типов 
    }
}


void boyer_moore_search(string str, string pat) {
    int str_size = str.size();
    int pat_size = pat.size();

    int shift_table[CHAR_NUM];

    calc_char_table(str, pat_size, shift_table);

    int shift = 0;

    while (shift <= (str_size - pat_size)) {
        int j = pat_size - 1;
        while(j >= 0 && pat[j] == str[shift + j]) {
            j--;
        }

        if (j < 0) {
            cout << "Паттерн найден по индексу: " << shift << endl; 
            if (shift + pat_size < str_size) {
                shift += pat_size - shift_table[(int)str[shift + pat_size]];
            }
            else {
                shift++;
            }
        }
        
        else {
            shift += max(1, j - shift_table[(int)str[shift + j]]);
        }
    }
}


int *calc_prefix(string pat, int size) {
    int *lps = new int[size];
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < size) {
        if (pat[i] == pat[len]) {
            lps[i] = len;
            len++;
            i++;
        } 
        else if(len != 0) {
            len = lps[len - 1];
        }
        else {
            lps[i] = 0;
            i++;
        }
    }
    return lps;
}


void knuth_morris_pratt_search(string str, string pat) {
    int str_size = str.size();
    int pat_size = pat.size();

    int *lps = calc_prefix(pat, pat_size);

    int str_idx = 0;
    int pat_idx = 0;

    while ((str_size - str_idx) >= (pat_size - pat_idx)) {
        if (pat[pat_idx] == str[str_idx]) {
            pat_idx++;
            str_idx++;
        }

        if (pat_idx == pat_size) {
            cout << "Паттерн найден по индексу: " << str_idx - pat_idx << endl;
            pat_idx = lps[pat_idx - 1];
        }
        else if (str_idx < str_size && pat[pat_idx] != str[str_idx]) {
            if (pat_idx != 0) {
                pat_idx = lps[pat_idx - 1];
            }
            else {
                str_idx++;
            }
        }
    }
}



int main() {
    string str, substr;
    cout << "Введите строку, затем подстроку:" << endl;
    getline(cin, str);
    getline(cin, substr);

    cout << "Результат по поиску Бойера-Мура:" << endl;
    boyer_moore_search(str, substr);

    cout << "Результат по поиску Кнута-Морриса-Пратта:" << endl;
    knuth_morris_pratt_search(str, substr);

    return 0;
}