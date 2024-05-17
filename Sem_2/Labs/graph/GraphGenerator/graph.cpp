#include "graph.h"

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

Graph::~Graph()
{
    // Освобождаем память, выделенную для матрицы смежности
    if (matrix) {
        for (int i = 0; i < sizeOfMatrix; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Освобождаем память, выделенную для массива ellipses
    if (matrixOfEllipses) {
        delete[] matrixOfEllipses;
    }

    // Освобождаем память, выделенную для массива groups
    if (matrixOfGroups) {
        delete[] matrixOfGroups;
    }

    // Освобождаем память, выделенную для элементов вектора arrows
    for (auto arrow : vectorOfArrows) {
        delete arrow;
    }
}

int Graph::getSize()
{
    return sizeOfMatrix;
}

int Graph::getSerialNumber()
{
    return curSerialNumber;
}

int** Graph::getMatrix()
{
    return matrix;
}

QGraphicsEllipseItem** Graph::getMatrixOfEllipses()
{
    return matrixOfEllipses;
}

QGraphicsItemGroup** Graph::getMatrixOfGroups()
{
    return matrixOfGroups;
}

std::vector<QGraphicsItemGroup*>& Graph::getVectorOfArrows()
{
    return vectorOfArrows;
}

void Graph::addEdge(int from, int to, int weight)
{
    matrix[to][from] = weight;
}

void Graph::delEdge(int from, int to)
{
    matrix[to][from] = 0;
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

    // Создаем новую матрицу
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

    // Обновляем в матрице номера узлов
    for (int i = 0; i < sizeOfMatrix; ++i)
    {
        matrix[0][i] = i;
        matrix[i][0] = i;
    }
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

void Graph::increaseSerialNumber()
{
    curSerialNumber += 1;
}

void Graph::addNodeOnLastPos(QGraphicsEllipseItem* node, QGraphicsItemGroup* group)
{
    // Добавляем последний добавленный узел
    matrix[0][sizeOfMatrix - 1] = curSerialNumber;
    matrix[sizeOfMatrix - 1][0] = curSerialNumber;

    matrixOfEllipses[sizeOfMatrix - 1] = node;
    matrixOfGroups[sizeOfMatrix - 1] = group;
}

void Graph::updateMatrixOfEllipses(int index, QGraphicsEllipseItem* node)
{
    matrixOfEllipses[index] = node;
}

void Graph::updateMatrixOfGroups(int index, QGraphicsItemGroup* group)
{
    matrixOfGroups[index] = group;
}

void Graph::updateVector(std::vector<QGraphicsItemGroup*>& vect)
{
    vectorOfArrows = vect;
}

void Graph::printMatrix()
{
    for (int i = 0; i < sizeOfMatrix; i++)
    {
        QString rowString;
        for (int j = 0; j < sizeOfMatrix; j++)
        {
            rowString += QString::number(matrix[j][i]) + " ";
        }
        qDebug() << rowString;
    }
    qDebug() << "\n";
}

std::vector<int> Graph::dfs(int start)
{
    // Создание вектора для отслеживания посещенных вершин, инициализированного нулями
    std::vector<int> visited(sizeOfMatrix, 0);
    // Вызов рекурсивной функции dfs для запуска обхода в глубину
    dfs(start, visited);
    return visited;
}

void Graph::dfs(int cur, std::vector<int>& visited)
{
    // Помечаем текущую вершину как посещенную
    visited[cur] = 1;
    for (int i = 1; i < sizeOfMatrix; i++)
    {
        // Если есть ребро между текущей вершиной и вершиной i и вершина i ещё не посещалась
        if (matrix[i][cur] != 0 && visited[i] == 0)
        {
            // Рекурсивно вызываем dfs для вершины i
            dfs(i, visited);
        }
    }
}

std::vector<int> Graph::bfs(int start)
{
    std::vector<int> distance(sizeOfMatrix, 1e9);
    std::queue<int> q;

    // Начальная вершина имеет расстояние 0
    distance[start] = 0;
    q.push(start);

    // Начало обхода в ширину
    while(!q.empty())
    {
        // Получаем текущую вершину из очереди
        int cur = q.front();
        q.pop();

        // Проходим по всем смежным вершинам текущей
        for (int i = 1; i < sizeOfMatrix; i++)
        {
            // Если вершина ещё не посещена и есть ребро между текущей и i
            if (distance[i] == 1e9 && matrix[i][cur] != 0)
            {
                // Расстояние до вершины i равно расстоянию до текущей + 1
                distance[i] = distance[cur] + 1;
                // Добавляем вершину i в очередь для дальнейшего обхода
                q.push(i);
            }
        }
    }

    return distance;
}

std::vector<std::vector<int>> Graph::floyd()
{
    std::vector<std::vector<int>> dist(sizeOfMatrix - 1, std::vector<int>(sizeOfMatrix - 1, 1e9));

    // Задание нулевых расстояний для диагональных элементов (вершин до самих себя)
    for (int i = 0; i < sizeOfMatrix - 1; i++)
    {
        dist[i][i] = 0;
    }

    // Заполнение матрицы расстояний из матрицы смежности графа
    for (int i = 1; i < sizeOfMatrix; i++)
    {
        for (int j = 1; j < sizeOfMatrix; j++)
        {
            if (matrix[i][j] != 0)
            {
                // Если между вершинами есть ребро, записываем его в матрицу расстояний
                dist[i - 1][j - 1] = matrix[i][j];
            }
        }
    }

    for (int v = 0; v < sizeOfMatrix - 1; v++)
    {
        for (int i = 0; i < sizeOfMatrix - 1; i++)
        {
            for (int j = 0; j < sizeOfMatrix - 1; j++)
            {
                // Если существует путь через вершину v, короче, чем текущий путь от i до j
                if (dist[i][v] != 1e9 && dist[v][j] != 1e9 && dist[i][j] > dist[i][v] + dist[v][j])
                {
                    // Обновляем значение кратчайшего пути от i до j
                    dist[i][j] = dist[i][v] + dist[v][j];
                }
            }
        }
    }

    return dist;
}

std::vector<int> Graph::dijkstra(int start)
{
    std::vector<int> dist(sizeOfMatrix, 1e9);
    dist[start] = 0; // Расстояние до стартовой вершины равно 0
    std::vector<bool> visited(sizeOfMatrix, false);

    // Проходим по всем вершинам графа
    for (int k = 0; k < sizeOfMatrix - 1; k++) // Внешний цикл повторяется sizeOfMatrix - 1 раз, так как для каждой вершины будет найдено кратчайшее расстояние до всех остальных вершин за sizeOfMatrix - 1 итераций
    {
        // Находим вершину с наименьшим расстоянием
        int minDist = 1e9;
        int nearest = -1;
        for (int v = 0; v < sizeOfMatrix; v++)
        {
            if (!visited[v] && dist[v] < minDist)
            {
                minDist = dist[v];
                nearest = v;
            }
        }

        // Помечаем вершину как посещенную
        visited[nearest] = true;

        // Обновляем расстояния до смежных вершин
        for (int v = 0; v < sizeOfMatrix; v++)
        {
            if (matrix[nearest][v] != 0 && !visited[v] && dist[nearest] + matrix[nearest][v] < dist[v])
            {
                dist[v] = dist[nearest] + matrix[nearest][v];
            }
            if (matrix[v][nearest] != 0 && !visited[v] && dist[nearest] + matrix[v][nearest] < dist[v])
            {
                dist[v] = dist[nearest] + matrix[v][nearest];
            }
        }
    }

    return dist;
}

std::vector<int> Graph::tsp(int start, int end)
{
    std::vector<int> bestPath;  // Вектор для хранения наилучшего пути
    int minCost = INT_MAX;

    std::vector<int> path;      // Вектор для хранения текущего пути
    std::vector<bool> visited(sizeOfMatrix, false);     // Вектор для отслеживания посещенных узлов

    // Запуск рекурсивного обхода
    tspUtil(start, end, path, visited, 0, minCost, bestPath);

    // Добавляем конечный узел (начальный, в который мы возвращаемся) в путь для завершения цикла
    if (!bestPath.empty())
    {
        bestPath.push_back(start);
    }

    return bestPath;
}

void Graph::tspUtil(int curNode, int endNode, std::vector<int>& path, std::vector<bool>& visited, int curCost, int& minCost, std::vector<int>& bestPath)
{
    // Добавляем текущий узел в путь и помечаем его как посещенный
    path.push_back(curNode);
    visited[curNode] = true;

    // Проверка, если все узлы посещены
    if (path.size() == sizeOfMatrix - 1)
    {
        // Проверяем, если текущая стоимость пути меньше минимальной
        if (curCost < minCost)
        {
            // Обновляем минимальную стоимость и наилучший путь
            minCost = curCost;
            bestPath = path;
        }
        // Снятие метки посещения и удаление узла из пути
        visited[curNode] = false;
        path.pop_back();
        return;     // Возвращаемся к предыдущему узлу
    }

    // Перебираем все узлы графа для поиска следующего узла
    for (int nextNode = 1; nextNode < sizeOfMatrix; nextNode++)
    {
        // Проверяем, если следующий узел не посещен и существует ребро между текущим и следующим узлом
        if (!visited[nextNode] && matrix[nextNode][curNode] != 0)
        {
            int newCost = curCost + matrix[nextNode][curNode];      // Обновляем текущую стоимость пути
            tspUtil(nextNode, endNode, path, visited, newCost, minCost, bestPath);      // Рекурсивный вызов для следующего узла
        }
    }

    // Снятие метки посещения и удаление узла из пути
    visited[curNode] = false;
    path.pop_back();
}



