#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"

using namespace std;

TEST_CASE("Test placingTown")
{    
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = 0;i<Constants::inventorySize;i++)
    {
        p1.modifyResources(Constants::wood+i,100);
        p2.modifyResources(Constants::wood+i,100);
        p3.modifyResources(Constants::wood+i,100);
    }
    CHECK(c.GetPoint(1,2).getClassification()==Constants::empty);
    c.placeSettelemnt(Point(1,2));
    CHECK(c.GetPoint(1,2).getClassification()==Constants::settlement);
    CHECK(c.GetPoint(1,2).getOwner()==&p1);


    //placing a town too close
    c.placeRoad(Point(1,2),Point(2,2),true);
    c.placeSettelemnt(Point(2,2));
    CHECK(c.GetPoint(2,2).getClassification()==Constants::empty);

    c.endTurn();

    //placing a town in a space that is already in use
    c.placeSettelemnt(Point(1,2));
    CHECK(c.GetPoint(1,2).getOwner()==&p1);

    //placing a settlement for a later test
    c.placeSettelemnt(Point(5,0));

    c.endTurn();
    c.endTurn();

    //plaching a settlement with no roads connected to it
    c.placeSettelemnt(Point(5,8));
    CHECK(c.GetPoint(5,8).getClassification()==Constants::empty);

    //placing a road
    c.placeRoad(Point(2,2),Point(3,3),true);
    c.placeSettelemnt(Point(3,3));
    CHECK(c.GetPoint(3,3).getClassification()==Constants::settlement);
    CHECK(c.GetPoint(3,3).getOwner()==&p1);

    //placing a settlement connected only to a road that doesn't belong to you
    c.placeRoad(Point(2,2),Point(3,1),true); 
    c.endTurn();
    c.placeSettelemnt(Point(3,1));
    CHECK(c.GetPoint(3,1).getClassification()==Constants::empty);
    CHECK(c.GetPoint(3,1).getOwner()==nullptr);

    //testing builing on a regular turn
    c.placeRoad(Point(5,0),Point(4,1),true);
    c.placeRoad(Point(3,1),Point(4,1),true);
    c.placeSettelemnt(Point(3,1));
    CHECK(c.GetPoint(3,1).getClassification()==Constants::settlement);
    CHECK(c.GetPoint(3,1).getOwner()==&p2);

    c.endTurn();
    c.endTurn();

    c.placeSettelemnt(Point(3,1));
    CHECK(c.GetPoint(3,1).getClassification()==Constants::settlement);
    CHECK(c.GetPoint(3,1).getOwner()==&p2);
    c.endTurn();
    c.buildCity(Point(3,1));
    CHECK(c.GetPoint(3,1).getClassification()==Constants::city);

    c.printMap();
    c.rollDice(100);

    CHECK(c.getPlayer(0)->getVictoryPoints()==2);
    CHECK(c.getPlayer(1)->getVictoryPoints()==3);
    CHECK(c.getPlayer(2)->getVictoryPoints()==0);

}
TEST_CASE("Test trading")
{
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = 0;i<Constants::inventorySize;i++)
    {
        p1.modifyResources(Constants::wood+i,100);
        p2.modifyResources(Constants::wood+i,100);
        p3.modifyResources(Constants::wood+i,100);
    }
}
TEST_CASE("Test cards")
{
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = 0;i<Constants::inventorySize;i++)
    {
        p1.modifyResources(Constants::wood+i,100);
        p2.modifyResources(Constants::wood+i,100);
        p3.modifyResources(Constants::wood+i,100);
    }
}