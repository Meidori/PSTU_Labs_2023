#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "graph.h"
#include "addnewedgewindow.h"
#include "ui_addnewedgewindow.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class GraphGenerator; }
QT_END_NAMESPACE

class GraphGenerator : public QMainWindow
{
    Q_OBJECT

public:
    GraphGenerator(QWidget *parent = nullptr);
    void printArrows();
    ~GraphGenerator();

public slots:
    void addNode();
    void addEdge();

private:
    Graph graph;
    AddNewEdgeWindow addEdgeWindow;
    QGraphicsScene *scene;
    QGraphicsView *printGraph;
    Ui::GraphGenerator *ui;
};
#endif // GRAPHGENERATOR_H
