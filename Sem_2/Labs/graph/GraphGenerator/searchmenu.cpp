#include "searchmenu.h"
#include "ui_searchmenu.h"

output::output(Graph* graph, QWidget *parent) :
    QDialog(parent), m_graph(graph),
    ui(new Ui::output)
{
    ui->setupUi(this);

    connect(ui->dfsBtn, &QPushButton::clicked, this, &output::dfs);
    connect(ui->bfsBtn, &QPushButton::clicked, this, &output::bfs);
    connect(ui->floydBtn, &QPushButton::clicked, this, &output::floyd);
    connect(ui->dijkstraBtn, &QPushButton::clicked, this, &output::dijkstra);
}

output::~output()
{
    delete ui;
}

void output::dfs()
{
    // Получаем значения с lineEdit пользовательского интерфейса и записываем их в переменные типа int (изменяя тип данных)
    QString startNode = ui->startLine->text();
    int start = startNode.toInt();
    std::vector<int> visited = m_graph->dfs(start);     // вызываем метод графа для обхода в глубину
    // Вывод:
    ui->outputDist->clear();
    ui->outputDist->setText("Path availability:\n");
    for (int i = 1; i < visited.size(); i++)
    {
        QString node = QString::number(i), isVisited = QString::number(visited[i]);
        QString line;
        line.append(node).append(" : ").append(isVisited).append("\n");
        QString currentText = ui->outputDist->text();
        QString newText = currentText + line;
        ui->outputDist->setText(newText);
    }
}

void output::bfs()
{
    // Получаем значения с lineEdit пользовательского интерфейса и записываем их в переменные типа int (изменяя тип данных)
    QString startNode = ui->startLine->text();
    int start = startNode.toInt();
    std::vector<int> distance = m_graph->bfs(start);    // вызываем метод графа для обхода в ширину
    // Вывод:
    ui->outputDist->clear();
    ui->outputDist->setText("Minimum number of edges from the start node:\n");
    for (int i = 1; i < distance.size(); i++)
    {
        QString from = QString::number(start), to = QString::number(i), dist = QString::number(distance[i]);
        QString line;
        line.append(from).append(" -> ").append(to).append(" : ").append(dist).append("\n");
        QString currentText = ui->outputDist->text();
        QString newText = currentText + line;
        ui->outputDist->setText(newText);
    }
}

void output::floyd()
{
    std::vector<std::vector<int>> distance = m_graph->floyd();  // вызываем метод графа для алгоритма Флойда
    // Вывод:
    ui->outputDist->clear();
    ui->outputDist->setText("Shortest path from each node to each node");
    QString text;
    text.append("     ");
    for (int i = 0; i < m_graph->getSize() - 1; i++)
    {
        text.append(QString::number(i + 1)).append(QString(" ").repeated(4 - QString::number(i).length()));
    }
    text.append("\n");

    for (int i = 0; i < m_graph->getSize() - 1; i++)
    {
        text.append(QString::number(i + 1)).append(QString(" ").repeated(4 - QString::number(i).length()));
        for (int j = 0; j < m_graph->getSize() - 1; j++)
        {
            QString dist;
            dist = QString::number(distance[j][i]);
            if (distance[j][i] == 1e9)
            {
                dist = "_";
            }
            text.append(dist).append(QString(" ").repeated(4 - dist.length()));
        }
        text.append("\n");
    }
    ui->outputDist->setText(text);
}

void output::dijkstra()
{
    // Получаем значения с lineEdit пользовательского интерфейса и записываем их в переменные типа int (изменяя тип данных)
    QString startNode = ui->startLine->text();
    int start = startNode.toInt();
    std::vector<int> distance = m_graph->dijkstra(start);   // вызываем метод графа для алгоритма Дейкстры
    // Вывод:
    ui->outputDist->clear();
    ui->outputDist->setText("Minimum number of edges (considering the minimumpath length)\nfrom the start node:\n");
    for (int i = 1; i < distance.size(); i++)
    {
        QString from = QString::number(start), to = QString::number(i), dist = QString::number(distance[i]);
        QString line;
        line.append(from).append(" -> ").append(to).append(" : ").append(dist).append("\n");
        QString currentText = ui->outputDist->text();
        QString newText = currentText + line;
        ui->outputDist->setText(newText);
    }
}
