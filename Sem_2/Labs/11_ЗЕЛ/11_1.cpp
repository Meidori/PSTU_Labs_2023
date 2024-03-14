#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct Node {
    int data;
    Node *next;
};


struct list {
    Node *first;
    Node *last;


    void init() {
        first = nullptr;
        last = nullptr;
    }


    bool is_empty() {
        return first == nullptr;
    }

    
    void push_back(int value, int &k) {
        Node *p = new Node;
        p -> data = value;
        if (is_empty()) {
            first = p;
            last = p;
            k++;
            return;
        }
        last -> next = p;
        last = p;
        k++;
    }


    int pop(int pos, int &k) {
        if ((!(is_empty())) && (pos <= k) && (pos >= 0)) {
            pos--;
            Node *p = first, *prev = first;
            for (int i = 0; i < pos; i++) {
                prev = p;
                p = p -> next;
            }
            if (pos == 0) {
                first = p -> next;
            }
            else {
                prev -> next = p -> next;
            }
            int tmp = p -> data;
            free(p);
            k--;
            return tmp;
            }
    }


    void add_note(int pos, int &k) {
        Node *note = new Node;
        if ((pos <= k) && (pos >= 0)) {
            pos--;
            Node *p = first, *prev = first;
            for (int i = 0; i < pos; i++) {
                prev = p;
                p = p -> next;
            }
            int value;
            cout << "Введите значение элемента:" << endl;
            cin >> value;
            note -> data = value;

            if (pos == 0) {
                note -> next = first;
                first = note;
            }
            else if (pos == k - 1) {
                p -> next = note;
                note -> next = nullptr;
            }
            else {
                prev -> next = note;
                note -> next = p;
            }

            k++;
        }
    }


    void write(int &k) {
        int c = k;
        ofstream out;
        out.open("file.txt");
        if (out.is_open()) {
            for (int i = 0; i < c; i++) {
                out << pop(1, k) << endl;
            } 
        }
        out.close();

    }


    void restore(int &k, list l) {
        ifstream in("file.txt");
        if (in.is_open()) {
            int x;
            while (in >> x) {
                push_back(x, k);
            }
        }
        in.close();
    }


    void show_list() {
        if (is_empty()) {
            cout << "Список пустой." << endl;
            return;
        }
        Node *p = first;
        while (p != nullptr) {
            cout << p -> data << " ";
            p = p -> next;
        }
        cout << endl;
    }
};


int main() {
    list *l = new list;
    l -> init();
    int n, tmp, k = 0;
    cout << "Введите количество элементов в списке:" << endl;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Введите значение:" << endl;
        cin >> tmp;
        l -> push_back(tmp, k);
    }

    cout << "Список выглядит так:" << endl;
    l -> show_list();

    int K, pos1, pos2;
    cout << "Введите число K - количество элементов, которые будут удалены/добавлены:" << endl; 
    cin >> K;
    cout << "Введите номер элемента, с которого нужно удалить K элементов:" << endl;
    cin >> pos1;
    for (int i = 0; i < K; i++) {
        cout << "Удаляем элемент: " << l -> pop(pos1, k) << endl;
    }
    cout << "Список после удаления K элементов:" << endl;
    l -> show_list();

    cout << "Введите номер элемента, с которого нужно добавить K элементов:" << endl;
    cin >> pos2;
    for (int i = 0; i < K; i++) {
        l -> add_note(pos2, k);
        pos2++;
    }
    cout << "Список после добавления K элементов:" << endl;
    l -> show_list();

    l -> write(k);

    delete l;

    cout << "Содержимое файла:" << endl;
    ifstream in("file.txt");
    if (in.is_open()) {
        int x;
        while (in >> x) {
            cout << x << " ";
        }
        cout << endl;
    }
    in.close();
    
    list *restored_l = new list;
    restored_l -> init();
    restored_l -> restore(k, *restored_l);
    cout << "Содержимое восстановленного списка:" << endl;
    restored_l -> show_list();
    
    return 0;
}
