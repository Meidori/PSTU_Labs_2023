#ifndef ADDNEWEDGEWINDOW_H
#define ADDNEWEDGEWINDOW_H

#include <QDialog>
#include "graph.h"

namespace Ui {
    class AddNewEdgeWindow;
}

class AddNewEdgeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewEdgeWindow(const Graph& graph, QWidget *parent = nullptr);
    ~AddNewEdgeWindow();

private slots:
    void addNewEdge();

private:
    const Graph& m_graph;
    Ui::AddNewEdgeWindow *ui;
};

#endif // ADDNEWEDGEWINDOW_H
