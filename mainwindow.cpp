#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

//    rect = new rectangleItem();
//    rect->P1 = QPointF(-100,-100);
//    rect->P2 = QPointF(100,100);
//    scene->addItem(rect);
    grid = new gridItem();
    grid->setGrid(scene, 1280, 720, 2, 2);
//    scene->addItem(grid);

}

MainWindow::~MainWindow()
{
    delete ui;
}

