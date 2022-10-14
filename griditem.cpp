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
//    setGrid(scene, 1280, 720, 2, 2);
}

void gridItem::setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int rows, int columns)
{
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
        connect(rectRoi, SIGNAL(signalPointToChange(QPointF)), this, SLOT(slotMoveStartPoint(QPointF)));
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
    //update patchroi
//    if(PatchROIs.contains(moveStartP)){
        for(int i=0; i<PatchROIs.size(); i++){
            if((moveStartP.x()>(PatchROIs[i].P1.x()-7)) &&
               (moveStartP.x()<(PatchROIs[i].P1.x()+7)) &&
               (moveStartP.y()>(PatchROIs[i].P1.y()-7)) &&
               (moveStartP.y()<(PatchROIs[i].P1.y()+7))     )
//            if((PatchROIs[i].P1 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P1 < (moveStartP+QPointF(7,7))))
            {
                PatchROIs[i].P1 = point;
                pointChanged = true;
            }
            if((moveStartP.x()>(PatchROIs[i].P2.x()-7)) &&
               (moveStartP.x()<(PatchROIs[i].P2.x()+7)) &&
               (moveStartP.y()>(PatchROIs[i].P2.y()-7)) &&
               (moveStartP.y()<(PatchROIs[i].P2.y()+7))     )
//            if((PatchROIs[i].P2 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P2 < (moveStartP+QPointF(7,7))))
            {
                PatchROIs[i].P2 = point;
                pointChanged = true;
            }

        }
        if(pointChanged)
            moveStartP = point;
//    }
    //draw grid based off patchroi
    if(pointChanged == true)
        emit signalChangeGrid();
}

void gridItem::slotMoveStartPoint(QPointF point)
{
    moveStartP = point;
}

