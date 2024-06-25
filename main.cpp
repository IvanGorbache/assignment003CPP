#include "catan.hpp"
#include "player.hpp"

void demo()
{
    //Constucting the game
    Player p1 = Player("p1"), p2 = Player("p2"), p3 = Player("p3");
    Catan c = Catan(&p1,&p2,&p3,true);

    //Placing the first roads and towns
    std::cout<<"--------------------------------------"<<std::endl;
    c.printMap();

    c.placeSettelemnt(Point(0,3));
    c.placeRoad(Point(0,3),Point(1,4),true);
    c.placeRoad(Point(1,4),Point(2,4),true);
    c.placeSettelemnt(Point(2,4));
    c.endTurn();

    c.placeSettelemnt(Point(3,7));
    c.placeRoad(Point(3,7),Point(4,7),true);
    c.placeRoad(Point(4,7),Point(5,8),true);
    c.placeSettelemnt(Point(5,8));
    c.endTurn();

    c.placeSettelemnt(Point(5,2));
    c.placeRoad(Point(5,2),Point(6,2),true);
    c.placeRoad(Point(6,2),Point(7,1),true);
    c.placeSettelemnt(Point(7,1));
    c.endTurn();

    
    std::cout<<"---------------------------"<<std::endl;
    c.printMap();
    c.rollDice(5);

    //p1's turn: trades 1 brick for 1 wheat
    c.trade(&p3,Constants::brick,Constants::wheat,1,1);

    //buys victory card
    c.buyDevelopmentCard(Constants::victoryCard);

    //print to show that he lost resources to buy the card
    p1.printer();

    c.endTurn();

    //p2's turn: places two roads
    c.placeRoad(Point(5,8),Point(6,8),false);
    c.placeRoad(Point(7,7),Point(6,8),false);
    std::cout<<"---------------------------"<<std::endl;
    c.printMap();
    p2.printer();
    c.rollDice(5);
    c.endTurn();

    //p3's turn: places a road
    c.placeRoad(Point(6,2),Point(7,3),false);
    std::cout<<"---------------------------"<<std::endl;
    c.printMap();
    p3.printer();
    c.rollDice(5);

    
    c.endTurn();

    //p1's turn trades 1 wool for 3 wheat
    c.trade(&p3,Constants::wool,Constants::wheat,1,3);

    //Upgrades a settlement to a city
    c.buildCity(Point(0,3));
    std::cout<<"---------------------------"<<std::endl;
    c.printMap();
    c.rollDice(5);
    c.endTurn();

    //p2's turn: trades 2 bricks for 1 wheat and builds a settelement
    c.trade(&p3,Constants::brick,Constants::wheat,2,1);
    c.placeSettelemnt(Point(7,7));
    std::cout<<"---------------------------"<<std::endl;
    c.printMap();
    c.rollDice(5);
    c.endTurn();

    //p3's turn: trades 2 brick for 2 iron and buys a knight
    c.trade(&p1,Constants::brick,Constants::iron,2,2);
    c.buyDevelopmentCard(Constants::knight);
    c.rollDice(5);
}

int main()
{

    demo();

    return 0;
}