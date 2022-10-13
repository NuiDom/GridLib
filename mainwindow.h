#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
//#include "rectangleitem.h"
#include "griditem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_selectGroup_clicked();
//    bool eventFilter(QObject *obj, QEvent *event);
//    void mousePressEvent(QEvent *event) override;

    void on_pushButton_setGroup_clicked();
//    QRect getItemROI();
    void slotChangeGrid();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
//    rectangleItem *rect1;
//    rectangleItem *rect2;
    gridItem *grid;
//    rectangleItem *rect3;

    bool groupSelect = false;
    bool groupSelected = false;

    QPointF point1 = QPointF(0,0);
    QPointF point2 = QPointF(0,0);
};
#endif // MAINWINDOW_H
