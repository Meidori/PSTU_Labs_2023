#include "deletenode.h"
#include "ui_deletenode.h"

DeleteNodeWindow::DeleteNodeWindow(Graph& graph, QGraphicsScene* scene, QGraphicsView* printGraph, QGraphicsItemGroup** matrixOfGroups, QWidget *parent)
    : QDialog(parent), m_graph(graph), m_scene(scene), m_printGraph(printGraph), m_matrixOfGroups(matrixOfGroups), ui(new Ui::DeleteNodeWindow)
{
    ui->setupUi(this);

    connect(ui->delNodeBtn, &QPushButton::clicked, this, &DeleteNodeWindow::delNode);
}

DeleteNodeWindow::~DeleteNodeWindow()
{
    delete ui;
}

void DeleteNodeWindow::delNode()
{
    // Получаем значения с lineEdit пользовательского интерфейса
    QString nodeNumber = ui->numberLine->text();
    // Переводим полученнные данные в int
    int number = nodeNumber.toInt();

    // Удаляем со сцены объект узла (эллипс и текст)
    m_scene->removeItem(m_matrixOfGroups[number]);
    delete m_matrixOfGroups[number];
    m_matrixOfGroups[number] = nullptr;

    m_graph.delNode(number);    // удаляем узел из матрицы смежности
    close();    // после удаления ребра, закрываем окно
}
