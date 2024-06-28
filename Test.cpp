#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"

using namespace std;

TEST_CASE("Test placingTown")
{    
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = Constants::wood;i<=Constants::wool;i++)
    {
        p1.modifyResources(i,100);
        p2.modifyResources(i,100);
        p3.modifyResources(i,100);
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

    //for future check
    c.placeSettelemnt(Point(8,3));

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

    //checking if the resources were used for the building
    CHECK(c.getPlayer(0)->getVictoryPoints()==2);
    CHECK(c.getPlayer(1)->getVictoryPoints()==3);
    //CHECK(c.getPlayer(2)->getVictoryPoints()==0);


    //placing settlement 1 road away from enemy
    c.placeRoad(Point(4,1),Point(5,2),true);
    c.placeRoad(Point(5,2),Point(6,2),true);
    c.placeRoad(Point(7,3),Point(6,2),true);
    c.placeRoad(Point(8,3),Point(7,3),true);


    c.placeSettelemnt(Point(5,2));
    c.placeSettelemnt(Point(7,3));

    //checking placing settlement close to enemy
    CHECK(c.GetPoint(7,3).getClassification()==Constants::settlement);
    CHECK(c.GetPoint(7,3).getOwner()==&p2);

    //checking placing settlement close to ally
    c.placeSettelemnt(Point(6,2));
    CHECK(c.GetPoint(6,2).getClassification()==Constants::empty);
    CHECK(c.GetPoint(6,2).getOwner()==nullptr);


    c.printMap();
    c.rollDice(100);



}
TEST_CASE("Test trading")
{
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = Constants::wood;i<=Constants::wool;i++)
    {
        p1.modifyResources(i,100);
        p2.modifyResources(i,100);
        p3.modifyResources(i,100);
    }

    //illegal trades
    c.trade(&p2,Constants::wood,Constants::wood,1000,100);
    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==100);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==100);

    c.trade(&p2,Constants::wood,Constants::wood,100,1000);
    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==100);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==100);

    c.trade(&p2,Constants::wood,Constants::wood,1000,1000);
    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==100);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==100);

    //trading victory
    c.buyDevelopmentCard(Constants::victoryCard);
    c.trade(&p2,Constants::victoryCard,Constants::wood,1,0);
    CHECK(c.getPlayer(0)->getVictoryPoints()==0);
    CHECK(c.getPlayer(1)->getVictoryPoints()==1);

    std::cout<<"------------------";
    //trading knight
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::knight);

    c.trade(&p2,Constants::knight,Constants::wood,2,0);
    CHECK(c.getPlayer(0)->getVictoryPoints()==0);
    CHECK(c.getPlayer(1)->getVictoryPoints()==1);

    CHECK(c.getPlayer(1)->getResourceCount(Constants::knight)==2);
    c.trade(&p2,Constants::knight,Constants::wood,1,0);
    CHECK(c.getPlayer(0)->getVictoryPoints()==0);
    CHECK(c.getPlayer(1)->getVictoryPoints()==3);

    //regular trade
    c.trade(&p2,Constants::wood,Constants::brick,50,50);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==150);
    CHECK(c.getPlayer(0)->getResourceCount(Constants::brick)==150);
    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==50);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::brick)==50);

    
    c.rollDice(100);

}
TEST_CASE("Test cards")
{
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);
    for(int i = Constants::wood;i<=Constants::wool;i++)
    {
        p1.modifyResources(i,100);
        p2.modifyResources(i,100);
        p3.modifyResources(i,100);
    }
    c.rollDice(100);
    //using cards that you don't have
    c.useDevelopmentCard(Constants::monopoly,Constants::wood);

    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==100);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==100);
    CHECK(c.getPlayer(2)->getResourceCount(Constants::wood)==100);

    c.useDevelopmentCard(Constants::pleanty,Constants::wood);

    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==100);

    c.buyDevelopmentCard(Constants::monopoly);
    c.buyDevelopmentCard(Constants::pleanty);
    c.buyDevelopmentCard(Constants::builder);
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::victoryCard);
    c.placeSettelemnt(Point(1,8));

    //regular development card use


    c.useDevelopmentCard(Constants::monopoly,Constants::wood);

    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==200);
    CHECK(c.getPlayer(1)->getResourceCount(Constants::wood)==50);
    CHECK(c.getPlayer(2)->getResourceCount(Constants::wood)==50);

    c.useDevelopmentCard(Constants::pleanty,Constants::wood);

    CHECK(c.getPlayer(0)->getResourceCount(Constants::wood)==202);

    c.useDevelopmentCard(Constants::builder,0,1,8,2,8,2,8,3,9);

    CHECK(c.GetPoint(1,8).hasRoad(Point(2,8))==true);
    CHECK(c.GetPoint(2,8).hasRoad(Point(1,8))==true);
    
    CHECK(c.GetPoint(3,9).hasRoad(Point(2,8))==true);
    CHECK(c.GetPoint(2,8).hasRoad(Point(3,9))==true);

    //1 for settelement
    //1 for victory card
    //2 for 3 knights
    CHECK(c.getPlayer(0)->getVictoryPoints()==4);

    c.printMap();



}