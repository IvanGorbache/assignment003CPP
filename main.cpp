#include "catan.hpp"
#include "player.hpp"

int main()
{
    Catan c = Catan(new Player("Doom"),new Player("Loom"),new Player("Boom"));
    c.printMap();
    return 0;
}