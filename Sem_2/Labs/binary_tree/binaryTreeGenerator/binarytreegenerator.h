#ifndef BINARYTREEGENERATOR_H
#define BINARYTREEGENERATOR_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <binarytree.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BinaryTreeGenerator; }
QT_END_NAMESPACE

class BinaryTreeGenerator : public QMainWindow
{
    Q_OBJECT

public:
    BinaryTreeGenerator(QWidget *parent = nullptr);
    BinaryTree tree;
    BinaryTree PBBT;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    ~BinaryTreeGenerator();

public slots:
    void addNode();
    void traverseAndPrintBase();
    void traverseAndPrintPBBT();
    void traverseAndPrint(Node* root, BinaryTree& tree);
    void printMaxNode();
    void printMinNode();
    void printHeights();

private:
    Ui::BinaryTreeGenerator *ui;
};
#endif // BINARYTREEGENERATOR_H
