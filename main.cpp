#include "catan.cpp"

int main()
{
    Catan c = Catan(new Player("Doom"),new Player("Loom"),new Player("Boom"));
    c.printMap();
    return 0;
}