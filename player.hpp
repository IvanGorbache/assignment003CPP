#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "point.hpp"
#include "constants.hpp"

class Point;

class Player
{
private:
    int victoryPoints;
    std::string name;
    std::vector<Point> settlements;
    int resources[Constants::inventorySize];
    int totalResources;
public:
    Player(std::string name);
    ~Player();

    int getTotalResources() const;
    int getVictoryPoints() const;
    std::vector<Point> getSettlements() const;
    bool canTrade(int resourceType, int amount);
    void modifyResources(int myResource, int myAmount);
    int getResourceCount(int resourceType);
    void modifyVictoryPoints(int count);
    void addSettlements(Point settlements);
    std::string getName() const;

    void printer();
};
