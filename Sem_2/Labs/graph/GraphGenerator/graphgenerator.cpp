#include "graphgenerator.h"
#include "ui_graphgenerator.h"

GraphGenerator::GraphGenerator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GraphGenerator)
{
    ui->setupUi(this);

    printGraph = ui -> printGraph;
    scene = new QGraphicsScene;
    printGraph -> setScene(scene);

    connect(ui->addNodeBtn, &QPushButton::clicked, this, &GraphGenerator::addNode);
    connect(ui->addEdgeBtn, &QPushButton::clicked, this, &GraphGenerator::addEdge);
    connect(ui->updateArrowsBtn, &QPushButton::clicked, this, &GraphGenerator::updateArrows);
    connect(ui->deleteEdgeBtn, &QPushButton::clicked, this, &GraphGenerator::delEdge);
    connect(ui->deleteNodeBtn, &QPushButton::clicked, this, &GraphGenerator::delNode);
    connect(ui->searchBtn, &QPushButton::clicked, this, &GraphGenerator::openMenu);
    connect(ui->tspBtn, &QPushButton::clicked, this, &GraphGenerator::tsp);
}

GraphGenerator::~GraphGenerator()
{
    delete scene;
    delete ui;
}

void GraphGenerator::addNode()
{
    QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 64, 64, QPen(Qt::black), QBrush(Qt::lightGray));   // добавляем эллипс на координату (0, 0) размер 64, черный контур, яркосерая заливка

    // Добавляем порядковый номер:
    QString nodeSerialNumber = QString::number(graph.getSerialNumber());
    QGraphicsTextItem *textItem = scene->addText(nodeSerialNumber);
    textItem->setPos(node->boundingRect().center().x() - textItem->boundingRect().width() / 2,
                     node->boundingRect().center().y() - textItem->boundingRect().height() / 2);

    // Объединяем в группу
    QList<QGraphicsItem*> items;
    items << node << textItem;
    QGraphicsItemGroup *group = scene->createItemGroup(items);      // объеденяем в группу эллипс и текст
    group->setFlag(QGraphicsItem::ItemIsMovable, true);     // даем возможность двигать группу мышкой
    /*
     * не имеет смысла, т. к. node и TextItem объеденины в группу, а дочерние элементы
     * группы не изменяют pos при перемещении группы
    node->setFlag(QGraphicsItem::ItemIsMovable, true);
    textItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    */
    scene->installEventFilter(this);      // обработка события, если узел перетаскивают мышкой, чтобы обновить pos
                                          // нужно, чтобы рисовать стрелки между узлами

    // Обновляем матрицу смежности и массивы объектов после добавления узла
    graph.resizeMatrix(1);
    graph.addNodeOnLastPos(node, group);
    graph.increaseSerialNumber();

    graph.printMatrix();    // вывод матрицы в консоль
}

void GraphGenerator::delNode()
{
    // Вызываем диалговое окно поверх основного окна
    DeleteNodeWindow DeleteNodeWindow(graph, scene, printGraph, graph.getMatrixOfGroups());
    DeleteNodeWindow.setModal(true);
    DeleteNodeWindow.exec();

    updateArrows();         // обновляем стрелки после удаления узла
    updateSerialNumbers();  // обновляем порядковые номера после удаления узла

    graph.printMatrix();    // вывод матрицы в консоль
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
    // Вызываем диалговое окно поверх основного окна
    DeleteEdgeWindow delEdgeWindow(graph);
    delEdgeWindow.setModal(true);
    delEdgeWindow.exec();

    updateArrows();     // обновляем стрелки после удаления ребра

    graph.printMatrix();    // выводим матрицу в консоль
}

void GraphGenerator::updateArrows()
{
    // Получаем объекты графа, чтобы рисовать/обновлять стрелки
    int** matrix = graph.getMatrix();
    QGraphicsItemGroup** matrixOfGroups = graph.getMatrixOfGroups();
    QGraphicsEllipseItem** matrixOfEllipses = graph.getMatrixOfEllipses();
    std::vector<QGraphicsItemGroup*> vectorOfArrows = graph.getVectorOfArrows();

    for (int i = 0; i < vectorOfArrows.size(); i++)
    {
        scene->removeItem(vectorOfArrows[i]); // Удаляем группы со сцены
        delete vectorOfArrows[i]; // Освобождаем память
    }
    vectorOfArrows.clear();

    // Перебираем элементы матрицы смежности для рисования стрелок
    for (int i = 1; i < graph.getSize(); i++)
    {
        for (int j = i; j < graph.getSize(); j++)
        {
            if (matrix[i][j] != 0 && matrix[i][j] == matrix[j][i] && i != j)      // если ребро в обе стороны и вес равен, то рисуем линию
            {
                // Получаем центры эллипсов, с помощью mapToScene
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

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
            else if (matrix[i][j] != 0 && matrix[j][i] == 0 && i != j)       // если стрелка только в одну сторону
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

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
            else if (matrix[j][i] != 0 && matrix[i][j] == 0 && i != j)               // если стрелка в другую сторону
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

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
            else if (matrix[i][j] != 0 && matrix[j][i] != 0 && matrix[i][j] != matrix[j][i] && i != j)      // если направление в обе стороны, но разные веса
            {
                QPointF center1 = matrixOfGroups[i]->mapToScene(matrixOfGroups[i]->boundingRect().center());
                QPointF center2 = matrixOfGroups[j]->mapToScene(matrixOfGroups[j]->boundingRect().center());

                qreal angle = qAtan2(center2.y() - center1.y(), center2.x() - center1.x()); // Находим угол между двумя центрами эллипсов

                // Вычисляем новые координаты начальной и конечной точек линии с учетом укорочения на 32 пикселя
                QPointF newStart(center1.x() + 32 * qCos(angle), center1.y() + 32 * qSin(angle));
                QPointF newEnd(center2.x() + 32 * qCos(angle + M_PI), center2.y() + 32 * qSin(angle + M_PI)); // Изменил угол на angle + M_PI

                QGraphicsLineItem *line1 = new QGraphicsLineItem(); // линия между эллипсами
                line1->setLine(QLineF(newStart, newEnd));

                // Создаем стрелковые концы линии
                QPolygonF arrowHead1 = createArrowHead(newStart, newEnd);
                QGraphicsPolygonItem *arrow1 = new QGraphicsPolygonItem(arrowHead1);
                arrow1->setBrush(Qt::black);
                arrow1->setPen(Qt::NoPen);

                // Вычисляем координаты текста на конце первой стрелки
                QPointF textPos1(newEnd.x(), newEnd.y());
                QGraphicsTextItem* textItem1 = scene->addText(QString::number(matrix[j][i])); // текст веса на конце первой стрелки
                textItem1->setPos(textPos1);

                QGraphicsLineItem *line2 = new QGraphicsLineItem(); // линия между эллипсами
                line2->setLine(QLineF(newEnd, newStart)); // Поменял начало и конец

                // Создаем стрелковые концы линии
                QPolygonF arrowHead2 = createArrowHead(newEnd, newStart);
                QGraphicsPolygonItem *arrow2 = new QGraphicsPolygonItem(arrowHead2);
                arrow2->setBrush(Qt::black);
                arrow2->setPen(Qt::NoPen);

                // Вычисляем координаты текста на конце второй стрелки
                QPointF textPos2(newStart.x(), newStart.y());
                QGraphicsTextItem* textItem2 = scene->addText(QString::number(matrix[i][j])); // текст веса на конце второй стрелки
                textItem2->setPos(textPos2);

                QList<QGraphicsItem*> items;
                items << line1 << textItem1 << arrow1 << line2 << textItem2 << arrow2;
                QGraphicsItemGroup *group = scene->createItemGroup(items); // добавляем в группу линию и вес

                vectorOfArrows.push_back(group);
            }
            else if (i == j && matrix[i][j] != 0)       // петля
            {
                QGraphicsEllipseItem *ellipse = matrixOfEllipses[i]; // Получаем узел (эллипс)

                // Вычисляем центр узла
                QPointF center = ellipse->mapToScene(ellipse->boundingRect().center());

                qreal radius = ellipse->boundingRect().width() / 2.0; // Радиус узла

                qreal angle = 45 * M_PI / 180; // Угол поворота петли

                // Вычисляем координаты точек для рисования петли на контуре узла
                QPointF start(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));
                QPointF end(center.x() + radius * qCos(angle + M_PI), center.y() + radius * qSin(angle + M_PI));

                // Контрольные точки для создания кривой Безье
                QPointF controlPoint1(center.x() + radius * qCos(angle - M_PI / 4), center.y() + radius * qSin(angle - M_PI / 4));
                QPointF controlPoint2(center.x() + radius * qCos(angle + M_PI + M_PI / 4), center.y() + radius * qSin(angle + M_PI + M_PI / 4));

                QPainterPath loopPath;
                loopPath.moveTo(start);
                loopPath.cubicTo(controlPoint1, controlPoint2, end);

                QGraphicsPathItem *loopItem = new QGraphicsPathItem(loopPath);

                // Создаем стрелковой конец петли
                QPolygonF loopArrowHead = createArrowHead(end, start);
                QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem(loopArrowHead);
                arrow->setBrush(Qt::black);
                arrow->setPen(Qt::NoPen);

                // Вычисляем координаты текста на петле
                QPointF textPos(ellipse->mapToScene(ellipse->boundingRect().topRight())); // текст веса на петле

                QGraphicsTextItem* textItem = scene->addText(QString::number(matrix[i][j])); // текст веса на петле
                textItem->setPos(textPos);

                QList<QGraphicsItem*> items;
                items << loopItem << textItem << arrow;
                QGraphicsItemGroup *loopGroup = scene->createItemGroup(items);      // добавляем в группу линию и вес

                vectorOfArrows.push_back(loopGroup);
            }
        }
    }
    graph.updateVector(vectorOfArrows);
}

bool GraphGenerator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == scene && event->type() == QEvent::GraphicsSceneMouseMove)
    {
        // Приводим событие к QGraphicsSceneMouseEvent для получения информации о движении мыши
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        // Проверяем, что произошло перемещение группы
        if (mouseEvent->buttons() & Qt::LeftButton)
        {
            // Проверяем, что элемент перемещаемый
            if (mouseEvent->lastScenePos() != mouseEvent->scenePos())
            {
                // Получаем элемент, на который указывает мышь
                QGraphicsItem *item = scene->itemAt(mouseEvent->scenePos(), QTransform());
                // Проверяем, является ли этот элемент группой объектов
                if (item && item->type() == QGraphicsItemGroup::Type)
                {
                    updateArrows();  // меняем стрелки
                    return true;    // Помечаем событие как обработанное
                }
            }
        }
    }
    // Если событие не обработано, передаем его дальше для обработки другими фильтрами
    return QObject::eventFilter(watched, event);
}

void GraphGenerator::openMenu()
{
    // // Вызываем диалговое окно поверх основного окна для поисков/обходов
    output searchMenu(&graph);
    searchMenu.setModal(true);
    searchMenu.exec();
}

void GraphGenerator::tsp()
{
    // Вызываем диалговое окно поверх основного окна для решения задачи коммивояжера
    TSP tspMenu(&graph);
    tspMenu.setModal(true);
    tspMenu.exec();
}

QPolygonF GraphGenerator::createArrowHead(const QPointF& startPoint, const QPointF& endPoint)
{
    // Добавление наконечника стрелки:

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

void GraphGenerator::updateSerialNumbers()
{
    int size = graph.getSize();
    QGraphicsItemGroup** groups = graph.getMatrixOfGroups();
    for (int i = 1; i < size; i++)
    {
        foreach (QGraphicsItem *item, groups[i]->childItems())      // перебор контейнера
        {
            QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
            if (textItem)
            {
                textItem->setPlainText(QString::number(i));     // обновляем порядковый номер на сцене
            }
        }
    }
    scene->update();
}
