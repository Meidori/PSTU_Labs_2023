#include "binarytreegenerator.h"
#include "ui_binarytreegenerator.h"
#include "binarytree.h"

#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <vector>

BinaryTreeGenerator::BinaryTreeGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BinaryTreeGenerator)
{
    ui -> setupUi(this);

    connect(ui -> addNodeBtn, SIGNAL(clicked()), this, SLOT(addNode()));

    connect(ui -> printTreeBtn, SIGNAL(clicked()), this, SLOT(traverseAndPrintBase()));

    connect(ui -> printPBBTBtn, SIGNAL(clicked()), this, SLOT(traverseAndPrintPBBT()));

    connect(ui -> printMaxBtn, SIGNAL(clicked()), this, SLOT(printMaxNode()));

    connect(ui -> printMinBtn, SIGNAL(clicked()), this, SLOT(printMinNode()));

    connect(ui -> printHeightsBtn, SIGNAL(clicked()), this, SLOT(printHeights()));

    graphicsView = ui -> graphicsView;
    scene = new QGraphicsScene;
    graphicsView -> setScene(scene);
}

void BinaryTreeGenerator::addNode() {
    QString nodeName = ui -> addNodeLine -> text();
    if (nodeName.isEmpty())
        return; // Защита от пустого имени узла

    std::string node = nodeName.toStdString();
    tree.insert(node[0]);
}

void BinaryTreeGenerator::traverseAndPrintBase()
{
    scene->clear();
    Node* root = tree.getTop();
    traverseAndPrint(root, tree);
}

void BinaryTreeGenerator::traverseAndPrintPBBT()
{
    scene->clear();
    PBBT = tree.regenerateToPBBT();
    if (PBBT.isEmpty()) {
        qDebug() << "PBBT is empty!";
        return;
    }
    Node* root = PBBT.getTop();
    traverseAndPrint(root, PBBT);
}

void BinaryTreeGenerator::traverseAndPrint(Node* root, BinaryTree& tree)
{
    if (root != nullptr)
    {
        traverseAndPrint(root->ptrToLeft, tree);

        QString node = QString::fromLatin1(&(root->key), 1);
        QGraphicsEllipseItem *ellipse = scene->addEllipse(root->x, root->y, 50, 50, QPen(Qt::black), QBrush(Qt::white));
        QGraphicsTextItem *textItem = scene->addText(node);
        textItem->setPos(ellipse->boundingRect().center().x() - textItem->boundingRect().width() / 2,
                         ellipse->boundingRect().center().y() - textItem->boundingRect().height() / 2);

        if (!tree.isEmpty() && tree.hasParent(root->key) && root->ptrToParent != nullptr) {
            double parentX = root->ptrToParent->x;
            double parentY = root->ptrToParent->y;
            double currentNodeX = root->x;
            double currentNodeY = root->y;

            // Найдем центры эллипсов
            QPointF parentCenter(parentX + 25, parentY + 25); // 25 - это половина ширины/высоты эллипса
            QPointF currentNodeCenter(currentNodeX + 25, currentNodeY + 25);

            // Создаем линию между центрами эллипсов
            scene->addLine(parentCenter.x(), parentCenter.y(), currentNodeCenter.x(), currentNodeCenter.y(), QPen(Qt::black));
        }
        ui->graphicsView->update();

        traverseAndPrint(root->ptrToRight, tree);
    }
}

void BinaryTreeGenerator::printMaxNode() {
    char node = tree.getMax();
    QString maxNode = QString::fromLatin1(&node, 1);
    ui->maxValueLabel->setText(maxNode);
}

void BinaryTreeGenerator::printMinNode() {
    char node = tree.getMin();
    QString minNode = QString::fromLatin1(&node, 1);
    ui->minValueLabel->setText(minNode);
}

void BinaryTreeGenerator::printHeights() {
    int treeHeight = tree.getHeight(tree.getTop());
    int PBBTHeight = PBBT.getHeight(PBBT.getTop());
    ui->heightsValueLabel->setText("Base: " + QString::number(treeHeight) + "\nPBBT: " + QString::number(PBBTHeight));
}

BinaryTreeGenerator::~BinaryTreeGenerator()
{
    delete ui;
}
