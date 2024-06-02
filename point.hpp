#include <vector>
#include "player.hpp"
#include "constants.hpp"
class Point
{
private:
    unsigned int id, x, y;
    Player owner;
    Constants::type classification;
    std::vector<Point> neighbors;
    
public:
    Point(unsigned int id, unsigned int x, unsigned int y, Constants::type classification);
    Point(unsigned int x, unsigned int y);
    ~Point();

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getId() const;
    Player getOwner() const; 
    std::vector<Point> getNeighbors() const;
    Constants::type getClassification() const;

    void addNeighbor(Point newNeighbor);
    void upgrade();
};
