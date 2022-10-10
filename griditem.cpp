#include "griditem.h"

gridItem::gridItem(QGraphicsItem *parent)
{

}

QRectF gridItem::boundingRect() const
{
    return QRectF(-100,0,100,100);
}

void gridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void gridItem::setGrid(QGraphicsScene *scene, int sceneWidth, int sceneHeight, int gridsX, int gridsY)
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

    // Create Grid
    float gridWidth = sceneWidth/gridsX;
    float gridHeight = sceneHeight/gridsY;
}

void AnomalyDetect::setupGridROIs(QGraphicsScene *scene)
{
//    int gridsX = 16;
//    int gridsY = 16;
    PatchROIs.clear();
    QList<QGraphicsItem *>  graphicItems = scene->items();
    foreach(QGraphicsItem *graphicItem,graphicItems){
        if(graphicItem->type()== RectangleFeatureItemType)
            {
            graphicItem->hide();
                scene->removeItem(graphicItem);
            }
    }

    float width = 1280 / gridsX;
    float height = 720 / gridsY;

    for(int gridY = 0; gridY < 720; gridY+=height)
    {
        for(int gridX = 0; gridX < 1280; gridX+=width)
        {
            RoiRectangle roiRect;
            roiRect.P1 = QPointF(gridX,gridY);
            roiRect.P2 = QPointF(gridX+width,gridY+height);
            PatchROIs.append(roiRect);

//            rectangleItem *rectRoi = new rectangleItem();
//            rectRoi->P1 = QPointF(gridX,gridY);
//            rectRoi->P2 = QPointF(gridX+width,gridY+height);

//            rectRoi->show();
//            rectRoi->setVisible(true);
//            scene->addItem(rectRoi);
        }
    }

    DrawGrid(scene);
}
