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
    float rectWidth = sceneWidth/columns;
    float rectHeight = sceneHeight/rows;

    for(int gridRows=0; gridRows<sceneHeight; gridRows+=rectHeight)
    {
        for(int gridsCols=0; gridsCols<sceneWidth; gridsCols+=rectWidth)
        {
            RoiRectangle roiRect;
            roiRect.P1 = QPointF(gridsCols,gridRows);
            roiRect.P2 = QPointF(gridsCols+rectWidth,gridRows+rectHeight);
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
    for(const RoiRectangle roiRect: qAsConst(PatchROIs))
    {
        rectangleItem *rectRoi = new rectangleItem();
        rectRoi->P1 = roiRect.P1;
        rectRoi->P2 = roiRect.P2;

        addToGroup(rectRoi);
//        rectRoi->show();
//        rectRoi->setVisible(true);
//        scene->addItem(rectRoi);

    }
}

