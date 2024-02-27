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


void add_note(Human &user) {

    cout << "Введите ФИО (не более 100 символов), год рождения, рост, вес:" << endl;
    scanf("%s", user.full_name);
    scanf("%d", &user.year_of_birth);
    scanf("%f", &user.height);
    scanf("%f", &user.weight);

    fwrite(&user, sizeof(Human), 1, f);
}


void del_note(Human user) {

}


void show_notes(Human user) {
    
}


int main() {
    Human user;
    f = fopen("file.dat", "wb");
    add_note(user);
    fclose(f);

    f = fopen("file.dat", "rb");
    show_notes(user);


    return 0;
}