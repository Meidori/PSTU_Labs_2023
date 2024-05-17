#ifndef GRAPH_H
#define GRAPH_H

#include <QGraphicsEllipseItem>
#include <QDebug>
#include <vector>
#include <queue>

class Graph
{
private:
    int sizeOfMatrix;       // размер матрицы смежности
    int** matrix;           // матрица смежности
    QGraphicsEllipseItem** matrixOfEllipses;    // массив указателей на эллипсы
    QGraphicsItemGroup** matrixOfGroups;        // массив указателей на группы узлов
    std::vector<QGraphicsItemGroup*> vectorOfArrows;    // вектор указателей на группы стрелок
    int curSerialNumber;    // порядковый номер нового узла

public:
    Graph();
    ~Graph();

    // Геттеры:
    int getSize();          // возвращает размер матрицы смежности (с учетом координатной строки и столбца)
    int getSerialNumber();  // возвращает текущий порядковый номер узла (не самый большой порядковый номер, а тот который будет следущий при добавлении)
    int** getMatrix();      // возвращает матрицу смежности
    QGraphicsEllipseItem** getMatrixOfEllipses();   // возвращает массив указателей на объект эллипса
    QGraphicsItemGroup** getMatrixOfGroups();       // возвращает массив указателей на группы узлов (эллипс и текст - порядковый номер)
    std::vector<QGraphicsItemGroup*>& getVectorOfArrows();      // возвращает вектор указателей на группы ребер

    // Изменение матрицы смежности:
    void addEdge(int, int, int);    // добавление ребра в матрицу смежности
    void delEdge(int, int);         // удаление ребра из матрицы смежности
    void delNode(int);              // удаление узла из матрицу смежности

    void resizeMatrix(int);         // увеличение матрицы (при добавлении узлов)
    void increaseSerialNumber();    // увеличение порядкового номера (при добавлении узлов)
    void addNodeOnLastPos(QGraphicsEllipseItem*, QGraphicsItemGroup*);   // добавление координатной ячейки в матрице смежности + изменение matrixOfEllipses и matrixOfGroups
    void updateMatrixOfEllipses(int, QGraphicsEllipseItem*);    // обновление matrixOfEllipses
    void updateMatrixOfGroups(int, QGraphicsItemGroup*);        // обновление matrixOfGroups
    void updateVector(std::vector<QGraphicsItemGroup*>&);       // обновление вектора стрелок

    // Для отладки:
    void printMatrix();     // вывод матрицы смежности в консоль

    // Обходы и задача коммивояжера
    std::vector<int> dfs(int);
    void dfs(int, std::vector<int>&);
    std::vector<int> bfs(int);
    std::vector<std::vector<int>> floyd();
    std::vector<int> dijkstra(int);
    std::vector<int> tsp(int, int);
    void tspUtil(int, int, std::vector<int>&, std::vector<bool>&, int, int&, std::vector<int>&);

};

#endif // GRAPH_H
