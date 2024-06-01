#include "player.hpp"
#include "board.hpp"
#include "constants.hpp"
#include "point.hpp"
#include "intersection.hpp"
#include "land.hpp"
#include "developmentCard.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>


class Catan
{
private:
    Player players[3];
    bool firstTurn[3];
    Board gameboard;
    int currentTurn;
public:
    Catan(Player p1, Player p2, Player p3);

    ~Catan();

    void rollDice();

    void placeSettelemnt(Point a);

    void placeRoad(Point a, Point b);


    void trade(Player player, Constants::resource myResource, Constants::resource otherResource, int myAmount, int otherAmount);

    void buyDevelopmentCard();

    void getCurrentPlayerCards();

    void useDevelopmentCard();

    bool checkVictory();

    void endTurn();
};
