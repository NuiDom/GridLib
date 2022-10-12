#include "rectangleitem.h"

rectangleItem::rectangleItem(QGraphicsItem *parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

    mouseHover = false;
    P1 = QPointF(50,50);
    P2 = QPointF(150,150);
    setPos(QPointF(0, 0));
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

    if(mouseHover == true){
        brush.setColor(Qt::red);
        painter->setBrush(brush);
    }
    else
    {
        brush.setColor(Qt::blue);
        painter->setBrush(brush);
    }

    painter->drawEllipse(pTopLeft,7,7);
    painter->drawEllipse(pBottomLeft,7,7);
    painter->drawEllipse(pTopRight,7,7);
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

void rectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MP event->button() : " << event->button();

    if(event->button()==Qt::LeftButton)
    {
        if((event->pos().x()>pTopLeft.x()-7) &&
                (event->pos().x()<pTopLeft.x()+7) &&
                (event->pos().y()>pTopLeft.y()-7) &&
                (event->pos().y()<pTopLeft.y()+7))
            moveTL = true;

        if((event->pos().x()>pBottomRight.x()-7) &&
                (event->pos().x()<pBottomRight.x()+7) &&
                (event->pos().y()>pBottomRight.y()-7) &&
                (event->pos().y()<pBottomRight.y()+7))
            moveBR = true;
        if((event->pos().x()>pTopRight.x()-7) &&
                (event->pos().x()<pTopRight.x()+7) &&
                (event->pos().y()>pTopRight.y()-7) &&
                (event->pos().y()<pTopRight.y()+7))
            moveTR = true;

        if((event->pos().x()>pBottomLeft.x()-7) &&
                (event->pos().x()<pBottomLeft.x()+7) &&
                (event->pos().y()>pBottomLeft.y()-7) &&
                (event->pos().y()<pBottomLeft.y()+7))
            moveBL = true;

        moveStartPoint = event->pos();
    }
    emit signalPointToChange(moveStartPoint);

    update();
    QGraphicsItem::mousePressEvent(event);
}

void rectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MR event->button() : " << event->button();

    moveTL = false;
    moveBR = false;
    moveTR = false;
    moveBL = false;

    prepareGeometryChange();
    update();

    QGraphicsItem::mouseReleaseEvent(event);
}

void rectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos();

    if(moveTL==true)
        P1 = event->pos();
    else if (moveBR==true)
         P2 = event->pos();
    else if (moveTR==true) {
        P1.setY(event->pos().y());
        P2.setX(event->pos().x());
    }
    else if (moveBL==true) {
        P1.setX(event->pos().x());
        P2.setY(event->pos().y());
    }
    else
    {
        P1 += event->pos() - moveStartPoint;
        P2 += event->pos() - moveStartPoint;
    }

    emit signalPointChanged(event->pos());
    moveStartPoint = event->pos();
    prepareGeometryChange();
    update();
}

void rectangleItem::hoverEnterEvent(QGraphicsSceneHoverEvent*event)
{
    setZValue(100);
    mouseHover = true;
    update();
}

void rectangleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*event)
{
    setZValue(10);
    mouseHover = false;
    update();
}
