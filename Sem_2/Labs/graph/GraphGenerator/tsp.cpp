#include "tsp.h"
#include "ui_tsp.h"

TSP::TSP(Graph* graph, QWidget *parent) :
    QDialog(parent), m_graph(graph),
    ui(new Ui::TSP)
{
    ui->setupUi(this);

    connect(ui->solveBtn, &QPushButton::clicked, this, &TSP::tsp);
}

void TSP::tsp()
{
    // Получаем значения с lineEdit пользовательского интерфейса и записываем их в переменные типа int (изменяя тип данных)
    QString getFrom = ui->fromLine->text();
    int from = getFrom.toInt();
    QString getTo = ui->toLine->text();
    int to = getTo.toInt();

    std::vector<int> path = m_graph->tsp(from, to);     // вызов метода для решения задачи коммивояжера
    std::reverse(path.begin(), path.end());     // "переворачиваем" вектор

    QString outputText = QString::number(path[1]);  // в path[0] промежуточный город (to)
    // если для узлов from -> to невозможно решить задачу коммивояжера, то вывод будет не совсем корректный
    for (int i = 2; i < path.size(); i++)
    {
        outputText += "->" + QString::number(path[i]);
    }
    ui->outputLabel->setText(outputText);   // выводим маршрут решения
}

TSP::~TSP()
{
    delete ui;
}
