#pragma once

#include "player.hpp"
#include "point.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#include "constants.hpp"


class Catan
{
private:
    Player *players[3];
    bool firstTurn[3];
    Point map[12][11];
    int currentTurn;
    int knightsCount;
public:
    Catan(Player *p1, Player *p2, Player *p3);

    ~Catan();

    void rollDice(int cheat);

    void placeSettelemnt(Point a);

    void placeRoad(Point a, Point b, bool isFree);

    void trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount);

    void buyDevelopmentCard();

    void getCurrentPlayerCards();

    void useDevelopmentCard(int card);

    bool checkVictory();

    void endTurn();

    void printMap() const;
};
