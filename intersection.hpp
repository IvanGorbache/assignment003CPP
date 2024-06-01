#include "point.hpp"
#include <vector>

class Intersection: public Point
{
private:
   int status;
   Player owner;
   std::vector<Intersection> neighbors;
public:
    Intersection(/* args */);
    ~Intersection();

    int getStatus();
    Player getOwner();
    std::vector<Intersection> geteighbors();
    void addNeighbor(Intersection neighbor);
    bool isNeighbor(Intersection intersection);

};

