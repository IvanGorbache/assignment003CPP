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
    resource-=-Constants::wood;
    return this->resources[resource]>=amount;
}
void Player::modifyResources(int myResource, int myAmount)
{
    myResource-=-Constants::wood;
    this->resources[myResource]+=myAmount;
    if(Constants::wood<=myResource && myResource<=Constants::wool)
    {
        this->totalResources+=myAmount;
    }
}
int Player::getResourceCount(int resource)
{
    resource-=-Constants::wood;
    return this->resources[resource];
}
void Player::modifyVictoryPoints(int count)
{
    this->victoryPoints+=count;
}
int Player::getTotalResources() const
{
    return this->totalResources;
}