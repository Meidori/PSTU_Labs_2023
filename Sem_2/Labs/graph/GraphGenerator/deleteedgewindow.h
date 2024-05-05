#ifndef DELETEEDGEWINDOW_H
#define DELETEEDGEWINDOW_H

#include <QDialog>
#include "graph.h"

namespace Ui {
    class DeleteEdgeWindow;
}

class DeleteEdgeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEdgeWindow(const Graph& graph, QWidget *parent = nullptr);
    ~DeleteEdgeWindow();

public slots:
    void delEdge();

private:
    const Graph& m_graph;
    Ui::DeleteEdgeWindow *ui;
};

#endif // DELETEEDGEWINDOW_H
