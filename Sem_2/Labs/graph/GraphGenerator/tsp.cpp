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

    QString outputText = QString::number(path[0]);
    for (int i = 1; i < path.size(); i++)
    {
        outputText += "->" + QString::number(path[i]);
    }
    ui->outputLabel->setText(outputText);   // выводим маршрут решения
}

TSP::~TSP()
{
    delete ui;
}
