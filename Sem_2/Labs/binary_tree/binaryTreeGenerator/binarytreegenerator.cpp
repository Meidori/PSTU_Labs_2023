#include "binarytreegenerator.h"
#include "ui_binarytreegenerator.h"

BinaryTreeGenerator::BinaryTreeGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BinaryTreeGenerator)
{
    ui->setupUi(this);

    graphicsView = ui->graphicsView;
    scene = new QGraphicsScene;
    graphicsView->setScene(scene);

    connect(ui->addNodeBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::addNode);
    connect(ui->printTreeBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::traverseAndPrintBase);
    connect(ui->printPBBTBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::traverseAndPrintPBBT);
    connect(ui->printMaxBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::printMaxNode);
    connect(ui->printMinBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::printMinNode);
    connect(ui->printHeightsBtn, &QPushButton::clicked, this, &BinaryTreeGenerator::printHeights);
}

BinaryTreeGenerator::~BinaryTreeGenerator()
{
    delete ui;
}

void BinaryTreeGenerator::addNode() {
    // Считываем имя узла
    QString nodeName = ui->addNodeLine->text();
    if (nodeName.isEmpty())
        return; // защита от пустого имени узла
    std::string node = nodeName.toStdString();

    tree.insert(node[0]);   // добавляем узел в дерево
}

void BinaryTreeGenerator::traverseAndPrintBase()
{
    scene->clear();     // очищаем сцену
    tree.coordCalculation(tree.getTop());   // вычисляем координаты
    if (tree.isEmpty())
    {
        qDebug() << "Tree is empty";
        return;
    }
    Node* root = tree.getTop();
    traverseAndPrint(root, tree);   // выводим дерево
}

void BinaryTreeGenerator::traverseAndPrintPBBT()
{
    scene->clear();     // очищаем сцену
    PBBT = tree.regenerateToPBBT();         // на основе базового дерева поиска делаем идеально сбалансированное
    PBBT.coordCalculation(PBBT.getTop());   // вычисляем координаты
    if (PBBT.isEmpty())
    {
        qDebug() << "PBBT is empty!";
        return;
    }
    Node* root = PBBT.getTop();
    traverseAndPrint(root, PBBT);   // выводим дерево
}

void BinaryTreeGenerator::traverseAndPrint(Node* root, BinaryTree& tree)
{
    if (root != nullptr)
    {
        // Рекурсивно обходим левое поддерево
        traverseAndPrint(root->ptrToLeft, tree);

        // "Рисуем" узел
        QString node = QString::fromLatin1(&(root->key), 1);
        QGraphicsEllipseItem *ellipse = scene->addEllipse(root->x, root->y, 64, 64, QPen(Qt::black), QBrush(Qt::lightGray));
        QGraphicsTextItem *textItem = scene->addText(node);
        textItem->setPos(ellipse->boundingRect().center().x() - textItem->boundingRect().width() / 2,
                         ellipse->boundingRect().center().y() - textItem->boundingRect().height() / 2);

        // Проверяем, не пусто ли дерево и существует ли родитель у текущего узла
        if (!tree.isEmpty() && tree.hasParent(root->key) && root->ptrToParent != nullptr)
        {
            // Берем координаты
            double parentX = root->ptrToParent->x;
            double parentY = root->ptrToParent->y;
            double currentNodeX = root->x;
            double currentNodeY = root->y;

            // Найдем центры эллипсов
            QPointF parentCenter(parentX + 32, parentY + 32);
            QPointF currentNodeCenter(currentNodeX + 32, currentNodeY + 32);

            // Создаем линию между центрами эллипсов
            scene->addLine(parentCenter.x(), parentCenter.y(), currentNodeCenter.x(), currentNodeCenter.y(), QPen(Qt::black));
        }
        ui->graphicsView->update();

        // Рекурсивно обходим правое поддерево
        traverseAndPrint(root->ptrToRight, tree);
    }
}

void BinaryTreeGenerator::printMaxNode()
{
    char node = tree.getMax();                          // Получаем максимаьный элемент дерева
    QString maxNode = QString::fromLatin1(&node, 1);    // переводим его в QString
    ui->maxValueLabel->setText(maxNode);                // и выводим на экран
}

void BinaryTreeGenerator::printMinNode()
{
    char node = tree.getMin();                          // Получаем минимальный элемент дерева
    QString minNode = QString::fromLatin1(&node, 1);    // переводим его в QString
    ui->minValueLabel->setText(minNode);                // и выводим на экран
}

void BinaryTreeGenerator::printHeights()
{
    int treeHeight = tree.getHeight(tree.getTop());     // получаем высоту дерева поиска (базового)
    int PBBTHeight = PBBT.getHeight(PBBT.getTop());     // получаем высоту идеально сбалансированного дерева
    ui->heightsValueLabel->setText("Base: " + QString::number(treeHeight) + "\nPBBT: " + QString::number(PBBTHeight));  // вывод
}
