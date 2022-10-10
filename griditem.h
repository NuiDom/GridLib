#ifndef GRIDITEM_H
#define GRIDITEM_H

#include "rectangleitem.h"

class gridItem : public QGraphicsItem
{
public:
    gridItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int gridsX, int gridsY);
};

#endif // GRIDITEM_H
