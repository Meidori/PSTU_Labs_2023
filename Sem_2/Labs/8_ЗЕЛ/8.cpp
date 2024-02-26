#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


FILE *f;


struct Human {
    char full_name[100];
    int year_of_birth;
    float height;
    float weight;
};


Human input_Human() {
    string name;
    Human obj;
    getline(cin, name);
    for (int i = 0; i < name.length(); i++) {
        obj.full_name[i] = name[i];
    }
    cin >> obj.year_of_birth;
    cin >> obj.height;
    cin >> obj.weight;
    return obj;
}


void write(Human user) {
    fwrite(&user, sizeof(Human), 1, f);
}


void output(Human user) {
    fread(&user, sizeof(Human), 1, f);
    printf("%s %d %f %f",user.full_name, user.year_of_birth, user.height, user.weight);
}


void replaceElements(Human user) {
    FILE *tmp;
    tmp = fopen("tmp.dat", "w+");
    f = tmp;
    fclose(tmp);
}


int main() {
    Human user;
    f = fopen("file.dat", "w+");
    if (f == NULL) {
        cout << "Не удалось открыть файл" << endl;
    }
    else {
        cout << "Файл открыт" << endl;
        cout << "Введите ФИО, год рождения, рост, вес:" << endl;
        Human user = input_Human();
        write(user);
        cout << "Вы ввели: " << endl;
        output(user);

        replaceElements(user);

        cout << "Вы ввели: " << endl;
        output(user);
    }

    fclose(f);
    return 0;
}