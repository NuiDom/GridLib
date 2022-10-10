#include "griditem.h"

gridItem::gridItem(QGraphicsItem *parent)
{

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
//    // Clear the Scene
//    QList<QGraphicsItem *>  graphicItems = scene->items();
//    foreach(QGraphicsItem *graphicItem,graphicItems){
//        if(graphicItem->type()== RectangleFeatureItemType)
//            {
//            graphicItem->hide();
//                scene->removeItem(graphicItem);
//            }
//    }

    // Create Grid
    float rectWidth = sceneWidth/columns;
    float rectHeight = sceneHeight/rows;

    for(int gridRows=0; gridRows<sceneHeight; gridRows+=rectHeight)
    {
        for(int gridsCols=0; gridsCols<sceneWidth; gridsCols+=rectWidth)
        {
            rectangleItem *rectRoi;
            rectRoi = new rectangleItem();
            rectRoi->P1 = QPointF(gridsCols, gridRows);
            rectRoi->P2 = QPointF(gridsCols+rectWidth, gridRows+rectHeight);
            scene->addItem(rectRoi);
        }
    }
}

//void AnomalyDetect::setupGridROIs(QGraphicsScene *scene)
//{
////    int gridsX = 16;
////    int gridsY = 16;
//    PatchROIs.clear();
//    QList<QGraphicsItem *>  graphicItems = scene->items();
//    foreach(QGraphicsItem *graphicItem,graphicItems){
//        if(graphicItem->type()== RectangleFeatureItemType)
//            {
//            graphicItem->hide();
//                scene->removeItem(graphicItem);
//            }
//    }

//    float width = 1280 / gridsX;
//    float height = 720 / gridsY;

//    for(int gridY = 0; gridY < 720; gridY+=height)
//    {
//        for(int gridX = 0; gridX < 1280; gridX+=width)
//        {
//            RoiRectangle roiRect;
//            roiRect.P1 = QPointF(gridX,gridY);
//            roiRect.P2 = QPointF(gridX+width,gridY+height);
//            PatchROIs.append(roiRect);

////            rectangleItem *rectRoi = new rectangleItem();
////            rectRoi->P1 = QPointF(gridX,gridY);
////            rectRoi->P2 = QPointF(gridX+width,gridY+height);

////            rectRoi->show();
////            rectRoi->setVisible(true);
////            scene->addItem(rectRoi);
//        }
//    }

//    DrawGrid(scene);
//}
