#include "binarytree.h"
#include "binarytreegenerator.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include <QtWidgets>


Node::Node()
{
    key = 'a';
    ptrToParent = nullptr;
    ptrToLeft = nullptr;
    ptrToRight = nullptr;
    x = 0.0;
    y = 0.0;
}


Node::Node(char key)
{
    this -> key = key;
    ptrToParent = nullptr;
    ptrToLeft = nullptr;
    ptrToRight = nullptr;
    x = 0.0;
    y = 0.0;
}


Node* BinaryTree::getTop()
{
    return ptrToTop;
}


void BinaryTree::insert(char key)
{
    if (ptrToTop == nullptr)
    {
        ptrToTop = new Node;
        ptrToTop -> key = key;
        ptrToTop -> ptrToLeft = nullptr;
        ptrToTop -> ptrToRight = nullptr;
        ptrToTop -> ptrToParent = nullptr;
        ptrToTop -> x = 0.0;
        ptrToTop -> y = 0.0;
    }
    else
    {
        Node* root = ptrToTop;
        while (root != nullptr)
        {
            if (key < root -> key)
            {
                if (root -> ptrToLeft == nullptr)
                {
                    Node* newRoot = new Node;
                    newRoot -> key = key;
                    newRoot -> ptrToLeft = nullptr;
                    newRoot -> ptrToRight = nullptr;
                    newRoot -> ptrToParent = root;
                    root -> ptrToLeft = newRoot;
                    newRoot -> x = root -> x - 1000 / std::pow(2, getHeight(ptrToTop) - 1);
                    newRoot -> y = root -> y + 100;

                    return;
                }
                else
                {
                    root = root -> ptrToLeft;
                }
            }
            else if (key > root -> key)
            {
                if (root -> ptrToRight == nullptr)
                {
                    Node* newRoot = new Node;
                    newRoot -> key = key;
                    newRoot -> ptrToLeft = nullptr;
                    newRoot -> ptrToRight = nullptr;
                    newRoot -> ptrToParent = root;
                    root -> ptrToRight = newRoot;
                    newRoot -> x = root -> x + 100 + 1000 / std::pow(2, getHeight(ptrToTop) - 1);
                    newRoot -> y = root -> y + 100;

                    return;
                }
                else
                {
                    root = root -> ptrToRight;
                }
            }
            else
            {
                std::cout << "Бинарное дерево уже имеет узел с ключом " << key << "." << std::endl;
                std::cout << "Элемент не добавлен в дерево." << std::endl;
                return;
            }
        }
    }
}


bool BinaryTree::isEmpty()
{
    return ptrToTop == nullptr;
}


bool BinaryTree::isInTree(char key)
{
    Node *root = ptrToTop;
    while (root != nullptr)
    {
        if (root -> key == key)
        {
            return true;
        }
        else if (key < root->key)
        {
            root = root -> ptrToLeft;
        }
        else
        {
            root = root -> ptrToRight;
        }
    }
    return false;
}


bool BinaryTree::hasParent(char key) {
    if (isInTree(key) && ptrToTop -> key != key)
    {
        return true;
    }
    return false;
}


std::vector<double> BinaryTree::getCoords(char key)
{
    std::vector<double> returnValue;
    Node *root = ptrToTop;
    while (root != nullptr)
    {
        if (root -> key == key)
        {
            returnValue.push_back(root -> x);
            returnValue.push_back(root -> y);
            return returnValue;
        }
        else if (key < root->key)
        {
            root = root -> ptrToLeft;
        }
        else
        {
            root = root -> ptrToRight;
        }
    }
    return returnValue;
}


std::vector<double> BinaryTree::getCoordsOfParent(char key)
{
    std::vector<double> returnValue;
    Node *root = ptrToTop;
    while (root != nullptr)
    {
        if (root -> key == key)
        {
            returnValue.push_back(root -> ptrToParent -> x);
            returnValue.push_back(root -> ptrToParent -> y);
            return returnValue;
        }
        else if (key < root->key)
        {
            root = root -> ptrToLeft;
        }
        else
        {
            root = root -> ptrToRight;
        }
    }
    return returnValue;
}


int BinaryTree::getHeight(Node* root)
{
    if (root == nullptr)
    {
        return 0; // Высота пустого дерева равна 0
    }
    else
    {
        // Рекурсивно находим высоту для левого и правого поддеревьев
        int leftHeight = getHeight(root -> ptrToLeft);
        int rightHeight = getHeight(root -> ptrToRight);

        // Высота дерева - максимальная высота из левого и правого поддеревьев, плюс 1 (текущий уровень)
        return std::max(leftHeight, rightHeight) + 1;
    }
}


void BinaryTree::traverseAndAddToVector(Node* root, std::vector<char>& result)
{
    if (root != nullptr)
    {
        traverseAndAddToVector(root -> ptrToLeft, result);
        result.push_back(root -> key);
        traverseAndAddToVector(root -> ptrToRight, result);
    }
}


std::vector<char> BinaryTree::getAllElementsOfTree()
{
    std::vector<char> result;
    traverseAndAddToVector(ptrToTop, result);
    return result;
}


char BinaryTree::getMax()
{
    std::vector<char> allElements = getAllElementsOfTree();
    return *max_element(allElements.begin(), allElements.end());
}


char BinaryTree::getMin()
{
    std::vector<char> allElements = getAllElementsOfTree();
    return *min_element(allElements.begin(), allElements.end());
}


void BinaryTree::insertToPBBT(int startIndex, int endIndex, std::vector<char>& roots, BinaryTree& tree)
{
    if (startIndex <= endIndex)
    {
        int midIndex = (startIndex + endIndex) / 2;

        // Вставляем узел в дерево PBBT
        tree.insert(roots[midIndex]);

        // Рекурсивно вызываем для левой и правой половин диапазона
        insertToPBBT(startIndex, midIndex - 1, roots, tree);
        insertToPBBT(midIndex + 1, endIndex, roots, tree);
    }
}

BinaryTree BinaryTree::regenerateToPBBT()
{
    BinaryTree PBBT;
    std::vector<char> allRoots = getAllElementsOfTree();
    sort(allRoots.begin(), allRoots.end());
    insertToPBBT(0, allRoots.size() - 1, allRoots, PBBT);
    return PBBT;
}

