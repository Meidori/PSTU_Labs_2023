#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct Human {
    string full_name;
    int year_of_birth;
    float height;
    float weight;
};


void create_note(Human human, ostream &file) {
    cout << "Введите ФИО, год рождения, рост, вес: " << endl;
    
    getline(cin, human.full_name);
    int size = human.full_name.length();
    file.write((char*)&size, sizeof(int));
    file.write(human.full_name.c_str(), size);

    cin >> human.year_of_birth;
    file.write((char*)&human.year_of_birth, sizeof(int));
    
    cin >> human.height;
    file.write((char*)&human.height, sizeof(float));
    
    cin >> human.weight;
    file.write((char*)&human.weight, sizeof(float));
}


void get_note(Human human, ifstream &file) {
    string name;
    
    int year;
    float hght, wght;
    
    int size;
    file.read((char*) &size, sizeof(int));
    char buffer[size];
    file.read(buffer, size);
    name = string(buffer); 

    file.read((char*)&year, sizeof(int));
    
    file.read((char*)&hght, sizeof(float));
    
    file.read((char*)&wght, sizeof(float));
    
    cout << name << endl;
    cout << year << endl;
    cout << hght << endl;
    cout << wght << endl;
}


int main() {
    Human human;
    ofstream fo("file.bin", ios::binary);
    if (fo.is_open()) {
        create_note(human, fo);
        fo.close();
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }

    ifstream fi("file.bin", ios::binary);
    if (fi.is_open()) {
        cout << "Вы ввели: " << endl;
        get_note(human, fi);
        fi.close();
    }
    else {
        cout << "Не удалось открыть файл для чтения" << endl;
    }

    return 0;
}

