#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
//#include "rectangleitem.h"
//#include "griditem.h"
#include "grid.h"

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

    void on_pushButton_setGroup_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
//    gridItem *grid;
    grid *myGrid;

    bool groupSelect = false;
    bool groupSelected = false;

};
#endif // MAINWINDOW_H
