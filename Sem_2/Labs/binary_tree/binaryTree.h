#pragma once
#include <iostream>
#include <vector>


class Node 
{
public:
    char key;                   // ключ. Тип данных дан в варианте
    Node* ptrToParent;        // указатель на родительский узел
    Node* ptrToLeft;          // указатель на дочерний левый узел
    Node* ptrToRight;         // указатель на дочерний правый узел


public:
    Node(char key = 0);
};


class BinaryTree 
{
private:
    Node *ptrToTop = nullptr;       // указатель на корневой узел дерева

public:
    Node* getTop();

    void insert(char key);

    bool isInTree(char key);

    int getHeight(Node* root);

    void traverseAndAddToVector(Node* root, std::vector<char>& result);

    std::vector<char> getAllElementsOfTree();

    char getMax();

    char getMin();

    void insertToPBBT(int startIndex, int endIndex, std::vector<char>& roots, BinaryTree& tree);

    BinaryTree regenerateToPerfectlyBalancedBinaryTree();
};