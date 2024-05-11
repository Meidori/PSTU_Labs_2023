// Диалоговое окно удаления узла

#ifndef DELETENODE_H
#define DELETENODE_H

#include <QDialog>
#include <QGraphicsView>

#include "graph.h"

namespace Ui {
    class DeleteNodeWindow;
}

class DeleteNodeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteNodeWindow(Graph& graph, QGraphicsScene* scene, QGraphicsView* printGraph, QGraphicsItemGroup** matrixOfGroups, QWidget *parent = nullptr);
    ~DeleteNodeWindow();

public slots:
    void delNode();

private:
    Graph& m_graph;
    QGraphicsScene* m_scene;
    QGraphicsView* m_printGraph;
    QGraphicsItemGroup** m_matrixOfGroups;
    Ui::DeleteNodeWindow *ui;
};

#endif // DELETENODE_H
