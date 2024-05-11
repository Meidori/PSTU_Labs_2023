#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <QtWidgets>

class Node
{
public:
    char key;                   // ключ. Тип данных дан в варианте
    Node* ptrToParent;          // указатель на родительский узел
    Node* ptrToLeft;            // указатель на дочерний левый узел
    Node* ptrToRight;           // указатель на дочерний правый узел
    double x, y;                // координаты того, где будет находится узел на сцене. Объявлен тип double, но по итогу при работе автоматически переводились в целые
    int posInSubTree;           // вспомагательная нумерация узлов в строке для определения координат
    int level;                  // уровень узла в глубину


public:
    Node();
    Node(char key);
};

class BinaryTree
{
private:
    Node *ptrToTop = nullptr;       // указатель на корневой узел дерева

public:
    // Геттеры:
    Node* getTop();     // возвращает указатель на корневой узел
    char getMax();      // возвращает макисмальное значение в дереве
    char getMin();      // возвращает минимальное значение в дереве
    int getHeight(Node* root);      // возвращает высоту от узла с ключом key
    std::vector<double> getCoords(char key);    // возвращает координаты узла с ключом key
    std::vector<double> getCoordsOfParent(char key);    // возвращает координаты родительского узла от узла с ключом key

    // Генерация дерева
    void insert(char key);  // вставка узла в базовое дерево поиска
    void insertToPBBT(int startIndex, int endIndex, std::vector<char>& roots, BinaryTree& tree);    // вставка узла в идеально сбалансированное
    BinaryTree regenerateToPBBT();      // чтобы получить из базового дерева поиска, идеально сбалансированное дерево

    // Проверки:
    bool isEmpty();     // пустое ли дерево
    bool isInTree(char key);    // есть ли в дереве узел с ключом key
    bool hasParent(char key);   // если ли у узла с ключом key родительски узел

    // Обходы:
    std::vector<char> getAllElementsOfTree();   // обход и добавление всех узлов в вектор
    void traverseAndAddToVector(Node* root, std::vector<char>& result);

    void coordCalculation(Node* root);      // вычисление координат для каждого узла
};

#endif // BINARYTREE_H
