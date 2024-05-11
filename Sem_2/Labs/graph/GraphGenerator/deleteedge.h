// Диалоговое окно удаления ребра

#ifndef DELETEEDGE_H
#define DELETEEDGE_H

#include <QDialog>

#include "graph.h"

namespace Ui {
    class DeleteEdgeWindow;
}

class DeleteEdgeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEdgeWindow(Graph& graph, QWidget *parent = nullptr);
    ~DeleteEdgeWindow();

public slots:
    void delEdge();

private:
    Graph& m_graph;
    Ui::DeleteEdgeWindow *ui;
};

#endif // DELETEEDGE_H
