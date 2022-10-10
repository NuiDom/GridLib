#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class rectangleItem : public QGraphicsItem
{
public:
    rectangleItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF P1;
    QPointF P2;

protected:
    QPointF pTopLeft;
    QPointF pBottomLeft;
    QPointF pTopRight;
    QPointF pBottomRight;
};

#endif // RECTANGLEITEM_H
