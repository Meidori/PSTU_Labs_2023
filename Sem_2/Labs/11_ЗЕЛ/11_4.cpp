#include <iostream>
#include <fstream>
using namespace std;


struct Node {
    int data;
    Node *ptr_to_next;
};


struct Queue {
    Node *ptr_to_front = nullptr;
    Node *ptr_to_back = nullptr;
    int size = 0;


    void init() {
        ptr_to_front = nullptr;
        ptr_to_back = nullptr;
        size = 0;
    }


    bool is_empty() {
        return size == 0;
    }


    void push(int value) {
        Node *tmp = new Node;
        tmp -> data = value;
        if (size == 0) {
            ptr_to_front = tmp;
            ptr_to_back = tmp;
        }
        else {
            tmp -> ptr_to_next = ptr_to_back;
            ptr_to_back = tmp;
        }
        size++;
    }


    int pop() {
        Node *tmp = ptr_to_front;
        Node *tmp_prev = ptr_to_back;
        int value = tmp -> data;
        if (size == 1) {
            ptr_to_back = nullptr;
        }
        for (int i = 0; i < size - 1 - 1; i++) {
            tmp_prev = tmp_prev -> ptr_to_next;
        }
        ptr_to_front = tmp_prev;
        ptr_to_front -> ptr_to_next = nullptr;
        size--;
        delete tmp;
        return value;
    }


    int delete_by_index(int index) {
        if (!(is_empty()) && index < size && index >= 0) {
            Queue *tmp_queue = new Queue;
            int value, queue_length = size, rev_index = queue_length - 1 - index;
            for (int i = 0; i < queue_length; i++) {
                value = pop();
                if (i != rev_index) {
                    tmp_queue -> push(value);
                }

            }
                
            for (int i = 0; i < (queue_length - 1); i++) {
                value = tmp_queue -> pop();
                push(value);
            }        
        }
        return 0;
    }


    void add_value_by_index(int index) {
        int value;
        cout << "Введите значение элемента:" << endl;
        cin >> value;
        if (is_empty() && index == 0) {
            push(value);
        }
        else if (index <= size && index >= 0) {
            Queue *tmp = new Queue;
            int queue_length = size, tmp_value;
            for (int i = 0; i < queue_length; i++) {
                tmp_value = pop();
                tmp -> push(tmp_value);
            }
            int rev_index = queue_length - 1 - index;
            if (index == queue_length) {
                push(value);
            }
            for (int i = 0; i < queue_length; i++) {
                tmp_value = tmp -> pop();
                push(tmp_value);
                if (i == rev_index) {
                    push(value);
                }
            }
        }
    }


    void write_in_file() {
        int queue_length = size;
        ofstream out;
        out.open("file_11_4.txt");
        if (out.is_open()) {
            for (int i = 0; i < queue_length; i++) {
                out << pop() << endl;
            }
        }
        out.close();
    }


    void resotre_from_file() {
        ifstream in; 
        in.open("file_11_4.txt");
        int value;
        while (in >> value) {
            push(value);
        }
        in.close();

    }


    Node *front() { 
        return ptr_to_front; 
        }


    Node *back() { 
        return ptr_to_back; 
        }



    void show_queue() {
        if (size == 0) {
            cout << "Очередь пустая." << endl;
        }
        else {
            Node *tmp = ptr_to_back;
            cout << tmp -> data;
            tmp = tmp -> ptr_to_next;
            for (int i = 1; i < size; i++) {
                cout << " " << tmp -> data;
                tmp = tmp -> ptr_to_next;
            }
            cout << endl;
        }
    }
};


int main() {
    Queue *queue_of_nums = new Queue;
    queue_of_nums -> init();
    int number_of_values, new_value;
    cout << "Введите количество значений, которое будет содержаться в очереди:" << endl;
    cin >> number_of_values;
    for (int i = 0; i < number_of_values; i++) {
        cout << "Введите значение:" << endl;
        cin >> new_value;
        queue_of_nums -> push(new_value);
    }

    cout << "Очередь после заполнения:" << endl;
    queue_of_nums -> show_queue();

    int number_of_changes, pos;
    cout << "Введите число K - количество элементов, которые будут удалены/добавлены:" << endl;
    cin >> number_of_changes;
    cout << "Введите номер элемента, с которого нужно удалить K элементов:" << endl;
    cin >> pos;
    
    for (int i = 0; i < number_of_changes; i++) {
        queue_of_nums -> delete_by_index(pos - 1);
    }
    
    cout << "Очередь после удаления K элементов:" << endl;
    queue_of_nums -> show_queue();

    cout << "Введите номер элемента, с которого нужно добавить K элементов:" << endl;
    cin >> pos;
    for (int i = 0; i < number_of_changes; i++) {
        queue_of_nums -> add_value_by_index(pos - 1);
        pos++;
    }
    
    cout << "Очередь после добавления K элементов:" << endl;
    queue_of_nums -> show_queue();

    queue_of_nums -> write_in_file();
    delete queue_of_nums;
    cout << "Очередь записана в файл и удалена из памяти." << endl;

    cout << "Содержимое файла:" << endl;
    ifstream in("file_11_4.txt");
    if (in.is_open()) {
        int x;
        while (in >> x) {
            cout << x << " ";
        }
        cout << endl;
    }
    in.close();

    Queue *restored_queue_of_nums = new Queue;
    restored_queue_of_nums -> init();
    cout << "Создана новая очередь." << endl;

    restored_queue_of_nums -> resotre_from_file();
    cout << "Содержимое очереди, после взятия данных из файла:" << endl;
    restored_queue_of_nums -> show_queue();

    return 0;
}