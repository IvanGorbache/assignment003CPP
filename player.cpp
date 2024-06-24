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
void Player::addSettlements(Point settlement) 
{
    this->settlements.push_back(settlement);
}
bool Player::canTrade(int resourceType, int amount)
{
    resourceType-=Constants::wood;
    return this->resources[resourceType]>=amount;
}
void Player::modifyResources(int myResource, int myAmount)
{
    myResource-=Constants::wood;
    this->resources[myResource]+=myAmount;
    if(Constants::wood<=myResource && myResource<=Constants::wool)
    {
        this->totalResources+=myAmount;
    }
}
int Player::getResourceCount(int resourceType)
{
    resourceType-=Constants::wood;
    return this->resources[resourceType];
}
void Player::modifyVictoryPoints(int count)
{
    this->victoryPoints+=count;
}
int Player::getTotalResources() const
{
    return this->totalResources;
}
std::string Player::getName() const
{
    return this->name;
}
void Player::printer()
{
    std::cout<<this->name<<std::endl;

    for (int i = 0; i < Constants::inventorySize; i++)
    {
        std::cout<<Constants::resource[i]<<this->resources[i]<<" ";
    }
    std::cout<<"\n";
    
}