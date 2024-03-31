#pragma once


struct Node {
    int data;
    Node *ptr_to_next = nullptr;
    Node *ptr_to_prev = nullptr;
};


struct List {
    Node *ptr_to_first = nullptr;
    Node *ptr_to_last = nullptr;


    void init() {
        ptr_to_first = nullptr;
        ptr_to_last = nullptr;
    }


    bool is_empty() {
        return ptr_to_first == nullptr;
    }


    int get_length() {
        if (is_empty()) {
            return 0;
        }
        else {
            Node *tmp = new Node;
            int counter = 1;
            tmp = ptr_to_first;
            while (tmp -> ptr_to_next != nullptr) {
                counter++;
                tmp = tmp -> ptr_to_next;
            }
            return counter;
        }
    }


    void push_back(int value) {
        Node *tmp = new Node;
        tmp -> data = value;
        if (is_empty()) {
            ptr_to_first = tmp;
            ptr_to_last = tmp;
        }
        else {
            ptr_to_last -> ptr_to_next = tmp;
            tmp -> ptr_to_prev = ptr_to_last;
            ptr_to_last = tmp;
        }
    }


    int pop(int index) {
        int list_length = get_length();
        if (!(is_empty()) && index < list_length && index >= 0) {
            Node *tmp = ptr_to_first;
            for (int i = 0; i < index; i++) {
                tmp = tmp -> ptr_to_next;
            }
            if (index == 0) {
                if (list_length == 1) {
                    ptr_to_first = nullptr;
                    ptr_to_last = nullptr;
                }
                else {
                    tmp -> ptr_to_next -> ptr_to_prev = tmp -> ptr_to_prev;
                    ptr_to_first = tmp -> ptr_to_next;
                    
                }
            }
            else if (index == list_length - 1) {
                tmp -> ptr_to_prev -> ptr_to_next = tmp -> ptr_to_next;
                ptr_to_last = tmp -> ptr_to_prev;
            }
            else {
                tmp -> ptr_to_prev -> ptr_to_next = tmp -> ptr_to_next;
                tmp -> ptr_to_next -> ptr_to_prev = tmp -> ptr_to_prev;
            }
            int deleted_value = tmp -> data;
            delete tmp;
            return deleted_value;
        }
        return 0;
    }
};