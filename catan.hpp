#include "constants.hpp"
#include "player.hpp"
#include "point.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>


class Catan
{
private:
    Player players[3];
    bool firstTurn[3];
    std::vector<std::vector<Point>> map;
    int currentTurn;
    int knightsCount;
public:
    Catan(Player p1, Player p2, Player p3);

    ~Catan();

    void rollDice(int cheat = 0);

    void placeSettelemnt(Point a);

    void placeRoad(Point a, Point b);

    void trade(Player player, Constants::type myResource, Constants::type otherResource, int myAmount, int otherAmount);

    void buyDevelopmentCard();

    void getCurrentPlayerCards();

    void useDevelopmentCard();

    bool checkVictory();

    void endTurn();
};
