#include "deleteedgewindow.h"
#include "ui_deleteedgewindow.h"

DeleteEdgeWindow::DeleteEdgeWindow(const Graph& graph, QWidget *parent)
    : QDialog(parent), m_graph(graph), ui(new Ui::DeleteEdgeWindow)
{
    ui->setupUi(this);

    connect(ui->delEdgeBtn, SIGNAL(clicked()), this, SLOT(delEdge()));
}

DeleteEdgeWindow::~DeleteEdgeWindow()
{
    delete ui;
}

void DeleteEdgeWindow::delEdge()
{
    QString fromLine = ui->fromLine->text();
    QString toLine = ui->toLine->text();
    int from = fromLine.toInt();
    int to = toLine.toInt();
    m_graph.delEdge(from, to);

    close();
}
