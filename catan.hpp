#pragma once

#include "player.hpp"
#include "point.hpp"
#include "road.hpp"
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
    int turnCounter[3];
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

    void buyDevelopmentCard(int choice = 0);

    void getCurrentPlayerCards();

    void useDevelopmentCard(int card=0,int resource=0,int x=0, int y=0,int u=0,int v=0);

    bool checkVictory();

    void endTurn();

    void printMap() const;

    Point GetPoint(int x,int y) const;

    Player* getPlayer(int index) const;
};
