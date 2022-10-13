#include "griditem.h"

gridItem::gridItem(QGraphicsItem *parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);

    mouseHover = false;
    P1 = QPointF(50,50);
    P2 = QPointF(150,150);
    setPos(QPointF(0, 0));
}

QRectF gridItem::boundingRect() const
{
    return QRectF(1280,720,10,10);
//    return QRectF(QPointF(P1.x()-10,P1.y()-10),QPointF(P2.x()+10,P2.y()+10)); //rectangleitem
}

void gridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    pTopLeft = P1;
    pBottomRight = P2;
    pBottomLeft = P3;
    pTopRight = P4;

    QBrush brush = painter->brush();
    brush.setStyle(Qt::SolidPattern);

    if(mouseHover == true){
        brush.setColor(Qt::red);
        painter->setBrush(brush);
    }
    else
    {
        brush.setColor(Qt::blue);
        painter->setBrush(brush);
    }

    painter->drawEllipse(pTopLeft,7,7);
    painter->drawEllipse(pBottomLeft,7,7);
    painter->drawEllipse(pTopRight,7,7);
    painter->drawEllipse(pBottomRight,7,7);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::green);
    painter->setPen(pen);

    painter->drawLine(pTopLeft,pBottomLeft);
    painter->drawLine(pTopLeft,pTopRight);
    painter->drawLine(pBottomLeft,pBottomRight);
    painter->drawLine(pTopRight,pBottomRight);
}

void gridItem::setGrid(int sceneWidth, int sceneHeight, int rows, int columns)
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
            roiRect.P3 = QPointF(gridsCols, gridRows+rectHeight);
            roiRect.P4 = QPointF(gridsCols+rectWidth, gridRows);
            PatchROIs.append(roiRect);

//            rectangleItem *rectRoi;
//            rectRoi = new rectangleItem();
//            rectRoi->P1 = QPointF(gridsCols, gridRows);
//            rectRoi->P2 = QPointF(gridsCols+rectWidth, gridRows+rectHeight);
//            scene->addItem(rectRoi);
        }
    }
}

void gridItem::paintRect()
{

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
        P1 = roiRect.P1;
        P2 = roiRect.P2;
        P3 = roiRect.P3;
        P4 = roiRect.P4;

//        addToGroup(rectRoi);
        scene->addItem(setGrid(1280,720,1,1));

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

//void gridItem::slotPointChanged(QPointF point)
//{
//    bool pointChanged = false;
//    //update patchroi
////    if(PatchROIs.contains(moveStartP)){
//        for(int i=0; i<PatchROIs.size(); i++){
//            if((moveStartP.x()>(PatchROIs[i].P1.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P1.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P1.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P1.y()+7))     )
////            if((PatchROIs[i].P1 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P1 < (moveStartP+QPointF(7,7))))
//            {
//                PatchROIs[i].P1 = point;
//                pointChanged = true;
//            }
//            if((moveStartP.x()>(PatchROIs[i].P2.x()-7)) &&
//               (moveStartP.x()<(PatchROIs[i].P2.x()+7)) &&
//               (moveStartP.y()>(PatchROIs[i].P2.y()-7)) &&
//               (moveStartP.y()<(PatchROIs[i].P2.y()+7))     )
////            if((PatchROIs[i].P2 > (moveStartP-QPointF(7,7))) && (PatchROIs[i].P2 < (moveStartP+QPointF(7,7))))
//            {
//                PatchROIs[i].P2 = point;
//                pointChanged = true;
//            }

//        }
//        if(pointChanged)
//            moveStartP = point;
////    }
//    //draw grid based off patchroi
//    if(pointChanged == true)
//        emit signalChangeGrid();
//}

//void gridItem::slotMoveStartPoint(QPointF point)
//{
//    moveStartP = point;
//}

//void rectangleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "MP event->button() : " << event->button();

//    if(event->button()==Qt::LeftButton)
//    {
//        if((event->pos().x()>pTopLeft.x()-7) &&
//                (event->pos().x()<pTopLeft.x()+7) &&
//                (event->pos().y()>pTopLeft.y()-7) &&
//                (event->pos().y()<pTopLeft.y()+7))
//            moveTL = true;

//        if((event->pos().x()>pBottomRight.x()-7) &&
//                (event->pos().x()<pBottomRight.x()+7) &&
//                (event->pos().y()>pBottomRight.y()-7) &&
//                (event->pos().y()<pBottomRight.y()+7))
//            moveBR = true;
//        if((event->pos().x()>pTopRight.x()-7) &&
//                (event->pos().x()<pTopRight.x()+7) &&
//                (event->pos().y()>pTopRight.y()-7) &&
//                (event->pos().y()<pTopRight.y()+7))
//            moveTR = true;

//        if((event->pos().x()>pBottomLeft.x()-7) &&
//                (event->pos().x()<pBottomLeft.x()+7) &&
//                (event->pos().y()>pBottomLeft.y()-7) &&
//                (event->pos().y()<pBottomLeft.y()+7))
//            moveBL = true;

//        moveStartPoint = event->pos();
//    }
//    if(moveTL || moveBL || moveBR || moveTR)
//        emit signalPointToChange(moveStartPoint);

//    update();
//    QGraphicsItem::mousePressEvent(event);
//}

//void rectangleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << "MR event->button() : " << event->button();

//    moveTL = false;
//    moveBR = false;
//    moveTR = false;
//    moveBL = false;

//    prepareGeometryChange();
//    update();

//    QGraphicsItem::mouseReleaseEvent(event);
//}

//void rectangleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug() << event->pos();

//    if(moveTL==true)
//        P1 = event->pos();
//    else if (moveBR==true)
//         P2 = event->pos();
//    else if (moveTR==true) {
//        P1.setY(event->pos().y());
//        P2.setX(event->pos().x());
//    }
//    else if (moveBL==true) {
//        P1.setX(event->pos().x());
//        P2.setY(event->pos().y());
//    }
//    else
//    {
//        P1 += event->pos() - moveStartPoint;
//        P2 += event->pos() - moveStartPoint;
//    }

//    if(moveTL || moveBL || moveBR || moveTR)
//        emit signalPointChanged(event->pos());
//    moveStartPoint = event->pos();
//    prepareGeometryChange();
//    update();
//}

//void rectangleItem::hoverEnterEvent(QGraphicsSceneHoverEvent*event)
//{
//    setZValue(100);
//    mouseHover = true;
//    update();
//}

//void rectangleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*event)
//{
//    setZValue(10);
//    mouseHover = false;
//    update();
//}
