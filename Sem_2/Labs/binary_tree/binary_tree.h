#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


class Node {
public:
    char key;                   // ключ. Тип данных дан в варианте
    Node* ptr_to_parent;        // указатель на родительский узел
    Node* ptr_to_left;          // указатель на дочерний левый узел
    Node* ptr_to_right;         // указатель на дочерний правый узел


public:
    Node(char key = 0) {
        this -> key = key;
        ptr_to_parent = nullptr;
        ptr_to_left = nullptr;
        ptr_to_right = nullptr;
    }
};


class Binary_Tree {
private:
    Node *ptr_to_top = nullptr;       // указатель на корневой узел дерева

public:
    Node* get_top() {
        return ptr_to_top;
    }


    void insert(char key) {
        if (ptr_to_top == nullptr) {
            ptr_to_top = new Node;
            ptr_to_top -> key = key;
            ptr_to_top -> ptr_to_left = nullptr;
            ptr_to_top -> ptr_to_right = nullptr;
            ptr_to_top -> ptr_to_parent = nullptr;
        }
        else {
            Node* root = ptr_to_top;
            while (root != nullptr) {
                if (key < root -> key) {
                    if (root -> ptr_to_left == nullptr) {
                        Node* new_root = new Node;
                        new_root -> key = key;
                        new_root -> ptr_to_left = nullptr;
                        new_root -> ptr_to_right = nullptr;
                        new_root -> ptr_to_parent = root;
                        root -> ptr_to_left = new_root;
                        return;
                    }
                    else {
                        root = root -> ptr_to_left;
                    }
                }
                else if (key > root -> key) {
                    if (root -> ptr_to_right == nullptr) {
                        Node* new_root = new Node;
                        new_root -> key = key;
                        new_root -> ptr_to_left = nullptr;
                        new_root -> ptr_to_right = nullptr;
                        new_root -> ptr_to_parent = root;
                        root -> ptr_to_right = new_root;
                        return;
                    } 
                    else {
                        root = root -> ptr_to_right;
                    }
                }
                else {
                    std::cout << "Бинарное дерево уже имеет узел с ключом " << key << "." << std::endl;
                    std::cout << "Элемент не добавлен в дерево." << std::endl;
                    return;
                }
            }
        }
    }


    bool is_in_tree(char key) {
        Node *root = ptr_to_top;
        while (root != nullptr) {
            if (root->key == key) {
                return true;
            }
            else if (key < root->key) {
                root = root->ptr_to_left;
            }
            else {
                root = root->ptr_to_right;
            }
        }
        return false;
    }


    int get_height(Node* root) {
        if (root == nullptr) {
            return 0; // Высота пустого дерева равна 0
        } 
        else {
            // Рекурсивно находим высоту для левого и правого поддеревьев
            int left_height = get_height(root -> ptr_to_left);
            int right_height = get_height(root -> ptr_to_right);
            
            // Высота дерева - максимальная высота из левого и правого поддеревьев, плюс 1 (текущий уровень)
            return std::max(left_height, right_height) + 1;
        }
    }


    void traverse_and_add_to_vector(Node* root, std::vector<char>& result) {
        if (root != nullptr) {
            traverse_and_add_to_vector(root -> ptr_to_left, result);
            result.push_back(root -> key);
            traverse_and_add_to_vector(root -> ptr_to_right, result);
        }
    }


    std::vector<char> get_all_elements_of_tree() {
        std::vector<char> result;
        traverse_and_add_to_vector(ptr_to_top, result);
        return result;
    }


    char get_max() {
        std::vector<char> all_elements = get_all_elements_of_tree();
        return *max_element(all_elements.begin(), all_elements.end());
    }


    char get_min() {
        std::vector<char> all_elements = get_all_elements_of_tree();
        return *min_element(all_elements.begin(), all_elements.end());
    }


    void insert_to_PBBT(int start_index, int end_index, std::vector<char>& roots, Binary_Tree& tree) {
        if (start_index > end_index) {
            return;
        }

        int mid_index = (start_index + end_index) / 2;
        
        if (tree.is_in_tree(roots[mid_index])) {
            return;
        }

        tree.insert(roots[mid_index]);
        
        insert_to_PBBT(start_index, mid_index - 1, roots, tree); // Левая часть
        insert_to_PBBT(mid_index + 1, end_index, roots, tree);   // Правая часть
    }


    Binary_Tree regenerate_to_perfectly_balanced_binary_tree() {
        Binary_Tree PBBT_tree;
        std::vector<char> all_roots = get_all_elements_of_tree();
        sort(all_roots.begin(), all_roots.end());
        insert_to_PBBT(0, all_roots.size() - 1, all_roots, PBBT_tree);
        return PBBT_tree;
    }
};