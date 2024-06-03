#include "point.hpp"
#include "player.hpp"

Point::Point()
{

}
Point::Point(unsigned int id, unsigned int x, unsigned int y, int classification)
{

}
Point::Point(unsigned int x, unsigned int y)
{

}
Point::~Point()
{

}

unsigned int Point::getX() const
{
    
}
unsigned int Point::getY() const
{

}
unsigned int Point::getId() const
{

}
Player* Point::getOwner() const
{

}
std::vector<Point> Point::getNeighbors() const
{

}
int Point::getClassification() const
{

}

void Point::setID(unsigned int id)
{

}
void Point::setOwner(Player *p)
{

}

void Point::addNeighbor(Point &newNeighbor)
{

}
bool Point::isNeighbor(Point a)
{

}
void Point::upgrade()
{

}