#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include "actoritem.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QKeyEvent>

#include <QString>

namespace Ui {
class MainWindow;
}

namespace StudentSide {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void setSize(int w, int h);
    void setTick(int t);

    // type 0 = stop
    // type 1 = nysse
    // type 2 = passenger
    // type 3 = player
    virtual void addActor(int locX, int locY, int type = 0);

    void updateCoords(int nX, int nY);
    void showTime();
    void setPicture(QImage &img);
    void setTime(int hours, int minutes);

signals:
    void gameStarted();
    void buttonPressed(char button);

public slots:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_startButton_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<QGraphicsItem*> actors_;
    ActorItem* last_;

    int hours_;
    int minutes_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

} //namespace

#endif // MAINWINDOW_HH
