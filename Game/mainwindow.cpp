#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

const int MATCH_MOUSEPRESS_XCOORD = 20;
const int MATCH_MOUSEPRESS_YCOORD = 15;

const int MAP_LEFT_SIDE_XCOORD = 8;
const int MAP_UPPER_YCOORD = 8;
const int MAP_RIGHT_SIDE_XCOORD = 480;
const int MAP_LOWER_YCOORD = 480;

const int PADDING = 40;
const int NEXTROW = 30;
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 600;

const int DESTROYED_NYSSES_NEEDED_FOR_WIN = 20;

const int NYSSE = 1;
const int PASSENGER = 2;
const int HELICOPTER= 3;
const int FIGHTER = 4;
const int SPACESHIP = 5;
const int CANNON = 6;

const int CANNON_NUM = 4;

namespace StudentSide {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize(WINDOW_WIDTH + ui->startButton->width() + PADDING, WINDOW_HEIGHT+ PADDING);

    ui->startButton->move(width_ + PADDING , PADDING);
    ui->timeLabel->move(width_ + PADDING, 3*NEXTROW);
    ui->logicTime->move(width_ + 3*PADDING, 3*NEXTROW);
    ui->timeFrame->move(width_ + 2.75*PADDING, 3*NEXTROW);

    ui->busesLabel->move(width_ + PADDING, 5*NEXTROW);
    ui->busCount->move(width_ + 4*PADDING, 5*NEXTROW);
    ui->busesAdded->move(width_ + PADDING, 6*NEXTROW);
    ui->busesAdded->setText("");

    ui->statisticsLabel->move(width_ + 1.2*PADDING, 7.2*NEXTROW);
    ui->statisticsLabel->setStyleSheet("border-bottom-width: 1px; border-bottom-style: solid; border-radius: 0px");
    ui->destroyedTextLabel->move(width_ + PADDING, 8.5*NEXTROW);
    ui->destroyedLabel->move(width_ + 6*PADDING, 8.5*NEXTROW);
    ui->killedTextLabel->move(width_ + PADDING, 9.5*NEXTROW);
    ui->killedLabel->move(width_ + 6*PADDING, 9.5*NEXTROW);
    ui->statisticsFrame->move(width_ + 0.8*PADDING, 7*NEXTROW);

    ui->endGameLabel->move(width_ + 1.2*PADDING, 14*NEXTROW);
    ui->runningTimeLabel->move(width_ + 1.2*PADDING, 15*NEXTROW);

    ui->player1HealthLabel->setText(QString::number(player1Health_));

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    resize(minimumSizeHint());
    //ui->gameView->fitInView(0,0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);

    timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &StudentSide::MainWindow::updateTime);


    player1Bullet_ = new StudentSide::Bullet();
    cannonBullet_ = new StudentSide::Bullet();

    connect(player1Bullet_, &StudentSide::Bullet::bulletMoved, this,
            &StudentSide::MainWindow::player1BulletMoved);
    connect(cannonBullet_, &StudentSide::Bullet::bulletMoved, this,
            &StudentSide::MainWindow::cannonBulletMoved);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTickAndStartTimer(int t)
{
    tick_ = t;
    timer->start(tick_);
}

void MainWindow::addActor(int locX, int locY, int type, std::shared_ptr<Interface::IActor> actor)
{
    ActorItem* nActor = new ActorItem(locX, locY, type);
    if (type == NYSSE) {
        std::shared_ptr<CourseSide::Nysse> nysse =
                       std::dynamic_pointer_cast<CourseSide::Nysse> (actor);
        buses_.insert( {nysse, nActor} );

    } else if (type == PASSENGER) {
        std::shared_ptr<CourseSide::Passenger> passenger =
                       std::dynamic_pointer_cast<CourseSide::Passenger> (actor);
        passengers_.insert( {passenger, nActor} );
        return;

    } else if (type == HELICOPTER) {
        player1_.first = actor;
        player1_.second = nActor;
        player1_.second->setTransformOriginPoint(WIDTH/2, WIDTH/2);
        player1Bullet_->setBulletSpeed(HELICOPTER);
    } else if (type == FIGHTER) {
        player1_.first = actor;
        player1_.second = nActor;
        player1_.second->setTransformOriginPoint(WIDTH/2, WIDTH/2);
        player1Bullet_->setBulletSpeed(FIGHTER);
    } else if (type == SPACESHIP) {
        player1_.first = actor;
        player1_.second = nActor;
        player1_.second->setTransformOriginPoint(WIDTH/2, WIDTH/2);
        player1Bullet_->setBulletSpeed(SPACESHIP);

    } else if (type == CANNON)
        player2_.first = actor;
        player2_.second = nActor;
        player2_.second->setTransformOriginPoint(WIDTH/2, WIDTH/2);
        cannonBullet_->setBulletSpeed(CANNON);

    map->addItem(nActor);
}

void MainWindow::addStop(int locX, int locY, int type, std::shared_ptr<Interface::IStop> stop)
{
    std::shared_ptr<CourseSide::Stop> stop2 =
                   std::dynamic_pointer_cast<CourseSide::Stop> (stop);
    ActorItem* nActor = new ActorItem(locX, locY, type);
    map->addItem(nActor);
    stops_.insert({stop2, nActor});
}

void MainWindow::updatePlayerCoords(int nX, int nY)
{
    player1_.second->setCoord(nX, nY);
}

void MainWindow::updateActorCoords(int nX, int nY, std::shared_ptr<Interface::IActor> actor,
                                   int type)
{
    if (type == 1) {
        std::map<std::shared_ptr<CourseSide::Nysse>,ActorItem*>::iterator it;
        std::shared_ptr<CourseSide::Nysse> nysse =
                       std::dynamic_pointer_cast<CourseSide::Nysse> (actor);
        it = buses_.find(nysse);
        if (it != buses_.end())
          it->second->setCoord(nX, nY);

    }
    updateStatistics(nyssesDestroyed_, passengersKilled_);
}

void StudentSide::MainWindow::MainWindow::showTime()
{
    QString minutes = QString::number(minutes_);
    QString hours = QString::number(hours_);

    if (minutes_ < 10) {
        minutes = "0" + minutes;
    }
    if (hours_ < 10) {
        hours = "0" + hours;
    }

    ui->logicTime->setText(hours + " : " + minutes);
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void MainWindow::setTime(int hours, int minutes)
{
    hours_ = hours;
    minutes_ = minutes;
}

void MainWindow::nysseCount(int count, int delta, std::string type)
{
    ui->busCount->setText(QString::number(count));
    if (type == "destroyed" && delta == 1) {
        return;
    }

    if (delta == 1) {
        ui->busesAdded->setText(QString::number(delta)+ " new bus journey");
    } else if (delta == -1) {
        ui->busesAdded->setText(QString::number(abs(delta))+ " bus arrived to final stop");
    } else if (delta > 1) {
        ui->busesAdded->setText(QString::number(delta)+ " new buses started the journey");
    } else if (delta < -1) {
        ui->busesAdded->setText(QString::number(abs(delta)) + " buses arrived to final stop");
    } else if (delta == 0) {
        ui->busesAdded->setText(" ");
    }
}

void MainWindow::updateStatistics(int buses, int passengers)
{
    ui->destroyedLabel->setText(QString::number(buses));
    ui->killedLabel->setText(QString::number(passengers));
}

void MainWindow::player1BulletMoved(int x2, int y2)
{

    player1Bullet_->setPos(x2, y2);
    checkCollision(player1Bullet_);
    checkBulletLocation(player1Bullet_);
}

void MainWindow::cannonBulletMoved(int x2, int y2)
{
    cannonBullet_->setPos(x2, y2);
    checkCollision(cannonBullet_);
    checkBulletLocation(cannonBullet_);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (isGameOver()) {
        return;
    }

    if(event->key() == Qt::Key_W) {
        emit buttonPressed('w');
        player1_.second->setRotation(-90);

    } else if (event->key() == Qt::Key_D) {
        emit buttonPressed('d');
        player1_.second->setRotation(0);

    } else if (event->key() == Qt::Key_S) {
        emit buttonPressed('s');
        player1_.second->setRotation(90);
    } else if (event->key() == Qt::Key_A) {
        emit buttonPressed('a');
        player1_.second->setRotation(180);

    } else if (event->key() == Qt::Key_Space) {
        qDebug() << "space pressed";
        spacePressed();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (cannonBullet_->isBulletMoving() == true) {
        return;
    }

    int x2 = event->x() - MATCH_MOUSEPRESS_XCOORD;
    int y2 = event->y() - MATCH_MOUSEPRESS_YCOORD;

    int x = player2_.first->giveLocation().giveX();
    int y = player2_.first->giveLocation().giveY();

    double dx = x2 - x;
    double dy = y2 - y;

    double angleInDegrees = -atan2(dx, dy) * (180/M_PI) + 90;
    player2_.second->setRotation(angleInDegrees);
    map->addItem(cannonBullet_);
    cannonBullet_->setPos(x, y);
    cannonBullet_->shoot(x, y, angleInDegrees);

}

void MainWindow::spacePressed()
{

    if (player1Bullet_->isBulletMoving() == true) {
        return;
    }
    map->addItem(player1Bullet_);
    player1Bullet_->setPos(player1_.first->giveLocation().giveX(),
                     player1_.first->giveLocation().giveY());
    player1Bullet_->shoot(player1_.first->giveLocation().giveX(),
                                      player1_.first->giveLocation().giveY(),
                                player1_.second->rotation());
}

void MainWindow::checkCollision(StudentSide::Bullet* bullet)
{
    if (bullet == cannonBullet_) {
        QList<QGraphicsItem *> collidingActors = bullet->collidingItems();

        for (QGraphicsItem* actor: collidingActors) {
            if (actor == player1_.second) {
                player1Health_--;
                updatePlayer1HealthLabel();
                bullet->stopTimer();
                map->removeItem(bullet);

                if (player1Health_ == 0) {
                    map->removeItem(player1_.second);
                    endGame("Player 2");
                }
                break;
            }
        }
    } else if (bullet == player1Bullet_) {
        QList<QGraphicsItem *> collidingActors = bullet->collidingItems();
        if (collidingActors.size() != 0) {
            for (QGraphicsItem* actor: collidingActors) {

                for(auto nysse: buses_) {
                    if (nysse.second->x() == actor->x() && nysse.second->y() == actor->y()) {

                        map->removeItem(nysse.second);
                        bullet->stopTimer();
                        map->removeItem(bullet);
                        nysse.first->remove();
                        //buses_.erase(nysse.first);

                        nyssesDestroyed_++;
                        emit nysseDestroyedSignal();

                        std::vector<std::shared_ptr<Interface::IPassenger>>
                                passengersInNysse =nysse.first->getPassengers();
                        for (auto passenger: passengersInNysse) {
                            passenger->remove();
                            passengersKilled_++;
                        }

                        if (nyssesDestroyed_ >= DESTROYED_NYSSES_NEEDED_FOR_WIN) {
                            updateStatistics(nyssesDestroyed_, passengersKilled_);
                            endGame("Player 1");
                        }
                        break;
                    }
                }
                for(auto stop: stops_) {
                    if (stop.second->x() == actor->x() && stop.second->y() == actor->y()) {
                        bullet->stopTimer();
                        map->removeItem(player1Bullet_);
                        break;
                    }
                }
            }
        }
    }
}

void MainWindow::removeBullet()
{
    map->removeItem(bullet_);
}

void MainWindow::checkBulletLocation(StudentSide::Bullet* bullet)
{
    if (bullet->x() < MAP_LEFT_SIDE_XCOORD -20
            || bullet->y() < MAP_UPPER_YCOORD -20
            || bullet->x() > MAP_RIGHT_SIDE_XCOORD + 20
            || bullet->y() > MAP_LOWER_YCOORD + 20) {

        bullet->stopTimer();
        map->removeItem(bullet);
    }
}

void MainWindow::endGame(QString player)
{
    gameOver_ = true;

    ui->endGameLabel->setText(player + " won the game!");

    //for ()
    if (runningMinutes_ == 0) {
        ui->runningTimeLabel->setText("Time spent: " +
                                      QString::number(runningSeconds_) + " seconds.");
    } else {
        ui->runningTimeLabel->setText(" Time spent: " +
                                      QString::number(runningMinutes_) +
                                      " minutes and " +
                                    QString::number(runningSeconds_) + " seconds.");
    }
    emit gameOverSignal();
}

void MainWindow::updateTime()
{
    if (runningSeconds_ >= 60) {
        runningMinutes_++;
        runningSeconds_ = 0;
    }
    runningSeconds_++;
}

void MainWindow::updatePlayer1HealthLabel()
{
    ui->player1HealthLabel->setText(QString::number(player1Health_));
}

bool MainWindow::isGameOver()
{
    return gameOver_;
}

void StudentSide::MainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    emit gameStarted();
}
}
