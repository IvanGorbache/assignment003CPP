#include "constants.hpp"
#include "player.hpp"
#include "point.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

class Catan
{
private:
    Player players[3];
    bool firstTurn[3];
    Point map[12][11];
    int currentTurn, knightsCount, victoryCardCount;
public:
    Catan(Player p1, Player p2, Player p3);

    ~Catan();

    void rollDice(int cheat = 0);

    void placeSettelemnt(Point a);

    void placeRoad(Point a, Point b);

    void trade(Player player, int myResource, int otherResource, int myAmount, int otherAmount);

    void buyDevelopmentCard();

    void getCurrentPlayerCards();

    void useDevelopmentCard(int card);

    bool checkVictory();

    void endTurn();

    void modifyResources(Player p, int myResource, int myAmount);

    void printMap() const;
};
