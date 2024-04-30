#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>

class Graph
{
private:
    int sizeOfMatrix;
    int** matrix;
    QGraphicsEllipseItem** matrixOfEllipses;
    QGraphicsItemGroup** matrixOfGroups;
    int curSerialNumber;

public:
    Graph();
    int getSize();
    int getSerialNumber();
    void increaseSerialNumber();
    void resizeMatrix(int);
    void addNodeOnLastPos(QGraphicsEllipseItem*, QGraphicsItemGroup*);
    QGraphicsEllipseItem** getMatrixOfEllipses();
    int** getMatrix();
    QGraphicsItemGroup** getMatrixOfGroups() const;
    void addEdge(int from, int to, int weight) const;
    void printMatrix();
    ~Graph();
};

#endif // GRAPH_H
