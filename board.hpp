#include "player.hpp"
#include "point.hpp"

class Board
{
private:
    /* data */
public:
    Board(/* args */);
    ~Board();
    Point getPointAt(unsigned int x, unsigned int y);
    void placeSettlement(Player owner, Point a);
};