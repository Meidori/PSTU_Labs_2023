#include <iostream>
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

    
    void push_back(int value) {
        Node *p = new Node;
        p -> data = value;
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last -> next = p;
        last = p;
    }


    // 


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
    list l;
    l.init();
    int n, tmp;
    cout << "Введите количество элементов в списке: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << endl << "Введите значение: ";
        cin >> tmp;
        l.push_back(tmp);
    }

    cout << endl << "Список выглядит так:" << endl;
    l.show_list();

    int K, pos1, pos2;
    cout << "Введите число K - количество элементов, которые будут удалены/добавлены: "; 
    cin >> K;
    cout << endl << "Введите номер элемента, с которого нужно удалить K элементов: ";
    cin >> pos1;
    // 
    cout << endl << "Список после удаления K элементов:" << endl;
    l.show_list();


}
