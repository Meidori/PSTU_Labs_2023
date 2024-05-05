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
    void delNode(int);
    void setDeletedSerialNumber(int);
    int getLastDeletedSerialNumber();
    QGraphicsEllipseItem** getMatrixOfEllipses();
    int** getMatrix();
    std::vector<QGraphicsItemGroup*>& getVectorOfArrows();
    void updateVector(std::vector<QGraphicsItemGroup*>&);
    QGraphicsItemGroup** getMatrixOfGroups() const;
    void updateMatrixOfGroups(int, QGraphicsItemGroup*);
    void updateMatrixOfEllipses(int, QGraphicsEllipseItem*);
    void addEdge(int, int, int) const;
    void delEdge(int, int) const;
    void printMatrix();
    ~Graph();
};

#endif // GRAPH_H
