#include "binarytree.h"

Node::Node()
{
    key = ' ';
    ptrToParent = nullptr;
    ptrToLeft = nullptr;
    ptrToRight = nullptr;
    x = 0.0;
    y = 0.0;
    posInSubTree = 0;
    level = 0;
}

Node::Node(char key)
{
    this->key = key;
    ptrToParent = nullptr;
    ptrToLeft = nullptr;
    ptrToRight = nullptr;
    x = 0.0;
    y = 0.0;
    posInSubTree = 0;
    level = 0;
}


Node* BinaryTree::getTop()
{
    return ptrToTop;
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

int BinaryTree::getHeight(Node* root)
{
    if (root == nullptr)
    {
        return 0; // Высота пустого дерева равна 0
    }
    else
    {
        // Рекурсивно находим высоту для левого и правого поддеревьев
        int leftHeight = getHeight(root->ptrToLeft);
        int rightHeight = getHeight(root->ptrToRight);

        // Высота дерева - максимальная высота из левого и правого поддеревьев, плюс 1 (текущий уровень)
        return std::max(leftHeight, rightHeight) + 1;
    }
}

std::vector<double> BinaryTree::getCoords(char key)
{
    std::vector<double> returnValue;
    Node *root = ptrToTop;
    while (root != nullptr)
    {
        if (root->key == key)       // нашли нужный узел
        {
            returnValue.push_back(root->x);
            returnValue.push_back(root->y);
            return returnValue;
        }
        else if (key < root->key)   // если ключ меньше, идем в левое поддерево
        {
            root = root->ptrToLeft;
        }
        else                        // если больше, то в правое
        {
            root = root->ptrToRight;
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
        if (root->key == key)
        {
            returnValue.push_back(root->ptrToParent->x);
            returnValue.push_back(root->ptrToParent->y);
            return returnValue;
        }
        else if (key < root->key)
        {
            root = root->ptrToLeft;
        }
        else
        {
            root = root->ptrToRight;
        }
    }
    return returnValue;
}

void BinaryTree::insert(char key)
{
    if (ptrToTop == nullptr)    // если это первый узел в дереве
    {
        ptrToTop = new Node;
        ptrToTop->key = key;
        ptrToTop->ptrToLeft = nullptr;
        ptrToTop->ptrToRight = nullptr;
        ptrToTop->ptrToParent = nullptr;
        ptrToTop->x = 0.0;
        ptrToTop->y = 0.0;
        ptrToTop->posInSubTree = 1;
        ptrToTop->level = 1;
    }
    else
    {
        Node* root = ptrToTop;
        while (root != nullptr)
        {
            if (key < root->key)    // учитываем условие дерева поиска
            {
                if (root->ptrToLeft == nullptr)     // если свободное добавляем
                {
                    Node* newRoot = new Node;
                    newRoot->key = key;
                    newRoot->ptrToLeft = nullptr;
                    newRoot->ptrToRight = nullptr;
                    newRoot->ptrToParent = root;
                    newRoot->posInSubTree = root->posInSubTree * 2 - 1;
                    newRoot->level = root->level + 1;
                    root->ptrToLeft = newRoot;

                    return;
                }
                else
                {
                    root = root->ptrToLeft;    // двигаемся дальше вправо
                }
            }
            else if (key > root->key)   // учитываем условие дерева поиска
            {
                if (root->ptrToRight == nullptr)    // если свободное добавляем
                {
                    Node* newRoot = new Node;
                    newRoot->key = key;
                    newRoot->ptrToLeft = nullptr;
                    newRoot->ptrToRight = nullptr;
                    newRoot->ptrToParent = root;
                    if (root == ptrToTop)
                    {
                        newRoot->posInSubTree = 1;
                    }
                    else
                    {
                        newRoot->posInSubTree = root->posInSubTree * 2;
                    }
                    newRoot->level = root->level + 1;
                    root->ptrToRight = newRoot;

                    return;
                }
                else
                {
                    root = root->ptrToRight;    // двигаемся дальше влево
                }
            }
            else
            {
                // Значения в дереве уникальны
                std::cout << "Бинарное дерево уже имеет узел с ключом " << key << "." << std::endl;
                std::cout << "Элемент не добавлен в дерево." << std::endl;
                return;
            }
        }
    }
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
    // На основе базового дерева поиска создаем идеально сбалансированное (используя вектор всех элементов дерева)
    BinaryTree PBBT;
    std::vector<char> allRoots = getAllElementsOfTree();
    sort(allRoots.begin(), allRoots.end());
    insertToPBBT(0, allRoots.size() - 1, allRoots, PBBT);
    return PBBT;
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
        if (root->key == key)
        {
            return true;
        }
        else if (key < root->key)
        {
            root = root->ptrToLeft;
        }
        else
        {
            root = root->ptrToRight;
        }
    }
    return false;
}

bool BinaryTree::hasParent(char key)
{
    if (isInTree(key) && ptrToTop->key != key)
    {
        return true;
    }
    return false;
}

std::vector<char> BinaryTree::getAllElementsOfTree()
{
    // Получаем все элементы дерева в вектор
    std::vector<char> result;
    traverseAndAddToVector(ptrToTop, result);
    return result;
}

void BinaryTree::traverseAndAddToVector(Node* root, std::vector<char>& result)
{
    if (root != nullptr)
    {
        traverseAndAddToVector(root->ptrToLeft, result);
        result.push_back(root->key);
        traverseAndAddToVector(root->ptrToRight, result);
    }
}

void BinaryTree::coordCalculation(Node* root)
{   // Алгоритм работает не идеально, но вывести дерево на небольшое кол-во узлов позволяет
    int height = getHeight(ptrToTop);
    int width = 64 * height + 96 * height;
    if (root != nullptr)
    {
        coordCalculation(root->ptrToLeft);
        if (root == ptrToTop)
        {
            root->x = 0.0;
            root->y = 0.0;
        }
        else if (root->key > ptrToTop->key)
        {
            root->x = width / root->level * root->posInSubTree;
            root->y = (root->level - 1) * 100;
        }
        else if (root->key < ptrToTop->key)
        {
            root->x = -width + width / root->level * root->posInSubTree;
            root->y = (root->level - 1) * 100;
        }

        qDebug() << root->key << " " << root->x << " " << root->y;
        coordCalculation(root->ptrToRight);
    }
}





