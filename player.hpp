#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "point.hpp"
#include "constants.hpp"

class Player
{
private:
    int victoryPoints;
    std::string name;
    std::vector<Point> settlements;
    int resources[Constants::pleanty+1];
public:
    Player(std::string name);
    ~Player();

    int getVictoryPoints() const;
    std::vector<Point> getSettlements() const;
    bool canTrade(int resource, int amount);
    void modifyResources(int myResource, int myAmount);
    int getResourceCount(int resource);
};