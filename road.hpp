#pragma once

#include "player.hpp"
#include "point.hpp"
class Player;
class Point;
class Road
{
private:
    Player* owner;
    Point* start, *end;

public:
    Road(Player *owner, Point *start, Point *end);
    ~Road();

    Player* getOwner() const;
    void setOwner(Player *p);

    Point* getStart() const;
    Point* getEnd() const; 
    std::string toString() const; // Declaration of toString() method
};

