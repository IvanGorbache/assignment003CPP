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

std::string Road::toString() const
{
    std::string ownerName = (owner != nullptr) ? owner->getName() : "None"; // Assuming Player has a getName() method

    std::string startStr = "(" + std::to_string(start->getX()) + "," + std::to_string(start->getY()) + ")";
    std::string endStr = "(" + std::to_string(end->getX()) + "," + std::to_string(end->getY()) + ")";

    return "Road owned by: " + ownerName + ", from " + startStr + " to " + endStr;
}