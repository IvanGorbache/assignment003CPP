#include "player.hpp"

Player::Player(std::string name) : victoryPoints(0), name(name), totalResources(0)
{
    std::fill(std::begin(resources), std::end(resources), 0);
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
    resourceType -= Constants::wood;
    return this->resources[resourceType] >= amount;
}

void Player::modifyResources(int myResource, int myAmount)
{

    if (Constants::wood <= myResource && myResource <= Constants::victoryCard)
    {
        myResource -= Constants::wood;
        this->totalResources += myAmount;
        this->resources[myResource] += myAmount;
    }
}

int Player::getResourceCount(int resourceType)
{
    resourceType -= Constants::wood;
    return this->resources[resourceType];
}

void Player::modifyVictoryPoints(int count)
{
    this->victoryPoints += count;
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
    std::cout << this->name << std::endl;

    for (int i = 0; i < Constants::inventorySize; i++)
    {
        std::cout << Constants::gameResourceIcons[i+Constants::wood] << ":" << this->resources[i] << " ";
    }
    std::cout << this->victoryPoints<<" \n";
}
