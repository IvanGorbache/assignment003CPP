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
    std::cout<<"//////////////\n";
    c.printMap();
    c.placeSettelemnt(Point(2,8));
    std::cout<<"//////////////\n";
    c.printMap();
    c.rollDice(5);
    std::cout<<"//////////////\n";
    return 0;
}