#pragma once

#include "player.hpp"
#include "point.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <random>   
#include <ctime> 


class Catan
{
private:
    Player *players[3];
    int tutnCounter[3];
    int originalMap[12][11];
    Point map[12][11];
    int currentTurn;
    int knightsCount, victoryCardCount;
    int minCard,maxCard;

public:
    Catan(Player *p1, Player *p2, Player *p3, bool useDefault,int defaultRoll=5);

    ~Catan();

    void rollDice(int cheat = 0);

    void placeSettelemnt(Point a);

    void buildCity(Point a);

    void placeRoad(Point a, Point b, bool isFree);

    void trade(Player *player, int myResource, int otherResource, int myAmount, int otherAmount);

    void buyDevelopmentCard();

    void getCurrentPlayerCards();

    void useDevelopmentCard(int card);

    bool checkVictory();

    void endTurn();

    void printMap() const;
};
