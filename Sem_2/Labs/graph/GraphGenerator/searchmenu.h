// Диалоговое окно - меню содержащее алгоритмы поиска по графу

#ifndef SEARCHMENU_H
#define SEARCHMENU_H

#include <QDialog>

#include "graph.h"

namespace Ui {
    class output;
}

class output : public QDialog
{
    Q_OBJECT

public:
    explicit output(Graph* graph, QWidget *parent = nullptr);
    ~output();

public slots:
    // Обходы:
    void dfs();     // обход в глубину
    void bfs();     // обход в ширину
    void floyd();   // алгоритм Флойда
    void dijkstra();    // алгоритм Дейкстры

private:
    Graph* m_graph;
    Ui::output *ui;
};

#endif // SEARCHMENU_H
