#include <iostream>
#include <string>
#include <fstream>
using namespace std;


FILE *f;


struct Human {
    string full_name;
    int year_of_birth;
    string height;
    string weight;
};


void add_notes(Human &user) {
    ofstream file("file.txt", ios::binary);

    cout << "Введите ФИО, год рождения, рос, вес:" << endl;
    getline(cin, user.full_name);
    cin >> user.year_of_birth;
    cin >> user.height;
    cin >> user.weight;

    file << user.full_name << "\n";
    file << user.year_of_birth << "\n";    
    file << user.height << "\n";    
    file << user.weight << "\n";    
    
    file.close();
}


void show_notes() {
    ifstream file("file.txt", ios::binary);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}


void replace_notes(Human &user) {
    string filename = "file.txt";
    string tmpname = "tmp.txt";
    ifstream file(filename, ios::binary);
    ofstream tmp(tmpname, ios::binary);   
        

    file.close();
    tmp.close();

    remove(filename.c_str());
    rename(tmpname.c_str(), filename.c_str());
}


int main() {
    Human user;
    add_notes(user);
    cout << "Вы ввели:" << endl;
    show_notes();
    cout << "Содержание файла после преобразований:" << endl;
    replace_notes(user);
    show_notes();

    return 0;
}