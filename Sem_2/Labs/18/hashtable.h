#pragma once


unsigned int get_hash(char *str, int size) {
    int hash;
    for (int i = 0; str[i] != '\0'; i++) {
        hash += str[i];
    }
    hash %= size;
    return abs(hash);
}


struct elem_of_table {
    std::string* name;          // key
    unsigned int* passport;
    std::string* adress;
};


struct hash_table {
    
};