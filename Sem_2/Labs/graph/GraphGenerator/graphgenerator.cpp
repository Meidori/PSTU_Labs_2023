#include "graphgenerator.h"
#include "ui_graphgenerator.h"
#include "addnewedgewindow.h"
#include "ui_addnewedgewindow.h"
#include "graph.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

GraphGenerator::GraphGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphGenerator)
    , addEdgeWindow(graph)
{
    ui->setupUi(this);

    printGraph = ui -> printGraph;
    scene = new QGraphicsScene;
    printGraph -> setScene(scene);

    connect(ui->addNodeBtn, SIGNAL(clicked()), this, SLOT(addNode()));

    connect(ui->addEdgeBtn, SIGNAL(clicked()), this, SLOT(addEdge()));
}

void GraphGenerator::addNode()
{
    QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 64, 64, QPen(Qt::black), QBrush(Qt::lightGray));

    QString nodeSerialNumber = QString::number(graph.getSerialNumber());
    QGraphicsTextItem *textItem = scene->addText(nodeSerialNumber);
    textItem->setPos(node->boundingRect().center().x() - textItem->boundingRect().width() / 2,
                     node->boundingRect().center().y() - textItem->boundingRect().height() / 2);

    QGraphicsItemGroup *group = scene->createItemGroup({node, textItem});
    group->setFlag(QGraphicsItem::ItemIsMovable, true);

    graph.resizeMatrix(1);
    graph.addNodeOnLastPos(node, group);
    graph.increaseSerialNumber();

    // graph.printMatrix();
}

void GraphGenerator::addEdge()
{
    AddNewEdgeWindow addEdgeWindow(graph);
    addEdgeWindow.setModal(true);
    addEdgeWindow.exec();

    printArrows();

    graph.printMatrix();
}

void GraphGenerator::printArrows()
{
    int** matrix = graph.getMatrix();
    QGraphicsEllipseItem** matrixOfEllipses = graph.getMatrixOfEllipses();
}

GraphGenerator::~GraphGenerator()
{
    delete scene;
    delete ui;
}
