#include "rectangleitem.h"

rectangleItem::rectangleItem(QGraphicsItem *parent)
{


}

QRectF rectangleItem::boundingRect() const
{
    return QRectF(QPointF(P1.x()-10,P1.y()-10),QPointF(P2.x()+10,P2.y()+10));
}

void rectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    pTopLeft = P1;
    pBottomRight = P2;
    pBottomLeft = QPointF(pTopLeft.x(),pBottomRight.y());
    pTopRight = QPointF(pBottomRight.x(),pTopLeft.y());

    QBrush brush = painter->brush();
    brush.setStyle(Qt::SolidPattern);

    brush.setColor(Qt::blue);
    painter->setBrush(brush);
    painter->drawEllipse(pTopLeft,7,7);

    brush.setColor(Qt::red);
    painter->setBrush(brush);
    painter->drawEllipse(pBottomLeft,7,7);

    brush.setColor(Qt::green);
    painter->setBrush(brush);
    painter->drawEllipse(pTopRight,7,7);

    brush.setColor(Qt::gray);
    painter->setBrush(brush);
    painter->drawEllipse(pBottomRight,7,7);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter->setPen(pen);

    painter->drawLine(pTopLeft,pBottomLeft);
    painter->drawLine(pTopLeft,pTopRight);
    painter->drawLine(pBottomLeft,pBottomRight);
    painter->drawLine(pTopRight,pBottomRight);
}
