#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
    ofstream file1;
    ofstream file2;

    file1.open("F1.txt");
    file2.open("F2.txt");

    if (file1.is_open() && file2.is_open()) {
        cout << "Файлы открыты." << endl; 
        cout << "Введите сколько вы хотите заполнить строк в файле: " << endl;
        int lines;
        cin >> lines;
        cout << "Введите строки: " << endl;
                
        for (int i = 0; i < lines; i++) {
            string line;
            cin >> line;
            file1 << line;
            file1 << "\n";
        }

        file1.close();
        ifstream file1;
        file1.open("F1.txt");
        
        cout << "Введите число k: " << endl;
        int k;
        cin >> k;
        string str;
        int i = 1;

        while(!file1.eof()) {
            getline(file1, str);
            if ((i >= k) && (i - k < 5)) {
                file2 << str;
                file2 << "\n";
            }
            i++;
        }

        file2.close();
        ifstream file2;
        file2.open("F2.txt");
        int vowel_counter = 0;
        char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
        char symbol;
        while(file2.get(symbol)) {
            symbol = tolower(symbol);
            for (int i = 0; i < 6; i++) {
                if (symbol == vowels[i]) {
                    vowel_counter++;
                }
            }
        }

        cout << "Гласных в файле F2.txt: " << vowel_counter << endl;
        
    }
    else {
        cout << "Файл не открыт" << endl;
    }

    file1.close();
    file2.close();

    return 0;
}