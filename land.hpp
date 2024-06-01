#include "constants.hpp"
#include "point.hpp"
class Land: public Point
{
private:
    Constants::resource resource;
    unsigned int id;
public:
    Land(/* args */);
    ~Land();
    Constants::resource getResource();
    unsigned int getId();
};