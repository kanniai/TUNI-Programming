#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "actoritem.hh"
#include "animation.hh"
#include "bullet.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>
#include <QString>
#include <map>


namespace Ui {
class MainWindow;
}

namespace StudentSide {

/**
 * @brief The MainWindow class displays the game window and displays
 * statistics and game time. Also tracks the movement of player and bullets
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    /**
     * @brief addActor adds new actor to the game
     * @param locX
     * @param locY
     * @param type of actor (Nysse, player, passenger)
     * @param actor
     */
    virtual void addActor(int locX, int locY, int type = 0,
                          std::shared_ptr<Interface::IActor> actor = nullptr);

    /**
     * @brief setSize
     * @param w: width of the game window
     * @param h: height of the game window
     */
    void setSize(int w, int h);

    /**
     * @brief setTick sets the frequency of timer
     * @param t
     */
    void setTick(int t);

    /**
     * @brief addStop adds new bus stop to the game
     * @param locX
     * @param locY
     * @param type
     * @param stop
     */
    void addStop(int locX, int locY, int type = 0,
                 std::shared_ptr<Interface::IStop> stop = nullptr);

    /**
     * @brief updatePlayerCoords updates the player coordinate
     * @param nX: new x-coordinate
     * @param nY: new y-coordinate
     */
    void updatePlayerCoords(int nX, int nY);

    /**
     * @brief updateActorCoords updates the coordinates of ingame actor
     * @param nX: new x-coordinate
     * @param nY: new y-coordinate
     * @param actor
     * @param type (nysse, passenger)
     */
    void updateActorCoords(int nX, int nY, std::shared_ptr<Interface::IActor>  actor, int type);

    /**
     * @brief showTime displays time on widget
     */
    void showTime();

    /**
     * @brief setPicture sets the game background
     * @param img of the background
     */
    void setPicture(QImage &img);

    /**
     * @brief setTime sets the game time in order
     * @param hours
     * @param minutes
     */
    void setTime(int hours, int minutes);

    /**
     * @brief nysseCount displays the count of buses in traffic
     * @param count: total count of the buses in traffic
     * @param delta: change of buses compared to previous interval
     */
    void nysseCount(int count, int delta);

    /**
     * @brief updateStatistics updates destroyed buses and killed passengers
     * @param buses
     * @param passengers
     */
    void updateStatistics(int buses, int passengers);



signals:
    void gameStarted();
    void buttonPressed(char button);
    void gameOverSignal();
    void nysseDestroyedSignal();

public slots:
    void checkBulletCollision(int animationXCoord_, int animationYCoord_,
                              int playerXCoord, int playerYCoord);
    void bulletMoved(int x2, int y2);

private slots:
    // Slots of different actions
    void on_startButton_clicked();
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void spacePressed();



private:

    /**
     * @brief checkCollision checks if bullet hits the actor
     * @param actorItem
     */
    void checkCollision(QGraphicsItem* actorItem);

    /**
     * @brief removeBullet removes the bullet when it hits actor or passes the
     * boundaries
     */
    void removeBullet();

    void endGame();
    void updateTime();
    bool isGameOver();


    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    ActorItem* bullet_;
    StudentSide::Bullet* bullet2_;

    // Data structures of different actors
    std::map<std::shared_ptr<CourseSide::Stop>, ActorItem*> stops_;
    std::map<std::shared_ptr<CourseSide::Nysse>, ActorItem*> buses_;
    std::map<std::shared_ptr<CourseSide::Passenger>, ActorItem*> passengers_;
    std::pair<std::shared_ptr<Interface::IActor>, ActorItem*> player1_;

    StudentSide::Animation* animation_;


    // Time used in complete the game
    int seconds_ = 0;

    // Time according to logic
    int hours_;
    int minutes_;

    int nyssesDestroyed_ = 0;
    int passengersKilled_ = 0;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms

    bool gameOver_ = false;
};

}

#endif // MAINWINDOW_HH
