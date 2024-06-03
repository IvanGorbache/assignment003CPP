#pragma once
#include <vector>
#include "constants.hpp"
#include "player.hpp"
class Player;
class Point
{
private:
     int id, x, y;
    Player* owner;
    int classification;
    std::vector<Point> neighbors;
    
public:
    Point();
    Point( int id,  int x,  int y, int classification);
    Point( int x,  int y);
    ~Point();

    int getX() const;
    int getY() const;
    int getId() const;
    Player* getOwner() const; 
    std::vector<Point> getNeighbors() const;
    int getClassification() const;

    void setID( int id);
    void setOwner(Player *p);
    void setClassification(int classification);

    void addNeighbor(Point &newNeighbor);
    bool isNeighbor(Point a);
    void upgrade();

    bool operator==(const Point& other) const;
};
