#include "deleteedge.h"
#include "ui_deleteedge.h"

DeleteEdgeWindow::DeleteEdgeWindow(Graph& graph, QWidget *parent)
    : QDialog(parent), m_graph(graph), ui(new Ui::DeleteEdgeWindow)
{
    ui->setupUi(this);

    connect(ui->delEdgeBtn, &QPushButton::clicked, this, &DeleteEdgeWindow::delEdge);
}

DeleteEdgeWindow::~DeleteEdgeWindow()
{
    delete ui;
}

void DeleteEdgeWindow::delEdge()
{
    // Получаем значения с lineEdit пользовательского интерфейса
    QString fromLine = ui->fromLine->text();
    QString toLine = ui->toLine->text();
    // Переводим полученнные данные в int
    int from = fromLine.toInt();
    int to = toLine.toInt();
    m_graph.delEdge(from, to); // удаляем ребро из матрицы смежности

    close();    // после удаления ребра, закрываем окно
}
