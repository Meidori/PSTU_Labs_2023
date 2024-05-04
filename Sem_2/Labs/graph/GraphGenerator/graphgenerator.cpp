#include "graphgenerator.h"
#include "ui_graphgenerator.h"
#include "addnewedgewindow.h"
#include "ui_addnewedgewindow.h"
#include "graph.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsItemGroup>
#include <QtMath>

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

    // graph.printMatrix();
}
/*
 * lkdfgnkjlfdnggkjdsnsd;ds/dsfg'
 * dfgsdZV
 * fgZDF
 * dssfdZFD
 * KDSF;KLFJADLKFJSKLKDASLFSK;LADKSFAK
 * fgdSFDSDAL;FSADKLASDLFSKFALSADFSF
 * dfgGFBSFDGHFGHGDJGHDJGXDFVSDFZ
 * gdsSADFSFDAFDSASDFADFGAHFGJGHKGHKHJ
 * gdfsCGHGDZDZFSDVSFSDDВЫАЫАЯМЧ
 * dfgSFDDSAFSDFBSYUTUTURTERFVSDCZX
 * gdfFDVGJES;hjeFDJZJSNVJKZDBJK
 * dXCVZXLKVNKZNDRV<DV
 * gdsSZDVDSZVZDFVDZVDVF
 * dVFDZVDFZVDFFVDVZDZVDVDVZDVDZ
 * gsDZFVZDFVDFV
 * gdZDFVDVD
 * gVZDVDF
 * ..........
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
                    updateNodePosition(group);  // меняем pos
                    return true;
                }
            }
        }
    }
    // Если событие не обработано, передаем его дальше для обработки другими фильтрами
    return QObject::eventFilter(watched, event);
}


void GraphGenerator::updateNodePosition(QGraphicsItemGroup *group)
{
    // qDebug() << "updateNodePosition";
    if (group)
    {
        qDebug() << "group: " << group;
        QGraphicsTextItem* serialNumberItem = nullptr;
        QGraphicsEllipseItem* node = nullptr;

        // Поиск текстового элемента и эллипса в группе
        foreach (QGraphicsItem *item, group->childItems())
        {
            if (QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(item))
            {
                serialNumberItem = textItem;
            }
            else if (QGraphicsEllipseItem *ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item))
            {
                node = ellipseItem;
            }
        }

        qDebug() << "serialNumberItem:" << serialNumberItem;
        qDebug() << "node:" << node;

        // Проверка, что найдены и текстовый элемент, и эллипс
        if (serialNumberItem && node)
        {
            // Получение порядкого номера из текстового элемента
            QString serialNumberQS = serialNumberItem->toPlainText();
            int serialNumber = serialNumberQS.toInt();

            // Обновление матрицы для эллипса и группы
            QPointF textItemPos = group->pos() + QPointF(node->boundingRect().center().x() - serialNumberItem->boundingRect().width() / 2,
                                                           node->boundingRect().center().y() - serialNumberItem->boundingRect().height() / 2);
            serialNumberItem->setPos(textItemPos);

            // Обновление позиции эллипса
            QPointF ellipsePos = group->pos();
            node->setPos(ellipsePos);

            graph.updateMatrixOfGroups(serialNumber, group);
            graph.updateMatrixOfEllipses(serialNumber, node);
        }
    }
}
*/
void GraphGenerator::addEdge()
{
    AddNewEdgeWindow addEdgeWindow(graph);
    addEdgeWindow.setModal(true);
    addEdgeWindow.exec();

    // updateArrows();

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
        tmp = vectorOfArrows[i];
        for (auto item : tmp->childItems())
        {
            scene->removeItem(item);    // удаляем нарисованные линни/стрелки
        }
        delete tmp;
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
        }
    }
}

GraphGenerator::~GraphGenerator()
{
    delete scene;
    delete ui;
}

void GraphGenerator::removeCurEllipses()
{
    QGraphicsEllipseItem* ellipse;
    QGraphicsEllipseItem** ellipses = graph.getMatrixOfEllipses();

    for (int i = 0; i < graph.getSize(); i++)
    {
        ellipse = ellipses[i];
        if (ellipse)
        {
            qDebug() << ellipse;
            scene->removeItem(ellipse);
        }
    }
}

void GraphGenerator::removeCurGroups()
{
    QGraphicsItemGroup* group;
    QGraphicsItemGroup** groups = graph.getMatrixOfGroups();

    for (int i = 0; i < graph.getSize(); i++)
    {
        group = groups[i];
        if (group)
        {
            qDebug() << group;
            scene->removeItem(group);
        }
    }
}
