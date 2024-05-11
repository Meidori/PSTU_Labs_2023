#include "addedge.h"
#include "ui_addedge.h"

AddNewEdgeWindow::AddNewEdgeWindow(Graph& graph, QWidget *parent)
    : QDialog(parent), m_graph(graph), ui(new Ui::AddNewEdgeWindow)
{
    ui->setupUi(this);

    connect(ui->addNewEdgeBtn, &QPushButton::clicked, this, &AddNewEdgeWindow::addNewEdge);
}

AddNewEdgeWindow::~AddNewEdgeWindow()
{
    delete ui;
}

void AddNewEdgeWindow::addNewEdge()
{
    // Получаем значения с lineEdit пользовательского интерфейса
    QString fromLine = ui->fromLine->text();
    QString toLine = ui->toLine->text();
    QString weightLine = ui->weightLine->text();
    // Переводим полученнные данные в int
    int from = fromLine.toInt();
    int to = toLine.toInt();
    int weight = weightLine.toInt();

    m_graph.addEdge(from, to, weight);  // добавляем ребро в матрицу смежности

    close();    // после добавления ребра, закрываем окно
}
