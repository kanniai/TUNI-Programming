#include "player.hh"

namespace StudentSide
{

Player::Player()
{}

StudentSide::Player::~Player()
{}

void StudentSide::Player::move(Interface::Location loc)
{
    playerLocation_ = loc;
}

Interface::Location StudentSide::Player::giveLocation() const
{
    return playerLocation_;

}


}
