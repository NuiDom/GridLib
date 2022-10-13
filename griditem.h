#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

#define UserType 65536
#define RectangleFeatureItemType UserType+5
struct RoiRectangle{
    QPointF P1;
    QPointF P2;
    QPointF P3;
    QPointF P4;
};

class gridItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    gridItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGrid(int sceneWidth, int sceneHeight, int rows, int columns);
    QVector<RoiRectangle> PatchROIs;

    void paintRect();

    void DrawGrid(QGraphicsScene *scene);
//    void AddGrid();

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


protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    void hoverEnterEvent(QGraphicsSceneHoverEvent*event);
//    void hoverLeaveEvent(QGraphicsSceneHoverEvent*event);

};

#endif // GRIDITEM_H
