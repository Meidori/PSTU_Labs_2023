#ifndef BINARYTREEGENERATOR_H
#define BINARYTREEGENERATOR_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsTextItem>
#include <vector>

#include "binarytree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BinaryTreeGenerator; }
QT_END_NAMESPACE

class BinaryTreeGenerator : public QMainWindow
{
    Q_OBJECT

public:
    BinaryTreeGenerator(QWidget *parent = nullptr);
    ~BinaryTreeGenerator();

    void traverseAndPrint(Node* root, BinaryTree& tree);    // вывод дерева

public slots:
    void addNode();                 // добавление узла
    void traverseAndPrintBase();    // сигнал вывода дерева поиска (базового)
    void traverseAndPrintPBBT();    // сигнал вывода идеально сбалансированного дерева
    void printMaxNode();            // вывод максимального значения в дереве
    void printMinNode();            // вывод минимального значения в дереве
    void printHeights();            // вывод высоты дерева

private:
    BinaryTree tree;    // Дерево поиска
    BinaryTree PBBT;    // Идеально сбалансированное дерево

    Ui::BinaryTreeGenerator *ui;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
};
#endif // BINARYTREEGENERATOR_H
