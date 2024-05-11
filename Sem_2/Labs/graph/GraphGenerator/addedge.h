// Диалоговое окно добавления ребра

#ifndef ADDEDGE_H
#define ADDEDGE_H

#include <QDialog>
#include <QGraphicsScene>

#include "graph.h"

namespace Ui {
    class AddNewEdgeWindow;
}

class AddNewEdgeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEdgeWindow(Graph& graph, QWidget *parent = nullptr);
    ~AddNewEdgeWindow();

private slots:
    void addNewEdge();

private:
    Graph& m_graph;
    Ui::AddNewEdgeWindow *ui;
};

#endif // ADDEDGE_H
