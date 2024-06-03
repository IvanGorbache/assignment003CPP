#include <vector>
#include "constants.hpp"
#include "player.hpp"

class Point
{
private:
    unsigned int id, x, y;
    Player owner;
    int classification;
    std::vector<Point> neighbors;
    char symbol;
    
public:
    Point();
    Point(unsigned int id, unsigned int x, unsigned int y, int classification, char Symbol);
    Point(unsigned int x, unsigned int y);

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getId() const;
    Player getOwner() const; 
    std::vector<Point> getNeighbors() const;
    int getClassification() const;
    char getSymbol() const;

    void setID(unsigned int id);
    void setOwner(Player p);

    void addNeighbor(Point newNeighbor);
    bool isNeighbor(Point a);
    void upgrade();
};
