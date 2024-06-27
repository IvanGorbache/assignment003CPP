#include "road.hpp"

Road::Road(Player *owner, Point *start, Point *end)
{
    this->owner = owner;
    this->start = start;
    this->end = end;
}

Road::~Road()
{
}

Player* Road::getOwner() const
{
    return this->owner;
}

void Road::setOwner(Player *p)
{
    this->owner = p;
}

Point* Road::getStart() const 
{
    return this->start;
}

Point* Road::getEnd() const
{
    return this->end;
}