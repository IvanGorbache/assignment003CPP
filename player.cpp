#include "player.hpp"

Player::Player(std::string name)
{
    this->name = name;
}
Player::~Player()
{

}

int Player::getVictoryPoints() const
{
    return this->victoryPoints;
}
std::vector<Point> Player::getSettlements() const
{
    return this->settlements;
}
bool Player::canTrade(int resource, int amount)
{
    return this->resources[resource]>=amount;
}
void Player::modifyResources(int myResource, int myAmount)
{
    this->resources[myResource]+=myAmount;
}
int Player::getResourceCount(int resource)
{
    return this->resources[resource];
}