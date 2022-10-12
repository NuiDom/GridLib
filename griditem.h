#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsScene>
#include "rectangleitem.h"

struct RoiRectangle{
    QPointF P1;
    QPointF P2;
};

class gridItem : public QGraphicsItemGroup
{
public:
    gridItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int rows, int columns);
    QVector<RoiRectangle> PatchROIs;

    void DrawGrid(QGraphicsScene *scene);
};

#endif // GRIDITEM_H
