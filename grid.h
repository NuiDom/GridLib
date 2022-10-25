#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QGraphicsScene>
#include "rectangleitem.h"

struct RoiRectangle{
    QPointF P1;
    QPointF P2;
    QPointF P3;
    QPointF P4;
};

class grid : public QObject
{
    Q_OBJECT
public:
    grid(QGraphicsScene *);

    void setGrid(int sceneWidth, int sceneHeight, int rows, int columns);
    QVector<RoiRectangle> PatchROIs;

    void DrawGrid();

public slots:
    void slotPointChanged(QPointF);
    void slotPointToChange(QPointF, currentPoint);
    void slotDoubleClicked(QPointF, currentPoint);

signals:
    void signalChangeGrid();

protected:
    QGraphicsScene *currentScene;

    QPointF moveStartP;
    currentPoint thisPoint;
    int IndexOfChangingRect;

    int numRows;
    int numCols;
    int gridWidth;
    int gridHeight;

    int doubleClickCounter = 0;
    QPointF doubleClickedPoint1;
    QPointF doubleClickedPoint2;
    rectangleItem groupSelectionRect;

    void P1HasChanged(QPointF);
    void P2HasChanged(QPointF);
    void P3HasChanged(QPointF);
    void P4HasChanged(QPointF);

    void groupSelection();
};

#endif // GRID_H
