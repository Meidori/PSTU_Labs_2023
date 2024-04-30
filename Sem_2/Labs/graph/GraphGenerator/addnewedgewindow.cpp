// addnewedgewindow.cpp
#include "addnewedgewindow.h"
#include "ui_addnewedgewindow.h"

#include <QGraphicsScene>

AddNewEdgeWindow::AddNewEdgeWindow(const Graph& graph, QWidget *parent)
    : QDialog(parent), m_graph(graph), ui(new Ui::AddNewEdgeWindow)
{
    ui->setupUi(this);

    connect(ui->addNewEdgeBtn, SIGNAL(clicked()), this, SLOT(addNewEdge()));
}

AddNewEdgeWindow::~AddNewEdgeWindow()
{
    delete ui;
}

void AddNewEdgeWindow::addNewEdge()
{
    QString fromLine = ui->fromLine->text();
    QString toLine = ui->toLine->text();
    QString weightLine = ui->weightLine->text();
    int from = fromLine.toInt();
    int to = toLine.toInt();
    int weight = weightLine.toInt();
    m_graph.addEdge(from, to, weight);

    QGraphicsItemGroup** matrixOfGroups = m_graph.getMatrixOfGroups();
    QGraphicsItemGroup* groupFrom = matrixOfGroups[from];
    QGraphicsItemGroup* groupTo = matrixOfGroups[to];

    QPointF fromCenter = groupFrom->boundingRect().center();
    QPointF toCenter = groupTo->boundingRect().center();

    close();
}
