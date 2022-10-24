#include "griditem.h"

gridItem::gridItem(QGraphicsItem *parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF gridItem::boundingRect() const
{
    return QRectF(1280,720,10,10);
}

void gridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void gridItem::setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int rows, int columns)
{
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
            PatchROIs.append(roiRect);

//            rectangleItem *rectRoi;
//            rectRoi = new rectangleItem();
//            rectRoi->P1 = QPointF(gridsCols, gridRows);
//            rectRoi->P2 = QPointF(gridsCols+rectWidth, gridRows+rectHeight);
//            scene->addItem(rectRoi);
        }
    }
}

void gridItem::DrawGrid(QGraphicsScene *scene)
{
    // Clear the Scene
    QList<QGraphicsItem *>  graphicItems = scene->items();
    foreach(QGraphicsItem *graphicItem,graphicItems){
        if(graphicItem->type()== RectangleFeatureItemType)
            {
            graphicItem->hide();
                scene->removeItem(graphicItem);
            }
    }

    for(const RoiRectangle roiRect: qAsConst(PatchROIs))
    {
        rectangleItem *rectRoi = new rectangleItem();
        connect(rectRoi, SIGNAL(signalPointChanged(QPointF)), this, SLOT(slotPointChanged(QPointF)));
        connect(rectRoi, SIGNAL(signalPointToChange(QPointF, currentPoint)), this, SLOT(slotPointToChange(QPointF, currentPoint)));
        rectRoi->P1 = roiRect.P1;
        rectRoi->P2 = roiRect.P2;
        rectRoi->P3 = roiRect.P3;
        rectRoi->P4 = roiRect.P4;

//        addToGroup(rectRoi);
        rectRoi->show();
        rectRoi->setVisible(true);
        scene->addItem(rectRoi);

    }
}

//void gridItem::AddGrid()
//{
//    for(const RoiRectangle roiRect: qAsConst(PatchROIs))
//    {
//        rectangleItem *rectRoi = new rectangleItem();
//        rectRoi->P1 = roiRect.P1;
//        rectRoi->P2 = roiRect.P2;

//        addToGroup(rectRoi);

//    }

void gridItem::slotPointChanged(QPointF point)
{
    bool pointChanged = false;
    QPointF ppoint;

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
////    if(PatchROIs.contains(moveStartP)){
//        for(int i=0; i<PatchROIs.size(); i++){
//            //If a P1 changes
//            if((moveStartP.x()>(PatchROIs[i].P1.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P1.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P1.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P1.y()+7))     )
////            if((PatchROIs[i].P1 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P1 < (moveStartP+QPointF(7,7))))
//            {
//                //If it was changed by a P2
////                if(thisPoint == point2)
////                    ppoint = PatchROIs[i].P1;

////                ppoint.x() = point.x();
//////                else
//////                    PatchROIs[i].P1 = point;
//                PatchROIs[i].P1 = point;
//                pointChanged = true;
//            }
//            //If a P2 changes
//            if((moveStartP.x()>(PatchROIs[i].P2.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P2.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P2.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P2.y()+7))     )
////            if((PatchROIs[i].P2 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P2 < (moveStartP+QPointF(7,7))))
//            {
//                PatchROIs[i].P2 = point;
//                pointChanged = true;
//            }
//            //If a P3 changes
//            if((moveStartP.x()>(PatchROIs[i].P3.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P3.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P3.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P3.y()+7))     )
//            {
//                PatchROIs[i].P3 = point;
//                pointChanged = true;
//            }
//            //If a P4 changes
//            if((moveStartP.x()>(PatchROIs[i].P4.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P4.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P4.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P4.y()+7))     )
//            {
//                PatchROIs[i].P4 = point;
//                pointChanged = true;
//            }

//        }
        if(pointChanged)
            moveStartP = point;
//    }
    //draw grid based off patchroi
    if(pointChanged == true)
        emit signalChangeGrid();
}

void gridItem::slotPointToChange(QPointF pointVal, currentPoint pointNum)
{
    moveStartP = pointVal;
    thisPoint = pointNum;
}

void gridItem::P1HasChanged(QPointF point)
{
    for(int i=0; i<PatchROIs.size(); i++){
        if((moveStartP.x()>(PatchROIs[i].P1.x()-7)) &&
           (moveStartP.x()<(PatchROIs[i].P1.x()+7)) &&
           (moveStartP.y()>(PatchROIs[i].P1.y()-7)) &&
           (moveStartP.y()<(PatchROIs[i].P1.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    PatchROIs[IndexOfChangingRect].P1 = point;
    PatchROIs[IndexOfChangingRect].P4 = QPointF(point.x(), PatchROIs[IndexOfChangingRect].P4.y());
    PatchROIs[IndexOfChangingRect].P3 = QPointF(PatchROIs[IndexOfChangingRect].P3.x(), point.y());

    PatchROIs[IndexOfChangingRect - 1].P3 = point;
    PatchROIs[IndexOfChangingRect - 1].P2 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - 1].P2.y());
    PatchROIs[IndexOfChangingRect - 1].P1 = QPointF(PatchROIs[IndexOfChangingRect - 1].P1.x(), point.y());

    PatchROIs[IndexOfChangingRect - numCols].P4 = point;
    PatchROIs[IndexOfChangingRect - numCols].P1 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - numCols].P1.y());
    PatchROIs[IndexOfChangingRect - numCols].P2 = QPointF(PatchROIs[IndexOfChangingRect - numCols].P2.x(), point.y());

    PatchROIs[IndexOfChangingRect - numCols - 1].P2 = point;
    PatchROIs[IndexOfChangingRect - numCols - 1].P3 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - numCols - 1].P3.y());
    PatchROIs[IndexOfChangingRect - numCols - 1].P4 = QPointF(PatchROIs[IndexOfChangingRect - numCols - 1].P4.x(), point.y());
}

void gridItem::P2HasChanged(QPointF point)
{
    for(int i=0; i<PatchROIs.size(); i++){
        if((moveStartP.x()>(PatchROIs[i].P2.x()-7)) &&
           (moveStartP.x()<(PatchROIs[i].P2.x()+7)) &&
           (moveStartP.y()>(PatchROIs[i].P2.y()-7)) &&
           (moveStartP.y()<(PatchROIs[i].P2.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    PatchROIs[IndexOfChangingRect].P2 = point;
    PatchROIs[IndexOfChangingRect].P3 = QPointF(point.x(), PatchROIs[IndexOfChangingRect].P3.y());
    PatchROIs[IndexOfChangingRect].P4 = QPointF(PatchROIs[IndexOfChangingRect].P4.x(), point.y());

    PatchROIs[IndexOfChangingRect + 1].P4 = point;
    PatchROIs[IndexOfChangingRect + 1].P1 = QPointF(point.x(), PatchROIs[IndexOfChangingRect+1].P1.y());
    PatchROIs[IndexOfChangingRect + 1].P2 = QPointF(PatchROIs[IndexOfChangingRect+1].P2.x(), point.y());

    PatchROIs[IndexOfChangingRect + numCols].P3 = point;
    PatchROIs[IndexOfChangingRect + numCols].P2 = QPointF(point.x(), PatchROIs[IndexOfChangingRect + numCols].P2.y());
    PatchROIs[IndexOfChangingRect + numCols].P1 = QPointF(PatchROIs[IndexOfChangingRect + numCols].P1.x(), point.y());

    PatchROIs[IndexOfChangingRect + numCols + 1].P1 = point;
    PatchROIs[IndexOfChangingRect + numCols + 1].P4 = QPointF(point.x(), PatchROIs[IndexOfChangingRect + numCols + 1].P4.y());
    PatchROIs[IndexOfChangingRect + numCols + 1].P3 = QPointF(PatchROIs[IndexOfChangingRect + numCols + 1].P3.x(), point.y());
}

void gridItem::P3HasChanged(QPointF point)
{
    for(int i=0; i<PatchROIs.size(); i++){
        if((moveStartP.x()>(PatchROIs[i].P3.x()-7)) &&
           (moveStartP.x()<(PatchROIs[i].P3.x()+7)) &&
           (moveStartP.y()>(PatchROIs[i].P3.y()-7)) &&
           (moveStartP.y()<(PatchROIs[i].P3.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    PatchROIs[IndexOfChangingRect].P3 = point;
    PatchROIs[IndexOfChangingRect].P2 = QPointF(point.x(), PatchROIs[IndexOfChangingRect].P2.y());
    PatchROIs[IndexOfChangingRect].P1 = QPointF(PatchROIs[IndexOfChangingRect].P1.x(), point.y());

    PatchROIs[IndexOfChangingRect + 1].P1 = point;
    PatchROIs[IndexOfChangingRect + 1].P4 = QPointF(point.x(), PatchROIs[IndexOfChangingRect + 1].P4.y());
    PatchROIs[IndexOfChangingRect + 1].P3 = QPointF(PatchROIs[IndexOfChangingRect + 1].P3.x(), point.y());

    PatchROIs[IndexOfChangingRect - numCols].P2 = point;
    PatchROIs[IndexOfChangingRect - numCols].P3 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - numCols].P3.y());
    PatchROIs[IndexOfChangingRect - numCols].P4 = QPointF(PatchROIs[IndexOfChangingRect - numCols].P4.x(), point.y());

    PatchROIs[IndexOfChangingRect - numCols + 1].P4 = point;
    PatchROIs[IndexOfChangingRect - numCols + 1].P1 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - numCols + 1].P1.y());
    PatchROIs[IndexOfChangingRect - numCols + 1].P2 = QPointF(PatchROIs[IndexOfChangingRect - numCols + 1].P2.x(), point.y());
}

void gridItem::P4HasChanged(QPointF point)
{
    for(int i=0; i<PatchROIs.size(); i++){
        if((moveStartP.x()>(PatchROIs[i].P4.x()-7)) &&
           (moveStartP.x()<(PatchROIs[i].P4.x()+7)) &&
           (moveStartP.y()>(PatchROIs[i].P4.y()-7)) &&
           (moveStartP.y()<(PatchROIs[i].P4.y()+7))   )
        {
            IndexOfChangingRect = i;
        }
    }

    PatchROIs[IndexOfChangingRect].P4 = point;
    PatchROIs[IndexOfChangingRect].P1 = QPointF(point.x(), PatchROIs[IndexOfChangingRect].P1.y());
    PatchROIs[IndexOfChangingRect].P2 = QPointF(PatchROIs[IndexOfChangingRect].P2.x(), point.y());

    PatchROIs[IndexOfChangingRect - 1].P2 = point;
    PatchROIs[IndexOfChangingRect - 1].P3 = QPointF(point.x(), PatchROIs[IndexOfChangingRect - 1].P3.y());
    PatchROIs[IndexOfChangingRect - 1].P4 = QPointF(PatchROIs[IndexOfChangingRect - 1].P4.x(), point.y());

    PatchROIs[IndexOfChangingRect + numCols].P1 = point;
    PatchROIs[IndexOfChangingRect + numCols].P4 = QPointF(point.x(), PatchROIs[IndexOfChangingRect + numCols].P4.y());
    PatchROIs[IndexOfChangingRect + numCols].P3 = QPointF(PatchROIs[IndexOfChangingRect + numCols].P3.x(), point.y());

    PatchROIs[IndexOfChangingRect + numCols - 1].P3 = point;
    PatchROIs[IndexOfChangingRect + numCols - 1].P2 = QPointF(point.x(), PatchROIs[IndexOfChangingRect + numCols - 1].P2.y());
    PatchROIs[IndexOfChangingRect + numCols - 1].P1 = QPointF(PatchROIs[IndexOfChangingRect + numCols - 1].P1.x(), point.y());
}

