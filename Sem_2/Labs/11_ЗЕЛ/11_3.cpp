#include <iostream>
#include <fstream>
using namespace std;


struct Node {
    int data;
    Node *ptr_to_next;
};


struct Stack {
    Node *ptr_to_top = nullptr;
    int size = 0;


    void init() {
        ptr_to_top = nullptr;
        size = 0;
    }


    bool is_empty() {
        return size == 0;
    }


    void push(int value) {
        Node *tmp = new Node;
        tmp -> data = value;
        tmp -> ptr_to_next = ptr_to_top;
        ptr_to_top = tmp;
        size++;
    }


    int pop() {
        int value = ptr_to_top -> data;
        Node *ptr_to_del_node = ptr_to_top;
        ptr_to_top = ptr_to_top -> ptr_to_next;
        delete ptr_to_del_node;
        size--;
        return value;
    }


    Node *top() {
        return ptr_to_top;
    }


    void delete_by_index(int index) {
        if (!(is_empty()) && index < size && index >= 0) {
            Stack *tmp_stack = new Stack;
            int value, length_size = size;
            for (int i = 0; i < length_size; i++) {
                value = pop();
                if (i != index) {
                    tmp_stack -> push(value);
                }
                else {
                    cout << "Удаляем элемент: " << value << endl;
                }          
            }

            length_size = tmp_stack -> size;
            for (int i = 0; i < length_size; i++) {
                value = tmp_stack -> pop();
                push(value);
            }

            delete tmp_stack;
        }
    }


    void add_by_index(int index) {
        int value;
        cout << "Введите значение элемента:" << endl;
        cin >> value;
        if (is_empty()) {
            push(value);
        }
        else if (index <= size && index >= 0){
            Stack *tmp_stack = new Stack;
            int value_from_stack, length_size = size;
            for (int i = 0; i < length_size; i++) {
                value_from_stack = pop();
                if (i == index) {
                    tmp_stack -> push(value);
                }
                tmp_stack -> push(value_from_stack);
            }
            if (index == length_size) {
                tmp_stack -> push(value);
            }

            length_size = tmp_stack -> size;
            for (int i = 0; i < length_size; i++) {
                value = tmp_stack -> pop();
                push(value);
            }

            delete tmp_stack;
        }
    }


    void write_in_file() {
        int stack_length = size, value;
        Stack *reversed_stack = new Stack;
        for (int i = 0; i < stack_length; i++) {
            value = pop();
            reversed_stack -> push(value);
        }
        ofstream out;
        out.open("file_11_3.txt");
        if (out.is_open()) {
            for (int i = 0; i < stack_length; i++) {
                out << reversed_stack -> pop() << endl;
            } 
        }
        out.close();
        delete reversed_stack; 
    }


    void resotre_from_file(Stack stack) {
        Stack *reversed_stack = new Stack;
        ifstream in;
        in.open("file_11_3.txt");
        int value;
        while (in >> value) {
            reversed_stack -> push(value);
        }
        in.close();
        
        int stack_length = reversed_stack -> size;
        for (int i = 0; i < stack_length; i++) {
            value = reversed_stack -> pop();
            push(value);
        }

        delete reversed_stack;
    }


    void show_stack() {
        if (is_empty()) {
            cout << "Стек пустой." << endl;
        }
        else {
            int value;
            Node *tmp = ptr_to_top;
            for (int i = 0; i < size; i++) {
                value = tmp -> data;
                tmp = tmp -> ptr_to_next;
                if (i == 0) {
                    cout << value;
                }
                else {
                    cout << " " << value;
                }
            }
            cout << endl;
            }
    }
};


int main() {
    Stack *stack_of_numbers = new Stack;
    stack_of_numbers -> init();
    int number_of_values, new_value;
    cout << "Введите количество значений, которое будет содержаться в стеке:" << endl;
    cin >> number_of_values;
    for (int i = 0; i < number_of_values; i++) {
        cout << "Введите значение:" << endl;
        cin >> new_value;
        stack_of_numbers -> push(new_value);
    }

    cout << "Стек после заполнения:" << endl;
    stack_of_numbers -> show_stack();

    int number_of_changes, pos;
    cout << "Введите число K - количество элементов, которые будут удалены/добавлены:" << endl;
    cin >> number_of_changes;
    cout << "Введите номер элемента, с которого нужно удалить K элементов:" << endl;
    cin >> pos;
    for (int i = 0; i < number_of_changes; i++) {
        stack_of_numbers -> delete_by_index(pos - 1);
    }

    cout << "Стек после удаления K элементов:" << endl;
    stack_of_numbers -> show_stack();

    cout << "Введите номер элемента, с которого нужно добавить K элементов:" << endl;
    cin >> pos;
    for (int i = 0; i < number_of_changes; i++) {
        stack_of_numbers -> add_by_index(pos - 1);
        pos++;
    }

    cout << "Стек после добавления K элементов:" << endl;
    stack_of_numbers -> show_stack();

    stack_of_numbers -> write_in_file();
    delete stack_of_numbers;
    cout << "Стек записан в файл и удален из памяти." << endl;

    cout << "Содержимое файла:" << endl;
    ifstream in("file_11_3.txt");
    if (in.is_open()) {
        int x;
        while (in >> x) {
            cout << x << " ";
        }
        cout << endl;
    }
    in.close();

    Stack *restored_stack_of_nums = new Stack;
    restored_stack_of_nums -> init();
    cout << "Создан новый стек." << endl;

    restored_stack_of_nums -> resotre_from_file(*restored_stack_of_nums);
    cout << "Содержимое стека, после взятия данных из файла:" << endl;
    restored_stack_of_nums -> show_stack();

    return 0;
}