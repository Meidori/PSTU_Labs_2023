#include "graphgenerator.h"
#include "ui_graphgenerator.h"
#include "addnewedgewindow.h"
#include "ui_addnewedgewindow.h"
#include "deleteedgewindow.h"
#include "ui_deleteedgewindow.h"
#include "deletenodewindow.h"
#include "ui_deletenodewindow.h"
#include "graph.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsItemGroup>
#include <QtMath>
#include <QPolygonF>

GraphGenerator::GraphGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphGenerator)
    , addEdgeWindow(graph)
{
    ui->setupUi(this);

    printGraph = ui -> printGraph;
    scene = new QGraphicsScene;
    printGraph -> setScene(scene);

    connect(ui->addNodeBtn, SIGNAL(clicked()), this, SLOT(addNode()));

    connect(ui->addEdgeBtn, SIGNAL(clicked()), this, SLOT(addEdge()));

    connect(ui->updateArrowsBtn, SIGNAL(clicked()), this, SLOT(updateArrows()));

    connect(ui->deleteEdgeBtn, SIGNAL(clicked()), this, SLOT(delEdge()));

    connect(ui->deleteNodeBtn, SIGNAL(clicked()), this, SLOT(delNode()));
}

void GraphGenerator::addNode()
{
    QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 64, 64, QPen(Qt::black), QBrush(Qt::lightGray));

    QString nodeSerialNumber = QString::number(graph.getSerialNumber());
    QGraphicsTextItem *textItem = scene->addText(nodeSerialNumber);
    textItem->setPos(node->boundingRect().center().x() - textItem->boundingRect().width() / 2,
                     node->boundingRect().center().y() - textItem->boundingRect().height() / 2);

    QList<QGraphicsItem*> items;
    items << node << textItem;
    QGraphicsItemGroup *group = scene->createItemGroup(items);      // объеденяем в группу эллипс и текст
    group->setFlag(QGraphicsItem::ItemIsMovable, true);
    /*
     * не имеет смысла, т. к. node и TextItem объеденины в группу, а дочерние элементы
     * группы не изменяют pos при перемещении группы
    node->setFlag(QGraphicsItem::ItemIsMovable, true);
    textItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    */
    scene->installEventFilter(this);      // обработка события, если узел перетаскивают мышкой, чтобы обновить pos
                                          // нужно, чтобы рисовать стрелки между узлами

    graph.resizeMatrix(1);
    graph.addNodeOnLastPos(node, group);
    graph.increaseSerialNumber();

    graph.printMatrix();
}

void GraphGenerator::delNode()
{
    DeleteNodeWindow DeleteNodeWindow(graph, scene, printGraph, graph.getMatrixOfGroups());
    DeleteNodeWindow.setModal(true);
    DeleteNodeWindow.exec();

    updateArrows();
    updateSerialNumbers();

    graph.printMatrix();
}

void GraphGenerator::updateSerialNumbers()
{
    int size = graph.getSize();
    QGraphicsItemGroup** groups = graph.getMatrixOfGroups();
    for (int i = 1; i < size; i++)
    {
        foreach (QGraphicsItem *item, groups[i]->childItems())
        {
            QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
            if (textItem)
            {
                textItem->setPlainText(QString::number(i));
            }
        }
    }
    scene->update();
}

bool GraphGenerator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == scene && event->type() == QEvent::GraphicsSceneMouseMove)
    {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        // Проверяем, что произошло перемещение группы
        if (mouseEvent->buttons() & Qt::LeftButton)
        {
            // Проверяем, что элемент перемещаемый
            if (mouseEvent->lastScenePos() != mouseEvent->scenePos())
            {
                QGraphicsItem *item = scene->itemAt(mouseEvent->scenePos(), QTransform());
                if (item && item->type() == QGraphicsItemGroup::Type)
                {
                    QGraphicsItemGroup *group = qgraphicsitem_cast<QGraphicsItemGroup *>(item);
                    updateArrows();  // меняем стрелки
                    return true;
                }
            }
        }
    }
    // Если событие не обработано, передаем его дальше для обработки другими фильтрами
    return QObject::eventFilter(watched, event);
}

void GraphGenerator::addEdge()
{
    AddNewEdgeWindow addEdgeWindow(graph);
    addEdgeWindow.setModal(true);
    addEdgeWindow.exec();

    updateArrows();

    graph.printMatrix();
}

void GraphGenerator::delEdge()
{
    DeleteEdgeWindow delEdgeWindow(graph);
    delEdgeWindow.setModal(true);
    delEdgeWindow.exec();

    updateArrows();

    graph.printMatrix();
}

void GraphGenerator::updateArrows()
{
    int** matrix = graph.getMatrix();
    QGraphicsItemGroup** matrixOfGroups = graph.getMatrixOfGroups();
    std::vector<QGraphicsItemGroup*> vectorOfArrows = graph.getVectorOfArrows();
    QGraphicsItemGroup* tmp;

    for (int i = 0; i < vectorOfArrows.size(); i++)
    {
        scene->removeItem(vectorOfArrows[i]); // Удаляем группы со сцены
        delete vectorOfArrows[i]; // Освобождаем память
    }
    vectorOfArrows.clear();

    for (int i = 1; i < graph.getSize(); i++)
    {
        for (int j = i + 1; j < graph.getSize(); j++)
        {
            if (matrix[i][j] > 0 && matrix[i][j] == matrix[j][i])      // если ребро в обе стороны и вес равен, то рисуем линию
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

                qDebug() << center1;
                qDebug() << center2;

                qreal angle = qAtan2(center2.y() - center1.y(), center2.x() - center1.x());     // Находим угол между двумя центрами эллипсов

                // Вычисляем новые координаты начальной и конечной точек линии с учетом укорочения на 32 пикселя
                QPointF newStart(center1.x() + 32 * qCos(angle), center1.y() + 32 * qSin(angle));
                QPointF newEnd(center2.x() - 32 * qCos(angle), center2.y() - 32 * qSin(angle));

                QGraphicsLineItem *line = new QGraphicsLineItem();    // линия между эллипсами
                line->setLine(QLineF(newStart, newEnd));

                QPointF textPos((center1.x() + center2.x()) / 2, (center1.y() + center2.y()) / 2);          // позиция текста веса на центре линии
                QGraphicsTextItem* textItem = scene->addText(QString::number(matrix[i][j]));            // текст веса на центре линии
                textItem->setPos(textPos);
                QList<QGraphicsItem*> items;
                items << line << textItem;
                QGraphicsItemGroup *group = scene->createItemGroup(items);          // добавляем в группу линию и вес

                vectorOfArrows.push_back(group);
            }
            else if (matrix[i][j] > 0 && matrix[j][i] == 0)
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

                qDebug() << center1;
                qDebug() << center2;

                qreal angle = qAtan2(center2.y() - center1.y(), center2.x() - center1.x());     // Находим угол между двумя центрами эллипсов

                // Вычисляем новые координаты начальной и конечной точек линии с учетом укорочения на 32 пикселя
                QPointF newStart(center1.x() + 32 * qCos(angle), center1.y() + 32 * qSin(angle));
                QPointF newEnd(center2.x() - 32 * qCos(angle), center2.y() - 32 * qSin(angle));

                QGraphicsLineItem *line = new QGraphicsLineItem();    // линия между эллипсами
                line->setLine(QLineF(newStart, newEnd));

                // Создаем стрелковые концы линии
                QPolygonF arrowHead = createArrowHead(newEnd, newStart);
                QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem(arrowHead);
                arrow->setBrush(Qt::black);
                arrow->setPen(Qt::NoPen);

                QPointF textPos((center1.x() + center2.x()) / 2, (center1.y() + center2.y()) / 2);          // позиция текста веса на центре линии
                QGraphicsTextItem* textItem = scene->addText(QString::number(matrix[i][j]));            // текст веса на центре линии
                textItem->setPos(textPos);

                QList<QGraphicsItem*> items;
                items << line << textItem << arrow;
                QGraphicsItemGroup *group = scene->createItemGroup(items);          // добавляем в группу линию и вес

                vectorOfArrows.push_back(group);
            }
            else if (matrix[j][i] > 0 && matrix[i][j] == 0)
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

                qDebug() << center1;
                qDebug() << center2;

                qreal angle = qAtan2(center2.y() - center1.y(), center2.x() - center1.x());     // Находим угол между двумя центрами эллипсов

                // Вычисляем новые координаты начальной и конечной точек линии с учетом укорочения на 32 пикселя
                QPointF newStart(center1.x() + 32 * qCos(angle), center1.y() + 32 * qSin(angle));
                QPointF newEnd(center2.x() - 32 * qCos(angle), center2.y() - 32 * qSin(angle));

                QGraphicsLineItem *line = new QGraphicsLineItem();    // линия между эллипсами
                line->setLine(QLineF(newStart, newEnd));

                // Создаем стрелковые концы линии
                QPolygonF arrowHead = createArrowHead(newStart, newEnd);
                QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem(arrowHead);
                arrow->setBrush(Qt::black);
                arrow->setPen(Qt::NoPen);

                QPointF textPos((center1.x() + center2.x()) / 2, (center1.y() + center2.y()) / 2);          // позиция текста веса на центре линии
                QGraphicsTextItem* textItem = scene->addText(QString::number(matrix[j][i]));            // текст веса на центре линии
                textItem->setPos(textPos);

                QList<QGraphicsItem*> items;
                items << line << textItem << arrow;
                QGraphicsItemGroup *group = scene->createItemGroup(items);          // добавляем в группу линию и вес

                vectorOfArrows.push_back(group);
            }
            else if (matrix[i][j] > 0 && matrix[j][i] > 0 && matrix[i][j] != matrix[j][i])
            {
                // потом для разных весов между двумя матрицами
            }
            else // if ...
            {
                // потом для цикла
            }
        }
    }
    graph.updateVector(vectorOfArrows);
}

QPolygonF GraphGenerator::createArrowHead(const QPointF& startPoint, const QPointF& endPoint) {
    QPolygonF arrowHead;

    // Рассчитываем угол между горизонтальной линией и линией между startPoint и endPoint
    qreal angle = qAtan2(endPoint.y() - startPoint.y(), endPoint.x() - startPoint.x());
    // Длина стрелки
    qreal arrowLength = 10.0; // Измените это значение по вашему усмотрению

    // Угол стрелки с горизонтальной линией (половина угла)
    qreal arrowAngle = M_PI / 6.0; // 30 градусов

    // Координаты точек стрелки
    QPointF arrowP1 = endPoint - QPointF(arrowLength * std::cos(angle + arrowAngle), arrowLength * std::sin(angle + arrowAngle));
    QPointF arrowP2 = endPoint - QPointF(arrowLength * std::cos(angle - arrowAngle), arrowLength * std::sin(angle - arrowAngle));

    // Добавляем точки в полигон стрелки
    arrowHead << endPoint << arrowP1 << arrowP2;

    return arrowHead;
}

GraphGenerator::~GraphGenerator()
{
    delete scene;
    delete ui;
}
