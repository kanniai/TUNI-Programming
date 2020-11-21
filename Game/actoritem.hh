#ifndef ACTORITEM_HH
#define ACTORITEM_HH

#include "dialog.hh"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <iostream>


namespace StudentSide {

class ActorItem : public QGraphicsItem
{
public:
    ActorItem(int x, int y, int type = 0);
    virtual ~ActorItem();
    QRectF boundingRect() const;
    QRectF playerRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void selectVehicle(int num);

    void setCoord(int x, int y);

    const int WIDTH = 15;
    const int HEIGHT = 15;

private:
    int x_;
    int y_;
    int type_;
    bool helicopter_ = false;
    bool fighter_ = false;
    bool spaceShip_ = false;
    StudentSide::Dialog dialog_;

};

}
#endif // ACTORITEM_HH
