#include "point.hpp"

Point::Point()
{
    this->id = 0;
    this->x = 0;
    this->y = 0;
    this->classification = Constants::empty;
    this->owner = NULL;
}
Point::Point( int id,  int x,  int y, int classification)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->classification = classification;
    this->owner = NULL;
}
Point::Point( int x,  int y)
{
    this->x = x;
    this->y = y;
}
Point::~Point()
{

}

 int Point::getX() const
{
    return this->x;
}
 int Point::getY() const
{
    return this->y;
}
 int Point::getId() const
{
    return this->id;
}
Player* Point::getOwner() const
{
    return this->owner;
}
std::vector<Point> Point::getNeighbors() const
{
    return this->neighbors;
}
int Point::getClassification() const
{
    return this->classification;
}

void Point::setID( int id)
{
    this->id = id;
}
void Point::setOwner(Player *p)
{
    this->owner = p;
}

void Point::setClassification(int classification)
{
    this->classification = classification;
}

void Point::addNeighbor(Point &newNeighbor)
{
    this->neighbors.push_back(newNeighbor);
}
bool Point::isNeighbor(Point a)
{
    return std::find(this->neighbors.begin(), this->neighbors.end(), a) != this->neighbors.end();
}
void Point::upgrade()
{
    if(this->classification==Constants::empty)
    {
        this->classification = Constants::settlement;
    }
    else if (this->classification==Constants::settlement)
    {
        this->classification = Constants::city;
    }
    
}

bool Point::operator==(const Point& other) const {
    return (this->x == other.x && this->y == other.y && this->id == other.id); 
}