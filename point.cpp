#include "point.hpp"

Point::Point()
{

}
Point::Point(unsigned int id, unsigned int x, unsigned int y, int classification, char symbol)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->classification = classification;
    this->symbol = symbol;
}
Point::Point(unsigned int x, unsigned int y)
{
    this->x = x;
    this->y = y;
}


unsigned int Point::getX() const
{
    return this->x;
}
unsigned int Point::getY() const
{
    return this->y;
}
unsigned int Point::getId() const
{
    return this->id;
}
Player Point::getOwner() const
{
    return this->owner;
}
std::vector<Point> Point::getNeighbors() const
{
    this->neighbors;
}
int Point::getClassification() const
{
    return this->classification;
}
char Point::getSymbol() const
{
    return this->symbol;
}

void Point::setID(unsigned int id)
{
    this->id = id;
}
void Point::setOwner(Player p)
{
    this->owner = p;
}

void Point::addNeighbor(Point newNeighbor)
{
    this->neighbors.push_back(newNeighbor)
}
bool Point::isNeighbor(Point a)
{
    return std::find(this->neighbors.begin(), this->neighbors.end(), a) != this->neighbors.end()) 
}
void Point::upgrade()
{
    if(this->classification == Constants::empty)
    {
        this->classification = Constants::settlement;
    }
    else if(this->classification == Constants::settlement)
    {
        this->classification = Constants::city;
    }
}