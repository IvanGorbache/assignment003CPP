#include "catan.hpp"
#include "player.hpp"

int main()
{
    Catan c = Catan(new Player("Doom"),new Player("Loom"),new Player("Boom"));
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
    c.rollDice();
    std::cout<<"//////////////\n";
    return 0;
}