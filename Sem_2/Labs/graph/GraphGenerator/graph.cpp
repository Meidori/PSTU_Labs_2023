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

    matrixOfEllipses[sizeOfMatrix - 1] = node;
    matrixOfGroups[sizeOfMatrix - 1] = group;
}

void Graph::delNode(int number)
{
    int curSize = getSize();

    // Удаление строки и столбца
    for (int i = number; i < curSize - 1; ++i)
    {
        for (int j = 0; j < curSize - 1; ++j)
        {
            // Сдвигаем элементы влево и вверх
            if (i < number || j < number)
                matrix[i][j] = matrix[i][j];
            else
                matrix[i][j] = matrix[i + 1][j + 1];
        }
    }

    int** newMatrix = new int*[curSize - 1];
    for (int i = 0; i < curSize - 1; ++i)
    {
        newMatrix[i] = new int[curSize - 1];
    }

    for (int i = 0; i < curSize - 1; ++i)
    {
        for (int j = 0; j < curSize - 1; ++j)
        {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    delete[] matrix;
    matrix = newMatrix;

    // Обновляем массивы групп и эллипсов
    QGraphicsEllipseItem** newMatrixOfEllipses = new QGraphicsEllipseItem*[curSize - 1];
    QGraphicsItemGroup** newMatrixOfGroups = new QGraphicsItemGroup*[curSize - 1];

    for (int i = 0; i < number; ++i)
    {
        newMatrixOfEllipses[i] = matrixOfEllipses[i];
        newMatrixOfGroups[i] = matrixOfGroups[i];
    }

    for (int i = number + 1; i < curSize; ++i)
    {
        newMatrixOfEllipses[i - 1] = matrixOfEllipses[i];
        newMatrixOfGroups[i - 1] = matrixOfGroups[i];
    }

    delete[] matrixOfEllipses;
    delete[] matrixOfGroups;

    matrixOfEllipses = newMatrixOfEllipses;
    matrixOfGroups = newMatrixOfGroups;

    sizeOfMatrix--;
    curSerialNumber--;

    // Обновляем матрицу индексов
    for (int i = 0; i < sizeOfMatrix; ++i)
    {
        matrix[0][i] = i;
        matrix[i][0] = i;
    }
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

std::vector<QGraphicsItemGroup*>& Graph::getVectorOfArrows()
{
    return vectorOfArrows;
}

void Graph::updateVector(std::vector<QGraphicsItemGroup*>& vect)
{
    vectorOfArrows = vect;
}

void Graph::addEdge(int from, int to, int weight) const
{
    matrix[to][from] = weight;
}

void Graph::delEdge(int from, int to) const
{
    matrix[to][from] = 0;
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
