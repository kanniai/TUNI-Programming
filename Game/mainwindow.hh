#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "../Course/CourseLib/graphics/simpleactoritem.hh"
#include "actoritem.hh"
#include "animation.hh"
#include "bullet.hh"

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
#include <map>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

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
    // type 4 = bullet
    virtual void addActor(int locX, int locY, int type = 0, std::shared_ptr<Interface::IActor> actor = nullptr);

    void updateCoords(int nX, int nY);
    void updateActorCoords(int nX, int nY, std::shared_ptr<Interface::IActor>  actor, int type);
    void showTime();
    void setPicture(QImage &img);
    void setTime(int hours, int minutes);

    void nysseCount(int count, int delta);

    std::pair<std::shared_ptr<Interface::IActor>, ActorItem*> getPlayer1() const;



signals:
    void gameStarted();
    void buttonPressed(char button);

public slots:
    void checkBulletCollision(int animationXCoord_, int animationYCoord_,
                              int playerXCoord, int playerYCoord);
    void bulletMoved(int x2, int y2);

private slots:
    void on_startButton_clicked();
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void spacePressed();



private:
    void checkCollision(QGraphicsItem* actorItem);
    std::shared_ptr<Interface::IActor> getActor(ActorItem* actorItem);
    void removeBullet();

    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    //QVector<QGraphicsItem*> actors_;
    ActorItem* last_;
    ActorItem* bullet_;
    StudentSide::Bullet* bullet2_;

    std::map<std::shared_ptr<Interface::IActor>, ActorItem*> buses_;
    std::map<std::shared_ptr<Interface::IActor>, ActorItem*> passengers_;
    std::pair<std::shared_ptr<Interface::IActor>, ActorItem*> player1_;

    StudentSide::Animation* animation_;

    int hours_;
    int minutes_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms
};

} //namespace

#endif // MAINWINDOW_HH
