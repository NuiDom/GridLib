#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#define UserType 65536
#define RectangleFeatureItemType UserType+5

enum currentPoint
{
    point1,
    point2,
    point3,
    point4
};

class rectangleItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    rectangleItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const override
    {
        return RectangleFeatureItemType;
    }

    QPointF P1;
    QPointF P2;
    QPointF P3;
    QPointF P4;

    QPointF pTopLeft;
    QPointF pBottomRight;
    QPointF pBottomLeft;
    QPointF pTopRight;

    bool moveTL = false;
    bool moveBR = false;
    bool moveTR = false;
    bool moveBL = false;

    bool mouseHover;
    bool isSelected = false;
    bool isTemplate = false;

    QPointF moveStartPoint;

signals:
    void signalPointChanged(QPointF);
    void signalPointToChange(QPointF, currentPoint);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent*event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*event);
};

#endif // RECTANGLEITEM_H
