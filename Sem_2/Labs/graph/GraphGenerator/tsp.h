// Диалоговое окно решения задачи коммивояжера

#ifndef TSP_H
#define TSP_H

#include <QDialog>
#include <QDebug>

#include "graph.h"

namespace Ui {
    class TSP;
}

class TSP : public QDialog
{
    Q_OBJECT

public:
    explicit TSP(Graph* graph, QWidget *parent = nullptr);
    ~TSP();

public slots:
    void tsp();     // задача коммивояжера

private:
    Graph* m_graph;
    Ui::TSP *ui;
};

#endif // TSP_H
