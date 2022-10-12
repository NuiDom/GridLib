#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

//    rect1 = new rectangleItem();
//    rect1->P1 = QPointF(0,0);
//    rect1->P2 = QPointF(200,200);
//    scene->addItem(rect1);

//    rect2 = new rectangleItem();
//    rect2->P1 = QPointF(-200,-200);
//    rect2->P2 = QPointF(0,0);
//    scene->addItem(rect2);
    rect3 = new rectangleItem();

    grid = new gridItem();
    grid->setGrid(scene, 1280, 720, 4, 4);
    grid->DrawGrid(scene);
    connect(grid, SIGNAL(signalChangeGrid()), this, SLOT(slotChangeGrid()));
//    scene->addItem(grid);

//    this->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotChangeGrid()
{
    grid->DrawGrid(scene);
}

void MainWindow::on_pushButton_selectGroup_clicked()
{
//    groupSelect = true;
    // Clear the Scene
    QList<QGraphicsItem *>  graphicItems = scene->items();
    foreach(QGraphicsItem *graphicItem,graphicItems){
        if(graphicItem->type()== RectangleFeatureItemType)
            {
            graphicItem->hide();
                scene->removeItem(graphicItem);
            }
    }
//    grid->AddGrid();
    scene->addItem(grid);
}

//void MainWindow::mousePressEvent(QEvent *event)
//{
//    qDebug() << "event";
//}

//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//    if(event->type() == QEvent::MouseButtonPress){
//          if(groupSelect == true){
//              qDebug() << "group select";
//              if(point1 == QPointF(0,0))
//                  point1 = QPointF(this->pos().x(),this->pos().y());
//              else if((point1 != QPointF(0,0)) && (point2 == QPointF(0,0)))
//                  point2 = QPointF(this->pos().x(),this->pos().y());
//              else if((point1 != QPointF(0,0)) && (point2 != QPointF(0,0)))
//                  groupSelected = true;
//              else
//                  return false;
//          }
//          return true;
//        }
//        else
//            return false;
//}


void MainWindow::on_pushButton_setGroup_clicked()
{
//    if(groupSelected == true){
//        rect3->P1 = point1;
//        rect3->P2 = point2;
//        scene->addItem(rect3);
//    }
}

//QRect MainWindow::getItemROI()
//{
//    QRect rectROI;

//    rectROI.setLeft(this->pos().x()+point1.x());
//    rectROI.setTop(this->pos().y()+point1.y());
//    rectROI.setRight(this->pos().x()+point2.x());
//    rectROI.setBottom(this->pos().y()+point2.y());

//    return rectROI;
//}

