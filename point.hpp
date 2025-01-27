#pragma once
#include <vector>
#include "constants.hpp"
#include "player.hpp"
#include "road.hpp"
class Player;
class Road;
class Point
{
private:
     int id, x, y;
    Player* owner;
    int classification;
    std::vector<Point> neighbors;
    std::vector<Road> roads;
    
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

    void addRoad(Road road);
    std::vector<Road> getRoads() const;
    bool hasRoad(Point b);
};
