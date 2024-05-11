#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

#include "graph.h"
#include "addedge.h"
#include "deleteedge.h"
#include "deletenode.h"
#include "searchmenu.h"
#include "tsp.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GraphGenerator; }
QT_END_NAMESPACE

class GraphGenerator : public QMainWindow
{
    Q_OBJECT

public:
    GraphGenerator(QWidget *parent = nullptr);
    ~GraphGenerator();

    QPolygonF createArrowHead(const QPointF& startPoint, const QPointF& endPoint);      // визуализация наконечника стрелки
    void updateSerialNumbers();     // обновление нумерации узлов, если удаляется узел

public slots:
    // Визуализация графа:
    void addNode();     // добавление узла
    void delNode();     // удаление узла
    void addEdge();     // добавление ребра
    void delEdge();     // удаление ребра
    void updateArrows();    // на случай, если стрелки автометически не обновились при перемещении
    bool eventFilter(QObject *object, QEvent *event);       // проверка на то, что был сдвинут узел (для обновления стрелок)

    // Обходы графа и задача коммивояжера:
    void openMenu();    // обход в ширину, глубину, алгоритм Флойда, алгоритм Дейкстры
    void tsp();         // задача коммивояжера

private:
    Graph graph;
    // "Окно" для визуализации:
    QGraphicsScene *scene;
    QGraphicsView *printGraph;
    Ui::GraphGenerator *ui;
};
#endif // GRAPHGENERATOR_H
