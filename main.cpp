#include "catan.hpp"
#include "player.hpp"

int main()
{
    Player p1 = Player("Doom"), p2 = Player("Loom"), p3 = Player("Boom");
    Catan c = Catan(&p1,&p2,&p3,true);
    c.printMap();
    c.placeSettelemnt(Point(0,7));
    c.placeRoad(Point(1,6),Point(0,7),true);
    c.placeRoad(Point(1,8),Point(0,7),true);
    c.placeRoad(Point(1,8),Point(2,8),true);
    std::cout<<"//////////////\n";
    c.printMap();
    c.placeSettelemnt(Point(1,6));
    c.placeSettelemnt(Point(1,6));
    c.placeSettelemnt(Point(1,4));
    c.placeSettelemnt(Point(3,1));
    std::cout<<"//////////////\n";
    c.printMap();
    c.placeSettelemnt(Point(2,8));
    c.placeSettelemnt(Point(4,7));
    std::cout<<"//////////////\n";
    c.printMap();
    c.rollDice(5);
    std::cout<<"//////////////\n";
    c.endTurn();
    c.printMap();
    std::cout<<"//////////////\n";
    c.placeSettelemnt(Point(0,7));
    c.placeRoad(Point(1,6),Point(0,7),true);
    c.placeRoad(Point(1,8),Point(0,7),true);
    c.placeRoad(Point(1,8),Point(2,8),true);
    c.placeSettelemnt(Point(0,3));
    c.printMap();
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    c.rollDice(5);
    //c.rollDice(7);
    c.endTurn();
    c.endTurn();
    c.buyDevelopmentCard(Constants::victoryCard);
    c.buyDevelopmentCard(Constants::monopoly);
    c.buyDevelopmentCard(Constants::knight);
    c.buyDevelopmentCard(Constants::pleanty);
    c.buyDevelopmentCard(Constants::builder);
    c.trade(&p2,Constants::wood,Constants::iron,20,10);
    c.useDevelopmentCard(Constants::monopoly,Constants::iron);
    c.useDevelopmentCard(Constants::pleanty,Constants::wood);
    c.useDevelopmentCard(Constants::builder,0,1,4,2,4);
    std::cout<<"//////////////\n";
    p1.printer();
    p2.printer();
    c.printMap();
    std::cout<<"//////////////\n";
    p1.printer();
    p2.printer();
    std::cout<<"//////////////\n";
    c.trade(&p2,Constants::wood,Constants::iron,39,4);
    p1.printer();
    p2.printer();

    return 0;
}