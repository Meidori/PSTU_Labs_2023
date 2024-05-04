#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>

#include <vector>

class Graph
{
private:
    int sizeOfMatrix;
    int** matrix;
    QGraphicsEllipseItem** matrixOfEllipses;
    QGraphicsItemGroup** matrixOfGroups;
    std::vector<QGraphicsItemGroup*> vectorOfArrows;
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
    std::vector<QGraphicsItemGroup*> getVectorOfArrows();
    QGraphicsItemGroup** getMatrixOfGroups() const;
    void updateMatrixOfGroups(int index, QGraphicsItemGroup* group);
    void updateMatrixOfEllipses(int index, QGraphicsEllipseItem* node);
    void addEdge(int from, int to, int weight) const;
    void printMatrix();
    ~Graph();
};

#endif // GRAPH_H
