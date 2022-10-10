#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsScene>
#include "rectangleitem.h"

class gridItem : public QGraphicsItem
{
public:
    gridItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int rows, int columns);
};

#endif // GRIDITEM_H
