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
    ~GraphGenerator();

    void removeCurEllipses();
    void removeCurGroups();

public slots:
    void addNode();
    // bool eventFilter(QObject *object, QEvent *event);
    // void updateNodePosition(QGraphicsItemGroup *group);
    void addEdge();
    void updateArrows();

private:
    Graph graph;
    AddNewEdgeWindow addEdgeWindow;
    QGraphicsScene *scene;
    QGraphicsView *printGraph;
    Ui::GraphGenerator *ui;
};
#endif // GRAPHGENERATOR_H
