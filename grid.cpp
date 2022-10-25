#include "grid.h"

grid::grid(QGraphicsScene *scene)
{
    currentScene = scene;
}

void grid::setGrid(int sceneWidth, int sceneHeight, int rows, int columns)
{
    gridWidth = sceneWidth;
    gridHeight = sceneHeight;
    numRows = rows;
    numCols = columns;

    // Create Grid
    float rectWidth = sceneWidth/columns;
    float rectHeight = sceneHeight/rows;

    for(int gridRows=0; gridRows<sceneHeight; gridRows+=rectHeight)
    {
        for(int gridsCols=0; gridsCols<sceneWidth; gridsCols+=rectWidth)
        {
            RoiRectangle roiRect;
            roiRect.P1 = QPointF(gridsCols,gridRows);
            roiRect.P2 = QPointF(gridsCols+rectWidth,gridRows+rectHeight);
            roiRect.P3 = QPointF(gridsCols+rectWidth,gridRows);
            roiRect.P4 = QPointF(gridsCols,gridRows+rectHeight);
            GridPatchROIs.append(roiRect);
        }
    }
}

void grid::DrawGrid()
{
    // Clear the Scene
    QList<QGraphicsItem *>  graphicItems = currentScene->items();
    foreach(QGraphicsItem *graphicItem,graphicItems){
        if(graphicItem->type()== RectangleFeatureItemType)
            {
            graphicItem->hide();
                currentScene->removeItem(graphicItem);
            }
    }

    for(const RoiRectangle roiRect: qAsConst(GridPatchROIs))
    {
        rectangleItem *rectRoi = new rectangleItem();
        connect(rectRoi, SIGNAL(signalPointChanged(QPointF)), this, SLOT(slotPointChanged(QPointF)));
        connect(rectRoi, SIGNAL(signalPointToChange(QPointF, currentPoint)), this, SLOT(slotPointToChange(QPointF, currentPoint)));
        rectRoi->P1 = roiRect.P1;
        rectRoi->P2 = roiRect.P2;
        rectRoi->P3 = roiRect.P3;
        rectRoi->P4 = roiRect.P4;

        rectRoi->show();
        rectRoi->setVisible(true);
        currentScene->addItem(rectRoi);

    }
}

void grid::slotPointChanged(QPointF point)
{
    bool pointChanged = false;

    if((moveStartP.x() > (0-7) && moveStartP.x() < (0+7)) ||
       (moveStartP.x() > (gridWidth-7) && moveStartP.x() < (gridWidth+7)) ||
       (moveStartP.y() > (0-7) && moveStartP.y() < (0+7)) ||
       (moveStartP.y() > (gridHeight-7) && moveStartP.y() < (gridHeight+7))){
        qDebug() << "Point on border";
        DrawGrid();
        return;
    }

    //update patchroi
    if(thisPoint == point1){
        P1HasChanged(point);
        pointChanged = true;
    }
    else if(thisPoint == point2){
        P2HasChanged(point);
        pointChanged = true;
    }
    else if(thisPoint == point3){
        P3HasChanged(point);
        pointChanged = true;
    }
    else if(thisPoint == point4){
        P4HasChanged(point);
        pointChanged = true;
    }
    else {
        pointChanged = false;
    }

    if(pointChanged)
        moveStartP = point;

    //draw grid based off patchroi
    if(pointChanged == true)
        DrawGrid();
}

void grid::slotPointToChange(QPointF pointVal, currentPoint pointNum)
{
    moveStartP = pointVal;
    thisPoint = pointNum;
}

void grid::P1HasChanged(QPointF point)
{
    for(int i=0; i<GridPatchROIs.size(); i++){
        if((moveStartP.x()>(GridPatchROIs[i].P1.x()-7)) &&
           (moveStartP.x()<(GridPatchROIs[i].P1.x()+7)) &&
           (moveStartP.y()>(GridPatchROIs[i].P1.y()-7)) &&
           (moveStartP.y()<(GridPatchROIs[i].P1.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    GridPatchROIs[IndexOfChangingRect].P1 = point;
    GridPatchROIs[IndexOfChangingRect].P4 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect].P4.y());
    GridPatchROIs[IndexOfChangingRect].P3 = QPointF(GridPatchROIs[IndexOfChangingRect].P3.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - 1].P3 = point;
    GridPatchROIs[IndexOfChangingRect - 1].P2 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - 1].P2.y());
    GridPatchROIs[IndexOfChangingRect - 1].P1 = QPointF(GridPatchROIs[IndexOfChangingRect - 1].P1.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - numCols].P4 = point;
    GridPatchROIs[IndexOfChangingRect - numCols].P1 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - numCols].P1.y());
    GridPatchROIs[IndexOfChangingRect - numCols].P2 = QPointF(GridPatchROIs[IndexOfChangingRect - numCols].P2.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - numCols - 1].P2 = point;
    GridPatchROIs[IndexOfChangingRect - numCols - 1].P3 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - numCols - 1].P3.y());
    GridPatchROIs[IndexOfChangingRect - numCols - 1].P4 = QPointF(GridPatchROIs[IndexOfChangingRect - numCols - 1].P4.x(), point.y());
}

void grid::P2HasChanged(QPointF point)
{
    for(int i=0; i<GridPatchROIs.size(); i++){
        if((moveStartP.x()>(GridPatchROIs[i].P2.x()-7)) &&
           (moveStartP.x()<(GridPatchROIs[i].P2.x()+7)) &&
           (moveStartP.y()>(GridPatchROIs[i].P2.y()-7)) &&
           (moveStartP.y()<(GridPatchROIs[i].P2.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    GridPatchROIs[IndexOfChangingRect].P2 = point;
    GridPatchROIs[IndexOfChangingRect].P3 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect].P3.y());
    GridPatchROIs[IndexOfChangingRect].P4 = QPointF(GridPatchROIs[IndexOfChangingRect].P4.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + 1].P4 = point;
    GridPatchROIs[IndexOfChangingRect + 1].P1 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect+1].P1.y());
    GridPatchROIs[IndexOfChangingRect + 1].P2 = QPointF(GridPatchROIs[IndexOfChangingRect+1].P2.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + numCols].P3 = point;
    GridPatchROIs[IndexOfChangingRect + numCols].P2 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect + numCols].P2.y());
    GridPatchROIs[IndexOfChangingRect + numCols].P1 = QPointF(GridPatchROIs[IndexOfChangingRect + numCols].P1.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + numCols + 1].P1 = point;
    GridPatchROIs[IndexOfChangingRect + numCols + 1].P4 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect + numCols + 1].P4.y());
    GridPatchROIs[IndexOfChangingRect + numCols + 1].P3 = QPointF(GridPatchROIs[IndexOfChangingRect + numCols + 1].P3.x(), point.y());
}

void grid::P3HasChanged(QPointF point)
{
    for(int i=0; i<GridPatchROIs.size(); i++){
        if((moveStartP.x()>(GridPatchROIs[i].P3.x()-7)) &&
           (moveStartP.x()<(GridPatchROIs[i].P3.x()+7)) &&
           (moveStartP.y()>(GridPatchROIs[i].P3.y()-7)) &&
           (moveStartP.y()<(GridPatchROIs[i].P3.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    GridPatchROIs[IndexOfChangingRect].P3 = point;
    GridPatchROIs[IndexOfChangingRect].P2 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect].P2.y());
    GridPatchROIs[IndexOfChangingRect].P1 = QPointF(GridPatchROIs[IndexOfChangingRect].P1.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + 1].P1 = point;
    GridPatchROIs[IndexOfChangingRect + 1].P4 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect + 1].P4.y());
    GridPatchROIs[IndexOfChangingRect + 1].P3 = QPointF(GridPatchROIs[IndexOfChangingRect + 1].P3.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - numCols].P2 = point;
    GridPatchROIs[IndexOfChangingRect - numCols].P3 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - numCols].P3.y());
    GridPatchROIs[IndexOfChangingRect - numCols].P4 = QPointF(GridPatchROIs[IndexOfChangingRect - numCols].P4.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - numCols + 1].P4 = point;
    GridPatchROIs[IndexOfChangingRect - numCols + 1].P1 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - numCols + 1].P1.y());
    GridPatchROIs[IndexOfChangingRect - numCols + 1].P2 = QPointF(GridPatchROIs[IndexOfChangingRect - numCols + 1].P2.x(), point.y());
}

void grid::P4HasChanged(QPointF point)
{
    for(int i=0; i<GridPatchROIs.size(); i++){
        if((moveStartP.x()>(GridPatchROIs[i].P4.x()-7)) &&
           (moveStartP.x()<(GridPatchROIs[i].P4.x()+7)) &&
           (moveStartP.y()>(GridPatchROIs[i].P4.y()-7)) &&
           (moveStartP.y()<(GridPatchROIs[i].P4.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    GridPatchROIs[IndexOfChangingRect].P4 = point;
    GridPatchROIs[IndexOfChangingRect].P1 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect].P1.y());
    GridPatchROIs[IndexOfChangingRect].P2 = QPointF(GridPatchROIs[IndexOfChangingRect].P2.x(), point.y());

    GridPatchROIs[IndexOfChangingRect - 1].P2 = point;
    GridPatchROIs[IndexOfChangingRect - 1].P3 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect - 1].P3.y());
    GridPatchROIs[IndexOfChangingRect - 1].P4 = QPointF(GridPatchROIs[IndexOfChangingRect - 1].P4.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + numCols].P1 = point;
    GridPatchROIs[IndexOfChangingRect + numCols].P4 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect + numCols].P4.y());
    GridPatchROIs[IndexOfChangingRect + numCols].P3 = QPointF(GridPatchROIs[IndexOfChangingRect + numCols].P3.x(), point.y());

    GridPatchROIs[IndexOfChangingRect + numCols - 1].P3 = point;
    GridPatchROIs[IndexOfChangingRect + numCols - 1].P2 = QPointF(point.x(), GridPatchROIs[IndexOfChangingRect + numCols - 1].P2.y());
    GridPatchROIs[IndexOfChangingRect + numCols - 1].P1 = QPointF(GridPatchROIs[IndexOfChangingRect + numCols - 1].P1.x(), point.y());
}
