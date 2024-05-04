#include "graph.h"

#include <QDebug>

Graph::Graph()
{
    sizeOfMatrix = 1;
    curSerialNumber = 1;
    matrix = new int* [sizeOfMatrix];
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        matrix[i] = new int [sizeOfMatrix];
    }
    matrix[0][0] = 0;

    matrixOfEllipses = new QGraphicsEllipseItem* [sizeOfMatrix];
    matrixOfEllipses[0] = nullptr;

    matrixOfGroups = new QGraphicsItemGroup* [sizeOfMatrix];
    matrixOfEllipses[0] = nullptr;
}

int Graph::getSize()
{
    return sizeOfMatrix;
}

int Graph::getSerialNumber()
{
    return curSerialNumber;
}

void Graph::increaseSerialNumber()
{
    curSerialNumber += 1;
}

void Graph::resizeMatrix(int difference)    // только в большую сторону
{
    // matrix:
    int** newMatrix;
    newMatrix = new int* [sizeOfMatrix + difference];
    for (int i = 0; i < sizeOfMatrix + difference; i++)
    {
        newMatrix[i] = new int [sizeOfMatrix + difference];
    }

    for (int i = 0; i < sizeOfMatrix; i++)
    {
        for (int j = 0; j < sizeOfMatrix; j++)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    for (int i = sizeOfMatrix; i < sizeOfMatrix + difference; i++)
    {
        for (int j = 0; j < sizeOfMatrix + difference; j++)
        {
            newMatrix[i][j] = 0;
            newMatrix[j][i] = 0;
        }
    }

    for (int i = 0; i < sizeOfMatrix; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;

    // matrixOfEllipses:
    QGraphicsEllipseItem** newMatrixOfEllipses = new QGraphicsEllipseItem* [sizeOfMatrix + 1];
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        newMatrixOfEllipses[i] = matrixOfEllipses[i];
    }
    delete matrixOfEllipses;
    matrixOfEllipses = newMatrixOfEllipses;

    //matrixOfGroups:
    QGraphicsItemGroup** newMatrixOfGroups = new QGraphicsItemGroup* [sizeOfMatrix + 1];
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        newMatrixOfGroups[i] = matrixOfGroups[i];
    }
    delete matrixOfGroups;
    matrixOfGroups = newMatrixOfGroups;

    sizeOfMatrix += difference;
}

void Graph::addNodeOnLastPos(QGraphicsEllipseItem* node, QGraphicsItemGroup* group)
{
    matrix[0][sizeOfMatrix - 1] = curSerialNumber;
    matrix[sizeOfMatrix - 1][0] = curSerialNumber;
    // matrix[sizeOfMatrix - 1][sizeOfMatrix - 1] = 0;

    matrixOfEllipses[curSerialNumber] = node;

    matrixOfGroups[curSerialNumber] = group;
}

QGraphicsEllipseItem** Graph::getMatrixOfEllipses()
{
    return matrixOfEllipses;
}

int** Graph::getMatrix()
{
    return matrix;
}

QGraphicsItemGroup** Graph::getMatrixOfGroups() const
{
    return matrixOfGroups;
}

void Graph::updateMatrixOfGroups(int index, QGraphicsItemGroup* group)
{
    matrixOfGroups[index] = group;
}

void Graph::updateMatrixOfEllipses(int index, QGraphicsEllipseItem* node)
{
    matrixOfEllipses[index] = node;
}

std::vector<QGraphicsItemGroup*> Graph::getVectorOfArrows()
{
    return vectorOfArrows;
}

void Graph::addEdge(int from, int to, int weight) const
{
    matrix[to][from] = weight;
}

void Graph::printMatrix()
{
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        QString rowString;
        for (int j = 0; j < sizeOfMatrix; j++)
        {
            rowString += QString::number(matrix[i][j]) + " ";
        }
        qDebug() << rowString;
    }
    qDebug() << "\n";
}

Graph::~Graph()
{
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    for (int i = 0; i < sizeOfMatrix; i++)
    {
        delete[] matrixOfEllipses[i];
    }
    delete[] matrixOfEllipses;

    for (int i = 0; i < sizeOfMatrix; i++)
    {
        delete[] matrixOfGroups[i];
    }
    delete[] matrixOfGroups;
}
