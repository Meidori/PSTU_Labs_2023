#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>


class Node
{
public:
    char key;                   // ключ. Тип данных дан в варианте
    Node* ptrToParent;        // указатель на родительский узел
    Node* ptrToLeft;          // указатель на дочерний левый узел
    Node* ptrToRight;         // указатель на дочерний правый узел
    double x, y;


public:
    Node();
    Node(char key);
};


class BinaryTree
{
private:
    Node *ptrToTop = nullptr;       // указатель на корневой узел дерева

public:
    Node* getTop();

    void insert(char key);

    bool isEmpty();

    bool isInTree(char key);

    bool hasParent(char key);

    std::vector<double> getCoords(char key);

    std::vector<double> getCoordsOfParent(char key);

    int getHeight(Node* root);

    void traverseAndAddToVector(Node* root, std::vector<char>& result);

    void traverseAndPrint(Node* root);

    std::vector<char> getAllElementsOfTree();

    char getMax();

    char getMin();

    void insertToPBBT(int startIndex, int endIndex, std::vector<char>& roots, BinaryTree& tree);

    BinaryTree regenerateToPBBT();
};

#endif // BINARYTREE_H
