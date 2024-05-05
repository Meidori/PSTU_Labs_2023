#include "deletenodewindow.h"
#include "ui_deletenodewindow.h"

DeleteNodeWindow::DeleteNodeWindow(Graph& graph, QGraphicsScene* scene, QGraphicsView* printGraph, QGraphicsItemGroup** matrixOfGroups, QWidget *parent)
    : QDialog(parent), m_graph(graph), m_scene(scene), m_printGraph(printGraph), m_matrixOfGroups(matrixOfGroups), ui(new Ui::DeleteNodeWindow)
{
    ui->setupUi(this);

    connect(ui->delNodeBtn, SIGNAL(clicked()), this, SLOT(delNode()));
}

DeleteNodeWindow::~DeleteNodeWindow()
{
    delete ui;
}

void DeleteNodeWindow::delNode()
{
    QString nodeNumber = ui->numberLine->text();
    int number = nodeNumber.toInt();

    m_scene->removeItem(m_matrixOfGroups[number]);
    delete m_matrixOfGroups[number];
    m_matrixOfGroups[number] = nullptr;

    m_graph.delNode(number);
    close();
}
