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
    pTopRight = P3;
    pBottomLeft = P4;


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

    currentPoint whichPoint;

    if(event->button()==Qt::LeftButton)
    {
        if((event->pos().x()>pTopLeft.x()-7) &&
                (event->pos().x()<pTopLeft.x()+7) &&
                (event->pos().y()>pTopLeft.y()-7) &&
                (event->pos().y()<pTopLeft.y()+7)){
            whichPoint = point1;
            moveTL = true;
        }

        if((event->pos().x()>pBottomRight.x()-7) &&
                (event->pos().x()<pBottomRight.x()+7) &&
                (event->pos().y()>pBottomRight.y()-7) &&
                (event->pos().y()<pBottomRight.y()+7)){
            whichPoint = point2;
            moveBR = true;
        }

        if((event->pos().x()>pTopRight.x()-7) &&
                (event->pos().x()<pTopRight.x()+7) &&
                (event->pos().y()>pTopRight.y()-7) &&
                (event->pos().y()<pTopRight.y()+7)){
            whichPoint = point3;
            moveTR = true;
        }


        if((event->pos().x()>pBottomLeft.x()-7) &&
                (event->pos().x()<pBottomLeft.x()+7) &&
                (event->pos().y()>pBottomLeft.y()-7) &&
                (event->pos().y()<pBottomLeft.y()+7)){
            whichPoint = point4;
            moveBL = true;
        }


        moveStartPoint = event->pos();
    }
    if(moveTL || moveBL || moveBR || moveTR)
        emit signalPointToChange(moveStartPoint, whichPoint);

    update();
    QGraphicsItem::mousePressEvent(event);
}

void rectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "MR event->button() : " << event->button();

    if(moveTL || moveBL || moveBR || moveTR)
        emit signalPointChanged(moveStartPoint);

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

    if(moveTL==true){
        P1 = event->pos();
        P4 = QPointF(event->pos().x(), P4.y());
        P3 = QPointF(P3.x(), event->pos().y());
    }
    else if (moveBR==true){
         P2 = event->pos();
         P4 = QPointF(P4.x(), event->pos().y());
         P3 = QPointF(event->pos().x(), P3.y());
    }
    else if (moveBL==true) {
        P4 = event->pos();
        P2 = QPointF(P2.x(), event->pos().y());
        P1 = QPointF(event->pos().x(), P1.y());
    }
    else if (moveTR==true) {
        P3 = event->pos();
        P2 = QPointF(event->pos().x(), P2.y());
        P1 = QPointF(P1.x(), event->pos().y());
    }
    else
    {
        P1 += event->pos() - moveStartPoint;
        P2 += event->pos() - moveStartPoint;
    }

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
