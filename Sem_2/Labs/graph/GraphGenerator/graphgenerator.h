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

    QPolygonF createArrowHead(const QPointF& startPoint, const QPointF& endPoint);

public slots:
    void addNode();
    void delNode();
    void updateSerialNumbers();
    bool eventFilter(QObject *object, QEvent *event);
    void addEdge();
    void delEdge();
    void updateArrows();

private:
    Graph graph;
    AddNewEdgeWindow addEdgeWindow;
    QGraphicsScene *scene;
    QGraphicsView *printGraph;
    Ui::GraphGenerator *ui;
};
#endif // GRAPHGENERATOR_H