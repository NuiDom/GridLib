#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsScene>
#include "rectangleitem.h"

struct RoiRectangle{
    QPointF P1;
    QPointF P2;
};

class gridItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    gridItem(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int rows, int columns);
    QVector<RoiRectangle> PatchROIs;

    void DrawGrid(QGraphicsScene *scene);
//    void AddGrid();


public slots:
    void slotPointChanged(QPointF);
    void slotMoveStartPoint(QPointF);

signals:
    void signalChangeGrid();

protected:
    QPointF moveStartP;
};

#endif // GRIDITEM_H
