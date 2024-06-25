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
        p1.modifyResources(Constants::wood+i,10);
        p2.modifyResources(Constants::wood+i,10);
        p3.modifyResources(Constants::wood+i,10);
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


}